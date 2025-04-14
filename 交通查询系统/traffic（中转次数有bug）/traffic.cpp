#include "traffic.h"

// 创建邻接矩阵
void CreateMatGraph(MatGraph*& G, double price[7][7], double time[7][7], double distance[7][7], int n, int e)
{
	G->n = n;									// 初始化结点数
	G->e = e;									// 初始化边数

	strcpy_s(G->vexs[0].city, "北京");
	strcpy_s(G->vexs[1].city, "西安");
	strcpy_s(G->vexs[2].city, "郑州");
	strcpy_s(G->vexs[3].city, "徐州");
	strcpy_s(G->vexs[4].city, "成都");
	strcpy_s(G->vexs[5].city, "广州");
	strcpy_s(G->vexs[6].city, "上海");

	for (int i = 0; i < n; i++)					// 初始化路径
	{
		G->vexs[i].no = i;
		for (int j = 0; j < n; j++)
		{
			G->weight[i][j].price = price[i][j];
			G->weight[i][j].time = time[i][j];
			G->weight[i][j].distance = distance[i][j];
			if (i != j && G->weight[i][j].distance < INF) // 最短路径终点的前驱（顶点 i 到 j 有边时）
				G->distance_path[i][j] = G->price_path[i][j] = G->time_path[i][j] = i;	
			else
				G->distance_path[i][j] = G->price_path[i][j] = G->time_path[i][j] = -1;
		}
			
	}
}

MatGraph* Floyed(MatGraph*& G)
{
	MatGraph* A = (MatGraph*)malloc(sizeof(MatGraph));
	*A = *G;
	for (int k = 0; k < G->n; k++)
	{
		for (int i = 0; i < G->n; i++)
			for (int j = 0; j < G->n; j++)
			{
				if (A->weight[i][j].distance > A->weight[i][k].distance + A->weight[k][j].distance) {
					A->weight[i][j].distance = A->weight[i][k].distance + A->weight[k][j].distance;
					A->distance_path[i][j] = A->distance_path[k][j];
				}
				if (A->weight[i][j].price > A->weight[i][k].price + A->weight[k][j].price) {
					A->weight[i][j].price = A->weight[i][k].price + A->weight[k][j].price;
					A->price_path[i][j] = A->price_path[k][j];
				}
				if (A->weight[i][j].time > A->weight[i][k].time + A->weight[k][j].time) {
					A->weight[i][j].time = A->weight[i][k].time + A->weight[k][j].time;
					A->time_path[i][j] = A->time_path[k][j];
				}
			}
	}

	return A;
}

void DispMap(MatGraph* G)
{
	for (int i = 0; i < G->n; i++)
	{
		for (int j = i + 1; j < G->n; j++)
		{
			if (G->weight[i][j].distance != INF)
			{
				cout << G->vexs[i].city << " <-> " << G->vexs[j].city << '\t';
				cout << "最短路程为：" << G->weight[i][j].distance << "公里" << '\t';
				cout << "最低价格为：" << G->weight[i][j].price << "元" << '\t';
				cout << "最少时间为：" << G->weight[i][j].time << "小时" << endl;
			}
		}
	}
}

