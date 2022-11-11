#include <iostream>
#include"algorithms.h"
using namespace std;

template<typename T>
void show_matrix(T** matrix, int size) 
{
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++) 
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
typedef void (*algorithm)(double** A, int d);
void UnitTest(algorithm foo)
{
	srand(time(NULL));
	size_t max_size = 6;
	size_t size = 6;
	double** A = new double* [max_size];
	for (int i = 0; i < max_size; i++)
		A[i] = new double[max_size];
	for (size_t i = 0; i < 20; i++)
	{
		size = rand()%(max_size+1);
		for (size_t j = 0; j < size; j++)
		{
			for (size_t k = 0; k < size; k++)
			{
				A[j][k] = rand() % 300;
			}
		}
		cout << "==================" << endl;
		cout << "\n\nInitial matrix:" << endl;//��������� ���������� �������
		show_matrix(A, size);
		cout << endl<<endl;
		foo(A, size);
		cout << "==================" << endl;
	}
}






int main()
{
	setlocale(LC_ALL, "Rus");
	size_t size = 4;
	
	double** A = new double* [size];
	for (int i = 0; i < size; i++)
		A[i] = new double[size];
	//������� ��� ��������
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
	//��������� ���������� �������� ������� 
	int type;
	
		cout << "\n���������: " << endl;
		cout << "1.�������� ��������� ��� �������� �������" << endl;
		cout << "2.�������� �������� ������i ������� �����-�������" << endl;
		cout << "3.�������� �������� ������i ������� LU" << endl;
		cout << "4.�������� �������� ������i ������� �������" << endl;
		cout << "0.���i�" << endl;
		cout << "\n�����i�� �������� ��� ����������: " << endl;
		cin >> type;
		cout << endl;
		switch (type)
		{
		case 1:
			Strassen_algo::KovalovMain(); //������ �1 �������� ��������� ��� �������� �������
			break;
		case 2:
			//Gauss_Zhordan::Zhevahin_Main(A, size, size); //������ �2 �������� �������� ������� ������� �����-�������
			UnitTest(&Gauss_Zhordan::Zhevahin_Main);
			break;
		case 3:
			//LU::PshonovskiyMain(A, size); //������ �3 �������� �������� ������� ������� LU
			 
			UnitTest(&LU::PshonovskiyMain);
			break;
		case 4:
			//Newtons_method::VolkovMain(A, size); //������ �4 �������� �������� ������� ������� �������
			
			UnitTest(&Newtons_method::VolkovMain);
			break;
		default:		
			break;
		}
	
	cout <<  endl;
	system("pause");


	return 0;
}