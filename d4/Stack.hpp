/* @author 张靖凯 */
#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <cstddef>

namespace MercedesKK
{
	/**
	* @brief 自行实现的stack容器
	* @details 栈顶指针为-1代表空栈
	*/
	template <class T>
	class Stack
	{
	public:
		using size_type  = size_t;
		using value_type = T;

	public:
		/// @brief Constructors
		Stack(size_type n = 10);
		~Stack();

		/// @name Operations
		/// @{
		void push(const value_type&);
		void pop();

		value_type& top() const;
		bool isEmpty() const;
		size_type size() const;
		/// @}
		/// end of Operations

	private:
		size_type _capacity;			     ///< 容量
		int _top;						     ///< 栈顶
		value_type* _ptrStack;				 ///< 一维数组指针

		void __ExpanCapacity();				 ///< 扩充数组函数
	};



	template <class value_type>
	Stack<value_type>::Stack(size_type n) : _capacity(n), _top(-1)
	{
		if (n < 1)
		{
			throw "参数错误,容量必须大于1 ";
		}

		_ptrStack = new value_type[n];
		if (_ptrStack == nullptr)
		{
			throw "系统错误,内存申请失败";
		}
	}

	template <class value_type>
	Stack<value_type>::~Stack()
	{
		if (_ptrStack != nullptr)
			delete[] _ptrStack;
	}

	template<class value_type>
	inline void Stack<value_type>::push(const value_type& item)
	{
		if (_top == _capacity - 1)
		{
			__ExpanCapacity();

		}
		_ptrStack[++_top] = item;
	}

	template<class value_type>
	inline void Stack<value_type>::pop()
	{
		if (isEmpty())
		{
			throw "空栈";
		}
		else
		{
			_top--;
		}
	}

	template<class value_type>
	inline value_type& Stack<value_type>::top() const
	{
		if (isEmpty())
		{
			throw "空栈";
		}
		else
		{
			return _ptrStack[_top];
		}
	}

	template<class value_type>
	inline bool Stack<value_type>::isEmpty() const
	{
		return _top == -1;
	}

	template<class value_type>
	inline size_t Stack<value_type>::size() const
	{
		return _top + 1;
	}

	template<class value_type>
	inline void Stack<value_type>::__ExpanCapacity()
	{
		value_type* temp = new value_type[2 * _capacity];

		if (temp == nullptr)
		{
			throw "系统错误";
		}
		std::copy(_ptrStack, _ptrStack + _capacity, temp);
		_capacity *= 2;
		delete[] _ptrStack;
		_ptrStack = temp;
	}
}

#endif // !_STACK_H_
