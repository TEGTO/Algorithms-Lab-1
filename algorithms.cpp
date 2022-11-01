#include<iostream>
#include<ctime>
#include<iomanip>
#include"algorithms.h"
using namespace std;



//обернена матриця за допомогою LU розклада
namespace LU
{
	//сума для знаходження матриці L та U
	double sum(int i, int j, double** L, double** U, int type)
	{
		double sum = 0;
		switch (type)
		{
		case 1:
			if (i > 0)
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
	void LUmatrixPrint(double** L, double** U, int size)
	{
		cout << std::setprecision(4);
		cout << "L: \n";
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << L[i][j] << " ";
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
	void matrixPrint(double** X, int size)
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

				C[i][j] = L[i][j] + U[i][j];
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
		double** L = new double* [size];
		double** U = new double* [size];
		double** C = new double* [size];
		double** X = new double* [size];
		for (int i = 0; i < size; i++)
		{
			L[i] = new double[size];
			U[i] = new double[size];
			C[i] = new double[size];
			X[i] = new double[size];
		}
		//Заповнюємо всі матриці нулями
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
				if (i <= j)
					U[i][j] = (double)(A[i][j] - sum(i, j, L, U, 1));
				if (i >= j)
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
		cout << "\nthe time of Newton's method is : " << searchTime << endl;
	}
}

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
namespace Strassen_algo {
    void copy(int *a, int *b, int ib, int jb, int n)
    {
        int i, j, k;
        int imax = ib+n/2;      // до якого індекса рядка копіюємо
        int jmax = jb+n/2;      // аналогічно по стовпцях
    
        for(k=0,i=ib; i<imax; i++)
        {
            for(j=jb; j<jmax; j++)
            {
                a[k++] = b[i*n+j];  //в матриці а елементи йдуть підряд
            }
        }
    }
 
//копіюємо в квадрант матриці а лінійно розміщену матрицю б
//починаємо з елемента a[ia][[ja]
//n - розмірність матриці a
    void copyback(int *a, int ia, int ja, int *b, int n)
    {
        int i, j, k;
        int imax = ia+n/2;
        int jmax = ja+n/2;
    
        for(k=0,i=ia; i<imax; i++)
        {
            for(j=ja; j<jmax; j++)
            {
                a[i*n+j] = b[k++];
            }
        }
    }
 
//додаємо лінійно дозміщені матриці c = a + b
    void add(int *c, int *a, int *b, int n)
    {
        for(int i=0; i<n*n; i++)
            c[i] = a[i] + b[i];
    }
 
//вдінімаємо лінійно розміщені матриці
    void sub(int *c, int *a, int *b, int n)
    {
        for(int i=0; i<n*n; i++)
            c[i] = a[i] - b[i];
    }
 
// звичайне матричне множення c = a * b
    void mul_normal(int *c, int *a, int *b, int n)
    {
        int i, j, k;
        for(i=0; i<n; i++)
            for(j=0; j<n; j++)
            {
                c[i*n+j] = 0;
                for(k=0; k<n; k++)
                    c[i*n+j] += a[i*n+k] * b[k*n+j];
            }
    }
 
//множення алгоритмом Штрассена
//c = a * b
    void mul(int *c, int *a, int *b, int n)
    {
        //при значеннях, менших за деяке, вигідніше використовувати звичайне множення
        if (n <= 2)
            mul_normal(c, a, b, n);         //звичайне множення
        else
        {
            int h = n/2;                    //ділимо розмірність навпіл
            int *M = new int[h*h*29];       //виділяємо пам'ять під 29 допоміжних матриць
    
    //0-3: чверті матриці A
            copy(&M[0], a, 0, 0, n);                    //M[0] = A11
            copy(&M[h*h], a, 0, h, n);                  //M[1] = A12
            copy(&M[2*h*h], a, h, 0, n);                //M[2] = A21
            copy(&M[3*h*h], a, h, h, n);                //M[3] = A22
    
    //4-7: чверті матриці B
            copy(&M[4*h*h], b, 0, 0, n);                //M[4] = B11
            copy(&M[5*h*h], b, 0, h, n);                //M[5] = B12
            copy(&M[6*h*h], b, h, 0, n);                //M[6] = B21
            copy(&M[7*h*h], b, h, h, n);                //M[7] = B22
    
    //8-15: S1 - S8
            add(&M[8*h*h], &M[2*h*h], &M[3*h*h], h);    //M[8] = S1 = A21 + A22
            sub(&M[9*h*h], &M[8*h*h], &M[0], h);        //M[9] = S2 = S1 - A11
            sub(&M[10*h*h], &M[0], &M[2*h*h], h);       //M[10] = S3 = A11 - A21
            sub(&M[11*h*h], &M[h*h], &M[9*h*h], h);     //M[11] = S4 = A12 - S2
            sub(&M[12*h*h], &M[5*h*h], &M[4*h*h], h);   //M[12] = S5 = B12 - B11
            sub(&M[13*h*h], &M[7*h*h], &M[12*h*h], h);  //M[13] = S6 = B22 - S5
            sub(&M[14*h*h], &M[7*h*h], &M[5*h*h], h);   //M[14] = S7 = B22 - B12
            sub(&M[15*h*h], &M[13*h*h], &M[6*h*h], h);  //M[15] = S8 = S6 - B21
    
    //16-22: P1 - P7: рекурсивний виклик самої себе для множення
            mul(&M[16*h*h], &M[9*h*h], &M[13*h*h], h);  //M[16] = P1 = S2 * S6
            mul(&M[17*h*h], &M[0], &M[4*h*h], h);       //M[17] = P2 = A11 * B11
            mul(&M[18*h*h], &M[h*h], &M[6*h*h], h);     //M[18] = P3 = A12 * B21
            mul(&M[19*h*h], &M[10*h*h], &M[14*h*h], h); //M[19] = P4 = S3 * S7
            mul(&M[20*h*h], &M[8*h*h], &M[12*h*h], h);  //M[20] = P5 = S1 * S5
            mul(&M[21*h*h], &M[11*h*h], &M[7*h*h], h);  //M[21] = P6 = S4 * B22
            mul(&M[22*h*h], &M[3*h*h], &M[15*h*h], h);  //M[22] = P7 = A22 * S8
    
    //23-24: T1, T2
            add(&M[23*h*h], &M[16*h*h], &M[17*h*h], h); //M[23] = T1 = P1 + P2
            add(&M[24*h*h], &M[23*h*h], &M[19*h*h], h); //M[24] = T2 = T1 + P4
    
    //25-28: чверті результуючої матриці C
            add(&M[25*h*h], &M[17*h*h], &M[18*h*h], h); //M[25] = C11 = P2 + P3
            add(&M[26*h*h], &M[23*h*h], &M[20*h*h], h); //M[26] = C12 = T1 + P5
            add(&M[26*h*h], &M[26*h*h], &M[21*h*h], h); //M[26] = C12 += P6
            sub(&M[27*h*h], &M[24*h*h], &M[22*h*h], h); //M[27] = C21 = T2 - P7
            add(&M[28*h*h], &M[24*h*h], &M[20*h*h], h); //M[28] = C22 = T2 + P5
    
    //копіюємо результат
            copyback(c, 0, 0, &M[25*h*h], n);           //C11 = M[25]
            copyback(c, 0, h, &M[26*h*h], n);           //C12 = M[26]
            copyback(c, h, 0, &M[27*h*h], n);           //C21 = M[27]
            copyback(c, h, h, &M[28*h*h], n);           //C22 = M[28]
            delete M;
        }
    }

    void Strassen_algo() {      
    int a[8][8] =
    {
        {11,12,13,14,15,16,17,18},
        {21,22,23,24,25,26,27,28},
        {31,32,33,34,35,36,37,38},
        {41,42,43,44,45,46,47,48},
        {11,12,13,14,15,16,17,18},
        {21,22,23,24,25,26,27,28},
        {31,32,33,34,35,36,37,38},
        {41,42,43,44,45,46,47,48}
    };
    int b[8][8] =
    {
        {11,12,13,14,15,16,17,18},
        {21,22,23,24,25,26,27,28},
        {31,32,33,34,35,36,37,38},
        {41,42,43,44,45,46,47,48},
        {11,12,13,14,15,16,17,18},
        {21,22,23,24,25,26,27,28},
        {31,32,33,34,35,36,37,38},
        {41,42,43,44,45,46,47,48}
    };
    int c[8][8];
    int c1[8][8];
 
//множимо методом Штрасена
    mul((int*)c, (int*)a, (int*)b, 8);
//для контролю - звичайним множенням
    mul_normal((int*)c1, (int*)a, (int*)b, 8);
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
       
    }

    void KovalovMain() {
        unsigned int startTime = clock();
        Strassen_algo();
        unsigned int endTime = clock();
        unsigned int searchTime = endTime - startTime;
        cout << "\nthe time of Strassen's method is : " << searchTime  << endl;
    }
}


