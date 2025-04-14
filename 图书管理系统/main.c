#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {//书籍信息 
    int booknum;//编号 
    char bookname[10];//书名 
    int amount;//现存数量
    int borrownum;//外借数量 
}BOOK;

typedef struct  //借书清单
{
    char rbn[20]; //readerbookname 所借书名
}booklist;

typedef struct { //读者信息，假设每人最多借5本书
    int readerID; //读者编号
    char readername[20]; //读者姓名
    int num; //借阅数目 
    booklist book[5];
}Reader;

typedef struct {
    int ID;
    char name[20];
}Adminer;

BOOK books[256];
Reader person[256];
Adminer adminers[256];
int i = 0, p = 0;  //i指书的数量，p指读者数量
int v = 0;    //v指当前正在操作的用户  
//代码中的count均用作判断存在问题
FILE* np, * ip, * fp;

//管理员系统
void admin();       //管理员选择菜单
void addbook();     //添加书籍
void deletebook();  //删除书籍
void changebook();  //修改书籍信息
void searchbook();  //查找书籍
void setreader();   //录入读者信息
void deletereader(); //删除读者信息
void changereader();//修改读者信息
void searchreader();//查询读者信息
void newbook(); //更新书籍文本内容
void getbook();  //获取书籍文本内容 
void getadmin(); //获取图书管理员信息

//读者系统
void reader(char name[20]);  //读者界面
void borrow();  //借书
void back();    //还书
void newreader(); //更新读者文本内容
void getreader(); //获取读者文本内容


int main(int argc, char** argv) {
    getbook();
    getreader();
   // char arr[10] = { "\0" };
    //strcpy(arr, argv[2]);
    getadmin();
    int a;

    if (strcmp(argv[1], "-a") == 0)
    {
        int j = 0;
        for (; j < 256; j++)
        {
            if (strcmp(adminers[j].name, argv[2]) == 0)
            {
                admin();
            }
        }
        if (j == 256)
        {
            printf("无此管理员\n");
        }
    }
    else if (strcmp(argv[1], "-u") == 0)
    {
        reader(argv[2]);
    }
    return 0;
}

void getadmin()
{
   
    int i = 0;
    if ((fp = fopen("adminer.txt", "r")) == NULL)
    {
        printf("wrong\n");
        exit(0);
    }
    while (!(feof(fp)))    //读取内容
    {
        fscanf(fp, "%d%s", &adminers[i].ID, adminers[i].name);
        i++;
    }
    if (i > 0)
    {
        i--;
    }
    fclose(fp);
    fp = NULL;
}

void admin() {
    
    int c = 9;
    do
    {
        printf("\n--------图书馆管理系(administrators)-----------\n");
        printf("| 你可以选择以下操作(按下相应数字键):           |\n");
        printf("| 0.退出程序                                  |\n");
        printf("| 1.录入图书信息                              |\n");
        printf("| 2.删除图书信息                              |\n");
        printf("| 3.修改图书信息                              |\n");
        printf("| 4.查询图书信息                              |\n");
        printf("| 5.录入读者信息                              |\n");
        printf("| 6.删除读者信息                              |\n");
        printf("| 7.修改读者信息                              |\n");
        printf("| 8.查询读者信息                              |\n");
        printf("----------------------------------------------\n");
        scanf("%d", &c);
        switch (c)
        {
        case 0:
            printf("您已退出！\n");
            break;
        case 1:
            addbook();
            break;
        case 2:
            deletebook();
            break;
        case 3:
            changebook();
            break;
        case 4:
            searchbook();
            break;
        case 5:
            setreader();
            break;
        case 6:
            deletereader();
            break;
        case 7:
            changereader();
            break;
        case 8:
            searchreader();
            break;
        default:
            printf("输入异常！\n");
            break;
        }
    } while (c != 0);
}

void addbook() {
    if (i != 0)
    {
        int a, b = 0; //a来存储要添加的书的名称，b判断是否存在
        printf("请输入书的编号：\n");
        scanf("%d", &a);
        for (int j = 0; j < i; j++)
        {
            if (books[j].booknum == a)
            {
                printf("已有此书\n");
                printf("添加失败！\n");
                b++;
                break;
            }
        }
        if (b == 0)
        {
            books[i].booknum = a;
            printf("请输入书名：\n");
            scanf("%s", &books[i].bookname);
            printf("请输入要添加的数量：\n");
            scanf("%d", &books[i].amount);
            books[i].borrownum = 0;
            printf("添加成功！\n");
            i++;
        }
        newbook();
    }
    else if (i == 0)
    {
        printf("请输入书的编号：\n");
        scanf("%d", &books[i].booknum);
        printf("请输入书名：\n");
        scanf("%s", &books[i].bookname);
        printf("请输入要添加的数量：\n");
        scanf("%d", &books[i].amount);
        books[i].borrownum = 0;
        printf("添加成功！\n");
        if ((np = fopen("book.txt", "w")) == NULL)
        {
            printf("wrong\n");
            exit(0);
        }
        fprintf(np, "%d %s %d %d\n", books[i].booknum, books[i].bookname, books[i].amount, books[i].borrownum);
        i++;
        fclose(np);
    }
}

