/*
* @file LinkList
* @author MercedesKK
* @date 2022-9-7
* @brief the Linklist written by me
* @email 2455650395@qq.com
*/
#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include<iostream>
#include<assert.h>

using std::cin;
using std::cout;
using std::endl;

namespace MercedesKK
{
	// 前向声明
	template<class T>
	class List;

	// @brief 结点类
	template<class T>
	class Node
	{
	public:
		T _data;			///< 元素
		Node<T>* _next;		///< 后指针
		Node<T>* _prev;		///< 前指针

		Node(const T& val = T()) :_data(val), _next(nullptr), _prev(nullptr) {}

		void prints() { cout << "sss" << endl; }
	};

	// @brief 封装迭代器
	template<class T, class Ref, class Ptr>
	class ListIterator
	{
		friend List<T>;

	public:
		using LinkNode = Node<T>;
		using self = ListIterator<T, Ref, Ptr>;
		// 引用
		using reference = Ref;
		using const_reference = const Ref;
		// 指针
		using pointer = Ptr;
		using const_pointer = const Ptr;

	private:
		LinkNode* _pnode;				///< 迭代器本质是指针

	public:

		ListIterator(LinkNode* pnode = nullptr) :_pnode(pnode) {}

		ListIterator(const self& lt) :_pnode(lt._pnode) {}

		reference operator*() { return _pnode->_data; }
		pointer operator->() { return &(operator*()); }
		const_reference operator*()const { return _pnode->_data; }
		const_pointer operator->()const { return &(operator*()); }

		bool operator!=(const self& x)const { return _pnode != x._pnode; }
		bool operator==(const self& x)const { return _pnode == x._pnode; }

		// @brief 前置自增
		self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		// @brief 后置自增
		self operator++(int)
		{
			LinkNode* tmp = _pnode;
			_pnode = _pnode->_next;
			return tmp;
		}

		// @brief 前置自减
		self& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		// @brief 后置自减
		self operator--(int)
		{
			LinkNode* tmp = _pnode;
			_pnode = _pnode->_prev;
			return tmp;
		}

		// @brief 重载+
		self operator+(int i)
		{
			while (i--)
			{
				_pnode = _pnode->_next;
			}
			return *this;
		}

		// @brief 重载-
		self operator-(int i)
		{
			while (i--)
			{
				_pnode = _pnode->_prev;
			}
			return *this;
		}
	};

	/// @brief 仿照STL中的List
	template<class T>
	class List
	{
	public:
		using LinkNode = Node<T>;
		using iterator = ListIterator<T, T&, T*>;
		using const_iterator = ListIterator<T, const T&, const T*>;

	private:
		LinkNode* _head;		///< 头指针

		/// @brief 创建头结点
		void Creatphead()
		{
			_head = new LinkNode;
			_head->_next = _head;
			_head->_prev = _head;
		}

	public:
		iterator begin() { return _head->_next; }					///< 头迭代器
		iterator end() { return _head; }							///< 尾迭代器
		const_iterator cbegin()const { return _head->_next; }		///< const 头迭代器
		const_iterator cend()const { return _head; }				///< const 尾迭代器

		/// @brief 无参构造函数
		List() { Creatphead(); }

