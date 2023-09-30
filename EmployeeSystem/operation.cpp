#include "operation.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

bool saved = false;
bool changed = false;

// ��ȡ����̨��������
char getInput() {
	// ���cin����������δ��ȡ����Ϣ
	cin.sync();
	string input = "";
	char ch = ' ';
	while (input == "")	{
		getline(cin, input);
		if (input.length() > 1)
			ch = '0';
		else
			ch = input[0];
	}
	return ch;
}

// �½��ļ� 
void newFile(Database& path, Formal*& f, Informal*& i) {
	void clearList(Formal*&, Informal*&);

	string str;
	cout << "������txt�ļ���: ";
	cin >> str;

	// ���������Ƿ���ڴ��ļ� 
	fstream testFile(str, ios::in);
	if (testFile.is_open())	{
		cout << "�ļ�" << str << "�Ѵ���..." << endl;
		testFile.clear();
		testFile.close();
		return;
	}

	// ���ļ����������½��ļ� 
	path = str;
	FILE* myin;
	errno_t err = fopen_s(&myin, str.c_str(), "w");
	fclose(myin);
	if (err) {
		cout << "�½��ļ�" << str << "ʧ��..." << endl;
		return;
	}
	cout << "�½��ļ�" << str << "�ɹ�..." << endl;
	clearList(f, i);
}

// ���ļ�ͬʱ����Ա����Ϣ���� ��ʵ�����Ǵ�һ����
void openFile(Database& path, Formal*& f, Informal*& i) {
	// �������ļ�����������������
	while (1) {
		string str;
		cout << "�������ļ���: ";
		cin >> str;
		path = str;

		ifstream in(str, ios::in);

		if (!in.is_open()) {
			cout << "���ļ�" << str << "ʧ��..." << endl;
		} else {
			cout << "���ļ�" << str << "�ɹ�..." << endl;
			void clearList(Formal * &f, Informal * &i);
			void staffList(ifstream & in, Formal * &f, Informal * &i);
			clearList(f, i);
			staffList(in, f, i);
			in.close();
			break;
		}
	}
}

// �����ļ���ѡ�񱣴��ļ���ʽ 
void saveFile(Database& path, Formal* f, Informal* i) {
	if (!f->next && !i->next) {
		cout << "��ǰû������, �޷�����..." << endl;
		return;
	}
	// ѡ��洢��ʽ���Ǳ�����Ĭ���ļ�����ѡ��������ļ�
	void directSave(Database & path, Formal * f, Informal * i);
	void saveAs(Database & path, Formal * f, Informal * i);
	cout << "1->����, 2->���Ϊ, 3->�˳�" << endl;

	char option = getInput();
	if (option == '1') {
		directSave(path, f, i);
	} else if (option == '2') {
		saveAs(path, f, i);
	} else if (option == '3') {
		cout << "�˳�����..." << endl;
	} else {
		cout << "���������..." << endl << "�˳�����..." << endl;
	}
}

// ֱ�ӱ��� 
void directSave(Database& path, Formal* f, Informal* i) {
	Formal* pf = f->next;
	Informal* pi = i->next;

	ofstream out(path, ios::out);

	if (!out.is_open())	{
		cout << "��" << path << "ʧ��..." << endl;
		return;
	}

	cout << "��" << path << "�ɹ�..." << endl;
	while (pf) {
		pf->writeToFile(out);
		pf = pf->next;
	}

	while (pi) {
		pi->writeToFile(out);
		pi = pi->next;
	}

	saved = true;
	cout << "������" << path << "�ɹ�!" << endl;
	out.clear();
	out.close();
}

// ��� 
void saveAs(Database& path, Formal* f, Informal* i) {
	cout << "�����ѡ�����Ϊ, ��֮�������Ҳ�ᱣ������..." << endl;

	string str;
	cout << "�������ļ���: ";
	cin >> str;
	path = str;

	FILE* myin;
	errno_t err = fopen_s(&myin, str.c_str(), "w");//�½��ļ��в�����
	fclose(myin);
	if (err) {
		cout << "�½��ļ�" << str << "ʧ��..." << endl;
		return;
	}
	cout << "�½��ļ�" << str << "�ɹ�..." << endl;
	
	ofstream out(path, ios::out);
	if (!out.is_open())	{
		cout << "��" << path << "ʧ��..." << endl;
		return;
	}
	cout << "��" << path << "�ɹ�..." << endl;

	Formal* pf = f->next;
	Informal* pi = i->next;
	while (pf) {
		pf->writeToFile(out);
		pf = pf->next;
	}

	while (pi) {
		pi->writeToFile(out);
		pi = pi->next;
	}

	cout << "�����" << path << "�ɹ�!" << endl;
	out.clear();
	out.close();
}

