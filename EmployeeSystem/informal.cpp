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
	cout << "��������: ";
	cin >> id;
	cout << "����������: ";
	cin >> name;
	cout << "�������Ա�: ";
	cin >> sex;
	cout << "����������: ";
	cin >> age;
	cout << "�������ַ: ";
	cin >> addr;
	cout << "�������������: ";
	cin >> sal;
	cout << "�����뽱��: ";
	cin >> bounce;
	cout << "�������������˰: ";
	cin >> tax;
	salary = sal + bounce - tax;
	cout << "ʵ������: " << salary << endl;
}

void Informal::display() {
	if (!this->next)
		displayOnce();
	else
		cout << "��"
		<< setw(5) << id << "��"
		<< setw(9) << name << "��"
		<< setw(7) << sex << "��"
		<< setw(5) << age << "��"
		<< setw(13) << addr << "��"
		<< setw(9) << sal << "��"
		<< setw(5) << bounce << "��"
		<< setw(11) << tax << "��"
		<< setw(9) << salary << "��"
		<< endl
		<< "�������������੤�����������������੤�������������੤����������"
		<< "���������������������������੤�����������������੤���������੤���������������������੤������������������" << endl;
}

void Informal::displayOnce() {
	cout << "��"
		<< setw(5) << id << "��"
		<< setw(9) << name << "��"
		<< setw(7) << sex << "��"
		<< setw(5) << age << "��"
		<< setw(13) << addr << "��"
		<< setw(9) << sal << "��"
		<< setw(5) << bounce << "��"
		<< setw(11) << tax << "��"
		<< setw(9) << salary << "��"
		<< endl
		<< "�������������ة������������������ة��������������ة�����������"
		<< "���������������������������ة������������������ة����������ة����������������������ة�������������������" << endl;
}

void Informal::inFromFile(ifstream& file) {
	if (!file.peek()) {
		cout << "�ļ��޷���ȡ..." << endl;
		return;
	}
	file.ignore(2, ' ');	// ����ǰ���������ַ�
	// �õ��ļ���
	file >> id >> name >> sex >> addr >> age >> sal >> bounce >> tax >> salary;
}

void Informal::writeToFile(ofstream& file) {
	if (!file) {
		cout << "�޷�д���ļ�...";
		exit(0);
	}

	file << 'i' << ' ' << id << ' ' << name << ' ' << sex << ' ' << addr << ' ' << age << ' ' << sal << ' ' << bounce << ' ' << tax << ' ' << salary << endl;
}

void printInformalTableHead() {
	cout << "�������������Щ������������������Щ��������������Щ����������Щ��������������������������Щ������������������Щ����������Щ����������������������Щ�������������������" << endl
		<< "�� ��ũ�   ����  ��  �Ա� �� ���䩦     ��ַ    �� �������ʩ� ���� ��������˰�� ʵ�����ʩ�" << endl
		<< "�������������੤�����������������੤�������������੤���������੤�������������������������੤�����������������੤���������੤���������������������੤������������������" << endl;
}