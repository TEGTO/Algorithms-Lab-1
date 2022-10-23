#include <iostream>
#include"algorithms.h"
#include <iomanip>
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





 void myMain()
 {
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

	
	 LU(A, size);
	
 }
}