#pragma once
#include<iostream>
#include<fstream>
template<class T>
class TVector
{
protected:
	T* data;
	int len;

public:

	TVector(int _len = 0);
	TVector(const TVector<T>& vec);
	~TVector();
	T Getlen();
	T Vozvrat();
	void Vstavka(T v);
	T& operator[](int n);
	TVector<T> operator + (const TVector<T>& vec);
	TVector<T> operator - (const TVector<T>& vec);
	TVector<T> operator / (const TVector<T>& vec);
	TVector<T>& operator = (const TVector<T>& vec);

	void ReSize(int Newlen = 0);

	bool operator == (const TVector<T>& vec);
};



template<class T>
std::istream& operator>>(std::istream& str, TVector<T>& vec)
{

	int count = 0;
	str >> count;
	T v = 0;
	int len = vec.Getlen();
	vec.ReSize(0);

	v = 0;
	for (int i = 0; i < count; i++)
	{
		str >> v;
		vec.Vstavka(v);
	}
	return str;
}

template<class T>
std::ostream& operator<<(std::ostream& str, TVector<T>& vec)
{
	for (int i = 0; i < vec.Getlen(); i++)
	{
		str << vec[i] << ' ';
	}
	return str;
}

template<class T>
inline TVector<T>::TVector(int _len)
{
	data = 0;
	data = new T[_len];
	len = _len;
}
template <class T>
inline TVector<T>::TVector(const TVector<T>& vec)
{
	if (vec.data == 0) throw "varriable of vector is empty!";
	else
	{
		if (data != 0)
		{
			data = 0;
			delete[] data;
			data = 0;
			data = new T[vec.len];
		}
		else
			data = new T[vec.len];
		len = vec.len;
		for (int i = 0; i < len; i++)
		{
			data[i] = vec.data[i];
		}
	}
}

template<class T>
inline TVector<T>::~TVector()
{
	if (data != 0) delete[] data;
	data = 0;
}

template<class T>
inline T TVector<T>::Getlen()
{
	return len;
}

template<class T>
inline T TVector<T>::Vozvrat()
{
	if (len <= 0) { throw"ошибка"; }
	else
	{
		T* temp = new T[len];
		for (int i = 0; i < len; i++)
		{
			temp[i] = data[i];
		}
		T v = data[len - 1];

		data = 0;
		delete[] data;
		data = 0;
		data = new T[len - 1];
		len--;
		for (int i = 0; i < len; i++)
		{
			data[i] = temp[i];
		}
		temp = 0;
		delete[] temp;
		temp = 0;

		return v;
	}
}

template<class T>
inline void TVector<T>::Vstavka(T v)
{

	T* temp = new T[len];
	for (int i = 0; i < len; i++)
	{
		temp[i] = data[i];
	}
	data = 0;
	delete[] data;
	data = 0;
	data = new T[len + 1];
	for (int i = 0; i < len; i++)
	{
		data[i] = temp[i];
	}
	data[len] = v;
	len++;

}

template<class T>
inline T& TVector<T>::operator[](int n)
{
	return data[n];
}

template<class T>
TVector<T> TVector<T>::operator+ (const TVector<T>& vec)
{
	if (vec.data == 0 && vec.len < 0) throw "пусто";
	if (vec.len != this->len) throw "длина 1 вектора не равна 2";
	else
	{
		TVector<T> result(*this);
		for (int i = 0; i < len; i++)
		{
			result.data[i] = (this->data[i]) + vec.data[i];
		}

		return result;
	}
}

template<class T>
TVector<T> TVector<T>::operator-(const TVector<T>& vec)
{
	if (vec.data == 0 && vec.len < 0) throw "ошибка";
	if (vec.len != this->len) throw "длина 1 вектора не равна 2";
	else
	{
		TVector<T> result(*this);
		for (int i = 0; i < len; i++)
		{
			result.data[i] = (this->data[i]) - vec.data[i];
		}

		return result;
	}
}

template<class T>
TVector<T> TVector<T>::operator/(const TVector<T>& vec)
{
	if (vec.data == 0 && vec.len < 0) throw "пусто";
	if (vec.len != this->len) throw "длина 1 вектора не равна 2";
	else
	{
		TVector<T> result(*this);
		for (int i = 0; i < len; i++)
		{
			if (vec.data[i] != 0)
				result.data[i] = (this->data[i]) / vec.data[i];
			else throw "/0!";
		}

		return result;
	}
}

template<class T>
inline TVector<T>& TVector<T>::operator=(const TVector<T>& vec)
{
	if (data == 0) data = new T[vec.len];
	else if (data != 0)
	{
		data = 0;
		delete[] data;
		data = 0;
		data = new T[vec.len];
	}

	len = vec.len;
	for (int i = 0; i < len; i++)
	{
		data[i] = vec.data[i];
	}
	return *this;
}

template<class T>
inline void TVector<T>::ReSize(int Newlen)
{
	if (Newlen < 0) throw "The new len (or eiuals) less than zero";
	if (Newlen >= 0)
	{
		T* temp = new T[Newlen];
		for (int i = 0; i < Newlen; i++)
		{
			temp[i] = data[i];
		}

		data = 0;
		delete[] data;
		data = 0;

		data = new T[Newlen];
		len = Newlen;

		for (int i = 0; i < len; i++)
			data[i] = temp[i];
		temp = 0;
		delete[] temp;
		temp = 0;
	}

}

template<class T>
inline bool TVector<T>::operator==(const TVector<T>& vec)
{
	if (len != vec.len) return false;
	for (int i = 0; i < len; i++)
	{
		if (data[i] != vec.data[i]) return false;
	}
	return true;
}