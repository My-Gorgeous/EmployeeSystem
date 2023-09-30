#include "formal.h"
#include <iomanip>
#include <string>

Formal::Formal() {
	this->allowance = 0;
	this->pension = 0;
	this->housing = 0;
	this->medicare = 0;
	this->tax = 0;
	this->salary = 0;
	this->type = FORMAL;
	this->next = NULL;
}

Formal::~Formal() {}

void Formal::set() {
	cout << "请输入编号: ";
	cin >> id;
	cout << "请输入姓名: ";
	cin >> name;
	cout << "请输入性别: ";
	cin >> sex;
	cout << "请输入年龄: ";
	cin >> age;
	cout << "请输入地址: ";
	cin >> addr;
	cout << "请输入基本工资: ";
	cin >> sal;
	cout << "请输入职位津贴: ";
	cin >> allowance;
	cout << "请输入养老保险: ";
	cin >> pension;
	cout << "请输入住房积金: ";
	cin >> housing;
	cout << "请输入医疗保险: ";
	cin >> medicare;
	cout << "请输入个人所交税: ";
	cin >> tax;
	salary = sal + allowance - pension - housing - medicare - tax;
	cout << "实发工资: " << salary << endl;
}

void Formal::display() {
	if (!this->next)
		// 如果对象链表中只有一个对象，那么使用displayOnce函数（区别在于框框）
		displayOnce();
	else
		cout << "│"
		<< setw(5) << id << "│"
		<< setw(9) << name << "│"
		<< setw(7) << sex << "│"
		<< setw(5) << age << "│"
		<< setw(13) << addr << "│"
		<< setw(9) << sal << "│"
		<< setw(9) << allowance << "│"
		<< setw(9) << pension << "│"
		<< setw(9) << housing << "│"
		<< setw(9) << medicare << "│"
		<< setw(11) << tax << "│"
		<< setw(9) << salary << "│"
		<< endl
		<< "├─────┼─────────┼───────┼─────┼─────────────┼─────────┼"
		<< "─────────┼─────────┼─────────┼─────────┼───────────┼─────────┤" << endl;
}

void Formal::displayOnce() {
	cout << "│"
		<< setw(5) << id << "│"
		<< setw(9) << name << "│"
		<< setw(7) << sex << "│"
		<< setw(5) << age << "│"
		<< setw(13) << addr << "│"
		<< setw(9) << sal << "│"
		<< setw(9) << allowance << "│"
		<< setw(9) << pension << "│"
		<< setw(9) << housing << "│"
		<< setw(9) << medicare << "│"
		<< setw(11) << tax << "│"
		<< setw(9) << salary << "│"
		<< endl
		<< "└─────┴─────────┴───────┴─────┴─────────────┴─────────┴"
		<< "─────────┴─────────┴─────────┴─────────┴───────────┴─────────┘" << endl;
}

void Formal::inFromFile(ifstream& file) {
	// 判断文件是否为空
	if (!file.peek()) {
		cout << "文件无法读取..." << endl;
		return;
	}
	file.ignore(2, ' ');	// 跳过前两个无用字符
	// 将文件中的数据放入输入流中
	file >> id >> name >> sex >> addr >> age >> sal >> allowance >> pension >> housing >> medicare >> tax >> salary;
}

void Formal::writeToFile(ofstream& file) {
	if (!file) {
		cout << "文件无法写入..." << endl;
		exit(0);
	}
	// 将数据写入文件
	file << 'f' << ' ' << id << ' ' << name << ' ' << sex << ' ' << addr << ' ' << age << ' ' << sal << ' ' << allowance << ' ' << pension << ' ' << housing << ' ' << medicare << ' ' << tax << ' ' << salary << endl;
}

void printFormalTableHead() {
	cout << "┌─────┬─────────┬───────┬─────┬─────────────┬─────────┬"
		<< "─────────┬─────────┬─────────┬─────────┬───────────┬─────────┐" << endl
		<< "│ 编号│   姓名  │  性别 │ 年龄│     地址    │ 基本工资│" << " 职位津贴│ 养老保险│ 住房积金│ 医疗保险│ 个人所交税│ 实发工资│" << endl
		<< "├─────┼─────────┼───────┼─────┼─────────────┼─────────┼"
		<< "─────────┼─────────┼─────────┼─────────┼───────────┼─────────┤" << endl;
}