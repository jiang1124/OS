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
#include<iomanip>
#include<string>
#include<fstream>
using namespace std;

#define max_ram 100 //物理块(页框)
#define name_str 20
#define paper_size 4096 //页面大小

//分配内存空间，作为程序运行的可用存储空间，建立管理存储空间的基本存储结构
int ram[max_ram];
int no_use = max_ram, flag = 0;//未使用物理块数,物理块标记
//进程的基本数据结构
struct process
{
	int NO;//进程编号
	int count;//进程页面数
	char pro_name[name_str];
	int page[max_ram];//页表,下标为页号，对应值为其储存的物理块
	struct process *next;
};
//应用程序的模型的基本数据结构
struct program
{
	char program_name[name_str];//名字 
	int program_size;//大小
	program *next;
};
//打印内存情况
void show_ram(int ram[],int no_use,int flag)
{
	cout << "————————————————" << endl;
	cout << "未使用物理块数目：" << no_use << "   物理块标记位置" << flag << endl;
	cout << "内存使用情况：" << endl;
	for (int j = 0; j < max_ram; j++)
	{
		cout << right << setw(8) << ram[j];
		if (j%10 == 9)
			cout << endl;
	}
	cout << "————————————————" << endl;
}
//打印进程情况
void show_process(process *pro_0)
{
	cout << "————————————————" << endl;
	process *l;
	l = pro_0->next;
	cout << left << setw(10) << "进程编号" << setw(name_str) << "进程名" << setw(10) << "页面数" << setw(20) << "所在页框" << endl;
	while (l)
	{
		cout << left << setw(10) << l->NO << setw(name_str) << l->pro_name << setw(10) << l->count;
		for (int j = 0; l->page[j] != -1 && j < max_ram; j++)
		{
			cout << setw(4) << l->page[j] << ",";
			if (j % 10 == 9)
			{
				cout << endl;
				for (int i = 0; i < name_str + 20; i++)
					cout << " ";
			}
		}
		cout << endl;
		l = l->next;
	}
	cout << "————————————————" << endl;
}
//打印程序情况
void show_program(program *app_0) {
	cout << "————————————————" << endl;
	program *l;
	l = app_0->next;
	cout << left << setw(20) << "程序名" << setw(15) << "程序大小" << endl;
	while (l)
	{
		cout << left << setw(20) << l->program_name << setw(15) << l->program_size << endl;
		l = l->next;
	}
	cout << "————————————————" << endl;
}
//创建程序的基本算法
void create_app(program *app_0,char app_name[])
{
	program *app = app_0;
	bool flag_c_a = true;
	while (true)
	{
		if (strcmp(app->program_name,app_name)==0)
			flag_c_a = false;
		if (app->next == NULL)
			break;
		else
			app = app->next;
	}
	if (flag_c_a)
	{
		program *app_1;
		app_1 = (program*)malloc(sizeof(program));
		app_1->next = NULL;
		int i = 0;
		while (app_name[i] != '\0')
		{
			app_1->program_name[i] = app_name[i];
			i++;
		}
		if (i < name_str)
			app_1->program_name[i] = '\0';
		cout << "请输入程序大小：";
		cin >> app_1->program_size;
		app->next = app_1;
	}
	else
		cout << "已创建同名程序！" << endl;
	cout << "————————————————" << endl;
}
//创建进程的基本算法
int create_process(process *pro_0, program*app_0,char name_0[],int NO)
{
	process *pro = pro_0;
	program *app = app_0->next;
	bool flag_c_p1 = false ;
	bool flag_c_p2 = true;
	while (true)
	{
		if (strcmp(pro->pro_name, name_0) == 0)
			flag_c_p2 = false;
		if (pro->next == NULL)
			break;
		else
			pro = pro->next;
	}
	if (flag_c_p2)
	{
		while (app)
		{
			if (strcmp(app->program_name, name_0)==0)
			{
				flag_c_p1 = true;
				break;
			}
			else
				app = app->next;
		}
		if (flag_c_p1)
		{
			process * pro_1;
			pro_1 = (process *)malloc(sizeof(process));
			pro_1->next = NULL;
			pro_1->NO = NO;
			pro_1->count = app->program_size / paper_size;
			if ((app->program_size % paper_size) > 0)
				pro_1->count += 1;
			if (pro_1->count <= no_use)
			{
				int i = 0;
				while (app->program_name[i] != '\0')
				{
					pro_1->pro_name[i] = app->program_name[i];
					i++;
				}
				if (i < name_str)
					pro_1->pro_name[i] = '\0';
				int j = 0;
				for (; j < pro_1->count; j++)
				{
					while (ram[flag] != 0)
						flag = (flag + 1) % max_ram;
					no_use -= 1;
					pro_1->page[j] = flag;
					ram[flag] = 1;
				}
				if (j < max_ram)
					pro_1->page[j] = -1;
				pro->next = pro_1;
				NO += 1;
				cout << "创建成功！" << endl;
			}
			else
				cout << "#内存不足！#" << endl;
		}
		else
			cout << "#找不到该程序！#" << endl;
	}
	else
		cout << "已创建同名进程！" << endl;
	cout << "————————————————" << endl;
	return NO-1;
}
//删除进程
void delete_process(process *pro_0, char pro_name[])
{
	process*pro = pro_0;
	process*pro_1 = pro;
	bool flag_d_p = false;
	while (true)
	{
		if (strcmp(pro->pro_name, pro_name) == 0)
		{
			flag_d_p = true;
			break;
		}
		if (pro->next == NULL)
			break;
		else
		{
			pro_1 = pro;
			pro = pro->next;
		}
	}
	if (flag_d_p)
	{
		for (int i = 0; pro->page[i] != -1 && i < max_ram; i++)
		{
			ram[pro->page[i]] = 0;
			no_use += 1;
		}
		pro_1->next = pro->next;
		free(pro);
		cout << "该进程删除成功！" << endl;
	}
	else
		cout << "该进程未创建！" << endl;
	cout << "————————————————" << endl;
}
//删除程序
void delete_program(program*app_0, char app_name[], process *pro_0)
{
	program *app = app_0;
	program *app_1 = app;
	bool flag_d_a = false;
	while (true)
	{
		if (strcmp(app->program_name, app_name) == 0)
		{
			flag_d_a = true;
			break;
		}
		if (app->next == NULL)
			break;
		else
		{
			app_1 = app;
			app = app->next;
		}
	}
	if (flag_d_a)
	{
		cout << "&&";
		delete_process(pro_0, app_name);
		cout << "&&";
		app_1->next = app->next;
		free(app);
		cout << "该程序删除成功！" << endl;
	}
	else
		cout << "该程序未创建！" << endl;
	cout << "————————————————" << endl;
}
//转存信息
void out(program*app_0, process*pro_0)
{
	cout << "————————————————" << endl;
	string file_name;
	ofstream write;
	program *app = app_0->next;
	process *pro = pro_0->next;
	cout << "请输入文件名：";
	cin >> file_name;
	write.open(file_name.c_str(),ios::trunc);
	if(write.bad())
		cerr << "打开文件" << file_name << "失败" << endl;
	else {
		write << "program" << '\n';
		while (app)
		{
			write << app->program_name << '\t' << app->program_size << '\n';
			app = app->next;
		}
		write << "process" << '\n';
		while (pro)
		{
			write << pro->pro_name << '\t' << pro->count << '\t';
			for (int i = 0; pro->page[i] != -1 && i < max_ram; i++)
				write << pro->page[i] << '\0';
			write << '\n';
			pro = pro->next;
		}
		write << "ram" << '\n';
		for (int j = 0; j < max_ram; j++)
		{
			write << ram[j] << '\0';
		}
		write.close();
		cout << "转存完成！" << endl;
	}
	cout << "————————————————" << endl;
}
//读入信息
int in(program*app_0, process*pro_0,int NO)
{
	cout << "————————————————" << endl;
	string file_name, line;
	ifstream read;
	program*app = app_0;
	process*pro = pro_0;
	cout << "请输入文件名：";
	cin >> file_name;
	read.open(file_name.c_str(), ios::in);
	if (!read)
		cerr << "打开文件" << file_name << "失败" << endl;
	else 
	{
		getline(read, line);
		if (line == "program")
		{
			while (!read.eof())
			{
				program *app_1;
				app_1 = (program*)malloc(sizeof(program));
				app_1->next = NULL;
				getline(read, line);
				if (line != "process")
				{
					int i = 0;
					for (; i < line.length() && line[i] != '\t'; i++)
						app_1->program_name[i] = line[i];
					if (i < name_str)
						app_1->program_name[i] = '\0';
					i++;
					char buff0[8];
					for (int j = 0; j < 8 && i < line.length(); j++)
					{
						buff0[j] = line[i];
						i++;
					}
					app_1->program_size = atof(buff0);
					app->next = app_1;
					app = app_1;
				}
				else
					break;
			}
			while (!read.eof())
			{
				process *pro_1;
				pro_1 = (process*)malloc(sizeof(process));
				pro_1->next = NULL;
				getline(read, line);
				if (line != "ram")
				{
					int i = 0;
					pro_1->NO = NO;
					NO += 1;
					for (; i < line.length() && line[i] != '\t'; i++)
						pro_1->pro_name[i] = line[i];
					if (i < name_str)
						pro_1->pro_name[i] = '\0';
					i++;
					char buff1[8];
					for (int j = 0; j < 8 && i < line.length()&&line[i]!='\t'; j++)
					{
						buff1[j] = line[i];
						i++;
					}
					pro_1->count = atof(buff1);
					i++;
					int m = 0;
					for (; i < line.length(); i++)
					{
						char buff2[4];
						for (int n = 0; n < 4 && i < line.length(); n++)
						{
							if (line[i] != '\0')
							{
								buff2[n] = line[i];
								i++;
							}
							else
								break;
						}
						pro_1->page[m] = atof(buff2);
						m++;
					}
					if (m < max_ram)
						pro_1->page[m] = -1;
					pro->next = pro_1;
					pro = pro_1;
				}
				else
					break;
			}
			while (!read.eof())
			{
				getline(read, line);
				int j = 0;
				for (int i=0;i<line.length();i++)
				{
					if (line[i] != '\0')
					{
						if (line[i] == '1')
						{
							ram[j] = 1;
							no_use -= 1;
						}
						else
							ram[j] = 0;
						j++;
					}
				}
			}
		}
		read.close();
		cout << "读入完成！" << endl;
		show_program(app_0);
		show_process(pro_0);
		show_ram(ram,no_use,flag);
	}
	cout << "————————————————" << endl;
	return NO;
}
//退出
void exit(program*app_0, process*pro_0)
{

	program *app = app_0->next;
	char app_name[name_str];
	bool flag_d_a = false;
	while (app)
	{
		int i = 0;
		for (; i < name_str; i++)
		{
			app_name[i] = app->program_name[i];
		}
		if (i < name_str)
			app_name[i] = '\0';
		cout << "&&";
		delete_process(pro_0, app_name);
		app_0->next = app->next;
		free(app);
		app = app_0->next;
	}
}
int main() {
	int NO = 0;
	char s = '1';
	program *app;
	app = (program*)malloc(sizeof(program));
	app->next = NULL;
	process *pro;
	pro = (process*)malloc(sizeof(process));
	pro->next = NULL;
	while (s!='0')
	{
		cout << "**********分页存储管理系统模型**********" << endl;
		cout << "*        1.创建程序                    *" << endl;
		cout << "*        2.创建进程                    *" << endl;
		cout << "*        3.查看内存使用情况            *" << endl;
		cout << "*        4.查看程序                    *" << endl;
		cout << "*        5.查看进程                    *" << endl;
		cout << "*        6.删除程序                    *" << endl;
		cout << "*        7.删除进程                    *" << endl;
		cout << "*        8.转存存储信息                *" << endl;
		cout << "*        9.读入存储信息                *" << endl;
		cout << "*        0.退出                        *" << endl;
		cout << "****************************************" << endl;
		cout << "请选择操作：";
		cin >> s;
		if (s != 0)
		{
			switch (s)
			{
			case'0':
				cout << "————————————————" << endl;
				exit(app, pro);
				cout << "————————————————" << endl;
				break;
			case '1':
				cout << "————————————————" << endl;
				cout << "请输入程序名：";
				char name1[name_str];
				cin >> name1;
				create_app(app,name1);
				show_program(app);
				break;
			case '2':
				cout << "————————————————" << endl;
				char name2[name_str];
				cout << "请输入程序名：";
				cin >> name2;
				NO = create_process(pro, app, name2, NO) + 1;
				show_process(pro);
				break;
			case '3':
				show_ram(ram, no_use, flag);
				break;
			case '4':
				show_program(app);
				break;
			case '5':
				show_process(pro);
				break;
			case '6':
				cout << "————————————————" << endl;
				char name3[name_str];
				cout << "请输入要删除的程序名：";
				cin >> name3;
				delete_program(app, name3, pro);
				show_program(app);
				break;
			case '7':
				cout << "————————————————" << endl;
				char name4[name_str];
				cout << "请输入要删除的进程名：";
				cin >> name4;
				delete_process(pro, name4);
				show_process(pro);
				break;
			case '8':
				out(app, pro);
				break;
			case '9':
				NO = in(app, pro, NO);
				break;
			default:
				cout << "无效操作！" << endl;
				break;
			}
		}
		else
			break;
	}
	return 0;
}
