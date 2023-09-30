#pragma once
#include <iostream>
#include <fstream>
using namespace std;

enum Type {
	FORMAL,
	INFORMAL
};

class Employee {
public:
	Employee();  // 构造函数
	~Employee(); // 析构函数
	// 虚函数 
	virtual void set();                  // 给各参数赋值
	virtual void display();              // 打印
	virtual void displayOnce();          // 仅打印一次
	virtual void inFromFile(ifstream&);  // 将文件中的数据输出
	virtual void writeToFile(ofstream&); // 将数据写入文件

	// 成员变量 
	int id;			// 编号
	double sal;		// 基本职务工资 
	string name;	// 姓名
	int age;		// 年龄
	Employee* next;	// 指向下一个对象的指针

protected:
	string sex;		// 性别  
	string addr;	// 地址
};