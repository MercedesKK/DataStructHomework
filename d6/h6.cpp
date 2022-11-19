#include "SiblingTree.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	SiblingTree familyTree;
	string opt; 

	cout << "**              ���׹���ϵͳ              **" << endl;
	cout << "============================================" << endl;
	cout << "**           ��ѡ��Ҫִ�еĲ�����         **" << endl;
	cout << "**             A --- ���Ƽ���             **" << endl;
	cout << "**             B --- ��Ӽ�ͥ��Ա         **" << endl;
	cout << "**             C --- ��ɢ�ֲ���ͥ         **" << endl;
	cout << "**             D --- ���ļ�ͥ��Ա����     **" << endl;
	cout << "**             E --- �˳�����             **" << endl;
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
		
		cout << endl << endl << "��ѡ��Ҫִ�еĲ�����";
		cin >> opt;
	}

	cin.clear();
	cin.ignore(1024, '\n');

	cout << endl << "Enter to Exit";
	cin.get();

	return 0;
}