// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz == 0)
			throw out_of_range("Vector size should be greater than zero");
		if (sz > MAX_VECTOR_SIZE)
			throw out_of_range("Vector size was to large");
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}

	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		//assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}

	TDynamicVector(const TDynamicVector& v) :sz(v.sz)
	{
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}

	TDynamicVector(TDynamicVector&& v) noexcept
	{
		pMem = nullptr;
		swap(*this, v);
	}

	~TDynamicVector()
	{
		delete[] pMem;
	}

	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v)
			return *this;

		if (sz != v.sz)
		{
			T* tmp = new T[v.sz];
			sz = v.sz;
			delete[] pMem;
			pMem = tmp;
		}

		std::copy(v.pMem, v.pMem + v.sz, pMem);
		return *this;
	}

	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		sz = 0;
		delete[] pMem;
		pMem = nullptr;
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		return pMem[ind];
	}

	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}

	// индексация с контролем
	T& at(int ind)
	{
		if (ind < sz && ind > 0)
			return pMem[ind];
		else
			throw out_of_range("Index out of a range");
	}

	const T& at(size_t ind) const
	{
		if (ind < sz)
			return pMem[ind];
		else
			throw out_of_range("Index out of a range");
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
	{
		if (sz != v.sz)
			return false;

		for (size_t i = 0; i < sz; i++)
			if (pMem[i] != v[i])
				return false;

		return true;
	}

	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(*this==v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector tmp(*this);
		for (size_t i = 0; i < sz; i++)
			tmp[i] += val;
		return tmp;
	}

	TDynamicVector operator-(T val)
	{
		TDynamicVector tmp(*this);
		for (size_t i = 0; i < sz; i++)
			tmp[i] -= val;
		return tmp;
	}

	TDynamicVector operator*(T val)
	{
		TDynamicVector tmp(*this);
		for (size_t i = 0; i < sz; i++)
			tmp[i] *= val;
		return tmp;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw invalid_argument("The vectors must have the same size");

		TDynamicVector tmp(*this);
		for (size_t i = 0; i < sz; i++)
			tmp[i] += v[i];

		return tmp;
	}

	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw invalid_argument("The vectors must have the same size");

		TDynamicVector tmp(*this);
		for (size_t i = 0; i < sz; i++)
			tmp[i] -= v[i];

		return tmp;
	}

	T operator*(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw invalid_argument("The vectors must have the same size");

		T tmp = 0;
		for (size_t i = 0; i < sz; i++)
			tmp += v[i]*pMem[i];
		
		return tmp;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << '\t'; // требуется оператор<< для типа T
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (s > MAX_MATRIX_SIZE)
			throw exception("Matrix size was to large");

		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];

	size_t size() const noexcept { return sz; }

	T& at(int row, int col)
	{
		if (row < MAX_MATRIX_SIZE && row > 0 && col < MAX_MATRIX_SIZE && col> 0 && row<sz && col<sz)
		{
			return pMem[row][col];
		}
		throw exception("Index should be less than MAX_MATRIX_SIZE and greater than 0, and less then size");
	}

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::operator==(m);
	}

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val)
	{
		TDynamicMatrix tmp(*this);
		for (size_t i = 0; i < sz; i++)
			tmp[i] *= val;
		return tmp;
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		TDynamicVector<T> res(sz);
		for (size_t i = 0; i < sz; i++)
			res[i] = pMem[i] * v;
		return res;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		TDynamicMatrix tmp(sz);

		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] + m.pMem[i];

		return tmp;
	}

	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		TDynamicMatrix tmp(sz);

		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] - m.pMem[i];

		return tmp;
	}

	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		TDynamicMatrix tmp(sz);

		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				for (size_t k = 0; k < sz; k++)
					tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];

		return tmp;
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& v)
	{
		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			cout << v[i] << endl;
		return ostr;
	}
};

#endif
