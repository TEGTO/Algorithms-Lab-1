#include<iostream>
#include<ctime>
#include<iomanip>
#include"algorithms.h"
using namespace std;
namespace Gauss_Zhordan {
	template<typename T>//підключення шаблонів для універсальності
	void garbage_cleaning(T** matrix, int size) {//вивільнення пам'яті з об'єкту,що зберігає певну матрицю
		for (size_t i = 0; i < size; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	template<typename T>
	void show_matrix(T** matrix, int size) {//виведення матриці на консоль
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	template<typename T>
	T** add_simple_matrix(T** matrix, int size) {//розширення заданої матриці відповідною елементарною матрицею
		T** new_matrix = new T * [size];
		for (int i = 0; i < size; i++) {
			new_matrix[i] = new T[2 * size];//створення розширенної матриці
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				new_matrix[i][j] = matrix[i][j];//копіювання даних
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = size; j < 2 * size; j++) {
				if (i == j - size) {//заповнення елементарної матриці
					new_matrix[i][j] = 1;
				}
				else new_matrix[i][j] = 0;
			}
		}
		return new_matrix;
	}

	template<typename T>
	void Simplifying_Column(T** matrix, int size, int column) {//алгоритм Гауса-Жордана
		double divider = matrix[column][column];//визначення загального дільника
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < 2 * size; j++) {
				if (j != column && i != column) {//обчислення елементів,що не лежать на розглядаємому рядку(спрощуваному) і стовпчику
					matrix[i][j] -= matrix[i][column] * matrix[column][j] / divider;
				}
			}
		}
		for (int i = 0; i < size; i++) {//окремі дії над розглядаємим стовпчиком та рядком
			for (int j = 0; j < 2 * size; j++) {
				if (j == column && i != column) {
					matrix[i][j] = 0;//якщо розглядається спрощуваний стовпчик,то елементи в ньому замінюють на 0(окрім діагонального)
				}
				else if (j != column and i == column) {
					matrix[i][j] /= divider;//якщо розглядається рядок,то всі його елементи /=дільник
				}
				else if (j == column and i == column) {
					matrix[i][j] = 1;//якщо елемент діагональний-він дорівнює 1
				}
			}
		}
	}

	template<typename T>
	T** get_reversed_matrix(T** exp_matrix, int size) {
		T** reversed_matrix = new T * [size];
		for (int i = 0; i < size; i++) {
			reversed_matrix[i] = new T[size];
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				reversed_matrix[i][j] = exp_matrix[i][size + j];//отримання оберненої матриці з розширеної
			}
		}
		return reversed_matrix;
	}

	template<typename T>
	T** clone(T** arr, int n)//функція для копіювання даних матриці
	{
		T** newArr = new T * [n];
		for (int row = 0; row < n; row++)
		{
			newArr[row] = new T[n];
			for (int col = 0; col < n; col++)
				newArr[row][col] = arr[row][col];
		}
		return newArr;
	}

	template<typename T>
	double det(T** matrix, int n) //функція для знаходження визначника
	{
		T** B = clone(matrix, n);
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
		//Вивільнення пам'яті
		garbage_cleaning(B, n);
		return Det;
	}

	template<typename T>
	void Gauss_Zhordan_Method(T** matrix, int size1, int size2) {
		cout << "Initial matrix:" << endl;//виведення початковоъ матрицы
		show_matrix(matrix, size1);
		if (det(matrix, size1) == 0) { cout << "Determinant=0,so there is no reversed matrix!!"; return; }//умови,при яких оберненої матриці не існує
		if (size1 != size2) { cout << "Matrix is not quadratic,so there is no reversed matrix!!!"; return; }
		T** exp_matrix = add_simple_matrix(matrix, size1);//створення розширенної матриці
		for (int i = 0; i < size1; i++) {
			Simplifying_Column(exp_matrix, size1, i);//спрощення кожного стовпчика в розширенній матриці
		}
		T** reversedmatrix = get_reversed_matrix(exp_matrix, size1);//отримання оберненої матриці
		cout << "Reversed matrix:" << endl;//виведення оберненої матриці
		show_matrix(reversedmatrix, size1);
		garbage_cleaning(matrix, size1);//вивільнення пам'яті
		garbage_cleaning(exp_matrix, size1);
		garbage_cleaning(reversedmatrix, size1);
		return;
	}

	template<typename T>
	void Zhevahin_Main(T** matrix, int size1, int size2) {
		double start = clock();//початок відрахунку
		Gauss_Zhordan_Method(matrix, size1, size2);//виконання методу
		double end = clock();//кінець відрахунку
		cout << "Time of execution is:" << (end - start) / CLOCKS_PER_SEC << " seconds" << endl;//виведення часу виконання програми

	}

	template void Zhevahin_Main<double>(double** A, int size1, int size2);//створення шаблонів для основного методу
	template void Zhevahin_Main<int>(int** A, int size1, int size2);
	template void Zhevahin_Main<float>(float** A, int size1, int size2);

}
