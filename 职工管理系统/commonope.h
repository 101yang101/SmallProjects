#pragma once
#include <fstream>
#include <iostream>

//清空字符串内数据
void init_str(char a[], int n);

//初始化所属部门
void init_depart(int depart_check, char target_str[]);

//初始化系统登录密码，在boss类下使用，其他类无使用权限
void init_Master_password(char str[], int len);

//初始化姓名，所有类均有使用权限
void init_name(char str[]);

//初始化年龄，所有类均有使用权限
void init_age(int num);

//初始化身份证，所有类均有使用权限
void init_IDnumber(char str[], int len);

//初始化工号，所有类均有使用权限
void init_worknum(char sign, char str[], int len);

//初始化登录密码
void init_password(char str[], int len);

//信息保存
void save_in_file(const char file_cata[], const char* origin, std::ios_base::openmode mode, int w_size);//参数：(文件目录, 待写入内存指针, 写入方式, 写入大小) 

//登录密码确认
int common_check_password(char checkworknum[], char checkpassword[], const char file_cata[], std::ios_base::openmode mode, char* target_ptr, int size, char correct_worknum[], char correct_password[]);
				//参数表   (用户输入的工号，        用户输入的密码，        文件目录，                     文件读取方式，               目标地址，   读取大小，     正确工号，               正确密码)


//文件清空
void file_empty();