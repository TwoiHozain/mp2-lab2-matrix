// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void setRandMatrix(TDynamicMatrix<double> &m)
{
	for (size_t i = 0; i < m.size(); i++)
		for (size_t j = 0; j < m.size(); j++)
			m[i][j] = rand()%10+(rand()%10)/10;
}

void addMatrixs(size_t size)
{
	TDynamicMatrix<double> m1(size), m2(size);
	if (size > 3)
	{
		setRandMatrix(m1);
		setRandMatrix(m2);
		cout << m1 << endl;
		cout << m2 << endl;
	}
	else 
	{
		cout << "Enter first matrix"<<endl;
		cin >> m1;
		cout << endl << "Enter second matrix"<<endl;
		cin >> m2;
	}

	cout << m1 + m2;
}

void subMatrixs(size_t size)
{
	TDynamicMatrix<double> m1(size), m2(size);
	if (size > 3)
	{
		setRandMatrix(m1);
		setRandMatrix(m2);
		cout << m1 << endl;
		cout << m2 << endl;
	}
	else
	{
		cout << "Enter first matrix"<<endl;
		cin >> m1;
		cout << endl << "Enter second matrix"<<endl;
		cin >> m2;
	}

	cout << m1 - m2;
}

void multMatrixs(size_t size)
{
	TDynamicMatrix<double> m1(size), m2(size);
	if (size > 3)
	{
		setRandMatrix(m1);
		setRandMatrix(m2);
		cout << m1 << endl;
		cout << m2 << endl;
	}
	else
	{
		cout << "Enter first matrix"<<endl;
		cin >> m1;
		cout << endl << "Enter second matrix"<<endl;
		cin >> m2;
	}

	cout << m1 * m2;
}

void multMatrixAndScaler(size_t size)
{
	TDynamicMatrix<double> m1(size);
	double scaler;
	if (size > 3)
	{
		setRandMatrix(m1);
		cout << m1 << endl;
	}
	else
	{
		cout << "Enter first matrix"<<endl;
		cin >> m1;
	}

	cout << m1*scaler;
}

void mult(size_t size)
{
	int choose = 0;
	cout << "1 -Mult scaler and matrix.\n2 -Mult matrix and matrix?";
	cin >> choose;
	switch (choose)
	{
	case(1):
		multMatrixAndScaler(size);
		break;
	case(2):
		multMatrixs(size);
		break;
	default:
		cout << "Wrong choise";
		break;
	}
}

void main()
{
	size_t size=1;
	char operation;

	cout << "Enter matrix size"<<'\n';
	cin >> size;

	cout << "Enter operation" << '\n';
	cin >> operation;

	try 
	{
		switch (operation)
		{
		case('+'):
			addMatrixs(size);
			break;
		case('-'):
			subMatrixs(size);
			break;
		case('*'):
			mult(size);
			break;
		default:
			cout <<"Uncnown operation";
			break;
		}

	}catch(exception &exc)
	{
		cout << exc.what();
	}
}
//---------------------------------------------------------------------------
