#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book
{
	char id[20];
	char name[20];
	int flag; //+1 表示未被借走  -1表示被借走
	char stu_name[20];
	int existence;
};

struct Libsim
{
	struct Book* src;
	long int num;
};

struct User
{
	int lend_book_num;
	char id[20];
	char name[20];
	char book_ID[3][20];
};

struct User_set
{
	struct User* up;
	int stu_num;
};


// num 表示现在有的书的数量
int search(struct Book* src, int num, int option, char target[20])
//查询功能 支持名字查询和id查询俩中功能
{
	if (option == 1)// 表示按书名查找
	{
		for (int j = 0; j < num; j++)
		{
			if (strcmp(target, src[j].name) == 0 && src[j].existence == 1)
			{
				return j;
			}
		}
	}
	else if (option == 0) //表示按id查找
	{
		for (int j = 0; j < num; j++)
		{
			if (strcmp(target, src[j].id) == 0 && src[j].existence == 1)
			{
				return j;
			}
		}
	}

	return -1;//没找到书
}


void lend(struct Book* src, int num, struct User* up, char stu_name[20], int stu_num)
{
	printf("输入所借书的名字请输入  1\n");
	printf("输入所借书的id请输入    0\n");
	int option;
	scanf("%d", &option);
	char target[20] = { '\0' };
	scanf("%s", target);
	int i = search(src, num, option, target[20]);
	if (i == -1)
	{
		printf("没有该书\n");
	}
	else
	{
		src[i].flag = -1;
		int j = 0;
		for (; j < stu_num; j++)
		{
			if (strcmp(up[j].name, stu_name) == 0)
			{
				int c = up[j].lend_book_num;
				if (c >= 3)
				{
					printf("超过所借数目\n");
					return(-1);
				}
				else
				{
					strcpy(up[j].book_ID[c], src[i].id);
					up[j].lend_book_num++;

				}
			}
		}
	}
}


void return_book(struct Book* src, int num, struct User* up, char stu_name[20], int stu_num)
{
	printf("输入所借书的名字请输入  1\n");
	printf("输入所借书的id请输入    0\n");
	int option;
	scanf("%d", &option);
	char target[20] = { '\0' };
	scanf("%s", target);
	int i = search(src, num, option, target[20]);
	if (i == -1)
	{
		printf("没有该书\n");
	}
	else
	{
		src[i].flag = +1;
		int j = 0;
		for (; j < stu_num; j++)
		{
			if (strcmp(up[j].name, stu_name) == 0)
			{
				int c = up[j].lend_book_num;
				{
					char t[20] = { '\0' };
					strcpy(up[j].book_ID[c], t);
					up[j].lend_book_num--;

				}
			}
		}
	}

}

// 管理员添加图书
void add_book(struct Libsim* libraryPointer)
{
	for (int i = 0; i < 20; i++)
	{
		libraryPointer->src[libraryPointer->num].name[i] = '\0';
		libraryPointer->src[libraryPointer->num].stu_name[i] = '\0';
		libraryPointer->src[libraryPointer->num].id[i] = '\0';
	}
	printf("请输入图书书名：");
	scanf("%s", libraryPointer->src[libraryPointer->num].name);
	printf("请输入图书的ID号：");
	scanf("%s", libraryPointer->src[libraryPointer->num].id);
	libraryPointer->src[libraryPointer->num].flag = 0; //设置为未被借
	libraryPointer->src[libraryPointer->num].existence = 1; // 表示书籍存在
	libraryPointer->num++; // 图书数量+1
	printf("添加成功");
}

// 管理员删除图书
void del_book(struct Libsim* libraryPointer)
{
	char book_ID[20] = { '\0' };
	int option = -1;
	printf("请输入要删除的图书的ID：");
	scanf("%s", book_ID);
	int book_position = search(libraryPointer->src, libraryPointer->num, 0, book_ID);

	if (book_position == -1)
	{
		printf("未找到此书。");
	}
	else
	{
		//执行删除操作
		libraryPointer->src[book_position].existence = 0;// 表示书籍不存在
		printf("删除成功");
	}
}

// 管理员修改书籍信息
void mod_book(struct Libsim* libraryPointer)
{
	char book_ID[20] = { '\0' };
	printf("请输入你要修改的书籍的ID：");
	scanf("%s", book_ID);
	int book_position = search(libraryPointer->src, libraryPointer->num, 0, book_ID);

	if (book_position == -1)
	{
		printf("未找到此书。");
	}
	else
	{
		//执行修改操作
		int option = -1;
		printf("1.修改ID名	2.修改书籍名字\n");
		printf("选择要进行的操作：");
	again_1:
		scanf("%d", &option);

		switch (option)
		{
		case 1:
			for (int i = 0; i < 20; i++)
			{
				libraryPointer->src[libraryPointer->num].id[i] = '\0';
			}
			printf("修改成的ID：");
			scanf("%s", libraryPointer->src[book_position].id);
			printf("修改成功");
			break;
		case 2:
			for (int i = 0; i < 20; i++)
			{
				libraryPointer->src[libraryPointer->num].name[i] = '\0';
			}
			printf("修改成的书名：");
			scanf("%s", libraryPointer->src[book_position].name);
			printf("修改成功");
			break;
		default:
			goto again_1;
		}
	}
}

// 管理员添加用户信息
void add_user(struct User_set* usersPointer)
{
	usersPointer->up[usersPointer->stu_num].lend_book_num = 0;
	for (int i = 0; i < 20; i++)
	{
		usersPointer->up[usersPointer->stu_num].id[i] = '\0';
		usersPointer->up[usersPointer->stu_num].name[i] = '\0';
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			usersPointer->up[usersPointer->stu_num].book_ID[i][j] = '\0';
		}
	}
	printf("请输入成员ID：");
	scanf("%s", usersPointer->up[usersPointer->stu_num].id);
	printf("请输入成员姓名：");
	scanf("%s", usersPointer->up[usersPointer->stu_num].name);
	printf("添加成功");
}

