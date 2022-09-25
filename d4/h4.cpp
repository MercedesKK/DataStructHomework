/* @author �ž��� */
#include "Stack.hpp"
#include "Vector.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace MercedesKK;

Vector<string> ans;							///< ����
static const string operators = "+-*/()";	///< �������
char priority[255];							///< ����������ȼ�

void trans(const string& str)
{
	Stack<char> ops;   ///< ������ջ
	ops.push('#');	   ///< ջ�ױ��
	string tempStr;	   ///< �������ֻ������

	for (int i = 0; i < str.size(); i++)
	{
		// ����Ƿ��Ǵ����ŵ�����
		// 1. ����������ǰһ���ַ�Ϊ�������i=0ʱֱ�Ӵ������ŵ�Ҳ�����֣�
		// 2. ��ǰ�ַ�Ϊ����
		if (((str[i] == '-' || str[i] == '+') && (i == 0 || string("+-*/(").find(str[i - 1]) != string::npos)) ///< �����Ų���Ҫ����Ϊһ���Ǽ���
			|| isdigit(str[i]))
		{
			// �Ѳ��������뵽��׺ʽ��
			// ��������žͲ��ü��룬���Ż������ֱ���Ҫ����
			tempStr = str[i] != '+' ? str.substr(i, 1) : "";
			while (i + 1 < str.size() && operators.find(str[i + 1]) == string::npos) ///< С����Ҳ���ȥ���Ѿ�
				tempStr += str[++i];

			ans.push_back(tempStr);
		}
		else // ���ֲ�����
		{
			if (str[i] == '(')
				ops.push(str[i]);
			else if (str[i] == ')') // ����������ȫ����ȥֱ��������
			{
				while (ops.top() != '(')
				{
					ans.push_back(string(1, ops.top())); // ���찲ȫ��ʱ����
					ops.pop();
				}
				ops.pop(); // ����'('
			}
			else
			{
				while (priority[str[i]] <= priority[ops.top()])
				{
					ans.push_back(string(1, ops.top()));
					ops.pop();
				}
				ops.push(str[i]); // ѹ�����ջ���������
			}
		}
	}

	while (ops.size() > 1)
	{
		ans.push_back(string(1, ops.top()));
		ops.pop();
	}
}

int main()
{
	// ����������
	priority['*'] = priority['/'] = 3;
	priority['+'] = priority['-'] = 2;
	priority['('] = 1;
	priority['#'] = 0;

	string str;
	getline(cin, str); // ��ȡ�ո�,c++����

	trans(str);

	for (int i = 0; i < ans.Size(); i++)
		cout << (i ? " " : "") << ans[i];

	cin.clear();
	cin.ignore(1024, '\n');

	cout << endl << "Enter to Exit";
	cin.get();

	return 0;
}