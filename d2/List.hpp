/* @author �ž��� */

#pragma once

#include <iostream>
#include <assert.h>
#include <xutility>

using std::cin;
using std::cout;
using std::endl;

namespace MercedesKK
{
	// ǰ������
	template <typename value_type> class List; 
	template <typename T, typename Ref, typename Ptr> class ListIterator;

	/// @brief �����
	template<class T>
	class Node
	{
	public:
		using value_type = T;
		using NodePtr = Node<T>*;
		using NodeRef = Node<T>&;

	public:
		value_type _data;	///< Ԫ��
		NodePtr _next;		///< ��ָ��
		NodePtr _prev;		///< ǰָ��

		Node() noexcept :_data(value_type()), _next(this), _prev(this) {}
		Node(value_type val, NodePtr next, NodePtr prev) :_data(), _next(next), _prev(prev) {}
		Node(const Node& right) = delete;
		~Node() {}
	};


	/**
	* @class ListIterator
	* @brief �õ�������װָ�룬����++ -- ()��operator
	* ͬʱ��������������Ϊbidirectional_iterator_tag
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
		LinkNode* _pnode;				///< ������������ָ��

	public:

		/// @brief ָ��ת���������캯��
		ListIterator(LinkNode* pnode = nullptr) :_pnode(pnode) {}
		/// @brief �������캯��
		ListIterator(const self& lt) :_pnode(lt._pnode) {}


		reference operator*() { return _pnode->_data; }						///< ����*
		pointer operator->() { return &(operator*()); }						///< ����->
		const_reference operator*()const { return _pnode->_data; }			///< ����*  const����
		const_pointer operator->()const { return &(operator*()); }			///< ����-> const����
		bool operator!=(const self& x)const { return _pnode != x._pnode; }	///< ����!=
		bool operator==(const self& x)const { return _pnode == x._pnode; }	///< ����==
		self& operator++(){_pnode = _pnode->_next;return *this;}
		self operator++(int){LinkNode* tmp = _pnode;_pnode = _pnode->_next;return tmp;}
		self& operator--(){_pnode = _pnode->_prev;return *this;}
		self operator--(int){LinkNode* tmp = _pnode;_pnode = _pnode->_prev;return tmp;}
	};

	/// @brief ��STL�е�List
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
		LinkNode* _head;		///< ͷָ��

		/// @brief ����ͷ���
		void Creatphead() 
		{
			_head = new LinkNode;
			_head->_next = _head;
			_head->_prev = _head;
		}

	public:
		iterator begin()	   noexcept { return _head->_next; }			///< ͷ������
		iterator end()		   noexcept { return _head; }					///< β������
		const_iterator cbegin()const noexcept { return _head->_next; }		///< const ͷ������
		const_iterator cend()  const noexcept { return _head; }				///< const β������

		/// @{
		/// @brief �޲ι��캯��
		List()noexcept { Creatphead(); }

		/// @brief ���������乹�캯��
		/// @param ����������
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

		/// @brief ����ָ��n��Ԫ�غ���
		List(int n, const T& val = T())noexcept
		{
			Creatphead();
			while (n)
			{
				push_back(val);
				n--;
			}
		}

		/// @brief �������캯��
		List(const List<T>& lt)noexcept
		{
			Creatphead();
			List tmp(lt.cbegin(), lt.cend());
			swap(tmp);
		}

		/// @brief ��������
		~List()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		/// @}
		/// end of Constructors

		/// @brief ��ֵ���������
		List<T>& operator=(List<T>& lt)
		{
			return lt;
		}

		/// @brief β��
		void push_back(const T& val) { insert(end(), val); }

		/// @brief ͷ��
		void push_front(const T& val) { insert(begin(), val); }

		/// @brief βɾ
		void pop_back() { erase(--end()); }

		/// @brief ͷɾ
		void pop_front() { erase(begin()); }

		/// @brief ����λ�ò���һ������
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

		/// @brief ����λ�ò���������
		void insert(iterator pos, int n, const T& val)
		{
			iterator it = pos;
			while (n)
			{
				it = insert(it, val);
				n--;
			}
		}

		/// @brief ����λ�ò���һ�����������������
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
		/// @brief  ����λ��ɾ��һ������
		/// @return ���ص���ɾ��Ԫ�ص���һ��λ��
		iterator erase(iterator pos)
		{
			LinkNode* pdel = pos._pnode;
			LinkNode* pnext = pdel->_next;
			LinkNode* pprev = pdel->_prev;

			//���Ϊ�վͲ��ý���ɾ��������ͬʱ����ɾ��ͷ���
			if (!empty() && pdel != _head)
			{
				pprev->_next = pnext;
				pnext->_prev = pprev;
				delete pdel;
			}

			return pnext;
		}

		/// @brief ɾ��һ�����������������[first, last)
		iterator erase(iterator first, iterator last)
		{
			iterator it = first;
			while (it != last)
			{
				it = erase(it);
			}
			return last;
		}

		/// @brief ����Ԫ��
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


		/// @brief ����Ԫ��
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

		/// @brief �п�
		bool empty() { return _head->_next == _head; }

		/// @brief �������
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

		/// @brief ���
		void clear() { erase(begin(), end()); }

		/// @brief ����
		void swap(List<T>& lt) { std::swap(_head, lt._head); }
	};
}

//��ӡ����
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