void deletebook() {
    int a, count = 0, b;
    printf("请输入要删除的ID:\n");
    scanf("%d", &a);
    for (int j = 0; j < i; j++)
    {
        if (books[j].booknum == a)
        {
            b = j;
            count++;
            break;
        }
    }
    if (count == 0)
    {
        printf("没有找到该书！\n");
    }
    else {
        if (b == i - 1)
        {
            i--;
            newbook();
        }
        else if (b < i - 1) {
            for (int c = b; c < i - 1; c++)
            {
                books[c].booknum = books[c + 1].booknum;
                books[c].amount = books[c + 1].amount;
                books[c].borrownum = books[c + 1].borrownum;
                strcpy(books[c].bookname, books[c + 1].bookname);
            }
            i--;
            newbook();
        }
        printf("删除成功！\n");
    }
}

void searchbook() {
    printf("按书名查询请按0，按ID查询请按1：\n");
    int a;
    char b[20];
    int  c;
    scanf("%d", &a);
    if (a == 0)
    {
        int count = 0;
        printf("请输入书名：\n");
        scanf("%s", &b);
        for (int j = 0; j < i; j++)
        {
            if (strcmp(books[j].bookname, b) == 0)
            {
                printf("这是寻找到的信息：\n");
                printf("编号：%d\n", books[j].booknum);
                printf("书名：%s\n", books[j].bookname);
                printf("馆存数量：%d\n", books[j].amount);
                printf("外借数量：%d\n", books[j].borrownum);
                count++;
                break;
            }
        }
        if (count == 0)
        {
            printf("没有找到该书！\n");
        }
    }
    if (a == 1)
    {
        int count = 0;
        printf("请输入书的ID：\n");
        scanf("%d", &c);
        for (int j = 0; j < i; j++)
        {
            if (books[j].booknum == c)
            {
                printf("这是寻找到的信息：\n");
                printf("编号：%d\n", books[j].booknum);
                printf("书名：%s\n", books[j].bookname);
                printf("馆存数量：%d\n", books[j].amount);
                printf("外借数量：%d\n", books[j].borrownum);
                count++;
                break;
            }
        }
        if (count == 0)
        {
            printf("没有找到该书！\n");
        }
    }
}

void changebook() {
    printf("请输入您要修改的图书编号：");
    int a, b;
    scanf("%d", &a);
    int count = 0;
    for (int j = 0; j < i; j++)
    {
        if (books[j].booknum == a)
        {
            b = j;
            count++;
            break;
        }
    }
    int c;
    if (count == 0)
    {
        printf("查无此书!\n");
    }
    else {
        do {
            printf("请选择你要修改的选项：\n");
            printf("0.退出   1.编号   2.书名   3.馆藏数量\n");
            scanf("%d", &c);
            switch (c)
            {
            case 0:
                printf("修改完毕！\n");
                break;
            case 1:
                printf("请输入新的编号：\n");
                scanf("%d", &books[b].booknum);
                break;
            case 2:
                printf("请输入新的书名：\n");
                scanf("%s", &books[b].bookname);
                break;
            case 3:
                printf("请输入新的数目：\n");
                scanf("%d", &books[b].amount);
                break;
            default:
                break;
            }
        } while (c != 0);
        newbook();
    }
}

void setreader() {
    char n[20];
    printf("请输入要添加的用户姓名：\n");
    scanf("%s", &n);
    int count =0;
    if (p == 0)
    {
        strcpy(person[0].readername, n);
        person[0].num = 0;
        printf("请安排编号：\n");
        scanf("%d", &person[0].readerID);
        if ((ip = fopen("reader.txt", "w")) == NULL)
        {
            printf("wrong\n");
            exit(0);
        }
        fprintf(ip, "%d %s %d\n", person[0].readerID, person[0].readername, person[0].num);
        p++;
        fclose(ip);
        printf("添加成功！\n");
    }
    else {
        for (int j = 0; j < p; j++)
        {
            if ((strcmp(person[j].readername, n)) == 0)
            {
                count++;
                break;
            }
        }
        if (count != 0)
        {
            printf("该用户已存在。\n");
        }
        else {
            printf("请安排编号：\n");
            scanf("%d", &person[p].readerID);
            strcpy(person[p].readername, n);
            person[p].num = 0;
            if ((ip = fopen("reader.txt", "a")) == NULL)
            {
                printf("wrong\n");
                exit(0);
            }
            fprintf(ip, "%d %s %d\n", person[p].readerID, person[p].readername, person[p].num);
            p++;
            fclose(ip);
            printf("添加成功！\n");
        }
    }
}

