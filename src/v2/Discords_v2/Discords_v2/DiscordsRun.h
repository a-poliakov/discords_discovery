/**
* A module containing discords search logic
*/

#ifndef DISCORDSRUN_H
#define DISCORDSRUN_H

#include "Config.h"

extern int bsfPos;
extern float bsfDist;
extern series_t timeSeries;

// length of full time series
extern int _m;
// length of one subsequence
extern int _n;

void startApp();

void prepareConfig();

/**
* Нахождение диссонанса заданной длины в данном временном ряде
* для заданной подпоследовательности
* @param T - временной ряд
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @param bsf_dist - расстояние до ближайшего соседа
* @return индекс начала диссонанса
*/
int findDiscord(const series_t T, const int m, const int n, float* bsf_dist);

/**
* Создание матрицы подпоследовательностей
* для заданной подпоследовательности
* @param T - временной ряд
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @return матрица подпоследовательностей
*/
matrix_t createSubsequencies(const series_t T, const int m, const int n);

/**
* Нахождения количества non-self-match подпоследовательностей
* для заданной подпоследовательности
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @param p - индекс начала подпоследовательности
* @return количество non-self-match подпоследовательностей
*/
int* findSelfMatch(int m, int n, long startIndex);

/**
 * Нахождения количества non-self-match подпоследовательностей
 * для заданной подпоследовательности
 * @param m - длина временного ряда
 * @param n - длина подпоследовательности
 * @param p - индекс начала подпоследовательности
 * @return количество non-self-match подпоследовательностей
 */
int countNonSelfMatchSubsequencies(int m, int n, int p);

#endif
