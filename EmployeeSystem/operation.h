#pragma once
#include "formal.h"
#include "informal.h"
#include <fstream>
#include <string>

typedef string Database;

char getInput();										// 获取从控制台输入的数据

void newFile(Database&, Formal*&, Informal*&);			// 新建文件, 打开文件不需要生成输出流, 只要保存输入流就好了

void openFile(Database&, Formal*&, Informal*&);			// 打开文件

void saveFile(Database&, Formal*, Informal*);			// 保存文件

void inputStaff(Formal*&, Informal*&);					// 输入函数, 输入一个员工信息并插入到链表尾

void edit(Formal*, Informal*);							// 修改成员信息, 并询问用户是否需要保存

void count(Formal*, Informal*);							// 统计实发工资总额以及平均工资

void quit(Database&, Formal*, Informal*);				// 退出程序, 并询问是否需要保存

void del(Formal*, Informal*, Formal*&, Informal*&);		// 删除员工信息, 并可以保存

void recover(Formal*, Informal*, Formal*, Informal*);	// 恢复所有被删除的员工信息

void openRecoverFile(Formal*& f, Informal*& i);			// 打开回收站

void saveRecoverFile(Formal*& f, Informal*& i);			// 保存回收站的信息

void search(Formal*, Informal*);						// 搜索是否存在某一个id, name

void show(Formal* f, Informal* i);						// 缩略版的sort

void printMenu();										// 打印菜单