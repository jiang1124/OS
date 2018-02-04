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
#include "Application.h"
using namespace std;

#define max_ram 100
#define name_str 10

//分配一片较大的内存空间，作为程序运行的可用存储空间，建立管理存储空间的基本存储结构
int ram_flag[max_ram] = { -1 };
//建立进程的基本数据结构
struct process
{
	char pro_name[name_str];//名字
	int pro_size;//大小
	int content;//进程内容
};
//建立应用程序的模型的基本数据结构
struct app
{
	char app_name[name_str];//名字 
	int app_size;//大小
	int pro_sum;//进程数
	process *pro;//进程
	int *pro_order;//进程调用顺序
};

int main() {

	return 0;
}