// ����Ա������
void staffList(ifstream& in, Formal*& f, Informal*& i) {
	Formal* pf = f->next;
	Informal* pi = i->next;

	while (!in.eof()) {
		char ch;
		in >> ch;
		//��������������ļ��洢ʱ�ٶ�Ӧ����ǰ��f/i������ʶ����������
		if (!in.eof() && ch == 'f') {
			Formal* p = new Formal();
			in.clear();
			p->inFromFile(in);
			if (pf) {
				pf->next = p;
				pf = p;
			} else {
				pf = p;
				f->next = pf;
			}

			in.get();
		} else if (!in.eof() && ch == 'i') {
			Informal* p = new Informal();
			in.clear();
			p->inFromFile(in);
			if (pi) {
				pi->next = p;
				pi = p;
			} else {
				pi = p;
				i->next = pi;
			}

			in.get();
		}
	}
}

// �������
void clearList(Formal*& f, Informal*& i) {
	Formal* prevf = f->next;
	while (prevf) {
		f->next = prevf->next;
		delete prevf;
		prevf = f->next;
	}

	Informal* previ = i->next;
	while (previ) {
		i->next = previ->next;
		delete previ;
		previ = i->next;
	}
}

// ����Ա����Ϣ
void inputStaff(Formal*& f, Informal*& i) {
	Database path = "";
	openFile(path, f, i);//���ļ�
	changed = true;
	Formal* pf = f;
	Informal* pi = i;

	while (pf->next)
		pf = pf->next;
	while (pi->next)
		pi = pi->next;
	// ������ѭ��������һֱ����Ա����Ϣ
	while (1) {
		cout << "ְ��: f->��ʽ��, i->��ʱ��, q->�˳�" << endl;
		char staff = getInput();

		if (staff == 'f') {
			Formal* p = new Formal();
			p->set();
			if (f->next) {
				pf->next = p;
			} else {
				f->next = p;
				pf = p;
			}

			cout << "����ɹ�!" << endl;
		} else if (staff == 'i') {
			Informal* p = new Informal();
			p->set();
			if (i->next) {
				pi->next = p;
			} else {
				i->next = p;
				pi = p;
			}
			cout << "����ɹ�!" << endl;
		} else if (staff == 'q') {
			cout << "�Ƿ񱣴����ݣ�Y->���棻N->�˳�" << endl;
			char option = getInput();
			if (option == 'y' || option == 'Y') {
				directSave(path, f, i);
				cout << "����ɹ���" << endl << "�˳�����..." << endl;
				break;
			} else if (option == 'n' || option == 'N') {
				cout << "�˳�����..." << endl;
				break;
			}
		} else {
			cout << "��������...\n���������룡" << endl;
		}
	}
}

// �޸�Ա����Ϣ
void edit(Formal* f, Informal* i) {
	Database path = "";
	changed = true;
	openFile(path, f, i);
	if (!f && !i) {
		cout << "��ǰ����Ϣ, �޷��޸�..." << endl;
		return;
	}

	while (1) {
		cout << "ְ��: f->��ʽ��, i->��ʱ��, q->�˳�" << endl;
		char staff = getInput();

		if (staff == 'f') {
			cout << "�������޸���ʽԱ���ı��: ";
			int id;
			cin >> id;
			Formal* p = f->next;
			while (p && p->id != id) {
				p = p->next;
			}

			if (!p) {
				cout << "��ʽԱ�������ڴ˱��..." << endl;
				continue;
			}

			cout << "���ڴ˱��, �������µ���ʽԱ����Ϣ!" << endl;
			printFormalTableHead();
			p->displayOnce();
			p->set();
			cout << "�޸ĳɹ�...";
		} else if (staff == 'i') {
			cout << "�������޸���ʱԱ���ı��: ";
			int id;
			cin >> id;
			Informal* p = i->next;
			while (p && p->id != id) {
				p = p->next;
			}

			if (!p) {
				cout << "��ʱԱ�������ڴ˱��..." << endl;
				continue;
			}

			cout << "���ڴ˱��, �������µ���ʱԱ����Ϣ!" << endl;
			printInformalTableHead();
			p->displayOnce();
			p->set();
			cout << "�޸ĳɹ�...";
		} else if (staff == 'q') {
			cout << "�Ƿ񱣴��޸ģ�Y->���棻N->������" << endl;
			char option = getInput();
			if (option == 'y' || option == 'Y') {
				directSave(path, f, i);
				cout << "�޸ĳɹ���" << endl << "�˳��޸�..." << endl;
				break;
			} else if (option == 'n' || option == 'N') {
				cout << "�˳��޸�..." << endl;
				break;
			}
		} else {
			cout << "��������...\n����������!" << endl;
		}
	}
}

