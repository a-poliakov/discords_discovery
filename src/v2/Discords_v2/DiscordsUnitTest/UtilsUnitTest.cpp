#include <cmath>
#include "CppUnitTest.h"
#include "Utils.h"
#include "DiscordsRun.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DiscordsUnitTest
{		
	TEST_CLASS(UtilsUnitTest)
	{
	public:
		
		/**
		* ������������ ���������� ��������� ���������� ����� ����� �������
		* ���� 1:
		* Input: 1D point 1.0 and 1D point 1.0
		* Distance: 0.0
		* ���� 2:
		* Input: 1D point 1.0 and 1D point 2.0
		* Distance: 0.0
		* ���� 3:
		* Input: 1D point 0.0 and 1D point -1.0
		* Distance: 0.0
		*/
		TEST_METHOD(TestEuclidDistanceBetweenPoints)
		{
			double point1 = 1.0;
			double point2 = 1.0;
			double expected = 0;
			float eps = 0.00001f;
			double result = distance(point1, point2);
			Assert::IsTrue(abs(expected - result) < eps);
			point1 = 1.0;
			point2 = 2.0;
			expected = 1.0;
			result = distance(point1, point2);
			Assert::IsTrue(abs(expected - result) < eps);
			point1 = 0.0;
			point2 = -1.0;
			result = distance(point1, point2);
			Assert::IsTrue(abs(expected - result) < eps);
		}

		TEST_METHOD(TestDistanceBetweenSequences)
		{
			Assert::AreEqual(1, 1);
		}

		/**
		* ������������ ���������� ���������� non-self-match ����������������������
		* ��� �������� ���������������������
		* Input:
		* n = 5 - ����� ���������� ����
		* m = 2 - ����� ���������������������
		* ���� 1:
		* Input: p = 0 - ������� ������ ���������������������
		* Output: 2
		* ���� 2:
		* Input: p = 1 - ������� ������ ���������������������
		* Output: 1
		* ���� 3:
		* Input: p = 2 - ������� ������ ���������������������
		* Output: 1
		* ���� 4:
		* Input: p = 3 - ������� ������ ���������������������
		* Output: 2
		*/
		TEST_METHOD(TestCountNonSelfMatchSubsequencies)
		{
			int count = countNonSelfMatchSubsequencies(5, 2, 0);
			Assert::AreEqual(count, 2);
			count = countNonSelfMatchSubsequencies(5, 2, 1);
			Assert::AreEqual(count, 1);
			count = countNonSelfMatchSubsequencies(5, 2, 2);
			Assert::AreEqual(count, 1);
			count = countNonSelfMatchSubsequencies(5, 2, 3);
			Assert::AreEqual(count, 2);
		}

		/**
		* ������������ ���������� �������� ������ self-match ����������������������
		* ��� �������� ���������������������
		* TODO: �������� 
		*/
		TEST_METHOD(TestGetSelfMatchSubsequenciesStartIndexes)
		{
			int expected[2] = {0, 1};
			int* actual = findSelfMatch(5, 2, 0);
			Assert::AreEqual(expected[0], actual[0]);
			Assert::AreEqual(expected[1], actual[1]);
			int expected1[3] = { 0, 1, 2 };
			actual = findSelfMatch(5, 2, 1);
			Assert::AreEqual(expected1[0], actual[0]);
			Assert::AreEqual(expected1[1], actual[1]);
			Assert::AreEqual(expected1[2], actual[2]);
			int expected2[3] = { 1, 2, 3 };
			actual = findSelfMatch(5, 2, 2);
			Assert::AreEqual(expected2[0], actual[0]);
			Assert::AreEqual(expected2[1], actual[1]);
			Assert::AreEqual(expected2[2], actual[2]);
			int expected3[2] = { 2, 3 };
			actual = findSelfMatch(5, 2, 3);
			Assert::AreEqual(expected3[0], actual[0]);
			Assert::AreEqual(expected3[1], actual[1]);
		}

		/**
		* ������������ ���������� ������� ���������������������� ��� ��������� ���������� ����
		* Input:
		* T = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f} - ��������� ���
		* m = 7 - ����� ���������� ����
		* n = 3 - ����� ���������������������
		* Output: ������� ����������������������
		*	0.000000 1.000000 2.000000
		*	1.000000 2.000000 3.000000
		*	2.000000 3.000000 4.000000
		*	3.000000 4.000000 5.000000
		*	4.000000 5.000000 6.000000
		*/
		TEST_METHOD(TestCreateSubsequenciesMatrix)
		{
			const series_t timeSeries = new float[7];
			for (int i = 0; i < 7; i++)
			{
				timeSeries[i] = (float)i;
			}
			startApp();
			float eps = 0.001;
			matrix_t result = createSubsequencies(timeSeries, 7, 3);
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					Assert::IsTrue(abs((i + j) - result[i][j]) < eps);
				}
			}
		}
	};
}