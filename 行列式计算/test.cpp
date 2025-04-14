#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//计算的最高阶数
#define HIGHEST_ORDER 10


void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}





//判断序列的逆序数为偶数还是奇数(偶数返回true)
bool inverse_num_odevity(int num[], int order)
{
	//记录逆序数
	int sum = 0;
	for (int i = 1; i <= order; i++)
	{
		for (int j = i + 1; j <= order; j++)
		{
			if (num[i] > num[j])
			{
				sum++;
			}
		}
	}

	if (sum % 2 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//计算在num数组中按col的列序列算出来的数
int calculate_by_col(int num[][HIGHEST_ORDER], int col[], int order)
{
	int ret = 1;
	for (int i = 0; i < order; i++)
	{
		ret *= num[i][col[i + 1] - 1];
	}

	return ret;
}



void calculate()
{
	int n = 0;
	cout << "请输入行列式的阶数" << ":>";
	cin >> n;

	//创建数组
	int num[HIGHEST_ORDER][HIGHEST_ORDER] = { 0 };
	
	//输入数据
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> num[i][j];
		}
	}

	//记录结果
	int ret = 0;

	

	int i, j, x;

	//列排序
	int col_order[HIGHEST_ORDER + 1] = { 0 };
	for (i = 1; i <= n; i++)
	{
		col_order[i] = i;
	}

	while (1)
	{
		int y = HIGHEST_ORDER, m = 1;
		col_order[y] = 0xffff;

		//计算此排列的逆序数为偶数或为奇数
		//若为偶数，则加到ret上去
		//若为奇数，则取相反数后加到ret上去
		if (inverse_num_odevity(col_order, n) == true)
		{
			ret += calculate_by_col(num, col_order, n);
		}
		else
		{
			ret -= calculate_by_col(num, col_order, n);
		}
		


		for (i = 1; i <= n; i++)//验证此时是否到最后一个 
		{
			if (col_order[i] != n - i + 1) {
				m = 0;
				break; 
			}
		}

		if (m)
		{
			break;
		}

		for (i = n;; --i)//自右至左找出排列中第一个比相邻右边数字小的数字
		{
			if (col_order[i - 1] < col_order[i]) {
				m = i - 1;
				break;
			}
		}

		for (i = m + 1; i <= n; i++)//在该数字后的数字中找出比它大的数中最小的数 
		{
			if (col_order[i] > col_order[m])
			{
				x = i;
			}

			if (col_order[y] > col_order[x])
			{
				y = i;
			}
		}
		swap(col_order[m], col_order[y]);//交换，倒转 

		for (i = m + 1, j = n; i <= j; ++i, --j)
		{
			swap(col_order[i], col_order[j]);
		}
	}

	cout << ret << endl;
	cout << "**************************************************" << endl;
}


int main()
{
	while (1)
	{
		calculate();
	}

	return 0;
}