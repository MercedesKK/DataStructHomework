#include <iostream>
#include "List.hpp"
#include <cassert>

using namespace MercedesKK;
using namespace std;

/// @brief �����Ͻ�������ϳ�һ������
/// @param		list1 ��һ������
/// @param		list2 �ڶ�������
/// @return ���غϲ��������
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
	cout << "��֪�����ǽ�����������S1��S2,�����2�У��ֱ���ÿ�и��������ɸ����������ɵķǽ������У���-1��ʾ���еĽ�β��-1������������У�" << endl;
	cout << "������S1��";

	int i;
	//����
	while (cin >> i && i != -1)
		list1.push_back(i);
	while (cin >> i && i != -1)
		list2.push_back(i);
	list3 = mergeList(list1, list2, list3);
	cout << "�ϲ��������";
	//������
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