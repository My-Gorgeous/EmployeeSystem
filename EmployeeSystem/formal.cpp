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
	cout << "������ְλ����: ";
	cin >> allowance;
	cout << "���������ϱ���: ";
	cin >> pension;
	cout << "������ס������: ";
	cin >> housing;
	cout << "������ҽ�Ʊ���: ";
	cin >> medicare;
	cout << "�������������˰: ";
	cin >> tax;
	salary = sal + allowance - pension - housing - medicare - tax;
	cout << "ʵ������: " << salary << endl;
}

void Formal::display() {
	if (!this->next)
		// �������������ֻ��һ��������ôʹ��displayOnce�������������ڿ��
		displayOnce();
	else
		cout << "��"
		<< setw(5) << id << "��"
		<< setw(9) << name << "��"
		<< setw(7) << sex << "��"
		<< setw(5) << age << "��"
		<< setw(13) << addr << "��"
		<< setw(9) << sal << "��"
		<< setw(9) << allowance << "��"
		<< setw(9) << pension << "��"
		<< setw(9) << housing << "��"
		<< setw(9) << medicare << "��"
		<< setw(11) << tax << "��"
		<< setw(9) << salary << "��"
		<< endl
		<< "�������������੤�����������������੤�������������੤���������੤�������������������������੤������������������"
		<< "�������������������੤�����������������੤�����������������੤�����������������੤���������������������੤������������������" << endl;
}

void Formal::displayOnce() {
	cout << "��"
		<< setw(5) << id << "��"
		<< setw(9) << name << "��"
		<< setw(7) << sex << "��"
		<< setw(5) << age << "��"
		<< setw(13) << addr << "��"
		<< setw(9) << sal << "��"
		<< setw(9) << allowance << "��"
		<< setw(9) << pension << "��"
		<< setw(9) << housing << "��"
		<< setw(9) << medicare << "��"
		<< setw(11) << tax << "��"
		<< setw(9) << salary << "��"
		<< endl
		<< "�������������ة������������������ة��������������ة����������ة��������������������������ة�������������������"
		<< "�������������������ة������������������ة������������������ة������������������ة����������������������ة�������������������" << endl;
}

void Formal::inFromFile(ifstream& file) {
	// �ж��ļ��Ƿ�Ϊ��
	if (!file.peek()) {
		cout << "�ļ��޷���ȡ..." << endl;
		return;
	}
	file.ignore(2, ' ');	// ����ǰ���������ַ�
	// ���ļ��е����ݷ�����������
	file >> id >> name >> sex >> addr >> age >> sal >> allowance >> pension >> housing >> medicare >> tax >> salary;
}

void Formal::writeToFile(ofstream& file) {
	if (!file) {
		cout << "�ļ��޷�д��..." << endl;
		exit(0);
	}
	// ������д���ļ�
	file << 'f' << ' ' << id << ' ' << name << ' ' << sex << ' ' << addr << ' ' << age << ' ' << sal << ' ' << allowance << ' ' << pension << ' ' << housing << ' ' << medicare << ' ' << tax << ' ' << salary << endl;
}

void printFormalTableHead() {
	cout << "�������������Щ������������������Щ��������������Щ����������Щ��������������������������Щ�������������������"
		<< "�������������������Щ������������������Щ������������������Щ������������������Щ����������������������Щ�������������������" << endl
		<< "�� ��ũ�   ����  ��  �Ա� �� ���䩦     ��ַ    �� �������ʩ�" << " ְλ������ ���ϱ��թ� ס������ ҽ�Ʊ��թ� ��������˰�� ʵ�����ʩ�" << endl
		<< "�������������੤�����������������੤�������������੤���������੤�������������������������੤������������������"
		<< "�������������������੤�����������������੤�����������������੤�����������������੤���������������������੤������������������" << endl;
}