void deletereader() {
    printf("请输入您要删除的读者姓名：\n");
    char name[20];
    int count = 0;
    int a;
    scanf("%s", &name);
    for (int j = 0; j < p; j++)
    {
        if ((strcmp(person[j].readername, name)) == 0)
        {
            a = j;
            count++;
            break;
        }
    }
    if (count == 0)
    {
        printf("查无此人！\n");
    }
    else {
        if (a == p - 1)
        {
            for (int j = 0; j < i; j++)
            {
                for (int k = 0; k < person[a].num; k++)
                {
                    if (strcmp(books[j].bookname, person[a].book[k].rbn) == 0);
                    {
                        books[j].amount++;
                        books[j].borrownum--;
                    }
                }
            }
            p = p - 1;
            newreader();
            newbook();
            printf("删除成功！\n");
        }
        else {
            for (int j = a; j < p - 1; j++)
            {
                person[j].readerID = person[j + 1].readerID;
                strcpy(person[j].readername, person[j + 1].readername);
                person[j].num = person[j + 1].num;
                for (int k = 0; k < person[j + 1].num; k++)
                {
                    strcpy(person[j].book[k].rbn, person[j + 1].book[k].rbn);
                }
            }
            for (int j = 0; j < i; j++)
            {
                for (int k = 0; k < person[a].num; k++)
                {
                    if (strcmp(books[j].bookname, person[a].book[k].rbn) == 0);
                    {
                        books[j].amount++;
                        books[j].borrownum--;
                    }
                }
            }
            p = p - 1;
            newbook();
            newreader();
            printf("删除成功！\n");
        }
    }
}

void changereader() {
    int n, a;
    int count = 0;
    printf("请输入要修改的用户的编号：\n");
    scanf("%d", &n);
    for (int j = 0; j < p; j++)
    {
        if (person[j].readerID == n)
        {
            a = j;
            count++;
            break;
        }
    }
    if (count == 0)
    {
        printf("查无此人！\n");
    }
    else {
        int b = 1;
        do
        {
            printf("请选择要修改的信息：\n");
            printf("0.退出  1.编号  2.姓名\n");
            scanf("%d", &b);
            switch (b)
            {
            case 0:
                break;
            case 1:
                printf("请输入新的编号：\n");
                scanf("%d", &person[a].readerID);
                break;
            case 2:
                printf("请输入新的名字：\n");
                scanf("%s", &person[a].readername);
                break;
            default:
                printf("输入错误，修改失败。\n");
                break;
            }
        } while (b != 0);
        printf("修改成功！\n");
        newreader();
    }
}

void searchreader() {
    int n, a;
    int count = 0;
    printf("请输入要查询的用户的编号：\n");
    scanf("%d", &n);
    for (int j = 0; j < p; j++)
    {
        if (person[j].readerID == n)
        {
            a = j;
            count++;
            break;
        }
    }
    if (count == 0)
    {
        printf("查无此人！\n");
    }
    else {
        printf("查询结果如下：\n");
        printf("编号：%d\n", person[a].readerID);
        printf("姓名：%s\n", person[a].readername);
        printf("所借书目：\n");
        for (int k = 0; k < person[a].num; k++)
        {
            printf("%s\n", person[a].book[k].rbn);
        }
        printf("\n");
    }
}

void newbook() {
    if ((np = fopen("book.txt", "w")) == NULL)
    {
        printf("wrong\n");
        exit(0);
    }
    for (int j = 0; j < i; j++)
    {
        fprintf(np, "%d %s %d %d\n", books[j].booknum, books[j].bookname, books[j].amount, books[j].borrownum);
    }
    fclose(np);
}

void getbook() {
    //获取图书信息
    i = 0;
    if ((np = fopen("book.txt", "r")) == NULL)
    {
        printf("wrong\n");
        exit(0);
    }
    while (!(feof(np)))    //读取内容
    {
        fscanf(np, "%d%s%d%d", &books[i].booknum, &books[i].bookname, &books[i].amount, &books[i].borrownum);
        i++;
    }
    if (i > 0)
    {
        i--;
    }
    fclose(np);
    np = NULL;
}

