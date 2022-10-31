#include <iostream>
#include"algorithms.h"
using namespace std;












int main()
{
	setlocale(LC_ALL, "Rus");
	size_t size = 4;
	double** A = new double* [size];
	for (int i = 0; i < size; i++)
		A[i] = new double[size];
	//матриця для прикладу
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
	//алгоритми обчислення оберненої матриці 
	int type;
	
		cout << "\nАлгоритми: " << endl;
		cout << "2.Методом Гауса-Жордана" << endl;
		cout << "3.LU алгоритм" << endl;
		cout << "4.Метод Ньютона" << endl;
		cout << "0.Вихiд" << endl;
		cout << "\nВиберiть алгоритм для обчислення: " << endl;
		cin >> type;
		cout << endl;
		switch (type)
		{
		case 2:
			Gauss_Zhordan::Zhevahin_Main(A, size, size); //Задача №4 методом Гауса-Жордана
			break;
		case 3:
			LU::PshonovskiyMain(A, size); //Задача №3 методом LU 
			break;
		case 4:
			Newtons_method::VolkovMain(A, size); //Задача №4 методом Ньютона 
			break;
		default:		
			break;
		}
	
	cout <<  endl;
	system("pause");


	return 0;
}