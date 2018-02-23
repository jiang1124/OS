/*
分页存储管理系统；建立一个基本分页存储管理系统的模型。
	1.首先分配一片较大的内存空间，作为程序运行的可用存储空间；
	2.建立应用程序的模型；
	3.建立进程的基本数据结构及相应算法；
	4.建立管理存储空间的基本存储结构；
	5.建立管理分页的基本数据结构与算法；
	6.设计存储空间的分配与回收算法；
	7.提供信息转储功能，可将存储信息存入磁盘，也可从磁盘读入。
*/


#include<iostream>
using namespace std;

#define max_ram 100 //物理块(页框)总数
#define name_str 10
#define paper_size 4096 //页面大小

//分配一片较大的内存空间，作为程序运行的可用存储空间，建立管理存储空间的基本存储结构
int ram_flag[max_ram] = { 0 };
int sum = max_ram;//未使用物理块数
//进程的基本数据结构
struct process
{
	int NO;//进程编号
	char pro_name[name_str];//名字
	int pro_size;//大小
	int count;//进程页面数
	struct process *next;
};
//应用程序的模型的基本数据结构
struct app
{
	char app_name[name_str];//名字 
	int app_size;//大小
	int pro_sum;//进程数
	process *pro;//进程
	string pro_order;//进程调用顺序
};
//PCB
int pcb[max_ram];//下标为进程编号，对应值为该进程页表初始地址
//页表
int paper[max_ram];//下标为页号，对应值为其储存的物理块

int create_process(process *pro, int NO)
{
	cout << "————————————————" << endl;
	process * pro_1;
	pro_1 = (process *)malloc(sizeof(process));
	pro_1->next = NULL;
	pro_1->NO = NO;
	cout << "请输入进程名：";
	cin >> pro_1->pro_name;
	cout << "请输入进程大小：";
	cin >> pro_1->pro_size;
	pro_1->count = pro_1->pro_size / paper_size;
	if ((pro_1->pro_size % paper_size) > 0)
		pro_1->count += 1;
	pro->next = pro_1;
	cout << "————————————————" << endl;
	NO += 1;
	return NO;
}

void showme(process *pro_0)
{
	process *l;
	l = pro_0->next;
	cout << "进程编号	进程名	进程大小	页面数" << endl;
	while (l)
	{
		cout << l->NO << "		" << l->pro_name << "		" << l->pro_size << "		" << l->count << endl;
		l = l->next;
	}
}


int main() {
	int NO = 0;
	int s = 1;
	process *pro;
	pro = (process *)malloc(sizeof(process));
	pro->next = NULL;
	process * pro_0;
	pro_0 = pro;
	while (s!=9)
	{
		cout << "**********分页存储管理系统模型**********" << endl;
		cout << "1.创建程序" << endl;
		cout << "2.删除程序" << endl;
		cout << "3.查看内存使用情况" << endl;
		cout << "4.查看进程" << endl;
		cout << "9.退出" << endl;
		cout << "****************************************" << endl;
		cout << "请选择操作：";
		cin >> s;
		if (s != 9)
		{
			switch (s)
			{
			case 1:
				NO = create_process(pro, NO);
				pro = pro->next;
				showme(pro_0);
				break;
			default:
				break;
			}
		}
		else
			break;
	}
	return 0;
}
