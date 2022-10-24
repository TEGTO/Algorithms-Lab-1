#include <iostream>
#include"algorithms.h"
#include <iomanip>
#include <ctime>
using namespace std;


// write your solutions of tasks here 
namespace LU
{
	//сума 
	double sum(int i , int j, double ** L, double** U, int type)
	{
		double sum = 0;
		switch (type)
		{
		case 1:
			if (i>0)
			{
				for (int k = 0; k <= i - 1; k++)
				{
					sum += L[i][k] * U[k][j];
				}
			}
			break;
		case 2:	
			for (int k = 0; k <= j - 1; k++)
			{
				sum += L[i][k] * U[k][j];
			}
			break;

		default:
			break;
		}
		return sum;
	}
	//виводить L та U матриці
	void LUmatrixPrint(double** L, double** U,int size)
	{
		cout <<std::setprecision(4);
		cout << "L: \n";
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << L[i][j]<<" ";
			}
			cout << "\n";
		}
		cout << "\n\nU: \n";
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << U[i][j] << " ";
			}
			cout << "\n";
		}
	}
	//виводить матрицю
	void matrixPrint(double** X,int size)
	{
		cout << std::setprecision(5);
		cout << "\nX: \n";
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << X[i][j] << " ";
			}
			cout << "\n";
		}

	}
	//находить суму матриць та віднімає одиничну матрицю
	void matrixSum(double** L, double** U, double** C, int size)
	{

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				
				C[i][j] =L[i][j] + U[i][j];
				if (i == j) 
					C[i][j]--;
		

			}
		}
	}
 template <typename T>
 void LU(T** A, int size)
 {
	 double** L = new double*[size];
	 double** U = new double*[size];
	 double** C = new double*[size];
	 double** X= new double*[size];
	 for (int i = 0; i < size; i++)
	 {
		 L[i] = new double[size];
		 U[i] = new double[size];
		 C[i] = new double[size];
		 X[i] = new double[size];
	 }
	 for (int i = 0; i < size; i++)
	 {
		 for (int j = 0; j < size; j++)
		 {
			 L[i][j] = 0;
			 U[i][j] = 0;
			 C[i][j] = 0;
			 X[i][j] = 0;
			 
		 }
	 }
	 for (int i = 0; i < size; i++)
	 {
		 for (int j = 0; j < size; j++)
		 {
			 if (i<=j)
				 U[i][j] = (double)(A[i][j] - sum(i, j, L, U, 1));
			 if (i>=j)
			 L[i][j] = ((double)(A[i][j] - sum(i, j, L, U, 2)) / (double)U[j][j]);
		 }
	 }
	 LUmatrixPrint(L, U, size);
	 matrixSum(L, U, C, size);

	 for (int k = size - 1; k >= 0; k--) {
		 X[k][k] = 1;
		 for (int j = size - 1; j > k; j--) X[k][k] -= C[k][j] * X[j][k];
		 X[k][k] /= C[k][k];
		 for (int i = k - 1; i >= 0; i--) {
			 for (int j = size - 1; j > i; j--) {
				 X[i][k] -= C[i][j] * X[j][k];
				 X[k][i] -= C[j][i] * X[k][j];
			 }
			 X[i][k] /= C[i][i];
		 }
	 }
	 matrixPrint(X, size);
 }



 template <typename D>
void myMain(D** A, int size)
 {
	unsigned int start_time = clock();
	
	 LU(A, size);
	 unsigned int end_time = clock();
	 cout << "\nЧас виконання алгоритму LU : " << end_time << " мс" << endl;
 }
template void myMain<double>(double** A, int size);
}