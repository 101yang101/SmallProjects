#pragma once
#include <iostream>
#include "abstract_class.h"
using namespace std;

//老板类定义，继承 boss_abstractclass (抽象类)
class boss :public boss_abstractclass
{
public:
	boss();

	virtual void initalize();

	virtual void name_change();

	virtual void age_change();

	virtual void IDnum_change();

	virtual void worknum_change();

	virtual void password_change();

	virtual void Master_password_change();//重置系统密码

	virtual void Master_password_save();

	virtual void information_show();

	virtual void information_save();

	//virtual int password_check(char checkworknum[], char checkpassword[]);

	virtual int operation_face();

	virtual int second_set();
};