		/// @brief 迭代器区间构造函数
		/// @param 两个迭代器
		template<class InputIterator>
		List(InputIterator first, InputIterator last)
		{
			Creatphead();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		/// @brief 构造指定n个元素函数
		List(int n, const T& val = T())
		{
			Creatphead();
			while (n)
			{
				push_back(val);
				n--;
			}
		}

		/// @brief 拷贝构造函数
		List(const List<T>& lt)
		{
			Creatphead();
			List tmp(lt.cbegin(), lt.cend());
			swap(tmp);
		}

		/// @brief 析构函数
		~List()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		/// @brief 赋值运算符重载
		List<T>& operator=(const List<T>& lt)
		{
			List<T> tmp(lt);
			swap(tmp);
		}

		/// @brief 尾插
		void push_back(const T& val) { insert(end(), val); }

		/// @brief 头插
		void push_front(const T& val) { insert(begin(), val); }

		/// @brief 尾删
		void pop_back() { erase(--end()); }

		/// @brief 头删
		void pop_front() { erase(begin()); }

		/// @brief 任意位置插入一个数据
		iterator insert(iterator pos, const T& val = T())
		{
			LinkNode* new_node = new LinkNode;
			new_node->_data = val;
			LinkNode* pprev = pos._pnode->_prev;

			new_node->_prev = pprev;
			pprev->_next = new_node;
			pos._pnode->_prev = new_node;
			new_node->_next = pos._pnode;

			return pos;
		}

		/// @brief 任意位置插入一个数据   n从1开始
		void insert(int n, const T& val = T())
		{
			iterator pos = begin() + n - 1;

			LinkNode* new_node = new LinkNode;
			new_node->_data = val;
			LinkNode* pprev = pos._pnode->_prev;

			new_node->_prev = pprev;
			pprev->_next = new_node;
			pos._pnode->_prev = new_node;
			new_node->_next = pos._pnode;
		}

		/// @brief 任意位置插入多个数据
		void insert(iterator pos, int n, const T& val)
		{
			iterator it = pos;
			while (n)
			{
				it = insert(it, val);
				n--;
			}
		}

		/// @brief 任意位置插入一个迭代器区间的数据
		template<class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last)
		{
			iterator it = pos;
			while (first != last)
			{
				it = insert(it, *first);
				first++;
			}
		}
		/// @brief  任意位置删除一个数据
		/// @return 返回的是删除元素的下一个位置
		iterator erase(iterator pos)
		{
			LinkNode* pdel = pos._pnode;
			LinkNode* pnext = pdel->_next;
			LinkNode* pprev = pdel->_prev;

			//如果为空就不用进行删除操作，同时不能删除头结点
			if (!empty() && pdel != _head)
			{
				pprev->_next = pnext;
				pnext->_prev = pprev;
				delete pdel;
			}

			return pnext;
		}

		/// @brief 删除一个迭代器区间的数据[first, last)
		iterator erase(iterator first, iterator last)
		{
			iterator it = first;
			while (it != last)
			{
				it = erase(it);
			}
			return last;
		}

		/// @brief  任意位置删除一个数据 n从1开始
		void erase(int n)
		{
			iterator pos = begin() + n - 1;

			LinkNode* pdel = pos._pnode;
			LinkNode* pnext = pdel->_next;
			LinkNode* pprev = pdel->_prev;

			//如果为空就不用进行删除操作，同时不能删除头结点
			if (!empty() && pdel != _head)
			{
				pprev->_next = pnext;
				pnext->_prev = pprev;
				delete pdel;
			}
		}

		/// @brief 查找元素
		iterator find(iterator first, iterator last, T element)
		{
			iterator it = first;
			while (it != last)
			{
				if (*it == element)
					return it;
				it++;
			}
			return last;
		}


		/// @brief 查找元素
		int find(const T& element)
		{
			int i = 1;
			iterator it = begin();
			while (it != end())
			{
				if (*it == element)
					return i;
				it++;
				i++;
			}
			return -1;
		}

		/// @brief 判空
		bool empty() { return _head->_next == _head; }

		/// @brief 计算个数
		size_t size() 
		{
			size_t count = 0;
			iterator it = begin();
			while (it != end())
			{
				count++;
				it++;
			}
			return count;
		}

		/// @brief 清除
		void clear() { erase(begin(), end()); }

		/// @brief 交换
		void swap(List<T>& lt) { std::swap(_head, lt._head); }
	};
}

//打印函数
template<class T>
void PrintCon(const MercedesKK::List<T>& con)
{
	auto it = con.cbegin();
	while (it != con.cend())
	{
		cout << *it << endl;
		it++;
	}
	cout << endl;
}

#endif