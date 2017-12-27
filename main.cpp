#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

float **matrix, **matrix1, **matrix2;

void create(float ** & elements, unsigned int rows,	unsigned int columns, float filler = 0.0f) 
{
	elements = new float *[rows];
	for (unsigned int i = 0; i < rows; ++i) 
	{
		elements[i] = new float[columns];
		for (unsigned int j = 0; j < columns; ++j) 
		{
			elements[i][j] = filler;
		}
	}
}

void write(float ** elements, unsigned int rows, unsigned int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << elements[i][j] << " ";
		}
		cout << endl;
	}

}

bool add(float ** lhs_elements,	unsigned int lhs_rows, unsigned int lhs_columns, float ** rhs_elements,
	unsigned int rhs_rows, unsigned int rhs_columns, float ** & result_elements, unsigned int & result_rows,
	unsigned int & result_columns)
{
	unsigned int rows;
	unsigned int columns;
	rows = lhs_rows;
	columns = lhs_columns;
	create(result_elements, rows, columns);
	result_rows = rows;
	result_columns = columns;
	if ((lhs_rows == rhs_rows) && (lhs_columns == rhs_columns)) 
	{
		for (int i = 0; i < rows; i++) 
		{
			for (int j = 0; j < columns; j++)
			{
				result_elements[i][j] = lhs_elements[i][j] + rhs_elements[i][j];
			}
		}
		return true;
	}
	else return false;
}

bool sub(float ** lhs_elements,	unsigned int lhs_rows, unsigned int lhs_columns, float ** rhs_elements,
	unsigned int rhs_rows, unsigned int rhs_columns, float ** & result_elements, unsigned int & result_rows,
	unsigned int & result_columns) 
{
	unsigned int rows;
	unsigned int columns;
	rows = lhs_rows;
	columns = lhs_columns;
	create(result_elements, rows, columns);
	if ((lhs_rows == rhs_rows) && (lhs_columns == rhs_columns))
	{
		for (int i = 0; i < rows; i++) 
		{
			for (int j = 0; j < columns; j++)
			{
				result_elements[i][j] = lhs_elements[i][j] - rhs_elements[i][j];
			}
		}
		return true;
	}
	else return false;

}

bool multiply(float ** lhs_elements, unsigned int lhs_rows,	unsigned int lhs_columns,
	float ** rhs_elements, unsigned int rhs_rows, unsigned int rhs_columns,	float ** & result_elements,
	unsigned int & result_rows,	unsigned int & result_columns)
{
	unsigned int rows;
	unsigned int columns;
	rows = lhs_rows;
	columns = lhs_columns;
	create(result_elements, rows, columns);
	result_rows = rows;
	result_columns = columns;
	if ((lhs_rows == rhs_columns) && (lhs_columns == rhs_rows)) 
	{
		for (int i = 0; i < rows; i++) 
		{
			for (int j = 0; j < columns; j++) 
			{
				for (int k = 0; k < lhs_columns; k++)
					result_elements[i][j] += lhs_elements[i][k] * rhs_elements[k][j];
			}
		}
		return true;
	}
	else return false;
}

bool transpose(float ** lhs_elements, unsigned int lhs_rows, unsigned int lhs_columns,
	float ** & result_elements,	unsigned int & result_rows,	unsigned int & result_columns) 
{
	unsigned int rows;
	unsigned int columns;
	rows = lhs_columns;
	columns = lhs_rows;
	create(result_elements, rows, columns);
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < columns; j++) 
		{
			result_elements[i][j] = lhs_elements[j][i];
		}
	}
	return true;
}

void GetMatr(float **&mas, float **p, int i, int j, int m) 
{
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki<m - 1; ki++) // проверка индекса строки
	{ 
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj<m - 1; kj++) // проверка индекса столбца
		{ 
			if (kj == j) dj = 1;
			p[ki][kj] = mas[ki + di][kj + dj];
		}
	}
}
// Рекурсивное вычисление определителя
int Determinant(float **&mas, unsigned int m) 
{
	int i, j, d, k, n;
	float **p;
	p = new float*[m];
	for (i = 0; i<m; i++)
		p[i] = new float[m];
	j = 0; d = 0;
	k = 1; //(-1) в степени i
	n = m - 1;
	if (m<1) cout << "Определитель вычислить невозможно!";
	if (m == 1) 
	{
		d = mas[0][0];
		return(d);
	}
	if (m == 2)
	{
		d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
		return(d);
	}
	if (m>2)
	{
		for (i = 0; i<m; i++) 
		{
			GetMatr(mas, p, i, 0, m);
			//    PrintMatr(p, n);
			d = d + k * mas[i][0] * Determinant(p, n);
			k = -k;
		}
	}
	return(d);
}

