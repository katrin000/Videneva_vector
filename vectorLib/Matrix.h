#pragma once
#include "Vector.h"
#include <iostream>
template <class T>
class TMatrix : public TVector<TVector<T>>
{
protected:

	int width;
public:
	TMatrix();
	~TMatrix();
	TMatrix(int _len);
	TMatrix(int _len, int width, T v);
	TMatrix(const TMatrix<T>& m);
	int GetWidth();
	int Getlen();
	TMatrix<T> operator + (const TMatrix<T>& m);
	TMatrix<T> operator - (const TMatrix<T>& m);
	TMatrix<T>& operator = (const TMatrix<T>& m);
	TMatrix<T> operator * (const TMatrix<T>& m);
	TMatrix<T> operator * (const TVector<T>& vec);
	bool operator == (const TMatrix<T>& m);
	void Show();
};

template<class T>
std::ostream& operator<<(std::ostream& str, TMatrix<T>& m)
{
	for (int i = 0; i < m.GetWidth(); i++)
	{
		for (int i = 0; i < m.Getlen(); i++)
			str << m[i][i] << ' ';
		str << std::endl;
	}
	return str;
}

template<class T>
std::istream& operator>>(std::istream& str, TMatrix<T>& m)
{
	T var = 0;
	for (int i = 0; i < m.GetWidth(); i++)
	{
		for (int i = 0; i < m.Getlen(); i++)
		{
			str >> var;
			m[i][i] = var;
		}

	}
	return str;
}

template<class T>
inline TMatrix<T>::TMatrix()
{
	this->len = 0;
	this->width = 0;
	this->data = 0;
}

template<class T>
inline TMatrix<T>::~TMatrix()
{
	if (data != 0)
	{

		for (int i = 0; i < width; i++)
		{
			this->data[i].~TVector();
			this->data[i] = 0;
		}

		this->data = 0;
		delete[] this->data;
		this->data = 0;
	}

}


template<class T>
inline TMatrix<T>::TMatrix(int _len) : TVector(_len)
{
	width = _width;
	this->data = new TVector<T>[width];
	for (int i = 0; i < width; i++)
		this->data[i] = TVector<T>(this->len);
	this->len = _len;
}

template<class T>
inline TMatrix<T>::TMatrix(int _len, int _width, T v) : TVector(_len)
{
	width = _width;
	this->data = new TVector<T>[width];
	for (int i = 0; i < width; i++)
		this->data[i] = TVector<T>(_len);
	this->len = _len;

	for (int i = 0; i < width; i++)
		for (int i = 0; i < this->len; i++)
			this->data[i][i] = v;
}

template<class T>
inline TMatrix<T>::TMatrix(const TMatrix<T>& m)
{

	width = m.width;
	this->len = m.len;
	this->data = new TVector<T>[width];
	for (int i = 0; i < width; i++)
		this->data[i] = TVector<T>(this->len);
	this->len = m.len;

	for (int i = 0; i < m.width; i++)
		for (int w = 0; w < m.len; w++)
			this->data[i][w] = m.data[i][w];

}

template<class T>
inline int TMatrix<T>::GetWidth()
{
	return width;
}

template<class T>
inline int TMatrix<T>::Getlen()
{
	return this->len;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator+(const TMatrix& m)
{
	if (this->len != m.len || width != m.width) throw "размеры 1 матрицы не равны размерам 2";
	TMatrix result(*this);
	for (int i = 0; i < width; i++)
		for (int w = 0; w < this->len; w++)
			result.data[i][w] = this->data[i][w] + m.data[i][w];
	return result;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator-(const TMatrix<T>& m)
{
	if (this->len != m.len || width != m.width) throw "размеры 1 матрицы не равны размерам 2";
	TMatrix result(*this);
	for (int i = 0; i < width; i++)
		for (int w = 0; w < this->len; w++)
			result.data[i][w] = this->data[i][w] - m.data[i][w];
	return result;
}

template<class T>
inline TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T>& m)
{
	if (this == &m) return *this;
	if (this->len != m.len || width != m.width) throw "размеры 1 матрицы не равны размерам 2";
	for (int i = 0; i < width; i++)
		for (int w = 0; w < this->len; w++)
			data[i][w] = m.data[i][w];
	return *this;
}

template<class T>
inline TMatrix<T> TMatrix<T>::operator*(const TMatrix<T>& m)
{
	if (this->len != m.width) throw "некорректный размер матрицы!";
	TMatrix<T> result(m.len, width, 0);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < m.len; j++)
		{
			result[i][j] = 0;
			for (int x = 0; x < this->len; x++)
				result[i][j] += this->data[i][x] * m.data[x][j];
		}
	}
	return result;
}

template<class T>
TMatrix<T> TMatrix<T>::operator*(const TVector<T>& vec)
{
	TVector<T> temp(vec);
	if ((this->len) != temp.Getlen()) throw "некорректный размер матрицы!";

	TMatrix<T> result(1, width, 0);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			result[i][j] = 0;
			for (int x = 0; x < this->len; x++)
				result[i][j] += this->data[i][x] * temp[x];
		}
	}
	result.Show();
	return result;
}

template<class T>
inline bool TMatrix<T>::operator==(const TMatrix<T>& m)
{
	if (this == &m) return true;
	if (this->len != m.len || width != m.width) return false;
	for (int i = 0; i < width; i++)
	{
		for (int w = 0; w < this->len; w++)
			if (data[i][w] != m.data[i][w]) return false;
	}
	return true;
}


template<class T>
inline void TMatrix<T>::Show()
{
	for (int i = 0; i < width; i++)
	{
		for (int i = 0; i < this->len; i++)
			std::cout << this->data[i][i] << ' ';
		std::cout << std::endl;
	}
}