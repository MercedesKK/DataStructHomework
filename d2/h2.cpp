#include <iostream>
#include "List.hpp"
#include <cassert>

using namespace MercedesKK;
using namespace std;

/// @brief 两个废降序链表合成一条链表
/// @param		list1 第一个链表
/// @param		list2 第二个链表
/// @return 返回合并后的链表
List<int>& mergeList(List<int>& list1, List<int>& list2	,List<int>& list3)
{
	auto it1 = list1.begin();
	auto it2 = list2.begin();

	while (it1 != list1.end() && it2 != list2.end())
	{
		if (*it1 < *it2)
			++it1;
		else if (*it1 > *it2)
			++it2;
		else
		{
			list3.push_back(*it1);
			++it1;
			++it2;
		}
	}

	return list3;
}

int main()
{
	List<int> list1, list2, list3;
	cout << "已知两个非降序链表序列S1和S2,输入分2行，分别在每行给出由若干个正整数构成的非降序序列，用-1表示序列的结尾（-1不属于这个序列）" << endl;
	cout << "请输入S1：";

	int i;
	//输入
	while (cin >> i && i != -1)
		list1.push_back(i);
	while (cin >> i && i != -1)
		list2.push_back(i);
	list3 = mergeList(list1, list2, list3);
	cout << "合并后的链表：";
	//输出结果
	if (!list3.empty())
	{
		for (auto it = list3.begin(); it != list3.end(); ++it)
			cout << *it << " ";
	}
	else
		cout << "NULL";

	cin.clear();
	cin.ignore(1024, '\n');

	cout << endl << "Enter to Exit";
	cin.get();
	return 0;
}