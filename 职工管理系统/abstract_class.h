#pragma once
#include <iostream>
using namespace std;
//抽象类头文件


//经理抽象类
class manager_abstractclass {
public:
	char name[20];//姓名
	int age;//年龄
	char IDnumber[20];//身份证号
	char worknum[10];//工号
	char password[20];
	char department[20];//部门

public:
	virtual void initalize(int depart_check) = 0;

	virtual void name_change() = 0;

	virtual void age_change() = 0;

	virtual void IDnum_change() = 0;

	virtual void worknum_change() = 0;

	virtual void password_change() = 0;

	virtual void department_change() = 0;

	virtual void information_show() = 0;

	virtual void information_save() = 0;

	//virtual int password_check(char* checkworknum, char* checkpassword) = 0;

	virtual int operation_face() = 0;
};


//老板抽象类
class boss_abstractclass {
public:
	char name[20];
	int age;
	char IDnumber[20];
	char worknum[10];
	char password[20];
	char Master_password[20];//系统启动密码

public:
	virtual void initalize() = 0;

	virtual void name_change() = 0;

	virtual void age_change() = 0;

	virtual void IDnum_change() = 0;

	virtual void worknum_change() = 0;

	virtual void password_change() = 0;

	virtual void Master_password_change() = 0;//重置系统密码

	virtual void Master_password_save() = 0;

	virtual void information_show() = 0;

	virtual void information_save() = 0;

	//virtual int password_check(char checkworknum[], char checkpassword[]) = 0;

	virtual int operation_face() = 0;

	virtual int second_set() = 0;
};



//职工抽象类
class worker_abstractclass {
public:
	char name[20];
	int age;
	char IDnumber[20];
	char worknum[10];
	char password[20];
	char department[20];

public:
	virtual void initalize(int depart_check) = 0;

	virtual void name_change() = 0;

	virtual void age_change() = 0;

	virtual void IDnum_change() = 0;

	virtual void worknum_change() = 0;

	virtual void password_change() = 0;

	virtual void department_change() = 0;

	virtual void information_show() = 0;

	virtual void information_save(int depart_check) = 0;

	//virtual int password_check(char checkworknum[], char checkpassword[]) = 0;

	virtual int operation_face() = 0;
};