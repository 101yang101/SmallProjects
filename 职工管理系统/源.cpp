#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <fstream>
#include "workerManager.h"
#include "boss.h"
#include "manager.h"
#include "worker.h"
#include "macro_definition.h"
#include "commonope.h"
using namespace std;


int main() {
	//实例化管理者对象
	workerManager wm;
	wm.is_account();
	wm.system_start();
	wm.Show_Menu();
	return 0;
}