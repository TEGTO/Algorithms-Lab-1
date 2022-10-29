#include <iostream>
#include"algorithms.h"
#include <iomanip>
#include <ctime>
using namespace std;


//обернена матриця за допомогою LU розклада
namespace LU
{
	//сума для знаходження матриці L та U
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
	//виводить L та U матриці в консоль
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
	//виводить обернену матрица Х
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
	//Прибирає непотрібну пам'ять 
	void matrixMemoryClear(T** arr, int size)
	{
		for (int i = 0; i < size; i++)
			delete[] arr[i];
		delete[] arr;
	}

	template <typename T>
	 //основний метод (обчислення оберненої матриці LU алгоритмом) 
	 void LU(T** A, int size)
 { //Створення всіх матриць, які потрібні 
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
	 //Запомвнюємо всі матриці нулями
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
	 { //Алгоритм який находить L та U матриці
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
	 //Алгоритм який находить обернену матрицю
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
	 //Виводимо обернену матрицю
	 matrixPrint(X, size);
	 //Видаляємо вже непотрібні матрици 
	 matrixMemoryClear(L, size);
	 matrixMemoryClear(U, size);
	 matrixMemoryClear(C, size);
	 matrixMemoryClear(X, size);
 }
 


	 template <typename D>
	void PshonovskiyMain(D** A, int size)
	 {
		unsigned int startTime = clock();
		 LU(A, size);
		 unsigned int endTime = clock();
		 unsigned int searchTime = endTime - startTime;
		 cout << "\nЧас виконання алгоритму LU : " << searchTime << " мс" << endl;
	 }
	template void PshonovskiyMain<double>(double** A, int size);
	template void PshonovskiyMain<int>(int** A, int size);
	template void PshonovskiyMain<float>(float** A, int size);
}