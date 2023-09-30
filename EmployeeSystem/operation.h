#pragma once
#include "formal.h"
#include "informal.h"
#include <fstream>
#include <string>

typedef string Database;

char getInput();										// ��ȡ�ӿ���̨���������

void newFile(Database&, Formal*&, Informal*&);			// �½��ļ�, ���ļ�����Ҫ���������, ֻҪ�����������ͺ���

void openFile(Database&, Formal*&, Informal*&);			// ���ļ�

void saveFile(Database&, Formal*, Informal*);			// �����ļ�

void inputStaff(Formal*&, Informal*&);					// ���뺯��, ����һ��Ա����Ϣ�����뵽����β

void edit(Formal*, Informal*);							// �޸ĳ�Ա��Ϣ, ��ѯ���û��Ƿ���Ҫ����

void count(Formal*, Informal*);							// ͳ��ʵ�������ܶ��Լ�ƽ������

void quit(Database&, Formal*, Informal*);				// �˳�����, ��ѯ���Ƿ���Ҫ����

void del(Formal*, Informal*, Formal*&, Informal*&);		// ɾ��Ա����Ϣ, �����Ա���

void recover(Formal*, Informal*, Formal*, Informal*);	// �ָ����б�ɾ����Ա����Ϣ

void openRecoverFile(Formal*& f, Informal*& i);			// �򿪻���վ

void saveRecoverFile(Formal*& f, Informal*& i);			// �������վ����Ϣ

void search(Formal*, Informal*);						// �����Ƿ����ĳһ��id, name

void show(Formal* f, Informal* i);						// ���԰��sort

void printMenu();										// ��ӡ�˵