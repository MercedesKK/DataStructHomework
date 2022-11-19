#include "MSTGraph.h"
#include <iostream>

using namespace std;

void setUI()
{
	cout << "***********************************************\n";
	cout << "**                                           **\n";
	cout << "**              �������ģ��ϵͳ             **\n";
	cout << "**                                           **\n";
	cout << "***********************************************\n";
	cout << "**              A --- ������������           **\n";
	cout << "**              B --- ��ӵ����ı�           **\n";
	cout << "**              C --- ������С������         **\n";
	cout << "**              D --- ��ʾ��С������         **\n";
	cout << "**              E --- �˳�����               **\n";
	cout << "**                                           **\n";
	cout << "***********************************************\n\n";
}

int main()
{
	setUI();

	MSTGraph<char> g;
	while (1)
	{
		cout << "\n��ѡ������� ";

		if (!cin)		// �������봦��
		{
			cin.ignore(0x3f3f3f3f, '\n');
			cin.clear();
		}

		char op;
		cin >> op;
		cin.ignore(0x3f3f3f3f, '\n'); // �����������ַ�

		if (op == 'A')
			g.createNode();
		else if (op == 'B')
			g.createEdge();
		else if (op == 'C')
			g.createPrimTree();
		else if (op == 'D')
			g.printPrimTree();
		else if (op == 'E')
			break;
	}

	system("pause");

	return 0;
}