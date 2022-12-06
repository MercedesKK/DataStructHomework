/* @author 张靖凯 */

#pragma once

#include <iostream>
#include <assert.h>
#include <xutility>

using std::cin;
using std::cout;
using std::endl;

namespace MercedesKK
{
	// 前向声明
	template <typename value_type> class List; 
	template <typename T, typename Ref, typename Ptr> class ListIterator;

	/// @brief 结点类
	template<class T>
	class Node
	{
	public:
		using value_type = T;
		using NodePtr = Node<T>*;
		using NodeRef = Node<T>&;

	public:
		value_type _data;	///< 元素
		NodePtr _next;		///< 后指针
		NodePtr _prev;		///< 前指针

		Node() noexcept :_data(value_type()), _next(this), _prev(this) {}
		Node(value_type val, NodePtr next, NodePtr prev) :_data(), _next(next), _prev(prev) {}
		Node(const Node& right) = delete;
		~Node() {}
	};


	/**
	* @class ListIterator
	* @brief 用迭代器封装指针，重载++ -- ()等operator
	* 同时迭代器种类设置为bidirectional_iterator_tag
	*/
	template<class T, class Ref, class Ptr>
	class ListIterator
	{
	public:
		using LinkNode		    = Node<T>;
		using self				= ListIterator<T, Ref, Ptr>;

		using iterator_category = std::bidirectional_iterator_tag;
		using value_type		= T;
		using pointer			= Ptr;
		using reference		    = Ref;
		using size_type			= size_t;
		using difference_type   = ptrdiff_t;

		using const_reference   = const Ref;
		using const_pointer		= const Ptr;

		friend List<value_type>;

	private:
		LinkNode* _pnode;				///< 迭代器本质是指针

	public:

		/// @brief 指针转迭代器构造函数
		ListIterator(LinkNode* pnode = nullptr) :_pnode(pnode) {}
		/// @brief 拷贝构造函数
		ListIterator(const self& lt) :_pnode(lt._pnode) {}


		reference operator*() { return _pnode->_data; }						///< 重载*
		pointer operator->() { return &(operator*()); }						///< 重载->
		const_reference operator*()const { return _pnode->_data; }			///< 重载*  const类型
		const_pointer operator->()const { return &(operator*()); }			///< 重载-> const类型
		bool operator!=(const self& x)const { return _pnode != x._pnode; }	///< 重载!=
		bool operator==(const self& x)const { return _pnode == x._pnode; }	///< 重载==
		self& operator++(){_pnode = _pnode->_next;return *this;}
		self operator++(int){LinkNode* tmp = _pnode;_pnode = _pnode->_next;return tmp;}
		self& operator--(){_pnode = _pnode->_prev;return *this;}
		self operator--(int){LinkNode* tmp = _pnode;_pnode = _pnode->_prev;return tmp;}
	};

	/// @brief 仿STL中的List
	template<class T>
	class List
	{
	public:
		using value_type	  = T;
		using difference_type = ptrdiff_t;
		using size_type		  = size_t;
		using pointer		  = value_type*;
		using reference		  = value_type&;

		using LinkNode		  = Node<T>;
		using iterator		  = ListIterator<T, T&, T*>;
		using const_iterator  = ListIterator<T, const T&, const T*>;

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
		iterator begin()	   noexcept { return _head->_next; }			///< 头迭代器
		iterator end()		   noexcept { return _head; }					///< 尾迭代器
		const_iterator cbegin()const noexcept { return _head->_next; }		///< const 头迭代器
		const_iterator cend()  const noexcept { return _head; }				///< const 尾迭代器

		/// @{
		/// @brief 无参构造函数
		List()noexcept { Creatphead(); }

		/// @brief 迭代器区间构造函数
		/// @param 两个迭代器
		template<class InputIterator>
		List(InputIterator first, InputIterator last) noexcept
		{
			Creatphead();
			while (first != last)
			{
				push_back(*first);
				first++;
			}
		}

		/// @brief 构造指定n个元素函数
		List(int n, const T& val = T())noexcept
		{
			Creatphead();
			while (n)
			{
				push_back(val);
				n--;
			}
		}

		/// @brief 拷贝构造函数
		List(const List<T>& lt)noexcept
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
		/// @}
		/// end of Constructors

		/// @brief 赋值运算符重载
		List<T>& operator=(List<T>& lt)
		{
			return lt;
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