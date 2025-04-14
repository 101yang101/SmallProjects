#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
#include "boss.h"
#include "abstract_class.h"
#include "commonope.h"
#include "macro_definition.h"
using namespace std;

//boss类构造函数实现
boss::boss() {
	//将字符数组内数据清空
	init_str(IDnumber, IDNUMBER_LEN);

	init_str(worknum, WORKNUM_LEN);

	init_str(password, PASSWORD_LEN);

	init_str(name, NAME_LEN);

	init_str(Master_password, MASTER_PASSWORD_LEN);
}

//初始化对象
void boss::initalize() {
	//输入系统启动密码
	init_Master_password(Master_password, MASTER_PASSWORD_LEN);
	Master_password_save();

	//输入姓名
	init_name(name);

	//输入年龄
	init_age(age);

	//输入身份证
	init_IDnumber(IDnumber, IDNUMBER_LEN);


	//输入工号
	init_worknum('b', worknum, WORKNUM_LEN);

	//输入登录密码
	init_password(password, PASSWORD_LEN);

	system("cls");
	cout << "信息初始化成功";
}

//修改名字
void boss::name_change() {
	init_name(name);

	system("cls");
	cout << "修改成功";
}

//修改年龄
void boss::age_change() {
	init_age(age);

	system("cls");
	cout << "修改成功";
}

//修改身份证号码
void boss::IDnum_change() {
	init_IDnumber(IDnumber, IDNUMBER_LEN);

	system("cls");
	cout << "修改成功";
}

//修改工号
void boss::worknum_change() {
	init_worknum('b', worknum, WORKNUM_LEN);

	system("cls");
	cout << "修改成功";
}

//修改登录密码
void boss::password_change() {
	init_password(password, PASSWORD_LEN);

	system("cls");
	cout << "修改成功";
}

//修改系统登录密码
void boss::Master_password_change() {
	init_Master_password(Master_password, MASTER_PASSWORD_LEN);

	system("cls");
	cout << "修改成功";

	Master_password_save();
}

//系统登录密码保存
void boss::Master_password_save() {
	save_in_file(MASTER_PASSWORD_FILE, Master_password, BINARY_WRITE, sizeof(boss::Master_password));
}

//信息展示
void boss::information_show() {
	cout << "姓名：" << name << endl;
	cout << "工号：" << worknum << endl;
}

//信息保存
void boss::information_save() {
	save_in_file(BOSS_FILE, (const char*)this, BINARY_WRITE, sizeof(boss_abstractclass));
}

////密码确认，登录成功后由此进入boss操作一级界面
//int boss::password_check(char checkworknum[], char checkpassword[]) {
//	
//	int check = common_check_password(checkworknum, checkpassword, BOSS_FILE, BINARY_READ, (char*)this, sizeof(boss_abstractclass), worknum, password);
//	
//	if (check == 0) {
//		return check;//如果check为0，登录失败，退回上一界面
//	}
//	else {
//		//cout << this << endl;
//		//information_show();
//		//this->operation_face();
//		//this->operation_face();//如果check不为0，登录成功进入操作一级页面
//	}
//
//	return 1;
//}
//

//boss操作一级界面
int boss::operation_face() {
	aa:
	system("cls");
	cout << "*****************" << endl;
	cout << "1.查看未读信息" << endl;
	cout << "2.下发任务" << endl;
	cout << "3.历史发布任务" << endl;
	cout << "4.查看部门信息" << endl;
	cout << "*****************" << endl;
	cout << "|| 5.设置 ||" << endl;
	cout << "************" << endl;
	int ope = 0;
	cin >> ope;
	if (ope == 6) {
		ope = second_set();
	}
	if (ope == 0) {
		goto aa;
	}
	return 0;
}

//boss操作二级界面（设置）
int boss::second_set() {
	system("cls");
	cout << "**********" << endl;
	cout << "| 0.返回 |" << endl;
	cout << "*******************" << endl;
	cout << "1.修改个人信息" << endl;
	cout << "2.退出登录" << endl;
	cout << "*******************" << endl;
	int ope = 0;
	cin >> ope;
	return ope;
}
