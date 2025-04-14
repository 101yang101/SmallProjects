#pragma once
#include <iostream>
#include "abstract_class.h"
using namespace std;


class workerManager {
public:
	//构造函数
	workerManager();

	//菜单展示函数
	void Show_Menu();

	//密码输入界面
	int passwordinfer(int judge);

	//判断账户是否创建
	void is_account();

	//创建账号
	void ac_found();

	//系统启动
	void system_start();

	//退出界面展示
	void Exit_show();

	//析构函数
	~workerManager();
};