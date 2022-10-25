#include <iostream>
#include"algorithms.h"
using namespace std;


namespace Newtons_method {
    //очистить выделенную память
    void clear(double** arr, int n)
    {
        for (int i = 0; i < n; i++)
            delete[] arr[i];
        delete[] arr;
    }
    //создать копию массива
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
    //матричное умножение матриц
    double** matrix_multi(double** A, double** B, int n)
    {
        double** result = new double* [n];
        //заполнение нулями
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
    //умножение матрицы на число
    void scalar_multi(double** m, int n, double a) {
        for (int row = 0; row < n; row++)
            for (int col = 0; col < n; col++) {
                m[row][col] *= a;
            }
    }
    //вычисление суммы двух квадратных матриц
    void sum(double** A, double** B, int n)
    {
        for (int row = 0; row < n; row++)
            for (int col = 0; col < n; col++)
                A[row][col] += B[row][col];
    }

    //вычисление определителя
    double det(double** matrix, int n) //квадратная матрица размера n*n
    {
        double** B = clone(matrix, n);
        //приведение матрицы к верхнетреугольному виду
        for (int step = 0; step < n - 1; step++)
            for (int row = step + 1; row < n; row++)
            {
                double coeff = -B[row][step] / B[step][step]; //метод Гаусса
                for (int col = step; col < n; col++)
                    B[row][col] += B[step][col] * coeff;
            }
        //Рассчитать определитель как произведение элементов главной диагонали
        double Det = 1;
        for (int i = 0; i < n; i++)
            Det *= B[i][i];
        //Очистить память
        clear(B, n);
        return Det;
    }
    void Newt_method(double** A, int n) {      

        /* Численное вычисление обратной матрицы по методу Ньютона-Шульца
            1. Записать начальное приближение [Pan, Schreiber]:
                1) Транспонировать данную матрицу
                2) Нормировать по столбцам и строкам
            2. Повторять процесс до достижения заданной точности.
        */

        double N1 = 0, Ninf = 0; //норма матрицы по столбцам и по строкам
        double** A0 = clone(A, n);       //инициализация начального приближения
        for (size_t row = 0; row < n; row++) {
            double colsum = 0, rowsum = 0;
            for (size_t col = 0; col < n; col++) {
                rowsum += fabs(A0[row][col]);
                colsum += fabs(A0[col][row]);
            }
            N1 = std::max(colsum, N1);
            Ninf = std::max(rowsum, Ninf);
        }
        //транспонирование
        for (size_t row = 0; row < n - 1; row++) {
            for (size_t col = row + 1; col < n; col++)
                std::swap(A0[col][row], A0[row][col]);
        }
        scalar_multi(A0, n, (1 / (N1 * Ninf))); //нормирование матрицы
        //инициализация удвоенной единичной матрицы нужного размера
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
        double EPS = 0.001;   //погрешность
        if (det(A, n) != 0) { //если матрица не вырождена
            while (fabs(det(matrix_multi(A, inv, n), n) - 1) >= EPS) //пока |det(A * A[k](^-1)) - 1| >= EPS
            {
                double** prev = clone(inv, n); //A[k-1]
                inv = matrix_multi(A, prev, n);   //A.(A[k-1]^(-1))
                scalar_multi(inv, n, -1);         //-A.(A[k-1]^(-1))
                sum(inv, E2, n);                   //2E - A.(A[k-1]^(-1))
                inv = matrix_multi(prev, inv, n); //(A[k-1]^(-1)).(2E - A.(A[k-1]^(-1)))
                clear(prev, n);
            }
            //вывод матрицы на экран
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

