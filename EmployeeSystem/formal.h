#pragma once
#include "employee.h"

// Formal��ʽԱ����̳�EmployeeԱ������ 
class Formal :public Employee {
public:
	Formal();						// ���캯���������������ֵ
	~Formal();                      // �������� 

	void set();						// ��ʾ�û����룬Ϊ�������ݸ�ֵ
	void display();					// ��ӡ
	void displayOnce();				// ����ӡһ��
	void inFromFile(ifstream&);		// ���ļ�����ȡ
	void writeToFile(ofstream&);	// д���ļ���,�ļ������Լ��ƶ�,���õ���

	double	salary;					// ʵ������
	Type	type;					// Ա������
	Formal* next;					// ��һ��ָ��

private:
	double	allowance;				// ְλ����
	double	pension;				// ���ϱ���
	double	housing;				// ס��������
	double	medicare;				// ҽ�Ʊ���
	double	tax;					// ��������˰
};

// ��ӡ��ͷ
void printFormalTableHead();