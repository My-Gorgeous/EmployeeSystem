#pragma once
#include "employee.h"

// Formal正式员工类继承Employee员工基类 
class Formal :public Employee {
public:
	Formal();						// 构造函数，给各项参数赋值
	~Formal();                      // 析构函数 

	void set();						// 提示用户输入，为类中数据赋值
	void display();					// 打印
	void displayOnce();				// 仅打印一次
	void inFromFile(ifstream&);		// 从文件流读取
	void writeToFile(ofstream&);	// 写入文件流,文件流会自己移动,不用担心

	double	salary;					// 实发工资
	Type	type;					// 员工类型
	Formal* next;					// 下一项指针

private:
	double	allowance;				// 职位津贴
	double	pension;				// 养老保险
	double	housing;				// 住房公积金
	double	medicare;				// 医疗保险
	double	tax;					// 个人所交税
};

// 打印表头
void printFormalTableHead();