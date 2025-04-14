#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include "worker.h"
#include <windows.h>
#include "commonope.h"
#include "macro_definition.h"

//worker类构造函数实现
worker::worker() {
	//将字符数组内数据清空
	init_str(IDnumber, 20);

	init_str(worknum, 10);

	init_str(password, 20);

	init_str(name, 20);

	init_str(department, 20);
}

//信息初始化
void worker::initalize(int depart_check) {
	//输入所属部门
	init_depart(depart_check, department);

	//输入姓名
	init_name(name);

	//输入年龄
	init_age(age);

	//输入身份证
	init_IDnumber(IDnumber, IDNUMBER_LEN);

	//输入工号
	init_worknum('w', worknum, WORKNUM_LEN);


	//输入登录密码
	init_password(password, PASSWORD_LEN);

	system("cls");
	cout << "信息初始化成功";
}

//修改名字
void worker::name_change() {
	init_name(name);

	system("cls");
	cout << "修改成功";
}

//修改年龄
void worker::age_change() {
	init_age(age);

	system("cls");
	cout << "修改成功";
}

//修改身份证号码
void worker::IDnum_change() {
	init_IDnumber(IDnumber, IDNUMBER_LEN);

	system("cls");
	cout << "修改成功";
}

//修改工号
void worker::worknum_change() {
	init_worknum('w', worknum, WORKNUM_LEN);

	system("cls");
	cout << "修改成功";
}

//修改登录密码
void worker::password_change() {
	init_password(password, PASSWORD_LEN);

	system("cls");
	cout << "修改成功";
}

//修改部门
void worker::department_change() {
	int judge;
	char depart[6][20] = { DEPART_ONE, DEPART_TWO, DEPART_THREE, DEPART_FOUR, DEPART_FIVE, DEPART_SIX };
	do {
		system("cls");
		cout << "1." DEPART_ONE << endl;
		cout << "2." DEPART_TWO << endl;
		cout << "3." DEPART_THREE << endl;
		cout << "4." DEPART_FOUR << endl;
		cout << "5." DEPART_FIVE << endl;
		cout << "6." DEPART_SIX << endl;
		cout << "请输入部门：>";
		cin >> judge;

		if (judge == 1 || judge == 2 || judge == 3 || judge == 4 || judge == 5 || judge == 6) {
			init_depart(judge, department);
		}
		else {
			judge = 0;
			cout << "输入错误，请重新输入";
			Sleep(1000);
		}
	} while (judge == 0);

	system("cls");
	cout << "修改成功";
}

//信息展示
void worker::information_show() {
	system("cls");
	cout << "姓名：" << name << endl;
	cout << "工号：" << worknum << endl;
}

//信息保存
void worker::information_save(int depart_check) {
	switch (depart_check) {
	case 1:
		save_in_file(ADMIN_DEPART_FILE, (const char*)this, BINARY_APP, sizeof(worker_abstractclass));
		break;
	case 2:
		save_in_file(PROJECT_DEPART_FILE, (const char*)this, BINARY_APP, sizeof(worker_abstractclass));
		break;
	case 3:
		save_in_file(SALES_DEPART_FILE, (const char*)this, BINARY_APP, sizeof(worker_abstractclass));
		break;
	case 4:
		save_in_file(LAW_DEPART_FILE, (const char*)this, BINARY_APP, sizeof(worker_abstractclass));
		break;
	case 5:
		save_in_file(ACCOUNT_DEPART_FILE, (const char*)this, BINARY_APP, sizeof(worker_abstractclass));
		break;
	case 6:
		save_in_file(LOGISTICS_DEPART_FILE, (const char*)this, BINARY_APP, sizeof(worker_abstractclass));
		break;
	}
	save_in_file(ALLWORKER_FILE, (const char*)this, BINARY_APP, sizeof(worker_abstractclass));
}

////密码确认，登录成功后由此进入worker操作界面
//int worker::password_check(char* checkworknum, char* checkpassword) {
//	
//	int check = common_check_password(checkworknum, checkpassword, ALLWORKER_FILE, BINARY_READ, (char*)this, sizeof(worker_abstractclass), worknum, password);
//
//	if (check == 0) {
//		return check;//如果check为0，登录失败，退回上一界面
//	}
//	else {
//		operation_face();//如果check不为0，登录成功进入操作页面
//	}
//
//	return 1;
//}

//worker操作界面
int worker::operation_face() {
	return 0;
}