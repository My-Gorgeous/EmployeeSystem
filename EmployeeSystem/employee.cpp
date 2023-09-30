#include "employee.h"
#include <string>
#include <iomanip>

Employee::Employee() {
	this->id = 0;
	this->name = "无";
	this->sex = "无";
	this->addr = "无";
	this->age = 0;
	this->sal = 0;
	this->next = NULL;
}

Employee::~Employee() {}

void Employee::set() {}

void Employee::display() {}

void Employee::displayOnce() {}

void Employee::inFromFile(ifstream&) {}

void Employee::writeToFile(ofstream&) {}