// ���㹤���ܶ��ƽ������
void count(Formal* f, Informal* i)
{
	Database path = "";
	Formal* pf = f;
	Informal* pi = i;
	openFile(path, f, i);
	if (pf->next == NULL && pi->next == NULL)
	{
		cout << "��ǰδ��ȡ�κ���Ϣ..." << endl;
	}
	else
	{
		int num = 0;
		double salsum = 0;
		double average;
		while (pf = pf->next)
		{
			salsum += pf->salary;
			num++;
		}
		while (pi = pi->next)
		{
			salsum += pi->salary;
			num++;
		}
		average = salsum / num;
		cout << "�����������������������������Щ���������������������������" << endl
			<< "��   �����ܶ�  ��   ƽ������  ��" << endl
			<< "�����������������������������੤��������������������������" << endl
			<< "��" << setw(13) << fixed << setprecision(2) << salsum
			<< "��" << setw(13) << fixed << setprecision(2) << average << "��" << endl
			<< "�����������������������������ة���������������������������" << endl;
	}
}
//�˳�ϵͳ
void quit(Database& path, Formal* f, Informal* i)
{
	if (changed && !saved)
	{
		if (path._Equal("") == true)
		{
			cout << "��ǰδ���ļ�..." << endl << "�������ļ���: ";
			cin >> path;
		}

		if (f->next || i->next)
		{
			cout << "�Ƿ���Ҫ��������? (y/n)" << endl;
			char option = getInput();

			if (option == 'y' || option == 'Y')
				directSave(path, f, i);
			else if (option == 'n' || option == 'N')
				cout << "δ�����ļ�..." << endl;
			else
				cout << "���������, �ļ�δ����..." << endl;
		}
	}

	//û�б��޸Ļ��߱�����(!changed || saved)
	cout << "�˳��ɹ�!" << endl;
	system("pause");
	exit(0);
}
//ѡ��ɾ����ʽ
void del(Formal* f, Informal* i, Formal*& rf, Informal*& ri)
{
	void logicdelete(Formal*, Informal*, Formal*, Informal*, int);
	void physicdelete(Formal*, Informal*, int);
	Database path = "";
	changed = true;
	openFile(path, f, i);

	if (!f->next && !i->next)
	{
		cout << "��ǰδ������Ϣ��" << endl;
		return;
	}
	else
	{
		cout << "��������ʽԱ����Ϣ:" << endl;
		printFormalTableHead();
		Formal* pf = f->next;
		while (pf)
		{
			pf->display();
			pf = pf->next;
		}

		cout << "��������ʱԱ����Ϣ:" << endl;
		printInformalTableHead();
		Informal* pi = i->next;
		while (pi)
		{
			pi->display();
			pi = pi->next;
		}

		while (1)
		{
			int id;
			cout << "a->�߼�ɾ��, b->����ɾ��, q->�˳�" << endl;
			char ch = getInput();
			if (ch == 'A' || ch == 'a')
			{
				cout << "����ɾ���ɻָ���" << endl;
				cout << "������Ҫɾ��Ա���ı�ţ�" << endl;
				cin >> id;
				logicdelete(f, i, rf, ri, id);
			}
			else if (ch == 'B' || ch == 'b')
			{
				cout << "����ɾ�����ɻָ����Ƿ������Y/N��" << endl;
				char option = getInput();
				if (option == 'y' || option == 'Y')
				{
					cout << "������Ҫɾ��Ա���ı�ţ�" << endl;
					cin >> id;
					physicdelete(f, i, id);
				}
				else if (option == 'n' || option == 'N')
				{
					cout << "�˳�ɾ��..." << endl;
					return;
				}
			}
			else if (ch == 'Q' || ch == 'q')
			{
				cout << "�Ƿ񱣴��޸ģ�Y/N����";
				char yorn = getInput();
				if (yorn == 'Y' || yorn == 'y')
				{
					directSave(path, f, i);
					cout << "����ɹ���" << endl << "�˳�ɾ��..." << endl;
					return;
				}
				else if (yorn == 'N' || yorn == 'n')
				{
					cout << "�˳�ɾ��..." << endl;
					return;
				}
			}
		}



	}
}
//�߼�ɾ����ɾ����ɻָ���
void logicdelete(Formal* f, Informal* i, Formal* rf, Informal* ri, int id)
{

	Formal* pf = f;
	Formal* prf = rf;
	Informal* pi = i;
	Informal* pri = ri;

	while (pf)
	{
		if (pf->next && pf->next->id == id)
		{
			while (prf->next != NULL)		//�ҵ��ָ���������һ��
				prf = prf->next;
			prf->next = pf->next;
			pf->next = pf->next->next;
			prf->next->next = NULL;

			cout << "�߼�ɾ���ɹ�!" << endl;
			break;
		}

		pf = pf->next;
	}

	while (pi)
	{
		if (pi->next && pi->next->id == id)
		{
			while (pri->next != NULL)
				pri = pri->next;
			pri->next = pi->next;
			pi->next = pi->next->next;
			pri->next->next = NULL;

			cout << "�߼�ɾ���ɹ�!" << endl;
			break;
		}

		pi = pi->next;
	}

	if (!pi && !pf)
		cout << "δ�ҵ�ƥ����ţ�\n";
}
//����ɾ����ɾ���󲻿ɻָ���
void physicdelete(Formal* f, Informal* i, int id)
{

	Formal* pf = f;
	Informal* pi = i;
	while (pf)
	{
		if (pf->next && pf->next->id == id)
		{
			Formal* p = pf->next;
			pf->next = pf->next->next;

			delete p;
			cout << "����ɾ���ɹ�!" << endl;
			break;
		}

		pf = pf->next;
	}

	while (pi)
	{
		if (pi->next && pi->next->id == id)
		{
			Informal* p = pi->next;
			pi->next = pi->next->next;

			delete p;
			cout << "����ɾ���ɹ�!" << endl;
			break;
		}

		pi = pi->next;
	}

	if (pi == NULL && pf == NULL)
		cout << "δ�ҵ�ƥ����ţ�\n";
}
//�ָ�
void recover(Formal* f, Informal* i, Formal* rf, Informal* ri)
{
	void recoverFormal(Formal * f, Formal * rpf);
	void recoverInformal(Informal * i, Informal * rpi);
	Database path = "";
	changed = true;
	openFile(path, f, i);

	if (rf->next == NULL && ri->next == NULL)
	{
		cout << "��ǰ�޿ɻָ�����Ϣ..." << endl;
	}
	else
	{
		int id;
		Formal* qf = rf;
		Informal* qi = ri;
		cout << "������Ϣ�ɻָ���" << endl;

		if (rf->next)
		{
			cout << "��������ʽԱ��(�ɻָ�)����Ϣ:" << endl;
			printFormalTableHead();
			while (qf = qf->next)
			{
				qf->display();
			}
		}

		if (ri->next)
		{
			cout << "��������ʱԱ��(�ɻָ�)����Ϣ:" << endl;
			printInformalTableHead();
			while (qi = qi->next)
			{
				qi->display();
			}
		}

		qf = rf;
		qi = ri;

		cout << "��������Ҫ�ָ�Ա����Ϣ�ı��:" << endl;
		cin >> id;
		Formal* rpf;
		Informal* rpi;

		while (qf)
		{
			if (qf->next && qf->next->id == id)
			{
				rpf = qf->next;
				qf->next = qf->next->next;
				rpf->next = NULL;
				recoverFormal(f, rpf);
				break;
			}

			qf = qf->next;
		}

		while (qi)
		{
			if (qi->next && qi->next->id == id)
			{
				rpi = qi->next;
				qi->next = qi->next->next;
				rpi->next = NULL;
				recoverInformal(i, rpi);
				break;
			}

			qi = qi->next;
		}
		if (qf == NULL && qi == NULL)
		{
			cout << "����վ�޴�Ա����Ϣ��" << endl;
			return;
		}
		else
		{
			cout << "�ָ�Ա����Ϣ�ɹ���" << endl << "�Ƿ񱣴��޸ģ�Y/N����";
			char option = getInput();
			if (option == 'Y' || option == 'y')
			{
				directSave(path, f, i);
				cout << "����ɹ���" << endl << "�˳��ָ�..." << endl;
				return;
			}
			else if (option == 'N' || option == 'n')
			{
				cout << "�˳��ָ�..." << endl;
				return;
			}
		}
	}
}
//�ָ���ʽԱ����Ϣ
void recoverFormal(Formal* f, Formal* rpf)
{
	Formal* pf = f;
	while (pf->next != NULL)
		pf = pf->next;
	pf->next = rpf;

}
//�ָ���ʱ����Ϣ
void recoverInformal(Informal* i, Informal* rpi)
{
	Informal* pi = i;
	while (pi->next != NULL)
		pi = pi->next;
	pi->next = rpi;
}
//�򿪻���վ
void openRecoverFile(Formal*& f, Informal*& i)
{
	string str = "it_is_a_recover_file.txt";
	ifstream in(str, ios::in);

	if (!in.is_open())
	{
		return;
	}
	else
	{
	}

	clearList(f, i);
	void staffList(ifstream & in, Formal * &f, Informal * &i);
	staffList(in, f, i);
	in.close();
}
//�������վ�ļ�����������˳�ʱ�Զ�����ķ���
void saveRecoverFile(Formal*& f, Informal*& i)
{
	string str = "it_is_a_recover_file.txt";
	Formal* pf = f->next;
	Informal* pi = i->next;
	ofstream out(str, ios::out);

	while (pf)
	{
		pf->writeToFile(out);
		pf = pf->next;
	}

	while (pi)
	{
		pi->writeToFile(out);
		pi = pi->next;
	}

	out.clear();
	out.close();
}
//��Ҫ���ѯԱ����Ϣ
void search(Formal* f, Informal* i) {
	Database path = "";
	openFile(path, f, i);
	while (1)
	{
		Formal* pf = f->next;
		Informal* pi = i->next;
		cout << "��ѡ���ѯ�Ĺؼ��ʣ�" << endl << "a.����" << endl << "b.����" << endl << "c.ʵ������" << endl;
		char choice = getInput();

		switch (choice)
		{
			//����Ų�ѯ
		case 'a':
		{
			bool flag1 = false;
			bool flag2 = false;
			int ikey;
			cout << "��������Ҫ��ѯ�Ĺ���: ";
			cin >> ikey;

			while (pf)
			{
				if (pf->id == ikey)
				{
					flag1 = true;
					printFormalTableHead();
					pf->displayOnce();
				}
				pf = pf->next;
			}

			while (pi)
			{
				if (pi->id == ikey)
				{
					flag2 = true;
					printInformalTableHead();
					pi->displayOnce();
				}
				pi = pi->next;
			}

			if (flag1 == false && flag2 == false)
			{
				cout << "����Ա���в����ڱ��Ϊ" << ikey << "��ְ��..." << endl;
			}
			break;
		}
		//��������ѯ
		case 'b':
		{
			bool flag1 = false;
			bool flag2 = false;
			string nkey;
			cout << "��������Ҫ��ѯ������: ";
			cin >> nkey;

			while (pf)
			{
				if (pf->name._Equal(nkey))
				{
					flag1 = true;
					printFormalTableHead();
					pf->displayOnce();
				}
				pf = pf->next;
			}

			while (pi)
			{
				if (pi->name._Equal(nkey))
				{
					flag2 = true;
					printInformalTableHead();
					pi->displayOnce();
				}
				pi = pi->next;
			}

			if (flag1 == false && flag2 == false)
			{
				cout << "����Ա���в����ڱ��Ϊ" << nkey << "��ְ��..." << endl;
			}
			break;
		}
		//�����ʲ�ѯ
		case 'c':
		{
			bool flag1 = false;
			bool flag2 = false;
			double skey;
			cout << "��������Ҫ��ѯ��ʵ������: ";
			cin >> skey;

			while (pf)
			{
				if (pf->salary == skey)
				{
					flag1 = true;
					printFormalTableHead();
					pf->displayOnce();
				}
				pf = pf->next;
			}

			while (pi)
			{
				if (pi->salary == skey)
				{
					flag2 = true;
					printInformalTableHead();
					pi->displayOnce();
				}
				pi = pi->next;
			}

			if (flag1 == false && flag2 == false)
			{
				cout << "����Ա���в�����ʵ������Ϊ" << skey << "��ְ��..." << endl;
			}
			break;
		}
		default:
			cout << "���������..." << endl;
			break;
		}
		cout << "�Ƿ������ѯ��Y/N����" << endl;
		char option = getInput();
		if (option == 'Y' || option == 'y')
		{
			continue;
		}
		else if (option == 'N' || option == 'n')
		{
			break;
		}
	}

}
//��Ա����Ϣ��Ҫ������
template <class T>
//���û�ѡ��ķ�ʽ����
void sort(T* L, char key) {
	T* p, * q, * s;//pָ���������д�����λ�õ�ǰ���ڵ㣬qָ��δ�����е�һ���ڵ�(��ָ�������ڵ�)
	if (L->next == NULL)     //�������к��������ж�L��,��������ҲĬ��L����(�������򲻻���ֿ�ֵ�����������)
	{
		return;
	}
	q = L->next->next;
	L->next->next = NULL;   //�Ͽ�����������δ�����У��Ա�֤������Ϻ����ڵ�->nextΪ��
	switch (key)
	{
	case 'a':
		while (q != NULL)
		{
			p = L;
			while (p->next != NULL && q->id >= p->next->id) //���������λ�ýڵ�idֵ�ݴ�����ڵ�,�����λ�ú���
				p = p->next;
			s = q->next;         //���ҵ���ȷ����λ�ã���p�ڵ���뵽pre�ڵ�ĺ���
			q->next = p->next;
			p->next = q;
			q = s;
		}
		printf("�Ѱ���������������\n");
		break;
	case 'b':
		while (q != NULL)
		{
			p = L;
			while (p->next != NULL && q->name.compare(p->next->name) > 0)//q->name > p->next->name
				p = p->next;
			s = q->next;
			q->next = p->next;
			p->next = q;
			q = s;
		}
		printf("�Ѱ����������������\n");
		break;
	case 'c':
		while (q != NULL)
		{
			p = L;
			while (p->next != NULL && q->salary >= p->next->salary)
				p = p->next;
			s = q->next;
			q->next = p->next;
			p->next = q;
			q = s;
		}
		printf("�Ѱ�ʵ�����������������\n");
		break;
	case 'd':
		while (q != NULL)
		{
			p = L;
			while (p->next != NULL && q->age >= p->next->age)
				p = p->next;
			s = q->next;
			q->next = p->next;
			p->next = q;
			q = s;
		}
		printf("�Ѱ����������������\n");
		break;
	}
}
//��ʾ��Ϣ
void show(Formal* f, Informal* i) {
	Database path = "";
	openFile(path, f, i);
	while (1)
	{
		Formal* fhead = f;
		Informal* ihead = i;
		cout << "��ѡ������Ĺؼ��ʣ�" << endl << "a.����" << endl << "b.����" << endl << "c.ʵ������" << endl << "d.����" << endl;
		char choice = getInput();

		if (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd')
		{
			cout << "���������..." << endl << "�˳���ʾ" << endl;
			return;
		}

		if (fhead->next == NULL)
			cout << "û����ʽԱ��" << endl;
		else
		{
			cout << "��ʽԱ����" << endl;
			sort(fhead, choice);

			printFormalTableHead();
			Formal* p = f->next;
			while (p)
			{
				p->display();
				p = p->next;
			}
		}

		if (ihead->next == NULL)
			cout << "û����ʱԱ��" << endl;
		else
		{
			cout << "��ʱԱ����" << endl;
			sort(ihead, choice);

			printInformalTableHead();
			Informal* p = i->next;
			while (p)
			{
				p->display();
				p = p->next;
			}
		}
		cout << "�Ƿ��ַ�ʽ��ʾ��Ϣ��Y/N����";
		char option = getInput();
		if (option == 'Y' || option == 'y')
		{
			continue;
		}
		else if (option == 'N' || option == 'n')
		{
			break;
		}
	}
}
//�������ܽ���
void printMenu()
{
	cout << "������������������������������������������������������������������������������������������������������" << endl
		<< "��               ��ѡ�����¹�����:                 ��" << endl
		<< "������������������������������������������������������������������������������������������������������" << endl
		<< "��                1:�½��ļ�                       ��" << endl
		<< "��                2:���ļ�                       ��" << endl
		<< "��                3:�����ļ������                 ��" << endl
		<< "��                4:����/������Ϣ                  ��" << endl
		<< "��                5:��ѯ��Ϣ                       ��" << endl
		<< "��                6:��ʾ��Ϣ                       ��" << endl
		<< "��                7:�޸���Ϣ                       ��" << endl
		<< "��                8:ɾ����Ϣ                       ��" << endl
		<< "��                a:ͳ����Ϣ(�����ܶ�+ƽ��ֵ)      ��" << endl
		<< "��                b:�ָ�                           ��" << endl
		<< "��                q:�˳�                           ��" << endl
		<< "������������������������������������������������������������������������������������������������������" << endl
		<< "�����������: ";
}