#define _CRT_SECURE_NO_WARNINGS 1
#include "workerManager.h"
#include "boss.h"
#include "manager.h"
#include "worker.h"
#include "abstract_class.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "macro_definition.h"
#include "commonope.h"
using namespace std;

//管理类构造函数实现
workerManager::workerManager() {

}


//菜单展示函数实现
void workerManager::Show_Menu() {
	int judge = 0;
	do {
		system("cls");
		cout << "**********************" << endl;
		if (judge != 0) {
			cout << "  输入失败，请重新输入" << endl;
		}
		cout << "     1.老板登录" << endl;
		cout << "     2.经理登录" << endl;
		cout << "     3.员工登录" << endl;
		cout << "     0.退出系统" << endl;
		cout << "*********************" << endl;
		cin >> judge;

		if (judge == 0)
		{
			exit(0);
		}
		else if (judge <= 3 && judge >= 1) {
			judge = passwordinfer(judge);
		}
	} while (judge != 0);
}

//密码输入界面，一旦密码输入成功，将由此进入各职工操作界面
int workerManager::passwordinfer(int judge) {
	int judge1 = 1;
	do {
		if (judge1 == 0) {
			system("cls");
			cout << "登录失败，可能是工号或密码错误" << endl;
			cout << "请输入“1”继续登录或按其他任意键退出登录：>";
			string a = "1";
			cin >> a;
			if (a != "1") {
				return 1;//返回菜单展示界面进行选择
			}
		}

		system("cls");
		cout << "********请登录********" << endl;
		cout << "**********************" << endl;
		cout << "请输入工号：>";
		char check1[WORKNUM_LEN] = { 0 };
		cin >> check1;

		cout << "请输入密码：>";
		char check2[PASSWORD_LEN] = { 0 };
		cin >> check2;

		switch (judge) {
		case 1: {
			boss bossope;
			judge1 = common_check_password(check1, check2, BOSS_FILE, BINARY_READ, (char*)&bossope, sizeof(boss_abstractclass), bossope.worknum, bossope.password);
			boss bossp;
			bossp = bossope;
			cout << bossp.IDnumber;
		}
			break;
		case 2: {
			manager managerope;
			judge1 = common_check_password(check1, check2, MANAGER_FILE, BINARY_READ, (char*)&managerope, sizeof(manager_abstractclass), managerope.worknum, managerope.password);
			managerope.operation_face();
		}
			break;
		case 3: {
			worker workerope;
			judge1 = common_check_password(check1, check2, BOSS_FILE, BINARY_READ, (char*)&workerope, sizeof(boss_abstractclass), workerope.worknum, workerope.password);
			workerope.operation_face();
		}
			break;
		}
	} while (judge1 == 0);

	return 0;
}


//判断账户是否创建
void workerManager::is_account() {
	ifstream ifs;
	ifs.open(MASTER_PASSWORD_FILE, ios::in);
	char ch;
	ifs >> ch;

	if (ifs.eof()) {
		//清空所有文件的信息
		file_empty();

		//创建账户
		ac_found();
	}

	ifs.close();
}


//创建账户
void workerManager::ac_found() {
	system("cls");
	cout << "**********************************" << endl;
	cout << "    您还未创建账户，请先创建账户" << endl;
	cout << "          1. 创建账户" << endl;
	cout << "        其他任意键退出程序" << endl;
	cout << "**********************************" << endl;
	int ope;
	cin >> ope;
	if (ope == 1) {
		//初始化老板信息
		boss Bos;
		Bos.initalize();
		Bos.information_save();
		Sleep(1000);

		char depart[6][20] = { DEPART_ONE, DEPART_TWO, DEPART_THREE, DEPART_FOUR, DEPART_FIVE, DEPART_SIX };
		//初始化部门经理信息
		system("cls");
		cout << "**请输入各部门经理信息**" << endl;
		Sleep(1000);
		manager Man;
		for (int i = 0; i < 6; i++) {
			cout << "**" << depart[i] << "**" << endl;
			Sleep(1000);
			Man.initalize(i + 1);
			Man.information_save();
		}
		Sleep(1000);

		//初始化各部门员工信息
		worker wor;
		for (int i = 0; i < 6; i++) {
			system("cls");
			cout << "请输入" << depart[i] << "员工人数并进行员工信息初始化：>";
			int number;
			cin >> number;
			for (int j = 0; j < number; j++) {
				system("cls");
				cout << "员工" << j + 1 << endl;
				Sleep(1000);

				wor.initalize(i + 1);
				wor.information_save(i + 1);
			}
		}
	}
	else {
		exit(0);
	}
}

//系统启动
void workerManager::system_start() {
	//读取系统密码
	char correctpassword[MASTER_PASSWORD_LEN] = { 0 };
	ifstream ifs;
	ifs.open(MASTER_PASSWORD_FILE, BINARY_READ);

	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return;
	}

	ifs.read((char*)correctpassword, sizeof(boss_abstractclass::Master_password));
	ifs.close();
	int judge = 0;//判断是否需要重新输入
	do {
		system("cls");
		Sleep(1000);

		if (judge == 1) {
			cout << "密码输入错误，请重新输入：>";
		}
		else {
			cout << "系统启动成功，请输入系统登录密码：>";
		}

		//读取用户输入的密码
		char check[MASTER_PASSWORD_LEN] = { 0 };
		cin >> check;

		//判断密码是否正确
		for (int i = 0; i < MASTER_PASSWORD_LEN; i++) {
			if (check[i] == correctpassword[i]) {
				judge = 0;
			}
			else {
				judge = 1;
				break;
			}
		}

		if (judge == 0) {
			cout << "登录成功，欢迎使用" << endl;
			Sleep(1000);
		}
	} while (judge == 1);
}


//退出界面展示
void workerManager::Exit_show() {
	cout << "*******************************************************************************" << endl;
	cout << "******************************** 欢迎下次使用 *********************************" << endl;
	cout << "*******************************************************************************" << endl;
}


//管理类析构函数实现
workerManager::~workerManager() {

}