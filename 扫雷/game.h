#pragma once

/**********游戏难度修改********//*****************/
#define MINE_NUMBER 60       //******雷数*******/
#define ROW 30              //*行数（不大于58）*/
#define COL 30             //*列数（不大于58）*/
/*************************//*****************/

#define ROWS ROW + 2
#define COLS COL + 2

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int game();
void init_board(char board[ROWS][COLS], int rows, int cols, char sign);
void print_board(char board[ROWS][COLS], int row, int col);
int put_mine(char board[ROWS][COLS], int rows, int cols, int row, int col);
void mine_sweep(char mine_board[ROWS][COLS], char show_board[ROWS][COLS], int rows, int cols, int row, int col);
char count_board_mine(char mine_board[ROWS][COLS], char show_board[ROWS][COLS], int row, int col);
void mine_do(char mine_board[ROWS][COLS], char show_board[ROWS][COLS], int x, int y);
int win_check(char show_board[ROWS][COLS], int row, int col);