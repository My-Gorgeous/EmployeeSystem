#pragma once
#include "employee.h"

class Informal :public Employee {
public:
	Informal();                     //构造函数 ，初始化各参数 
	~Informal();                    //析构函数 

	void set();						//提示用户输入
	void display();					//打印
	void displayOnce();				//仅打印一次
	void inFromFile(ifstream&);     //从文件流读取
	void writeToFile(ofstream&);    //写入文件流

	double	salary;					//实发工资
	Type	type;					//员工类型
	Informal* next;                 //下一项指针 

private:
	double	bounce;					//奖金
	double	tax;					//所得税
};

void printInformalTableHead();