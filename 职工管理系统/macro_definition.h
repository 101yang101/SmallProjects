#pragma once
//文件目录
#define ALLWORKER_FILE "0所有员工信息.txt"
#define ADMIN_DEPART_FILE "1行政部.txt"
#define PROJECT_DEPART_FILE "2项目部.txt"
#define SALES_DEPART_FILE "3营销部.txt"
#define LAW_DEPART_FILE "4法务部.txt"
#define ACCOUNT_DEPART_FILE "5财务部.txt"
#define LOGISTICS_DEPART_FILE "6后勤部.txt"
#define BOSS_FILE "boss.txt"
#define MANAGER_FILE "manager.txt"
#define MASTER_PASSWORD_FILE "Master_password.txt"


//读写操作
#define BINARY_READ ios::in | ios::binary    //二进制读
#define BINARY_WRITE ios::out | ios::binary   //二进制写
#define BINARY_APP ios::app | ios::binary     //二进制追加
#define TEXT_READ ios::in      //文本文件读
#define TEXT_WRITE ios::out     //文本文件写
#define TEXT_APP ios::app       //文本文件追加


//输入信息最大长度(char)
#define MASTER_PASSWORD_LEN 20
#define PASSWORD_LEN 20
#define NAME_LEN 20
#define WORKNUM_LEN 10
#define IDNUMBER_LEN 20
#define DEPARTMENT_LEN 20


//部门编号
#define DEPART_ONE "行政部"
#define DEPART_TWO "项目部"
#define DEPART_THREE "营销部"
#define DEPART_FOUR "法务部"
#define DEPART_FIVE "财务部"
#define DEPART_SIX "后勤部"