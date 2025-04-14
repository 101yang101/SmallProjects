#pragma once
#include <malloc.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

#define MAXV 1000				// 最大顶点个数
#define INF 32767

typedef struct
{
	int no;						// 城市的编号
	char city[20];				// 城市名称
	int transfer_count;			// 中转次数
	int pre;					// 前驱结点在队列中的编号
} VertexType;

typedef struct
{
	double price;				// 某地到某地的花费
	double time;				// 时间
	double distance;			// 距离
} Info;

typedef struct
{
	//int edges[MAXV][MAXV];		// 邻接矩阵数组
	int n;						// 结点数（城市个数）
	int e;						// 边数
	//string city;			// 城市的名字
	Info weight[MAXV][MAXV];	// 由各种信息构成的邻接矩阵

	int distance_path[MAXV][MAXV];		// 存放 Floyed算法 得出的路径
	int price_path[MAXV][MAXV];
	int time_path[MAXV][MAXV];

	VertexType vexs[MAXV];		// 存放顶点信息
} MatGraph;						// 完整的图邻接矩阵类型


void CreateMatGraph(MatGraph*& G, double price[7][7], double time[7][7], double distance[7][7], int n, int e);	// 创建邻接矩阵
MatGraph* Floyed(MatGraph*& G);
void DispMap(MatGraph* G);
void ShortPath(MatGraph* G, MatGraph* A, int start, int end);					// 求一点到另一点的最短路径

void add(MatGraph*& G);		// 添加新城市
void move(MatGraph*& G);	// 删除已有的城市
void edit(MatGraph*& G);	// 编辑已有的城市
