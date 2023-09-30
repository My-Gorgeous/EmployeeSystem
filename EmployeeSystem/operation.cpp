#include "operation.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

bool saved = false;
bool changed = false;

// 读取控制台输入数据
char getInput() {
	// 清空cin缓冲区里面未读取的信息
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

// 新建文件 
void newFile(Database& path, Formal*& f, Informal*& i) {
	void clearList(Formal*&, Informal*&);

	string str;
	cout << "请输入txt文件名: ";
	cin >> str;

	// 检测磁盘内是否存在此文件 
	fstream testFile(str, ios::in);
	if (testFile.is_open())	{
		cout << "文件" << str << "已存在..." << endl;
		testFile.clear();
		testFile.close();
		return;
	}

	// 若文件不存在则新建文件 
	path = str;
	FILE* myin;
	errno_t err = fopen_s(&myin, str.c_str(), "w");
	fclose(myin);
	if (err) {
		cout << "新建文件" << str << "失败..." << endl;
		return;
	}
	cout << "新建文件" << str << "成功..." << endl;
	clearList(f, i);
}

// 打开文件同时建立员工信息链表 ，实质上是打开一个流
void openFile(Database& path, Formal*& f, Informal*& i) {
	// 若输入文件不存在则重新输入
	while (1) {
		string str;
		cout << "请输入文件名: ";
		cin >> str;
		path = str;

		ifstream in(str, ios::in);

		if (!in.is_open()) {
			cout << "打开文件" << str << "失败..." << endl;
		} else {
			cout << "打开文件" << str << "成功..." << endl;
			void clearList(Formal * &f, Informal * &i);
			void staffList(ifstream & in, Formal * &f, Informal * &i);
			clearList(f, i);
			staffList(in, f, i);
			in.close();
			break;
		}
	}
}

// 保存文件，选择保存文件方式 
void saveFile(Database& path, Formal* f, Informal* i) {
	if (!f->next && !i->next) {
		cout << "当前没有数据, 无法保存..." << endl;
		return;
	}
	// 选择存储方式，是保存在默认文件还是选择另外的文件
	void directSave(Database & path, Formal * f, Informal * i);
	void saveAs(Database & path, Formal * f, Informal * i);
	cout << "1->保存, 2->另存为, 3->退出" << endl;

	char option = getInput();
	if (option == '1') {
		directSave(path, f, i);
	} else if (option == '2') {
		saveAs(path, f, i);
	} else if (option == '3') {
		cout << "退出保存..." << endl;
	} else {
		cout << "错误的输入..." << endl << "退出保存..." << endl;
	}
}

// 直接保存 
void directSave(Database& path, Formal* f, Informal* i) {
	Formal* pf = f->next;
	Informal* pi = i->next;

	ofstream out(path, ios::out);

	if (!out.is_open())	{
		cout << "打开" << path << "失败..." << endl;
		return;
	}

	cout << "打开" << path << "成功..." << endl;
	while (pf) {
		pf->writeToFile(out);
		pf = pf->next;
	}

	while (pi) {
		pi->writeToFile(out);
		pi = pi->next;
	}

	saved = true;
	cout << "保存至" << path << "成功!" << endl;
	out.clear();
	out.close();
}

// 另存 
void saveAs(Database& path, Formal* f, Informal* i) {
	cout << "如果您选择另存为, 则之后的输入也会保存至此..." << endl;

	string str;
	cout << "请输入文件名: ";
	cin >> str;
	path = str;

	FILE* myin;
	errno_t err = fopen_s(&myin, str.c_str(), "w");//新建文件夹并开流
	fclose(myin);
	if (err) {
		cout << "新建文件" << str << "失败..." << endl;
		return;
	}
	cout << "新建文件" << str << "成功..." << endl;
	
	ofstream out(path, ios::out);
	if (!out.is_open())	{
		cout << "打开" << path << "失败..." << endl;
		return;
	}
	cout << "打开" << path << "成功..." << endl;

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

	cout << "另存至" << path << "成功!" << endl;
	out.clear();
	out.close();
}

// 建立员工链表
void staffList(ifstream& in, Formal*& f, Informal*& i) {
	Formal* pf = f->next;
	Informal* pi = i->next;

	while (!in.eof()) {
		char ch;
		in >> ch;
		//分两种情况，在文件存储时再对应数据前加f/i，便于识别数据类型
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

// 清空链表
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

// 输入员工信息
void inputStaff(Formal*& f, Informal*& i) {
	Database path = "";
	openFile(path, f, i);//打开文件
	changed = true;
	Formal* pf = f;
	Informal* pi = i;

	while (pf->next)
		pf = pf->next;
	while (pi->next)
		pi = pi->next;
	// 设置死循环，可以一直输入员工信息
	while (1) {
		cout << "职工: f->正式工, i->临时工, q->退出" << endl;
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

			cout << "输入成功!" << endl;
		} else if (staff == 'i') {
			Informal* p = new Informal();
			p->set();
			if (i->next) {
				pi->next = p;
			} else {
				i->next = p;
				pi = p;
			}
			cout << "输入成功!" << endl;
		} else if (staff == 'q') {
			cout << "是否保存数据：Y->保存；N->退出" << endl;
			char option = getInput();
			if (option == 'y' || option == 'Y') {
				directSave(path, f, i);
				cout << "保存成功！" << endl << "退出输入..." << endl;
				break;
			} else if (option == 'n' || option == 'N') {
				cout << "退出输入..." << endl;
				break;
			}
		} else {
			cout << "错误输入...\n请重新输入！" << endl;
		}
	}
}

// 修改员工信息
void edit(Formal* f, Informal* i) {
	Database path = "";
	changed = true;
	openFile(path, f, i);
	if (!f && !i) {
		cout << "当前无信息, 无法修改..." << endl;
		return;
	}

	while (1) {
		cout << "职工: f->正式工, i->临时工, q->退出" << endl;
		char staff = getInput();

		if (staff == 'f') {
			cout << "请输入修改正式员工的编号: ";
			int id;
			cin >> id;
			Formal* p = f->next;
			while (p && p->id != id) {
				p = p->next;
			}

			if (!p) {
				cout << "正式员工不存在此编号..." << endl;
				continue;
			}

			cout << "存在此编号, 请输入新的正式员工信息!" << endl;
			printFormalTableHead();
			p->displayOnce();
			p->set();
			cout << "修改成功...";
		} else if (staff == 'i') {
			cout << "请输入修改临时员工的编号: ";
			int id;
			cin >> id;
			Informal* p = i->next;
			while (p && p->id != id) {
				p = p->next;
			}

			if (!p) {
				cout << "临时员工不存在此编号..." << endl;
				continue;
			}

			cout << "存在此编号, 请输入新的临时员工信息!" << endl;
			printInformalTableHead();
			p->displayOnce();
			p->set();
			cout << "修改成功...";
		} else if (staff == 'q') {
			cout << "是否保存修改：Y->保存；N->不保存" << endl;
			char option = getInput();
			if (option == 'y' || option == 'Y') {
				directSave(path, f, i);
				cout << "修改成功！" << endl << "退出修改..." << endl;
				break;
			} else if (option == 'n' || option == 'N') {
				cout << "退出修改..." << endl;
				break;
			}
		} else {
			cout << "错误输入...\n请重新输入!" << endl;
		}
	}
}

// 计算工资总额和平均工资
void count(Formal* f, Informal* i)
{
	Database path = "";
	Formal* pf = f;
	Informal* pi = i;
	openFile(path, f, i);
	if (pf->next == NULL && pi->next == NULL)
	{
		cout << "当前未读取任何信息..." << endl;
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
		cout << "┌─────────────┬─────────────┐" << endl
			<< "│   工资总额  │   平均工资  │" << endl
			<< "├─────────────┼─────────────┤" << endl
			<< "│" << setw(13) << fixed << setprecision(2) << salsum
			<< "│" << setw(13) << fixed << setprecision(2) << average << "│" << endl
			<< "└─────────────┴─────────────┘" << endl;
	}
}
//退出系统
void quit(Database& path, Formal* f, Informal* i)
{
	if (changed && !saved)
	{
		if (path._Equal("") == true)
		{
			cout << "当前未打开文件..." << endl << "请输入文件名: ";
			cin >> path;
		}

		if (f->next || i->next)
		{
			cout << "是否需要保存数据? (y/n)" << endl;
			char option = getInput();

			if (option == 'y' || option == 'Y')
				directSave(path, f, i);
			else if (option == 'n' || option == 'N')
				cout << "未保存文件..." << endl;
			else
				cout << "错误的输入, 文件未保存..." << endl;
		}
	}

	//没有被修改或者被保存(!changed || saved)
	cout << "退出成功!" << endl;
	system("pause");
	exit(0);
}
//选择删除方式
void del(Formal* f, Informal* i, Formal*& rf, Informal*& ri)
{
	void logicdelete(Formal*, Informal*, Formal*, Informal*, int);
	void physicdelete(Formal*, Informal*, int);
	Database path = "";
	changed = true;
	openFile(path, f, i);

	if (!f->next && !i->next)
	{
		cout << "当前未输入信息！" << endl;
		return;
	}
	else
	{
		cout << "以下是正式员工信息:" << endl;
		printFormalTableHead();
		Formal* pf = f->next;
		while (pf)
		{
			pf->display();
			pf = pf->next;
		}

		cout << "以下是临时员工信息:" << endl;
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
			cout << "a->逻辑删除, b->物理删除, q->退出" << endl;
			char ch = getInput();
			if (ch == 'A' || ch == 'a')
			{
				cout << "以下删除可恢复：" << endl;
				cout << "请输入要删除员工的编号：" << endl;
				cin >> id;
				logicdelete(f, i, rf, ri, id);
			}
			else if (ch == 'B' || ch == 'b')
			{
				cout << "以下删除不可恢复！是否继续（Y/N）" << endl;
				char option = getInput();
				if (option == 'y' || option == 'Y')
				{
					cout << "请输入要删除员工的编号：" << endl;
					cin >> id;
					physicdelete(f, i, id);
				}
				else if (option == 'n' || option == 'N')
				{
					cout << "退出删除..." << endl;
					return;
				}
			}
			else if (ch == 'Q' || ch == 'q')
			{
				cout << "是否保存修改（Y/N）：";
				char yorn = getInput();
				if (yorn == 'Y' || yorn == 'y')
				{
					directSave(path, f, i);
					cout << "保存成功！" << endl << "退出删除..." << endl;
					return;
				}
				else if (yorn == 'N' || yorn == 'n')
				{
					cout << "退出删除..." << endl;
					return;
				}
			}
		}



	}
}
//逻辑删除（删除后可恢复）
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
			while (prf->next != NULL)		//找到恢复链表的最后一项
				prf = prf->next;
			prf->next = pf->next;
			pf->next = pf->next->next;
			prf->next->next = NULL;

			cout << "逻辑删除成功!" << endl;
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

			cout << "逻辑删除成功!" << endl;
			break;
		}

		pi = pi->next;
	}

	if (!pi && !pf)
		cout << "未找到匹配序号！\n";
}
//物理删除（删除后不可恢复）
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
			cout << "物理删除成功!" << endl;
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
			cout << "物理删除成功!" << endl;
			break;
		}

		pi = pi->next;
	}

	if (pi == NULL && pf == NULL)
		cout << "未找到匹配序号！\n";
}
//恢复
void recover(Formal* f, Informal* i, Formal* rf, Informal* ri)
{
	void recoverFormal(Formal * f, Formal * rpf);
	void recoverInformal(Informal * i, Informal * rpi);
	Database path = "";
	changed = true;
	openFile(path, f, i);

	if (rf->next == NULL && ri->next == NULL)
	{
		cout << "当前无可恢复的信息..." << endl;
	}
	else
	{
		int id;
		Formal* qf = rf;
		Informal* qi = ri;
		cout << "以下信息可恢复：" << endl;

		if (rf->next)
		{
			cout << "以下是正式员工(可恢复)的信息:" << endl;
			printFormalTableHead();
			while (qf = qf->next)
			{
				qf->display();
			}
		}

		if (ri->next)
		{
			cout << "以下是临时员工(可恢复)的信息:" << endl;
			printInformalTableHead();
			while (qi = qi->next)
			{
				qi->display();
			}
		}

		qf = rf;
		qi = ri;

		cout << "请输入需要恢复员工信息的编号:" << endl;
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
			cout << "回收站无此员工信息！" << endl;
			return;
		}
		else
		{
			cout << "恢复员工信息成功！" << endl << "是否保存修改（Y/N）：";
			char option = getInput();
			if (option == 'Y' || option == 'y')
			{
				directSave(path, f, i);
				cout << "保存成功！" << endl << "退出恢复..." << endl;
				return;
			}
			else if (option == 'N' || option == 'n')
			{
				cout << "退出恢复..." << endl;
				return;
			}
		}
	}
}
//恢复正式员工信息
void recoverFormal(Formal* f, Formal* rpf)
{
	Formal* pf = f;
	while (pf->next != NULL)
		pf = pf->next;
	pf->next = rpf;

}
//恢复临时工信息
void recoverInformal(Informal* i, Informal* rpi)
{
	Informal* pi = i;
	while (pi->next != NULL)
		pi = pi->next;
	pi->next = rpi;
}
//打开回收站
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
//保存回收站文件，这里采用退出时自动保存的方法
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
//按要求查询员工信息
void search(Formal* f, Informal* i) {
	Database path = "";
	openFile(path, f, i);
	while (1)
	{
		Formal* pf = f->next;
		Informal* pi = i->next;
		cout << "请选择查询的关键词：" << endl << "a.工号" << endl << "b.姓名" << endl << "c.实发工资" << endl;
		char choice = getInput();

		switch (choice)
		{
			//按编号查询
		case 'a':
		{
			bool flag1 = false;
			bool flag2 = false;
			int ikey;
			cout << "请输入需要查询的工号: ";
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
				cout << "所有员工中不存在编号为" << ikey << "的职工..." << endl;
			}
			break;
		}
		//按姓名查询
		case 'b':
		{
			bool flag1 = false;
			bool flag2 = false;
			string nkey;
			cout << "请输入需要查询的姓名: ";
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
				cout << "所有员工中不存在编号为" << nkey << "的职工..." << endl;
			}
			break;
		}
		//按工资查询
		case 'c':
		{
			bool flag1 = false;
			bool flag2 = false;
			double skey;
			cout << "请输入需要查询的实发工资: ";
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
				cout << "所有员工中不存在实发工资为" << skey << "的职工..." << endl;
			}
			break;
		}
		default:
			cout << "错误的输入..." << endl;
			break;
		}
		cout << "是否继续查询（Y/N）：" << endl;
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
//给员工信息按要求排序
template <class T>
//按用户选择的方式排序
void sort(T* L, char key) {
	T* p, * q, * s;//p指向已排序列待插入位置的前驱节点，q指向未排序列第一个节点(既指向待插入节点)
	if (L->next == NULL)     //由于所有函数均不判断L空,所有这里也默认L不空(整个程序不会出现空值传进来的情况)
	{
		return;
	}
	q = L->next->next;
	L->next->next = NULL;   //断开已排序列与未排序列，以保证排序完毕后最后节点->next为空
	switch (key)
	{
	case 'a':
		while (q != NULL)
		{
			p = L;
			while (p->next != NULL && q->id >= p->next->id) //如果待插入位置节点id值≥待插入节点,则待插位置后移
				p = p->next;
			s = q->next;         //已找到正确插入位置，将p节点插入到pre节点的后面
			q->next = p->next;
			p->next = q;
			q = s;
		}
		printf("已按编号升序排序完毕\n");
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
		printf("已按姓名升序排序完毕\n");
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
		printf("已按实发工资升序排序完毕\n");
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
		printf("已按年龄升序排序完毕\n");
		break;
	}
}
//显示信息
void show(Formal* f, Informal* i) {
	Database path = "";
	openFile(path, f, i);
	while (1)
	{
		Formal* fhead = f;
		Informal* ihead = i;
		cout << "请选择排序的关键词：" << endl << "a.工号" << endl << "b.姓名" << endl << "c.实发工资" << endl << "d.年龄" << endl;
		char choice = getInput();

		if (choice != 'a' && choice != 'b' && choice != 'c' && choice != 'd')
		{
			cout << "错误的输入..." << endl << "退出显示" << endl;
			return;
		}

		if (fhead->next == NULL)
			cout << "没有正式员工" << endl;
		else
		{
			cout << "正式员工：" << endl;
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
			cout << "没有临时员工" << endl;
		else
		{
			cout << "临时员工：" << endl;
			sort(ihead, choice);

			printInformalTableHead();
			Informal* p = i->next;
			while (p)
			{
				p->display();
				p = p->next;
			}
		}
		cout << "是否换种方式显示信息（Y/N）：";
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
//建立功能界面
void printMenu()
{
	cout << "┌─────────────────────────────────────────────────┐" << endl
		<< "│               请选择以下功能项:                 │" << endl
		<< "├─────────────────────────────────────────────────┤" << endl
		<< "│                1:新建文件                       │" << endl
		<< "│                2:打开文件                       │" << endl
		<< "│                3:保存文件或另存                 │" << endl
		<< "│                4:输入/插入信息                  │" << endl
		<< "│                5:查询信息                       │" << endl
		<< "│                6:显示信息                       │" << endl
		<< "│                7:修改信息                       │" << endl
		<< "│                8:删除信息                       │" << endl
		<< "│                a:统计信息(工资总额+平均值)      │" << endl
		<< "│                b:恢复                           │" << endl
		<< "│                q:退出                           │" << endl
		<< "└─────────────────────────────────────────────────┘" << endl
		<< "请输入操作号: ";
}