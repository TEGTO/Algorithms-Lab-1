#pragma once

namespace  Strassen_algo
{	
	void KovalovMain();
}
namespace LU
{
	template <typename T>//створення шаблону
	void PshonovskiyMain(T** A, int size);
}
namespace  Newtons_method
{
	void VolkovMain(double** A, int n);
}
namespace Gauss_Zhordan {
	template <typename T>
	void Zhevahin_Main(T** matrix, int size1);

}