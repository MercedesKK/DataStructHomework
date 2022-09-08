#include <iostream>
#include "LinkList.hpp"
#include <cassert>

using namespace MercedesKK;
using namespace std;

/// @brief �����Ͻ�������ϳ�һ������
/// @param		list1 ��һ������
/// @param		list2 �ڶ�������
/// @return ���غϲ��������
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
	cout << "��֪�����ǽ�����������S1��S2,�����2�У��ֱ���ÿ�и��������ɸ����������ɵķǽ������У���-1��ʾ���еĽ�β��-1������������У�" << endl;
	cout << "������S1��";
	while (1)
	{
		int s1;
		cin >> s1;
		assert(cin);
		if (s1 == -1)
			break;
		list1.rearAdd(s1);

	}
	cout << "������S2��";
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
	cout << "�ϲ��������";
	if (list3.size())
		list3.print();
	else
		cout << "NULL";
	cout << endl;
	return 0;
}