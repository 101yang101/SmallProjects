#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include <windows.h>
#include "commonope.h"
#include "macro_definition.h"
using namespace std;

//清空字符串
void init_str(char a[], int n) {
	for (int i = 0; i < n; i++) {
		a[i] = '\0';
	}
}

//初始化所属部门
void init_depart(int depart_check, char target_str[]) {
	char depart[6][20] = { DEPART_ONE, DEPART_TWO, DEPART_THREE, DEPART_FOUR, DEPART_FIVE, DEPART_SIX };

	switch (depart_check) {
	case 1:
		for (int i = 0; i < 20; i++) {
			target_str[i] = depart[depart_check - 1][i];
		}
		break;
	case 2:
		for (int i = 0; i < 20; i++) {
			target_str[i] = depart[depart_check - 1][i];
		}
		break;
	case 3:
		for (int i = 0; i < 20; i++) {
			target_str[i] = depart[depart_check - 1][i];
		}
		break;
	case 4:
		for (int i = 0; i < 20; i++) {
			target_str[i] = depart[depart_check - 1][i];
		}
		break;
	case 5:
		for (int i = 0; i < 20; i++) {
			target_str[i] = depart[depart_check - 1][i];
		}
		break;
	case 6:
		for (int i = 0; i < 20; i++) {
			target_str[i] = depart[depart_check - 1][i];
		}
		break;
	}
}

//初始化系统登录密码
void init_Master_password(char str[],int len) {
	system("cls");
	int judge = 0;
	char* check = (char*)malloc(len * sizeof(char));//用于确定密码是否正确，放在循环外是为了避免不断开辟内存

	do {
		if (judge == 1) {
			system("cls");
			cout << "密码输入失败，";
		}

		cout << "请输入系统启动密码：>";
		init_str(check, len);//为了保证准确型，需每次对check进行初始化操作
		cin >> check;
		system("cls");
		cout << "请再次输入密码：>";

		init_str(str, 20);
		cin >> str;
		for (int i = 0; i < 20; i++) {
			if (check[i] == str[i]) {
				judge = 0;
			}
			else {
				judge = 1;
				break;
			}
		}
	} while (judge == 1);

	free(check);
}

//初始化姓名
void init_name(char str[]) {
	system("cls");
	cout << "请输入您的姓名：>";
	init_str(str, 20);
	cin >> str;
}

//初始化年龄，所有类均有使用权限
void init_age(int num) {
	system("cls");
	cout << "请输入您的年龄：>";
	cin >> num;
}

//初始化身份证
void init_IDnumber(char str[], int len) {
	system("cls");
	cout << "请输入您的身份证号码：>";
	int judge = 0;//判断是否需要重新输入
	init_str(str, len);
	cin >> str;
	do {
		if (judge == 1) {
			system("cls");
			cout << "请输入正确的身份证号码：>";
			init_str(str, len);
			cin >> str;
		}

		//保证输入18位数字
		if (strlen(str) == 18) {
			for (int i = 0; i < 18; i++) {
				//保证18位均为数字
				if (str[i] <= '9' && str[i] >= '0') {
					judge = 0;
				}
				else {
					judge = 1;
					break;
				}
			}
		}
		else {
			judge = 1;
		}
	} while (judge == 1);
}

//初始化工号
void init_worknum(char sign, char str[], int len) {
	system("cls");
	cout << "请按格式输入工号(格式: " << sign << " + 数字)：>";
	init_str(str, len);
	cin >> str;
	int judge = 0;
	do {
		if (judge == 1) {
			system("cls");
			cout << "请按正确格式输入工号：>";
			init_str(str, len);
			cin >> str;
		}

		if (str[0] == sign) {
			for (int i = 1; i < strlen(str); i++) {
				if (str[i] <= '9' && str[i] >= '0') {
					judge = 0;
				}
				else {
					judge = 1;
					break;
				}
			}
		}
		else {
			judge = 1;
		}
	} while (judge == 1);
}

//初始化登录密码
void init_password(char str[], int len) {
	system("cls");
	int judge = 0;
	char* check = (char*)malloc(len * sizeof(char));//用于确定密码是否正确，放在循环外是为了避免不断开辟内存

	do {
		if (judge == 1) {
			system("cls");
			cout << "密码输入失败，";
		}

		cout << "请输入登录密码：>";
		init_str(check, len);
		cin >> check;

		system("cls");

		cout << "请再次输入密码：>";
		init_str(str, 20);
		cin >> str;

		for (int i = 0; i < 20; i++) {
			if (check[i] == str[i]) {
				judge = 0;
			}
			else {
				judge = 1;
				break;
			}
		}
	} while (judge == 1);

	free(check);
}

//信息保存(二进制文件)
void save_in_file(const char file_cata[], const char* origin, std::ios_base::openmode mode, int w_size)//参数：(文件目录, 待写入内存指针, 写入方式, 写入大小) 
{
	ofstream ofs;
	ofs.open(file_cata, mode);
	ofs.write(origin, w_size);
	ofs.close();
}

//登录密码确认
int common_check_password(char checkworknum[10], char checkpassword[20], const char file_cata[], std::ios_base::openmode mode, char* target_ptr, int size, char correct_worknum[], char correct_password[]) {
	ifstream ifs;
	ifs.open(file_cata, mode);

	//check 用于记录工号和密码是否正确
	int check = 0;
	while (ifs.read(target_ptr, size)) {
		//检查工号
		for (int i = 0; i < WORKNUM_LEN; i++) {
			if (checkworknum[i] == correct_worknum[i]) {
				check = 1;
			}
			else {
				check = 0;
				break;
			}
		}

		//若 check 仍为1，继续检查密码
		if (check == 1) {
			for (int i = 0; i < PASSWORD_LEN; i++) {
				if (checkpassword[i] == correct_password[i]) {
					check = 1;
				}
				else {
					check = 0;
					break;
				}
			}
		}

		//读到此若 check 仍为1，说明登录成功，可以退出
		if (check == 1) {
			cout << "**登录成功**" << endl;
			Sleep(1000);
			break;
		}
	}
	ifs.close();

	return check;//返回为1，登录成功
				 //返回为0，登录失败
}

//文件清空
void file_empty() {
	ofstream ofs;
	ofs.open(ALLWORKER_FILE, BINARY_WRITE);
	ofs.close();

	ofs.open(ADMIN_DEPART_FILE, BINARY_WRITE);
	ofs.close();

	ofs.open(PROJECT_DEPART_FILE, BINARY_WRITE);
	ofs.close();

	ofs.open(SALES_DEPART_FILE, BINARY_WRITE);
	ofs.close();

	ofs.open(LAW_DEPART_FILE, BINARY_WRITE);
	ofs.close();

	ofs.open(ACCOUNT_DEPART_FILE, BINARY_WRITE);
	ofs.close();

	ofs.open(LOGISTICS_DEPART_FILE, BINARY_WRITE);
	ofs.close();

	ofs.open(MASTER_PASSWORD_FILE, BINARY_WRITE);
	ofs.close();

	ofs.open(MANAGER_FILE, BINARY_WRITE);
	ofs.close();

	ofs.open(BOSS_FILE, BINARY_WRITE);
	ofs.close();
}