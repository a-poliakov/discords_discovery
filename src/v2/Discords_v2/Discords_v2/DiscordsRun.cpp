#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "omp.h"
#include "DiscordsRun.h"

int bsfPos;
float bsfDist;
series_t timeSeries;

/**
* Нахождение диссонанса заданной длины в данном временном ряде
* для заданной подпоследовательности
* @input T - временной ряд
* @input m - длина временного ряда
* @input n - длина подпоследовательности
* @output bsf_dist - расстояние до ближайшего соседа
* @input threadNum - кол-во потоков, на которых запускается алгоритм
* @output time - время затраченное на выполнение алгоритма
* @return индекс начала диссонанса
* @return индекс начала диссонанса
*/
int findDiscord(const series_t T, const int m, const int n, float* bsf_dist, int threadNum, double* time)
{
	// create matrix of subsequencies
	matrix_t timeSeriesSubsequences = createSubsequencies(T, m, n);
	// calc distance matrix
	matrix_t distancies = createDistanceMatrix(m, n, timeSeriesSubsequences, threadNum, time);
	item_t* mins = (item_t*)__align_malloc((m - n + 1) * sizeof(item_t));
	omp_set_nested(true);
	double start = omp_get_wtime();
	int countOfSubseq = m - n + 1;
	// for each row in distance matrix find min element
	#pragma omp parallel for num_threads(threadNum) shared(mins, distancies)
    for (int i = 0; i < countOfSubseq; i++)
    {
        assert(n != 0);
        mins[i] = POS_INF;
        for (long i = 0; i < countOfSubseq; i++)
        {
            if (distanceMatrix[rowIndex][i] < minValue)
            {
                mins[i] = distanceMatrix[rowIndex][i];
            }
        }
    }
	bsfDist = max(mins, countOfSubseq, &bsfPos);
	double end = omp_get_wtime();
	*time += (end - start);
	*bsf_dist = bsfDist;
	return bsfPos;
}

/**
* Создание матрицы подпоследовательностей
* для заданной подпоследовательности
* @param T - временной ряд
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @return матрица подпоследовательностей
*/
matrix_t createSubsequencies(const series_t T, const int m, const int n)
{
	matrix_t result = (matrix_t)__align_malloc((m - n + 1) * sizeof(series_t));
	assert(result != NULL);
	for (int i = 0; i < m - n + 1; i++)
	{
		result[i] = (series_t)__align_malloc(n * sizeof(item_t));
		assert(result[i] != NULL);
	}
	for (int i = 0; i < m - n + 1; i++)
	{
		memcpy(result[i], &T[i], n*sizeof(item_t));
	}
	return result;
}

matrix_t createDistanceMatrix(const long m, const long n, matrix_t timeSeriesSubsequences, int threadNum, double* time)
{
    matrix_t distancies = (matrix_t)__align_malloc((m - n + 1) * sizeof(series_t));
    assert(distancies != NULL);
    int subseqCount = m - n + 1;
    for (int i = 0; i < subseqCount; i++)
    {
        distancies[i] = (series_t)__align_malloc((subseqCount) * sizeof(item_t));
        assert(distancies[i] != NULL);
    }
    double start = omp_get_wtime();
    #pragma omp parallel for num_threads(threadNum)
    for (int i = 0; i < subseqCount; i++)
    {
        for (int j = 0; j < subseqCount; j++)
        {
            if (j <= i - n || j >= i + n)
            {
                distancies[i][j] = distance2(timeSeriesSubsequences[i], timeSeriesSubsequences[j], n);
            }
            else
            {
                distancies[i][j] = POS_INF;
            }
        }
    }
    double end = omp_get_wtime();
    *time += (end - start);
    return distancies;
}

/**
* Calculates the square of the Euclidean distance between two single-dimensional timeseries represented
* by the rational vectors.
* @param point1 The first timeseries.
* @param point2 The second timeseries.
* @param length The length of series.
* @return The Euclidean distance.
*/
item_t distance2(const series_t series1, const series_t series2, const long length)
{
    assert(length > 0);
    assert(series1 != NULL);
    assert(series2 != NULL);
    float sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += (series1[i] - series2[i]) * (series1[i] - series2[i]);
    }
    return sum;
}

item_t min(const series_t series, const int length, int* position)
{
    item_t result = series[0];
    for (long i = 0; i < length; i++)
    {
        if (series[i] < result)
        {
            result = series[i];
            *position = i;
        }
    }
    return result;
}

item_t max(const series_t series, const int length, int* position)
{
    item_t result = series[0];

    for (long i = 0; i < length; i++)
    {
        if (series[i] > result)
        {
            result = series[i];
            *position = i;
        }
    }
    return result;
}