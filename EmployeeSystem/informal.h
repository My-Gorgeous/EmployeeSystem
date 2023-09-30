#pragma once
#include "employee.h"

class Informal :public Employee {
public:
	Informal();                     //���캯�� ����ʼ�������� 
	~Informal();                    //�������� 

	void set();						//��ʾ�û�����
	void display();					//��ӡ
	void displayOnce();				//����ӡһ��
	void inFromFile(ifstream&);     //���ļ�����ȡ
	void writeToFile(ofstream&);    //д���ļ���

	double	salary;					//ʵ������
	Type	type;					//Ա������
	Informal* next;                 //��һ��ָ�� 

private:
	double	bounce;					//����
	double	tax;					//����˰
};

void printInformalTableHead();