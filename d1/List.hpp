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
	// ǰ������
	template<class T>
	class List;

	// @brief �����
	template<class T>
	class Node
	{
	public:
		T _data;			///< Ԫ��
		Node<T>* _next;		///< ��ָ��
		Node<T>* _prev;		///< ǰָ��

		Node(const T& val = T()) :_data(val), _next(nullptr), _prev(nullptr) {}

		void prints() { cout << "sss" << endl; }
	};

	// @brief ��װ������
	template<class T, class Ref, class Ptr>
	class ListIterator
	{
		friend List<T>;

	public:
		using LinkNode = Node<T>;
		using self = ListIterator<T, Ref, Ptr>;
		// ����
		using reference = Ref;
		using const_reference = const Ref;
		// ָ��
		using pointer = Ptr;
		using const_pointer = const Ptr;

	private:
		LinkNode* _pnode;				///< ������������ָ��

	public:

		ListIterator(LinkNode* pnode = nullptr) :_pnode(pnode) {}

		ListIterator(const self& lt) :_pnode(lt._pnode) {}

		reference operator*() { return _pnode->_data; }
		pointer operator->() { return &(operator*()); }
		const_reference operator*()const { return _pnode->_data; }
		const_pointer operator->()const { return &(operator*()); }

		bool operator!=(const self& x)const { return _pnode != x._pnode; }
		bool operator==(const self& x)const { return _pnode == x._pnode; }

		// @brief ǰ������
		self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		// @brief ��������
		self operator++(int)
		{
			LinkNode* tmp = _pnode;
			_pnode = _pnode->_next;
			return tmp;
		}

		// @brief ǰ���Լ�
		self& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		// @brief �����Լ�
		self operator--(int)
		{
			LinkNode* tmp = _pnode;
			_pnode = _pnode->_prev;
			return tmp;
		}

		// @brief ����+
		self operator+(int i)
		{
			while (i--)
			{
				_pnode = _pnode->_next;
			}
			return *this;
		}

		// @brief ����-
		self operator-(int i)
		{
			while (i--)
			{
				_pnode = _pnode->_prev;
			}
			return *this;
		}
	};

	/// @brief ����STL�е�List
	template<class T>
	class List
	{
	public:
		using LinkNode = Node<T>;
		using iterator = ListIterator<T, T&, T*>;
		using const_iterator = ListIterator<T, const T&, const T*>;

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
		iterator begin() { return _head->_next; }					///< ͷ������
		iterator end() { return _head; }							///< β������
		const_iterator cbegin()const { return _head->_next; }		///< const ͷ������
		const_iterator cend()const { return _head; }				///< const β������

		/// @brief �޲ι��캯��
		List() { Creatphead(); }

		/// @brief ���������乹�캯��
		/// @param ����������
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

		/// @brief ����ָ��n��Ԫ�غ���
		List(int n, const T& val = T())
		{
			Creatphead();
			while (n)
			{
				push_back(val);
				n--;
			}
		}

		/// @brief �������캯��
		List(const List<T>& lt)
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

		/// @brief ��ֵ���������
		List<T>& operator=(const List<T>& lt)
		{
			List<T> tmp(lt);
			swap(tmp);
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

		/// @brief ����λ�ò���һ������   n��1��ʼ
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

		/// @brief  ����λ��ɾ��һ������ n��1��ʼ
		void erase(int n)
		{
			iterator pos = begin() + n - 1;

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

#endif