//display_u(library.src, library.num, users.up, stu_name[20], users.stu_num);
void display_u(struct Book* src, int num, struct User* up, char stu_name[20], int stu_num)
{
again:
	printf(" 1: 借书功能    2:还书功能     3:查询功能   ");
	int a = 0;
	scanf("%d", &a);
	switch (a)
	{
	case 1:
		//struct Book* src,int num,struct User* up,char stu_name[20],int stu_num
		lend(src, num, up, stu_name, stu_num);  //借书
		break;
	case 2:
		//void return_book(struct Book* src, int num, struct User* up, char stu_name[20], int stu_num)
		return_book(src, num, up, stu_name, stu_num); //还书
		break;
	case 3:
		//int search(struct Book* src, int num, int option, char target[20])
		printf("输入所借书的名字请输入  1\n");
		printf("输入所借书的id请输入    0\n");
		int option;
		scanf("%d", &option);
		char target[20] = { '\0' };
		scanf("%s", target);
		int i = search(src, num, option, target[20]);
		printf("该书的书名为%s", src->name);
		printf("该书的id为%s", src->id);
		if (src->flag == +1)
		{
			printf("该书未被借走\n");
		}
		else
		{
			printf("该书已经被借走\n");
		}
		break;
	default:
		printf("请重新选择\n");
		goto again;
	}
}



void display_a(struct Libsim* libraryPointer, struct User_set* usersPointer)
{
	int option = -1;
	printf("1.添加图书\n"
		"2.删除图书\n"
		"3.修改图书信息\n"
		"4.读者信息录入\n");
	printf("请输入要进行的操作：");
again_2:
	scanf("%d", &option);



	switch (option)
	{
	case 1:
		//添加图书
		printf("a\n");
		add_book(libraryPointer);
		break;
	case 2:
		//删除图书
		del_book(libraryPointer);
		break;
	case 3:
		//修改图书信息
		mod_book(libraryPointer);
		break;
	case 4:
		//读者信息录入
		add_user(usersPointer);
		break;
	default:
		//输入错误
		printf("输入错误。重新输入：");
		goto again_2;
	}
}

// 数据读取,返回 1 表示读入成功，返回 0 表示读入失败
int dataReading(struct Libsim* libraryPointer, struct User_set* usersPointer)
{
	// （1）读取书籍信息
	FILE* pf_book = fopen("book.txt", "r");
	if (pf_book == NULL) {
		//如果文件打开失败，结束函数
		return 0;
	}

	// 二进制读取文件数据
	for (libraryPointer->num = 0; fread(&libraryPointer->src[libraryPointer->num], sizeof(struct Book), 1, pf_book); libraryPointer->num++)
	{
		// 循环读取数据
	}

	fclose(pf_book);//关闭文件



	//（2）读取用户信息
	FILE* pf_users = fopen("users.txt", "r");
	if (pf_users == NULL) {
		//如果文件打开失败，结束函数
		return 0;
	}

	for (usersPointer->stu_num = 0; fread(&usersPointer->up[usersPointer->stu_num], sizeof(struct User), 1, pf_users); usersPointer->stu_num++)
	{
		// 循环读取数据
	}

	fclose(pf_users);//关闭文件

	return 1;
}

// 数据写入,返回 1 表示写入成功，返回 0 表示写入失败
int dataWriting(struct Libsim* libraryPointer, struct User_set* usersPointer)
{
	// 写入书籍数据
	FILE* pf_book = fopen("book.txt", "w");
	if (pf_book == NULL) {
		//如果文件打开失败，结束函数
		return 0;
	}

	//二进制形式写
	for (int i = 0; i < libraryPointer->num; i++)
	{
		if (libraryPointer->src[i].existence)// 书籍存在则写入
		{
			fwrite(&libraryPointer->src[i], sizeof(struct Book), 1, pf_book);
		}
	}

	fclose(pf_book);//关闭文件


	// 写入用户信息
	FILE* pf_users = fopen("users.txt", "w");
	if (pf_users == NULL) {
		//如果文件打开失败，结束函数
		return 0;
	}

	//二进制形式写
	for (int i = 0; i < usersPointer->stu_num; i++)
	{
		fwrite(&usersPointer->up[i], sizeof(struct User), 1, pf_users);
	}

	fclose(pf_users);//关闭文件

	return 1;
}


int main(int argc, char** argv)
{
	struct Libsim library;
	library.src = (struct Book*)malloc(100 * sizeof(struct Book));
	library.num = 0;

	struct User_set users;
	users.up = (struct User*)malloc(100 * sizeof(struct User));
	users.stu_num = 0;

	// 读入数据
	dataReading(&library, &users);

	if (strcmp(argv[1], "-a") == 0)
	{
		// 图书管理员
		display_a(&library, &users);
	}
	else if (strcmp(argv[1], "-u") == 0) {
		// 用户 struct Book* src,int num,struct User* up,char stu_name[20],int stu_num
		printf("请输入学生名字\n");
		char stu_name[20];
		scanf("%s", stu_name);
		display_u(library.src, library.num, users.up, stu_name[20], users.stu_num);
	}
	else
	{
		printf("输入命令错误");
		return;
	}

	// 将数据写入文件中
	dataWriting(&library, &users);

	//释放内存
	free(library.src);
	free(users.up);

	return 0;
}

