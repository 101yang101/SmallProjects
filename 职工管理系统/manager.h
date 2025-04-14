#pragma once
#include <iostream>
#include "abstract_class.h"
using namespace std;

class manager :public manager_abstractclass
{
public:
	manager();

	virtual void initalize(int depart_check);

	virtual void name_change();

	virtual void age_change();

	virtual void IDnum_change();

	virtual void worknum_change();

	virtual void password_change();

	virtual void department_change();

	virtual void information_show();

	virtual void information_save();

	//virtual int password_check(char* checkworknum, char* checkpassword);

	virtual int operation_face();
};