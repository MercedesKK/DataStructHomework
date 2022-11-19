#include "SiblingTree.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	SiblingTree familyTree;
	string opt; 

	cout << "**              家谱管理系统              **" << endl;
	cout << "============================================" << endl;
	cout << "**           请选择要执行的操作：         **" << endl;
	cout << "**             A --- 完善家谱             **" << endl;
	cout << "**             B --- 添加家庭成员         **" << endl;
	cout << "**             C --- 解散局部家庭         **" << endl;
	cout << "**             D --- 更改家庭成员姓名     **" << endl;
	cout << "**             E --- 退出程序             **" << endl;
	cout << "============================================" << endl;

	familyTree.setAncestor();
	cin >> opt;

	while (opt != "E")
	{
		if (opt == "A")
			familyTree.perfectFamily();
		else if (opt == "B")
			familyTree.addMember();
		else if (opt == "C")
			familyTree.divMember();
		else if (opt == "D")
			familyTree.changeMember();
		
		cout << endl << endl << "请选择要执行的操作：";
		cin >> opt;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	cout << endl << "Enter to Exit";
	cin.get();

	return 0;
}