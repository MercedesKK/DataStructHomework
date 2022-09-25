/* @author 张靖凯 */
#include "Stack.hpp"
#include "Vector.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace MercedesKK;

Vector<string> ans;							///< 存结果
static const string operators = "+-*/()";	///< 存运算符
char priority[255];							///< 存运算符优先级

void trans(const string& str)
{
	Stack<char> ops;   ///< 操作符栈
	ops.push('#');	   ///< 栈底标记
	string tempStr;	   ///< 单个数字或运算符

	for (int i = 0; i < str.size(); i++)
	{
		// 检查是否是带符号的数字
		// 1. 带正负号且前一个字符为运算符（i=0时直接带正负号的也是数字）
		// 2. 当前字符为数字
		if (((str[i] == '-' || str[i] == '+') && (i == 0 || string("+-*/(").find(str[i - 1]) != string::npos)) ///< 右括号不需要，因为一定是减号
			|| isdigit(str[i]))
		{
			// 把操作数加入到后缀式中
			// 如果是正号就不用加入，负号或者数字本身都要加入
			tempStr = str[i] != '+' ? str.substr(i, 1) : "";
			while (i + 1 < str.size() && operators.find(str[i + 1]) == string::npos) ///< 小数点也算进去了已经
				tempStr += str[++i];

			ans.push_back(tempStr);
		}
		else // 出现操作符
		{
			if (str[i] == '(')
				ops.push(str[i]);
			else if (str[i] == ')') // 遇到有括号全弹出去直到左括号
			{
				while (ops.top() != '(')
				{
					ans.push_back(string(1, ops.top())); // 构造安全临时对象
					ops.pop();
				}
				ops.pop(); // 弹出'('
			}
			else
			{
				while (priority[str[i]] <= priority[ops.top()])
				{
					ans.push_back(string(1, ops.top()));
					ops.pop();
				}
				ops.push(str[i]); // 压入大于栈顶的运算符
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
	// 用数组来存
	priority['*'] = priority['/'] = 3;
	priority['+'] = priority['-'] = 2;
	priority['('] = 1;
	priority['#'] = 0;

	string str;
	getline(cin, str); // 读取空格,c++函数

	trans(str);

	for (int i = 0; i < ans.Size(); i++)
		cout << (i ? " " : "") << ans[i];

	cin.clear();
	cin.ignore(1024, '\n');

	cout << endl << "Enter to Exit";
	cin.get();

	return 0;
}