#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "abstract_class.h"
#include "boss.h"

//修改系统登录密码
void Masterpassword(boss_abstractclass*bp) {
	system("cls");
	int judge = 0;
	do {
		if (judge == 1) {
			cout << "密码输入失败，";
		}

		cout << "请输入系统启动密码：>";
		string check2;
		cin >> check2;
		system("cls");
		cout << "请再次输入密码：>";
		cin >> bp->Master_password;

		if (bp->Master_password != check2) {
			judge = 1;
		}
	} while (judge == 1);
}

//修改身份证
void idcardchange(boss_abstractclass* bp) {
	system("cls");
	cout << "请输入您的身份证号码：>";
	int judge = 0;//判断是否需要重新输入
	cin >> bp->IDnumber;
	do {
		if (judge == 1) {
			system("cls");
			cout << "请输入正确的身份证号码：>";
			cin >> bp->IDnumber;
		}

		if (strlen(bp->IDnumber) == 18) {
			for (int i = 0; i < 18; i++) {
				if (bp->IDnumber[i] <= '9' && bp->IDnumber[i] >= '0') {
					judge = 0;
				}
				else {
					judge = 1;
					break;
				}
			}
		}
	} while (judge == 1);
}


//修改工号
void worknumchange(boss_abstractclass* bp) {
	system("cls");
	cout << "请按格式输入工号(格式: b + 数字)：>";
	cin >> bp->worknum;
	int judge = 0;//判断是否需要重新输入
	cin >> bp->worknum;
	do {
		if (judge == 1) {
			system("cls");
			cout << "请按正确格式输入工号：>";
			cin >> bp->worknum;
		}

		if ((bp->worknum)[0] == 'b') {
			for (int i = 1; i < 10; i++) {
				if ((bp->worknum)[i] <= '9' && (bp->worknum)[i] >= '0') {
					judge = 0;
				}
				else {
					judge = 1;
					break;
				}
			}
		}
	} while (judge == 1);
}


//修改登录密码
void passwordchange(boss_abstractclass* bp) {
	system("cls");
	int judge = 0;
	do {
		if (judge == 1) {
			cout << "密码输入失败，";
		}

		cout << "请输入登录密码：>";
		string check2;
		cin >> check2;
		system("cls");
		cout << "请再次输入登录密码：>";
		cin >> bp->password;

		if (bp->password != check2) {
			judge = 1;
		}
	} while (judge == 1);
}