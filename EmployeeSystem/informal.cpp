#include "informal.h"
#include <iomanip>
#include <string>

Informal::Informal()
{
	this->bounce = 0;
	this->tax = 0;
	this->salary = 0;
	this->type = INFORMAL;
	this->next = NULL;
}

Informal::~Informal() {}

void Informal::set() {
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
	cout << "请输入奖金: ";
	cin >> bounce;
	cout << "请输入个人所得税: ";
	cin >> tax;
	salary = sal + bounce - tax;
	cout << "实发工资: " << salary << endl;
}

void Informal::display() {
	if (!this->next)
		displayOnce();
	else
		cout << "│"
		<< setw(5) << id << "│"
		<< setw(9) << name << "│"
		<< setw(7) << sex << "│"
		<< setw(5) << age << "│"
		<< setw(13) << addr << "│"
		<< setw(9) << sal << "│"
		<< setw(5) << bounce << "│"
		<< setw(11) << tax << "│"
		<< setw(9) << salary << "│"
		<< endl
		<< "├─────┼─────────┼───────┼─────┼"
		<< "─────────────┼─────────┼─────┼───────────┼─────────┤" << endl;
}

void Informal::displayOnce() {
	cout << "│"
		<< setw(5) << id << "│"
		<< setw(9) << name << "│"
		<< setw(7) << sex << "│"
		<< setw(5) << age << "│"
		<< setw(13) << addr << "│"
		<< setw(9) << sal << "│"
		<< setw(5) << bounce << "│"
		<< setw(11) << tax << "│"
		<< setw(9) << salary << "│"
		<< endl
		<< "└─────┴─────────┴───────┴─────┴"
		<< "─────────────┴─────────┴─────┴───────────┴─────────┘" << endl;
}

void Informal::inFromFile(ifstream& file) {
	if (!file.peek()) {
		cout << "文件无法读取..." << endl;
		return;
	}
	file.ignore(2, ' ');	// 跳过前两个无用字符
	// 得到文件流
	file >> id >> name >> sex >> addr >> age >> sal >> bounce >> tax >> salary;
}

void Informal::writeToFile(ofstream& file) {
	if (!file) {
		cout << "无法写入文件...";
		exit(0);
	}

	file << 'i' << ' ' << id << ' ' << name << ' ' << sex << ' ' << addr << ' ' << age << ' ' << sal << ' ' << bounce << ' ' << tax << ' ' << salary << endl;
}

void printInformalTableHead() {
	cout << "┌─────┬─────────┬───────┬─────┬─────────────┬─────────┬─────┬───────────┬─────────┐" << endl
		<< "│ 编号│   姓名  │  性别 │ 年龄│     地址    │ 基本工资│ 奖金│ 个人所交税│ 实发工资│" << endl
		<< "├─────┼─────────┼───────┼─────┼─────────────┼─────────┼─────┼───────────┼─────────┤" << endl;
}