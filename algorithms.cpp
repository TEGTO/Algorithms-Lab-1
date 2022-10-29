﻿#include <iostream>
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
	 {//Алгоритм який находить L та U матриці
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

namespace Newtons_method {
    //очистить виділену пам'ять
    void clear(double** arr, int n)
    {
        for (int i = 0; i < n; i++)
            delete[] arr[i];
        delete[] arr;
    }
    //створити копію масива
    double** clone(double** arr, int n)
    {
        double** newArr = new double* [n];
        for (int row = 0; row < n; row++)
        {
            newArr[row] = new double[n];
            for (int col = 0; col < n; col++)
                newArr[row][col] = arr[row][col];
        }
        return newArr;
    }
    //print the matrix
    void show(double** matrix, int n)
    {
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++)
                printf("%lf\t", matrix[row][col]);
            printf("\n");
        }
        printf("\n");
    }
    //матричне множення матриць
    double** matrix_multi(double** A, double** B, int n)
    {
        double** result = new double* [n];
        //заповнення нулями
        for (int row = 0; row < n; row++) {
            result[row] = new double[n];
            for (int col = 0; col < n; col++) {
                result[row][col] = 0;
            }
        }

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                for (int j = 0; j < n; j++) {
                    result[row][col] += A[row][j] * B[j][col];
                }
            }
        }
        return result;
    }
    //множення матриці на число
    void scalar_multi(double** m, int n, double a) {
        for (int row = 0; row < n; row++)
            for (int col = 0; col < n; col++) {
                m[row][col] *= a;
            }
    }
    //обчислення суми двох квадратних матриць
    void sum(double** A, double** B, int n)
    {
        for (int row = 0; row < n; row++)
            for (int col = 0; col < n; col++)
                A[row][col] += B[row][col];
    }

    //обчислення визначника
    double det(double** matrix, int n) //квадратна матриця розміру n*n
    {
        double** B = clone(matrix, n);
        //зведення матриці до верхньотрикутного вигляду
        for (int step = 0; step < n - 1; step++)
            for (int row = step + 1; row < n; row++)
            {
                double coeff = -B[row][step] / B[step][step]; //метод Гауса
                for (int col = step; col < n; col++)
                    B[row][col] += B[step][col] * coeff;
            }
        //Обчислення визначника як добутку елементів головної діагоналі
        double Det = 1;
        for (int i = 0; i < n; i++)
            Det *= B[i][i];
        //Очистити пам'ять
        clear(B, n);
        return Det;
    }
    void Newt_method(double** A, int n) {      

        /* Чисельне обчислення оберненої матриці  методом Ньютона-Шульца
            1. Записати початкове наближення:
                1) Транспонувати дану матрицю
                2) Нормувати по стовпчикам і рядкам
            2.Повторювати процес поки не буде досягнута задана точність.
        */

        double N1 = 0, Ninf = 0; //норма матриці по стовпчикам і по рядочкам
        double** A0 = clone(A, n);       //ініціалізація початковго наближення
        for (size_t row = 0; row < n; row++) {
            double colsum = 0, rowsum = 0;
            for (size_t col = 0; col < n; col++) {
                rowsum += fabs(A0[row][col]);
                colsum += fabs(A0[col][row]);
            }
            N1 = std::max(colsum, N1);
            Ninf = std::max(rowsum, Ninf);
        }
        //транспонування
        for (size_t row = 0; row < n - 1; row++) {
            for (size_t col = row + 1; col < n; col++)
                std::swap(A0[col][row], A0[row][col]);
        }
        scalar_multi(A0, n, (1 / (N1 * Ninf))); //нормування матриці
        //ініціалізація подвоєнної одиничної матриці потрібного розміру
        double** E2 = new double* [n];
        for (int row = 0; row < n; row++)
        {
            E2[row] = new double[n];
            for (int col = 0; col < n; col++) {
                if (row == col)
                    E2[row][col] = 2;
                else
                    E2[row][col] = 0;
            }
        }
        double** inv = clone(A0, n); //A_{0}
        double EPS = 0.001;   //похибка
        if (det(A, n) != 0) { //якщо матриця не вироджена
            while (fabs(det(matrix_multi(A, inv, n), n) - 1) >= EPS) //пока |det(A * A[k](^-1)) - 1| >= EPS
            {
                double** prev = clone(inv, n); //A[k-1]
                inv = matrix_multi(A, prev, n);   //A.(A[k-1]^(-1))
                scalar_multi(inv, n, -1);         //-A.(A[k-1]^(-1))
                sum(inv, E2, n);                   //2E - A.(A[k-1]^(-1))
                inv = matrix_multi(prev, inv, n); //(A[k-1]^(-1)).(2E - A.(A[k-1]^(-1)))
                clear(prev, n);
            }
            //друк матриці на екран
            show(inv, n);
        }
        else
            printf("Impossible\n");
        clear(A, n);
        clear(E2, n);
       
    }
    void VolkovMain(double** A, int n) {
        unsigned int startTime = clock();
        Newt_method(A, n);
        unsigned int endTime = clock();
        unsigned int searchTime = endTime - startTime;
        cout << "\nthe time of Newton's method is : " << searchTime  << endl;
    }
}