void getreader() {
    // 获取文本中的读者信息
    p = 0;
    if ((ip = fopen("reader.txt", "r")) == NULL)
    {
        printf("wrong\n");
        exit(0);
    }
    while (!(feof(ip)))    //读取内容
    {
        fscanf(ip, "%d%s%d", &person[p].readerID, &person[p].readername, &person[p].num);
        for (int j = 0; j < person[p].num; j++)
        {
            fscanf(ip, "%s", &person[p].book[j].rbn);
        }
        p++;
    }
    if (p > 0)
    {
        p--;
    }
    fclose(ip);
    ip = NULL;
}

void reader(char name[20]) {
    int count = 0;
    for (int j = 0; j < p; j++)
    {
        if ((strcmp(person[j].readername, name)) == 0)
        {
            v = j;
            count++;
            if (person[v].num == 0)
            {
                printf("您还未借书。\n");
            }
            else {
                printf("您现在已经借了%d本书，分别是：\n", person[v].num);
                for (int k = 0; k < person[v].num; k++)
                {
                    printf("%s\n", person[v].book[k].rbn);
                }
            }
            break;
        }
    }
    if (count == 0)
    {
        printf("您还未注册，请先去管理员处注册。\n");
    }
    else {
        int c = 4;
        do
        {
            printf("\n--------图书馆管理系(reader)------------------\n");
            printf("| 你可以选择以下操作(按下相应数字键):            |\n");
            printf("| 0.退出程序                                   |\n");
            printf("| 1.借书                                      |\n");
            printf("| 2.还书                                      |\n");
            printf("----------------------------------------------\n");
            scanf("%d", &c);
            switch (c)
            {
            case 0:
                break;
            case 1:
                borrow();
                break;
            case 2:
                back();
                break;
            default:
                break;
            }
        } while (c != 0);
    }
}

void borrow() {
    if (person[v].num == 5)
    {
        printf("您现在已经不能再借书了，请尽快归还所借书目！\n");
        exit(0);
    }
    else {
        char book[20]={"\0"};
        int count = 0;
        int count2 = 0;
        printf("请输入你要借阅的书名：\n");
        scanf("%s", &book);
        for (int k = 0; k < person[v].num; k++)
        {
            if (strcmp(person[v].book[k].rbn, book) == 0)
            {
                printf("您已借过该书！\n");
                count2++;
            }
        }if (count2 == 0)
        {
            for (int j = 0; j < 256; j++)
            {
                if (strcmp(books[j].bookname, book) == 0)
                {
                    count++;
                    if (books[j].amount != 0)
                    {
                        books[j].amount--;
                        books[j].borrownum++;
                        person[v].num++;
                        int f = person[v].num;
                        strcpy(person[v].book[f - 1].rbn, book);
                        newreader();
                        newbook();
                        printf("借阅成功!\n");
                        break;
                    }
                    else {
                        printf("抱歉，库存不足！\n");
                        break;
                    }
                    break;
                }
            }
            if (count == 0)
            {
                printf("没有找到该书！\n");
            }
        }
    }
}

void back() {
    int a;
    printf("请输入你要归还的书名：\n");
    char book[20];
    scanf("%s", &book);
    int count = 0;
    int count2 = 0;
    for (int j = 0; j < person[v].num; j++)
    {
        if (strcmp(person[v].book[j].rbn, book) == 0)
        {
            a = j;
            count++;
            break;
        }
    }
    if (count == 0)
    {
        printf("您没有借过该书！\n");
    }
    else {
        for (int j = 0; j < i; j++)
        {
            if (strcmp(books[j].bookname, book) == 0) {
                books[j].amount++;
                books[j].borrownum--;
                if (a + 1 == person[v].num)
                {
                    person[v].num--;
                    newreader();
                    newbook();
                }
                else {
                    for (int j = a; j < person[v].num - 1; j++)
                    {
                        strcpy(person[v].book[j].rbn, person[v].book[j + 1].rbn);
                    }
                    person[v].num--;
                    newreader();
                    newbook();
                }
                count2++;
                printf("归还成功！\n");
            }
        }
        if (count2 == 0)
        {
            printf("图书馆已下架该书，感谢您及时归还！\n");
            if (a + 1 == person[v].num)
            {
                person[v].num--;
                newreader();
            }
            else {
                for (int j = a; j < person[v].num - 1; j++)
                {
                    strcpy(person[v].book[j].rbn, person[v].book[j + 1].rbn);
                }
                person[v].num--;
                newreader();
            }
        }
    }
}

void newreader() {
    if ((ip = fopen("reader.txt", "w")) == NULL)
    {
        printf("wrong\n");
        exit(0);
    }
    for (int j = 0; j < p; j++)
    {
        fprintf(ip, "%d %s %d ", person[j].readerID, person[j].readername, person[j].num);
        for (int k = 0; k < person[j].num; k++)
        {
            fprintf(ip, "%s ", person[j].book[k].rbn);
        }
        fprintf(ip, "\n");
    }
    fclose(ip);
}