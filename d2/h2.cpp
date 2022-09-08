#include <iostream>
#include "LinkList.hpp"
#include <cassert>

using namespace MercedesKK;
using namespace std;

/// @brief 两个废降序链表合成一条链表
/// @param		list1 第一个链表
/// @param		list2 第二个链表
/// @return 返回合并后的链表
LinkList<int>& mergeList(LinkList<int>& list1, LinkList<int>& list2	,LinkList<int>& list3)
{
	Node<int>* l1 = list1.getHeader(), *l2 = list2.getHeader();

	while (l1 != NULL && l2 != NULL)
	{
		if (l1->data < l2->data)
		{
			list3.rearAdd(l1->data);
			l1 = l1->pnext;
		}
		else if (l1->data > l2->data)
		{
			list3.rearAdd(l2->data);
			l2 = l2->pnext;
		}
		else if (l1->data == l2->data)
		{
			list3.rearAdd(l2->data);
			l1 = l1->pnext;
			l2 = l2->pnext;
		}
	}
	while (l1 != NULL)
	{
		list3.rearAdd(l1->data);
		l1 = l1->pnext;
	}
	while (l2 != NULL)
	{
		list3.rearAdd(l2->data);
		l2 = l2->pnext;
	}
	return list3;
}

int main()
{
	LinkList<int> list1, list2, list3;
	cout << "已知两个非降序链表序列S1和S2,输入分2行，分别在每行给出由若干个正整数构成的非降序序列，用-1表示序列的结尾（-1不属于这个序列）" << endl;
	cout << "请输入S1：";
	while (1)
	{
		int s1;
		cin >> s1;
		assert(cin);
		if (s1 == -1)
			break;
		list1.rearAdd(s1);

	}
	cout << "请输入S2：";
	while (1)
	{
		int s2;
		cin >> s2;
		assert(cin);
		if (s2 == -1)
			break;
		list2.rearAdd(s2);

	}
	list3 = mergeList(list1, list2, list3);
	cout << "合并后的链表：";
	if (list3.size())
		list3.print();
	else
		cout << "NULL";
	cout << endl;
	return 0;
}