void ShortPath(MatGraph* G, MatGraph* A, int start, int end)
{
	int k, s;
	int d;													// 存放路径的中间顶点个数
	int distance_apath[MAXV];								// 存放路程最短的路径
	int price_apath[MAXV];									// 存放花销最低的路径
	int time_apath[MAXV];									// 存放耗时最少的路径

	if (A->weight[start][end].distance != INF && start != end)
	{
		cout << A->vexs[start].city << " -> " << A->vexs[end].city << " 最短路程路径：";
		k = A->distance_path[start][end];
		d = 0;
		distance_apath[d] = end;							// 路径上添加终点
		while (k != start)						// 路径上添加中间点
		{
			d++;
			distance_apath[d] = k;
			k = A->distance_path[start][k];
		}
		d++;
		distance_apath[d] = start;						// 路径上添加起点
		cout << A->vexs[distance_apath[d]].city << ' ';	// 输出起点
		for (s = d - 1; s >= 0; s--)			// 输出路径上的中间顶点
			cout << "-> " << A->vexs[distance_apath[s]].city << ' ';
		cout << "\t路程：" << A->weight[start][end].distance << endl;
	}

	if (A->weight[start][end].price != INF && start != end)
	{
		cout << A->vexs[start].city << " -> " << A->vexs[end].city << " 最低花销路径：";
		k = A->price_path[start][end];
		d = 0;
		price_apath[d] = end;							// 路径上添加终点
		while (k != start)						// 路径上添加中间点
		{
			d++;
			price_apath[d] = k;
			k = A->price_path[start][k];
		}
		d++;
		price_apath[d] = start;						// 路径上添加起点
		cout << A->vexs[price_apath[d]].city << ' ';	// 输出起点
		for (s = d - 1; s >= 0; s--)			// 输出路径上的中间顶点
			cout << "-> " << A->vexs[price_apath[s]].city << ' ';
		cout << "\t花销：" << A->weight[start][end].price << endl;
	}

	if (A->weight[start][end].time != INF && start != end)
	{
		cout << A->vexs[start].city << " -> " << A->vexs[end].city << " 最少耗时路径：";
		k = A->time_path[start][end];
		d = 0;
		time_apath[d] = end;							// 路径上添加终点
		while (k != start)						// 路径上添加中间点
		{
			d++;
			time_apath[d] = k;
			k = A->time_path[start][k];
		}
		d++;
		time_apath[d] = start;						// 路径上添加起点
		cout << A->vexs[time_apath[d]].city << ' ';	// 输出起点
		for (s = d - 1; s >= 0; s--)			// 输出路径上的中间顶点
			cout << "-> " << A->vexs[time_apath[s]].city << ' ';
		cout << "\t耗时：" << A->weight[start][end].time << endl;
	}



	// 最少中转次数路径
	MatGraph* T = (MatGraph*)malloc(sizeof(MatGraph));
	*T = *G;
	for (int i = 0; i < G->n; ++i)
	{
		for (int j = 0; j < G->n; ++j)
		{
			if (T->weight[i][j].distance != INF && T->weight[i][j].distance != 0)
				T->weight[i][j].distance = 1;
			T->distance_path[i][j] = j;
		}
	}


	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			cout << T->weight[i][j].distance << ' ';
		}
		cout << endl;
	}
	cout << endl;



	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			cout << T->distance_path[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;

	for (int k = 0; k < G->n; k++)
	{
		for (int i = 0; i < G->n; i++)
		{
			for (int j = 0; j < G->n; j++)
			{
				if (T->weight[i][j].distance > T->weight[i][k].distance + T->weight[k][j].distance)
				{//如果经过下标为k顶点路径比原两点间路径更短
					T->weight[i][j].distance = T->weight[i][k].distance + T->weight[k][j].distance;//将当前两点间权值设为更小的一个
					T->distance_path[i][j] = T->distance_path[i][k];//路径设置为经过下标为k的顶点
				}
			}
		}
	}

	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			cout << T->distance_path[i][j] << ' ';
		}
		cout << endl;
	}

	if (T->weight[start][end].distance != INF && start != end)
	{
		cout << T->vexs[start].city << " -> " << T->vexs[end].city << " 最少中转路径：";
		cout << start << ' ' << end << endl;
		k = T->distance_path[start][end];
		d = 0;
		distance_apath[d] = end;							// 路径上添加终点
		while (k != start)						// 路径上添加中间点
		{
			d++;
			distance_apath[d] = k;
			k = T->distance_path[start][k];
			cout << k << endl;
		}
		d++;
		distance_apath[d] = start;						// 路径上添加起点
		cout << T->vexs[distance_apath[d]].city << ' ';	// 输出起点
		for (s = d - 1; s >= 0; s--)			// 输出路径上的中间顶点
			cout << "-> " << T->vexs[distance_apath[s]].city << ' ';
		cout << "\t耗时：" << T->weight[start][end].distance << endl;
	}

	//// 通过广度优先遍历得到最少中转次数
	//VertexType* que = new VertexType[MAXV];
	//int enque_sign[MAXV] = { 0 };				// 标记是否已进队
	//int head = 0;
	//int tail = 0;
	//int temp = 0;								// 用于队列中进行循环
	//int judge = 0;								// 是否到达目标城市，若到达则停止输出

	//// 从初始地出发，将其加入队列
	//que[tail].no = start;
	//que[tail].transfer_count = 0;
	//que[tail].pre = -1;
	//tail++;
	//enque_sign[start] = 1;

	//// 当队列不为空时进行循环
	//while (head < tail)
	//{
	//	int temp = que[head].no;				// 当前队列中队头编号
	//	for (int i = 0; i < G->n; i++)
	//	{
	//		if (G->weight[temp][i].distance < INF && enque_sign[i] == 0) {
	//			que[tail].no = i;				// 入队
	//			que[tail].transfer_count = que[head].transfer_count + 1;	// 中转次数加1
	//			que[tail].pre = temp;			// 将入队的点连接到对应的前驱
	//			tail++;
	//			enque_sign[i] = 1;				// 已入队标记
	//		}
	//		if (que[tail - 1].no == end) {		// 到达目的地，退出循环
	//			judge = 1;
	//			break;
	//		}
	//	}
	//	if (judge)
	//		break;
	//	head++;
	//}

	//// 输出最少中转次数及对应的路径
	//int min_transfer_count = que[tail - 1].transfer_count - 1;		// 最少中转次数
	//int rear = tail - 1;
	//int apath[MAXV], p = 0;
	//cout << G->vexs[start].city << " -> " << G->vexs[end].city << ' ';
	//cout << "最少中转路径：";
	//while (true)
	//{
	//	if (que[rear].pre != -1) {
	//		apath[p] = que[rear].no;
	//		p++;
	//	}
	//	else {
	//		apath[p] = que[rear].no;
	//		break;
	//	}
	//	rear = que[rear].pre;
	//}

	//while (p >= 0)
	//{
	//	if (p == 0) {
	//		cout << G->vexs[apath[p]].city << endl;
	//		break;
	//	}
	//	cout << G->vexs[apath[p]].city << " -> ";
	//	p--;
	//}
	//delete[]que;
}

