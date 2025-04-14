#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void menu() {
	printf("*********************************\n");
	printf("***********  扫雷游戏  **********\n");
	printf("*********************************\n");
	printf("*********************************\n");
	printf("*********************************\n");
	printf("**********  1 . play  ***********\n");
	printf("**********  0 . exit  ***********\n");
	printf("*********************************\n");
}

int main()
{
	int input;
	srand((unsigned int)time(NULL));
	do {
		menu();
		printf("请选择：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			input = game();
			break;
		case 0:
			system("cls");
			printf("*********************************\n");
			printf("*********************************\n");
			printf("***********  游戏结束  **********\n");
			printf("*********************************\n");
			printf("*********************************\n");
			break;
		default:
			printf("选择错误，重新选择\n");
		}
	} while (input);

	return 0;
}
