#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

int game()
{
	char mine_board[ROWS][COLS];
	char show_board[ROWS][COLS];

	init_board(mine_board, ROWS, COLS, '-');
	init_board(show_board, ROWS, COLS, '*');

	system("cls");

	print_board(show_board, ROW, COL);

	//print_board(mine_board, ROW, COL);

	if (put_mine(mine_board, ROWS, COLS, ROW, COL)) {
		mine_sweep(mine_board, show_board, ROWS, COLS, ROW, COL);
		return 1;
	}

	return 0;
}

void init_board(char board[ROWS][COLS], int rows, int cols, char sign)
{
	int i;
	for (i = 0; i < rows; i++) {
		int j;
		for (j = 0; j < cols; j++) {
			board[i][j] = sign;
		}
	}
}

void print_board(char board[ROWS][COLS], int row, int col)
{
	int i;
	for (i = 0; i <= row; i++) {
		int j;
		if (i == 0) {
			printf(" 0 |");
			for (j = 1; j <= col; j++) {
				printf("%2d ", j);
			}
			printf("\n");
			printf("---+--");
			for (j = 2; j <= col; j++) {
				printf("---");
			}
			
		}
		else {
			printf("%2d |", i);
			for (j = 1; j <= col; j++) {
				printf(" %c ", board[i][j]);
			}
		}
		printf("\n");
	}
}

int put_mine(char board[ROWS][COLS], int rows, int cols, int row, int col)
{
	int x = 0, y = 0;
	/*int i;
	for (i = 1; i <= row; i++) {
		int j;
		for (j = 1; j <= col; j++) {
			if (i >= 2 && i <= 20 && j >= 2 && j <= 20) {
				;
			}
			else {
				board[i][j] = '+';
			}
		}
	}*/
	int num = MINE_NUMBER;
	if (num < row * col) {
		while (num--) {
			x = rand() % row + 1;
			y = rand() % col + 1;
			if (board[x][y] == '-') {
				board[x][y] = '+';
			}
		}
		return 1;
	}
	system("cls");
	printf("*************************************************\n"
	       "**********  雷数大于方格数，布雷失败  ***********\n"
		   "**********    请重新调整再开始游戏    ***********\n"
	       "*************************************************");

	return 0;
}

void mine_sweep(char mine_board[ROWS][COLS], char show_board[ROWS][COLS], int rows, int cols, int row, int col)
{
	int x = 0, y = 0;
	
	while (1) {
		printf("请输入你要扫的雷的坐标(行列)：");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col) {
			if (mine_board[x][y] == '+') {
				show_board[x][y] = '#';
				system("cls");
				printf("*************************************\n"
					   "*********   很遗憾，扫雷失败  *******\n"
					   "*************************************\n");
				printf("棋盘：\n");
				print_board(show_board, ROW, COL);
				printf("雷区：\n");
				print_board(mine_board, ROW, COL);
				break;
			}
			else if (show_board[x][y] != '*') {
				printf("此坐标已扫过，请重新输入坐标\n");
			}
			else {
				mine_do(mine_board, show_board, x, y);
				if (win_check(show_board, row, col)) {
					system("cls");
					printf("*************************************\n"
						   "********   扫雷成功了！！！  ********\n"
					       "*************************************\n");
					printf("棋盘：\n");
					print_board(show_board, ROW, COL);
					printf("雷区：\n");
					print_board(mine_board, ROW, COL);
					break;
				}
				system("cls");
				print_board(show_board, ROW, COL);
			}
		}
		else {
			printf("此坐标不存在，请重新输入\n");
		}
	}
}

void mine_do(char mine_board[ROWS][COLS], char show_board[ROWS][COLS], int x, int y)
{
	if (count_board_mine(mine_board, show_board, x, y) == '0' && show_board[x][y] != ' ') {
		show_board[x][y] = ' ';
		int i;
		for (i = x - 1; i <= x + 1; i++) {
			int j;
			for (j = y - 1; j <= y + 1; j++) {
				if (i != x || j != y) {
					if (i >= 1 && i <= ROW && j >= 1 && j <= COL) {
						mine_do(mine_board, show_board, i, j);
					}
				}
			}
		}
	}
}

char count_board_mine(char mine_board[ROWS][COLS], char show_board[ROWS][COLS], int x, int y)
{
	char cnt = '0';
	int m;
	for (m = x - 1; m <= x + 1; m++) {
		int n;
		for (n = y - 1; n <= y + 1; n++) {
			if (mine_board[m][n] == '+') {
				cnt++;
			}
		}
	}
	if (cnt != '0') {
		show_board[x][y] = cnt;
	}
	return cnt;
}

int win_check(char show_board[ROWS][COLS], int row, int col)
{
	int cnt = 0;
	int i;
	for (i = 1; i <= row; i++) {
		int j;
		for (j = 1; j <= col; j++) {
			if (show_board[i][j]=='*') {
				cnt++;
			}
		}
	}

	return (cnt == MINE_NUMBER) ? 1 : 0;
}