//检查输入的城市是否存在在数组中
bool city_exist(MatGraph* G, char city[]) 
{
	bool judge = false;
	for (int i = 0; i < G->n; i++) 
	{
		if (strcmp(G->vexs[i].city, city) == 0) {
			judge = true;
			break;
		}
	}
	return judge;
}

//城市索引值，用于通过城市名字找到这个城市的数组中的索引序号
int index_num(MatGraph* G, char city[]) 
{
	int i, city1;
	for (i = 0; i <= G->n; i++) {//遍历顶点，对比值，找到对应的索引下标
		if (strcmp(city, G->vexs[i].city) == 0)
		{
			city1 = G->vexs[i].no;
			break;
		}
	}
	return city1;
}

//添加新城市
void add(MatGraph*& G) 
{
	int city_num;		// 修改后的城市数量
	int c;
	double distance, price, time;
	char city1[20], city2[20];
	G->n++;
	city_num = G->n;
	printf("请输入需要添加的新城市：");
	cin >> city1;

	while (city_exist(G, city1) == 1) 
	{
		printf("该城市已经存在！请重新输入：");
		cin >> city1;
	}
	strcpy_s(G->vexs[city_num - 1].city, city1);
	G->vexs[city_num - 1].no = city_num - 1;


	printf("请输入需要添加的路线数：");
	cin >> c;
	G->e = G->e + c;
	G->weight[city_num - 1][city_num - 1].distance = 0;//初始化距离
	G->weight[city_num - 1][city_num - 1].price = 0;
	G->weight[city_num - 1][city_num - 1].time = 0;

	for (int i = 0; i < G->n - 1; i++) 
	{
		G->weight[i][city_num - 1].distance = INF;
		G->weight[city_num - 1][i].distance = INF;
		G->weight[i][city_num - 1].time = INF;
		G->weight[city_num - 1][i].time = INF;
		G->weight[i][city_num - 1].price = INF;
		G->weight[city_num - 1][i].price = INF;
	}

	//修改矩阵
	for (int i = 0; i < c; i++) 
	{
		printf("请输入第%d个存在路线的城市：", i + 1);
		cin >> city2;
		while (1) 
		{
			if (city_exist(G, city2)) 
				break;
			else {
				printf("该城市不存在！请重新输入！\n");
				printf("请输入存在路线城市：");
				cin >> city2;
			}
		}

		int id;
		id = index_num(G, city2);

		printf("请输入城市之间的距离：");
		cin >> distance;
		G->weight[city_num - 1][id].distance = distance;
		G->weight[id][city_num - 1].distance = distance;
		printf("请输入城市之间的花费：");
		cin >> price;
		G->weight[city_num - 1][id].price = price;
		G->weight[id][city_num - 1].price = price;
		printf("请输入城市交通的时间：");
		cin >> time;
		G->weight[city_num - 1][id].time = time;
		G->weight[id][city_num - 1].time = time;
	}
	for (int i = 0; i < G->n; i++)
	{
		for (int j = 0; j < G->n; j++)
		{
			cout << G->weight[i][j].distance << ' ';
		}
		cout << endl;
	}
}

