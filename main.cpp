#include <iostream>
#include"algorithms.h"
using namespace std;


typedef void (*algorithm)(double** A, int d);
void UnitTest(algorithm foo)
{
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
	foo(A, size);
	double** B = new double* [size];
	for (int i = 0; i < size; i++)
		B[i] = new double[size];
	//������� ��� ��������
	B[0][0] = 436.0;
	B[0][1] = 43.0;
	B[0][2] = 3438.0;
	B[0][3] = 333.0;
	B[1][0] = 34.0;
	B[1][1] = 41.0;
	B[1][2] = 41.0;
	B[1][3] = 15.0;
	B[2][0] = 93.0;
	B[2][1] = 143.0;
	B[2][2] = 437.0;
	B[2][3] = 46.0;
	B[3][0] = 854.0;
	B[3][1] = 4542.0;
	B[3][2] = 13.0;
	B[3][3] = 111.0;
	foo(B, size);

	double** C = new double* [size-1];
	for (int i = 0; i < size-1; i++)
		C[i] = new double[size-1];
	//������� ��� ��������
	C[0][0] = 2.0;
	C[0][1] = 13.0;
	C[0][2] = 31.0;

	C[1][0] = 31.0;
	C[1][1] = 35.0;
	C[1][2] = 54.0;

	C[2][0] = 311.0;
	C[2][1] = 43.0;
	C[2][2] = 343.0;


	foo(C, size - 1);
	double** D = new double* [size-1];
	for (int i = 0; i < size-1; i++)
		D[i] = new double[size-1];
	//������� ��� ��������
	D[0][0] = 23232;
	D[0][1] = 333;
	D[0][2] = 43;

	D[1][0] = 41;
	D[1][1] = 4141;
	D[1][2] = 343;

	D[2][0] = 4343;
	D[2][1] = 41313.0;
	D[2][2] = 233;


	foo(D, size - 1);

	double** E = new double* [size+1];
	for (int i = 0; i < size+1; i++)
		E[i] = new double[size+1];
	//������� ��� ��������
	E[0][0] = 33;
	E[0][1] = 33;
	E[0][2] = 131;
	E[0][3] = 2;
	E[0][4] = 13;
	E[1][0] = 232;
	E[1][1] = 22;
	E[1][2] = 323;
	E[1][3] = 355;
	E[1][4] = 34;
	E[2][0] = 434;
	E[2][1] = 22;
	E[2][2] = 343;
	E[2][3] = 131;
	E[2][4] = 3443;
	E[3][0] = 54;
	E[3][1] = 232;
	E[3][2] = 32;
	E[4][0] = 11;
	E[4][1] = 232;
	E[4][2] = 433;
	E[4][3] = 2424;
	E[4][4] = 141;
	foo(E, size+1);
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