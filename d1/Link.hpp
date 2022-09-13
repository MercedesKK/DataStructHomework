/*
* @file LinkList
* @author MercedesKK
* @date 2022-9-7
* @brief the Linklist written by me
* @email 2455650395@qq.com
*/
#pragma once
#include "List.hpp"

using namespace MercedesKK;

template <typename T>
class Link : public List<T>
{
public:
	using List<T>::erase;
	using List<T>::insert;
	using List<T>::begin;
	using List<T>::end;

	using LinkNode = Node<T>;
	using iterator = ListIterator<T, T&, T*>;
	using const_iterator = ListIterator<T, const T&, const T*>;

public:
	/// @return 返回元素
	T getElement(int n);

	/// @note   输入的是迭代器
	void modify(iterator it, const T& data);

	/// @note   输入的是位置
	void modify(int n, const T& data);

};

template<typename T>
inline T Link<T>::getElement(int n)
{
	iterator it = begin();
	int i = 1;
	while (it != end())
	{
		if (i == n)
		{
			return *it;
		}
		it++;
		i++;
	}
	return *it;
}

template<typename T>
inline void Link<T>::modify(iterator it, const T& data)
{

	iterator temp = erase(it);
	insert(temp, data);
}

template<typename T>
inline void Link<T>::modify(int n, const T& data)
{
	erase(n);
	insert(n, data);
}

