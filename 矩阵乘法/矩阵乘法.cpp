#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

#define HIGHEST_ORDER 10

void matrix_multi(int num1[HIGHEST_ORDER][HIGHEST_ORDER], int& row1, int& col1, int num2[HIGHEST_ORDER][HIGHEST_ORDER], int& row2, int& col2)
{
	int ret_matrix[HIGHEST_ORDER][HIGHEST_ORDER] = { 0 };

	
	//相乘后矩阵 row1 行 col2 列
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col2; j++)
		{
			int ret = 0;
			for (int k = 0; k < col1; k++)
			{
				ret += num1[i][k] * num2[k][j];
			}
			ret_matrix[i][j] = ret;
		}
	}

	//显示乘后矩阵
	cout << "***************" << endl;
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col2; j++)
		{
			num1[i][j] = num2[i][j] = ret_matrix[i][j];
			printf("%6d", ret_matrix[i][j]);
		}

		cout << endl;
	}
	col1 = col2;
	row2 = row1;
	cout << "***************************************************" << endl;
}

//填充数据
bool input(int num[HIGHEST_ORDER][HIGHEST_ORDER], int& row1, int& col1, int& row2, int& col2, const int check)
{
	char arr[5][10] = { "0","左","右" ,"左乘","右乘"};
	cout << "输入" << arr[check] << "矩阵的行数和列数:>";

	int row = 0, col = 0;
	if (check % 2 == 0)
	{
		cin >> row2 >> col2;
		row = row2;
		col = col2;
	}
	else
	{
		cin >> row1 >> col1;
		row = row1;
		col = col1;
	}

	if (check > 1 && col1 != row2)
	{
		cout << "无法相乘" << endl;
		return false;
	}

	cout << "**输入" << arr[check] << "矩阵**" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> num[i][j];
		}
	}

	return true;
}

int main()
{
	while (1)
	{
		int num1[HIGHEST_ORDER][HIGHEST_ORDER] = { 0 };
		int num2[HIGHEST_ORDER][HIGHEST_ORDER] = { 0 };
		int row1, col1;
		int row2, col2;

		//第一个矩阵
		input(num1, row1, col1, row2, col2, 1);


		//第二个矩阵
		if (input(num2, row1, col1, row2, col2, 2))
		{
			//计算乘积
			matrix_multi(num1, row1, col1, num2, row2, col2);
		}
		

		while (1)
		{
			cout << "1：上式左乘" << endl;
			cout << "2：上式右乘" << endl;
			cout << "3：开始新的运算" << endl;
			cout << "选择操作:>" << endl;

			int ope = 0;
			cin >> ope;

			if (ope == 1)
			{
				if (input(num1, row1, col1, row2, col2, 3))
				{
					matrix_multi(num1, row1, col1, num2, row2, col2);
				}
			}
			else if (ope == 2)
			{
				if (input(num2, row1, col1, row2, col2, 4))
				{
					matrix_multi(num1, row1, col1, num2, row2, col2);
				}
			}
			else
			{
				break;
			}
		}
	}

	return 0;
}