#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

bool ReadNameOfFileAndOper(string & name1, char & op, string & name2) 
{
	bool f = false;
	string str;
	getline(cin, str);
	istringstream stream(str);
	if (stream >> name1 && stream >> op) 
	{
		if (op == 'T' || op == 'R') 
		{
			f = !f;
			return f;
		}
		else 
		{
			if (stream >> name2)
			{
				f = !f;
			}
		}
	}
	return f;
}

bool ReadFileData(float ** & matrix, int & rows, int & columns, string name) 
{
	char op;
	ifstream fin;
	fin.open(name.c_str());
	if (!fin.is_open()) 
	{
		cout << "file isn't opened" << endl;
		return false;
	}
	string str;
	getline(fin, str);
	istringstream stream(str);
	if (stream >> rows && stream >> op && op == ',' && stream >> columns) 
	{
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) 
			{
				fin >> matrix[i][j];
			}
		}
	}
	fin.close();
	return true;
}

bool add(float **left_elem, int left_r, int left_col, float **right_elem, int right_r, int right_col, float ** & res_elem, int & res_r, int & res_col) 
{
	if (left_r != right_r || left_col != right_col)
	{
		return false;
	}
	res_r = left_r; 
	res_col = left_col;
	res_elem = new float *[res_r];
	for (int i = 0; i < res_r; ++i)
	{
		res_elem[i] = new float[res_col];
		for (int j = 0; j < res_col; ++j)
		{
			res_elem[i][j] = left_elem[i][j] + right_elem[i][j];
		}
	}
	return true;
}

bool sub(float **left_elem, int left_r, int left_col, float **right_elem, int right_r, int right_col, float ** & res_elem, int & res_r, int & res_col)
{
	if (left_r != right_r || left_col != right_col)
	{
		return false;
	}
	res_r = left_r; 
	res_col = left_col;
	res_elem = new float *[res_r];
	for (int i = 0; i < res_r; ++i)
	{
		res_elem[i] = new float[res_col];
		for (int j = 0; j < res_col; ++j)
		{
			res_elem[i][j] = left_elem[i][j] - right_elem[i][j];
		}
	}
	return true;
}

bool mul(float **left_elem, int left_r, int left_col, float **right_elem, int right_r, int right_col, float ** & res_elem, int & res_r, int & res_col)
{
	if (left_col != right_r) 
	{
		return false;
	}
	res_r = left_r;
	res_col = right_col;
	res_elem = new float *[res_r];
	for (int i = 0; i < res_r; ++i)
	{
		res_elem[i] = new float[res_col];
		for (int j = 0; j < res_col; ++j) 
		{
			float res_op = 0;
			for (int k = 0; k < left_col; ++k)
			{
				res_op += left_elem[i][k] * right_elem[k][j];
			}
			res_elem[i][j] = res_op;
		}
	}
	return true;
}

bool transpose(float **A, int r, int col, float ** & res_elem, int & res_r, int & res_col) 
{
	res_r = col;
	res_col = r;
	res_elem = new float *[res_r];
	for (int i = 0; i < res_r; ++i)
	{
		res_elem[i] = new float[res_col];
		for (int j = 0; j < res_col; ++j)
		{
			res_elem[i][j] = A[j][i];
		}
	}
	return true;
}

bool reverse(float **A, int r, int col, float ** & res_elem, int & res_r, int & res_col, bool & p) 
{
	if (r != col) 
	{
		return false;
	}
	res_r = r; 
	res_col = col;
	res_elem = new float *[res_r];
	for (int i = 0; i < res_r; ++i)
	{
		res_elem[i] = new float[res_col];
	}
	float temp;
	float **E = new float *[r];
	for (int i = 0; i < r; i++)
	{
		E[i] = new float[r];
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			E[i][j] = 0;
			if (i == j)
			{
				E[i][j] = 1;
			}
		}
	}
	for (int k = 0; k < r; k++)
	{
		temp = A[k][k];
		if (temp == 0)
		{
			p = 1;
			return true;
		}
		for (int j = 0; j < r; j++)
		{
			A[k][j] /= temp;
			E[k][j] /= temp;
		}
		for (int i = k + 1; i < r; i++)
		{
			temp = A[i][k];
			for (int j = 0; j < r; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}
	for (int k = r - 1; k > 0; k--) 
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = A[i][k];
			for (int j = 0; j < r; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < r; j++)
		{
			A[i][j] = E[i][j];
			res_elem[i][j] = A[i][j];
		}
	}
	return true;
}

void destroy(float ** & matrix, int & r)
{
	for (int i = 0; i<r; ++i)
	{
		delete[]matrix[i];
	}
	delete[]matrix;
}

int main()
{
	string name1, name2;
	char op;
	if (!(ReadNameOfFileAndOper(name1, op, name2))) {
		cout << "An error has occured while reading input data" << endl;
		return 10;
	}
	float **left_elem;
	int left_r, left_col;
	if (!(ReadFileData(left_elem, left_r, left_col, name1)))
	{
		cout << "An error has occured while reading input data" << endl;
		return -1;
	}
	if ((op != '+') && (op != '-') && (op != '*') && (op != 'R') && (op != 'T'))
	{
		cout << "An error has occured while reading input data" << endl;
		return -2;
	}
	float **res_elem;
	int res_r, res_col;
	switch (op) 
	{
	case '+': 
	{
		float **right_elem;
		int right_r, right_col;
		if (!(ReadFileData(right_elem, right_r, right_col, name2)))
		{
			cout << "An error has occured while reading input data" << endl;
			return -3;
		}
		if (!(add(left_elem, left_r, left_col, right_elem, right_r, right_col, res_elem, res_r, res_col))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		break;
	}
	case '-':
	{
		float **right_elem;
		int right_r, right_col;
		if (!(ReadFileData(right_elem, right_r, right_col, name2))) 
		{
			cout << "An error has occured while reading input data" << endl;
			return -3;
		}
		if (!(sub(left_elem, left_r, left_col, right_elem, right_r, right_col, res_elem, res_r, res_col)))
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		break;
	}
	case '*': 
	{
		float **right_elem;
		int right_r, right_col;
		if (!(ReadFileData(right_elem, right_r, right_col, name2)))
		{
			cout << "An error has occured while reading input data" << endl;
			return -3;
		}
		if (!(mul(left_elem, left_r, left_col, right_elem, right_r, right_col, res_elem, res_r, res_col)))
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		break;
	}
	case 'T':
	{
		if (!(transpose(left_elem, left_r, left_col, res_elem, res_r, res_col)))
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		break;
	}
	case 'R':
	{
		bool p = 0;
		if (!(reverse(left_elem, left_r, left_col, res_elem, res_r, res_col, p)))
		{
			cout << "An error has occured while reading input data" << endl;
			return -10;
		}
		if (p) 
		{
			cout << "There is no reverse matrix" << endl;
			return -20;
		}
		break;
	}
	}
	destroy(left_elem, left_r);
	for (int i = 0; i < res_r; ++i) 
	{
		for (int j = 0; j < res_col; ++j) 
		{
			cout << res_elem[i][j] << " ";
		}
		cout << endl;
	}
	destroy(res_elem, res_r);
	return 0;
}
