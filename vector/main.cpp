#include"Vector.h"
#include"Matrix.h"
#include<iostream>
int main(void)
{

	TMatrix<int> A(3, 3, 2);
	TVector<int> B(3);
	TVector<double>C(2);
	TVector<double>D = C;
	std::cin >> B;
	A* B;
	TVector<double>res;
	res = C + D;
	std::cout << "C+D="<<res;
	B.ReSize(10);
	return 0;


A.~TMatrix();
B.~TVector();
}