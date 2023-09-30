#include "formal.h"
#include "informal.h"
#include "operation.h"
#include <fstream>
#include <conio.h>
#include <Windows.h>

int main()
{
	Formal* f = new Formal();
	Informal* i = new Informal();
	Formal* rf = new Formal();
	Informal* ri = new Informal();

	Database path = "";

	openRecoverFile(rf, ri);//保持打开回收站，便于后续操作

	while (1)
	{
		system("cls");

		printMenu();
		char ch = getInput();
		switch (ch)
		{
		case '1': newFile(path, f, i); break;
		case '2': openFile(path, f, i); break;
		case '3': saveFile(path, f, i); break;
		case '4': inputStaff(f, i); break;
		case '5': search(f, i); break;
		case '6': show(f, i); break;
		case '7': edit(f, i); break;
		case '8': del(f, i, rf, ri); break;
		case 'a': count(f, i); break;
		case 'b': recover(f, i, rf, ri); break;
		case 'q': saveRecoverFile(rf, ri);   //退出时自动保存回收站文件
			quit(path, f, i);
			break;		//关闭文件流, 释放内存
		default: cout << "错误的输入! 请重新输入 " << endl;
		}

		system("pause");
	}
}