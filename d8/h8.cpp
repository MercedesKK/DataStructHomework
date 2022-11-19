#include "MSTGraph.h"
#include <iostream>

using namespace std;

void setUI()
{
	cout << "***********************************************\n";
	cout << "**                                           **\n";
	cout << "**              电网造价模拟系统             **\n";
	cout << "**                                           **\n";
	cout << "***********************************************\n";
	cout << "**              A --- 创建电网顶点           **\n";
	cout << "**              B --- 添加电网的边           **\n";
	cout << "**              C --- 构造最小生成树         **\n";
	cout << "**              D --- 显示最小生成树         **\n";
	cout << "**              E --- 退出程序               **\n";
	cout << "**                                           **\n";
	cout << "***********************************************\n\n";
}

int main()
{
	setUI();

	MSTGraph<char> g;
	while (1)
	{
		cout << "\n请选择操作： ";

		if (!cin)		// 错误输入处理
		{
			cin.ignore(0x3f3f3f3f, '\n');
			cin.clear();
		}

		char op;
		cin >> op;
		cin.ignore(0x3f3f3f3f, '\n'); // 清除多个多余字符

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