//删除已有城市
void move(MatGraph*& G) 
{
	int k = 0;
	int row, col;
	char city[20];
	printf("请输入要删除的城市：");
	cin >> city;
	while (1) 
	{
		bool judge;
		judge = city_exist(G, city);
		if (judge) 
			break;
		else {
			printf("该城市不存在！请重新输入！\n");
			printf("请输入要删除的城市：");
			cin >> city;
		}
	}
	for (int i = 0; i <= G->n; i++) 
	{
		if (strcmp(city, G->vexs[i].city) == 0) {
			k = G->vexs[i].no;
			break;
		}
	}
	for (int i = 0; i < G->n; i++)
	{
		G->weight[k][i].distance = G->weight[i][k].distance = INF;
		G->weight[k][i].price = G->weight[i][k].price = INF;
		G->weight[k][i].time = G->weight[i][k].time = INF;
	}

	for (int i = k; i < G->n; i++)
		G->vexs[i] = G->vexs[i + 1];

	G->n--;
	for (int i = 0; i < G->n; i++) 
		G->vexs[i].no = i;

	for (row = k; row < G->n; row++) 
	{
		for (col = 0; col < G->n; col++) 
		{
			G->weight[row][col] = G->weight[row + 1][col];
			if (row == col)
			{
				G->weight[row][col].distance = 0;
				G->weight[row][col].price = 0;
				G->weight[row][col].time = 0;
			}
		}
	}
	for (col = k; col < G->n; col++) 
	{
		for (row = 0; row < G->n; row++) 
		{
			G->weight[row][col] = G->weight[row][col + 1];
			if (row == col)
			{
				G->weight[row][col].distance = 0;
				G->weight[row][col].price = 0;
				G->weight[row][col].time = 0;
			}
		}
	}
	printf("城市%s已删除！\n", city);
}

//编辑已有城市
void edit(MatGraph*& G) 
{
	int i, k = 0;
	double distance, price, time;
	char city1[20], city2[20];
	printf("请输入修改的城市：");
	cin >> city1;

	bool judge;
	while (1) 
	{
		judge = city_exist(G, city1);
		if (judge) break;
		else {
			printf("该城市不存在！请重新输入！\n");
			printf("请输入修改的城市：");
			cin >> city1;
		}
	}
	printf("请输入另一个城市：");
	cin >> city2;
	while (1) 
	{
		judge = city_exist(G, city2);
		if (judge == 1) break;
		else {
			printf("该城市不存在！请重新输入！\n");
			printf("请输入需要修改的城市：");
			cin >> city2;
		}
	}
	printf("请输入城市之间的距离：");
	cin >> distance;
	printf("请输入城市之间的花费：");
	cin >> price;
	printf("请输入城市交通的时间：");
	cin >> time;

	int row, col;
	row = index_num(G, city1);
	col = index_num(G, city2);
	G->weight[row][col].distance = G->weight[col][row].distance = distance;
	G->weight[row][col].price = G->weight[col][row].price = price;
	G->weight[row][col].time = G->weight[col][row].time = time;
}