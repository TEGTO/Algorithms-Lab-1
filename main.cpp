#include <iostream>
#include"algorithms.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");
	int size = 4;
	double** A = new double* [size];
	for (int i = 0; i < size; i++)
		A[i] = new double[size];
	A[0][0] = 6.0;
	A[0][1] = 3.0;
	A[0][2] = 8.0;
	A[0][3] = 1.0;
	A[1][0] = 4.0;
	A[1][1] = 7.0;
	A[1][2] = 6.0;
	A[1][3] = 5.0;
	A[2][0] = 9.0;
	A[2][1] = 1.0;
	A[2][2] = 7.0;
	A[2][3] = 6.0;
	A[3][0] = 8.0;
	A[3][1] = 2.0;
	A[3][2] = 3.0;
	A[3][3] = 1.0;
	Gauss_Zhordan::Zhevahin_Main(A, size, size);


	return 0;
}