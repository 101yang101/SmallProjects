#include "traffic.h"

int main()
{
	double price[7][7] =
	{
		0, 885, 202, 225, INF, INF, INF,
		885, 0, 148, INF, 283, INF, INF,
		202, 148, 0, 112, INF, 495, INF,
		225, INF, 112, 0, INF, INF, 162,
		INF, 283, INF, INF, 0, 684, INF,
		INF, INF, 495, INF, 684, 0, 386,
		INF, INF, INF, 162, INF, 386, 0
	};
	double time[7][7] =
	{
		0, 8, 2.3, 2.5, INF, INF, INF,
		8, 0, 1.5, INF, 3, INF, INF,
		2.3, 1.5, 0, 1.2, INF, 5, INF,
		2.5, INF, 1.2, 0, INF, INF, 2,
		INF, 3, INF, INF, 0, 7, INF,
		INF, INF, 5, INF, 7, 0, 4,
		INF, INF, INF, 2, INF, 4, 0
	};
	double distance[7][7] =
	{
		0, 2553, 695, 704, INF, INF, INF,
		2553, 0, 511, INF, 812, INF, INF,
		695, 511, 0, 349, INF, 1579, INF,
		704, INF, 349, 0, INF, INF, 651,
		INF, 812, INF, INF, 0, 2368, INF,
		INF, INF, 1579, INF, 2368, 0, 1385,
		INF, INF, INF, 651, INF, 1385, 0
	};
	int n = 7;						// 图的点数
	int e = 10;						// 图的边数

    MatGraph* G = (MatGraph*)malloc(sizeof(MatGraph));
    MatGraph* A = (MatGraph*)malloc(sizeof(MatGraph));

    CreateMatGraph(G, price, time, distance, n, e);		// 创建邻接矩阵
    
    //DispMap(A);
    //ShortPath(G, A, 1, 6);

    int op;                         // 操作数
    while (1) 
    {
        printf("*************交通查询系统*************\n");
        printf("======================================\n");
        printf("\t1.显示所有路径\n");
        printf("\t2.查询两个城市往返的最优方案\n");;
        printf("\t3.添加新的城市\n");
        printf("\t4.删除已有的城市\n");
        printf("\t5.编辑已有的路径\n");
        printf("\t6.退出\n");
        printf("======================================\n");
        printf("请选择：");
        cin >> op;
        while (op > 6 || op < 1)
        {
            printf("输入错误！请重新输入：");
            cin >> op;
        }
        switch (op) {
        case 1: {
            A = Floyed(G);
            DispMap(A);
            printf("\n\n");
            break;
        }
        case 2: {
            A = Floyed(G);
            ShortPath(G, A, 1, 6);
            printf("\n");
            break;
        }
        case 3: {
            add(G);
            printf("已成功添加新的城市！\n\n");
            break;
        }
        case 4: {
            move(G);
            printf("\n");
            break;
        }
        case 5: {
            edit(G);
            printf("已成功编辑城市！\n\n");
            printf("\n");
            break;
        }
        }
        if (op == 6) break;
    }

	return 0;
}