bool reversing(float ** lhs_elements, unsigned int lhs_rows, unsigned int lhs_columns,
	float ** & result_elements,	unsigned int & result_rows,	unsigned int & result_columns) 
{
	if (Determinant(lhs_elements, lhs_rows) == 0) 
	{
		return false;
	}
	else 
	{
		if (lhs_rows != lhs_columns)
			return NULL;
		unsigned int rows;
		unsigned int columns;
		float t;
		rows = lhs_rows;
		columns = lhs_columns;
		create(result_elements, rows, columns);
		for (int i = 0; i < rows; i++)
			result_elements[i][i] = 1;
		for (int i = 0; i < rows; i++) 
		{
			t = lhs_elements[i][i];
			for (int j = 0; j < columns; j++)
			{
				lhs_elements[i][j] /= t;
				result_elements[i][j] /= t;
			}

			for (int k = 0; k < rows; k++) 
			{
				if (k != i) 
				{
					t = lhs_elements[k][i];
					for (int j = 0; j < columns; j++)
					{
						lhs_elements[k][j] -= lhs_elements[i][j] * t;
						result_elements[k][j] -= result_elements[i][j] * t;
					}
				}
			}
		}

		return true;
	}
}

bool read_matrix(float ** & elements, unsigned int & result_rows, 
	unsigned int & result_columns, string s) 
{
	char symbol;
	ifstream stream;
	stream.open(s);
	if ((stream >> result_rows) && (stream >> symbol) && (stream >> result_columns)) 
	{
		create(elements, result_rows, result_columns);
		bool success = true;
		for (int i = 0; i < result_rows && success; ++i) 
		{
			for (int j = 0; j < result_columns; ++j) 
			{
				if (!(stream >> elements[i][j])) 
				{
					success = false;
					break;
				}
			}
		}
		stream.close();
		return success;

	}

	else 
	{
		stream.close();
		return false;
	}
}

void destroy(float ** elements,	unsigned int rows, unsigned int columns)
{
	for (unsigned int i = 0; i < rows; ++i)
	{
		delete[] elements[i];
	}
	delete[] elements;
}

int main() 
{
	unsigned rows1, columns1;
	unsigned rows2, columns2;
	unsigned rows, columns;

	char symbol;
	bool q;
	string s, str1, str2;
	getline(cin, s);
	istringstream stream(s);
	stream >> str1 >> symbol >> str2;
	q = read_matrix(matrix1, rows1, columns1, str1);
	if (q) 
	{
		switch (symbol) 
		{
		case '+':
			q = read_matrix(matrix2, rows2, columns2, str2);
			add(matrix1, rows1, columns1, matrix2, rows2, columns2, matrix, rows, columns);
			if (q)
				write(matrix, rows, columns);
			else
				cout << "An error has occured while reading input data";
			destroy(matrix1, rows1, columns1);
			destroy(matrix2, rows2, columns2);
			destroy(matrix, rows, columns);
			break;

		case '-':
			q = read_matrix(matrix2, rows2, columns2, str2);
			sub(matrix1, rows1, columns1, matrix2, rows2, columns2, matrix, rows, columns);
			if (q)
				write(matrix, rows, columns);
			else
				cout << "An error has occured while reading input data";
			destroy(matrix1, rows1, columns1);
			destroy(matrix2, rows2, columns2);
			destroy(matrix, rows, columns);
			break;

		case '*':
			q = read_matrix(matrix2, rows2, columns2, str2);
			multiply(matrix1, rows1, columns1, matrix2, rows2, columns2, matrix, rows, columns);
			if (q)
				write(matrix, rows, columns);
			else
				cout << "An error has occured while reading input data";
			destroy(matrix1, rows1, columns1);
			destroy(matrix2, rows2, columns2);
			destroy(matrix, rows, columns);
			break;

		case 'T':
			transpose(matrix1, rows1, columns1, matrix, rows, columns);
			write(matrix, rows, columns);
			destroy(matrix1, rows1, columns1);
			destroy(matrix2, rows2, columns2);
			destroy(matrix, rows, columns);
			break;

		case 'R':
			q = reversing(matrix1, rows1, columns1, matrix, rows, columns);
			if (q)
				write(matrix, rows1, columns1);
			else {
				cout << "There is no reverse matrix";
				cout << endl;
			}
			destroy(matrix1, rows1, columns1);
			destroy(matrix2, rows2, columns2);
			destroy(matrix, rows, columns);
			break;
		}
	}
	else
		cout << "An error has occured while reading input data";
	cin.get();
	return 0;
}
