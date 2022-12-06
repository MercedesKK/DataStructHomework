/* @author 张靖凯 */
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdexcept>

namespace MercedesKK
{
	/**
	* @brief 自行实现的vector容器
	* @details 实现了元素数量超出_size时容量翻倍的操作
	* 简化，迭代器在Vector类内直接实现
	*/
	template <typename T>
	class Vector
	{
	public:
		using value_type = T;
		using iterator = T*;

	private:
		value_type* _data;		///< 动态分配实现的数组
		size_t _size;			///< 已有元素数量
		size_t _capacity;		///< 容器容量

	public:

		/// @name Constructors
		/// @{
		Vector() :_data(nullptr), _size(0), _capacity(0) {}
		Vector(int n) :_data(new value_type[n]()), _size(n), _capacity(n * 2) {}
		Vector(int n, value_type val);
		~Vector();
		Vector(const Vector& vec);
		Vector(Vector&& vec) = default;
		Vector& operator=(const Vector& vec);

		template <typename InputIterator>
		Vector(InputIterator first, InputIterator last);
		/// @} 
		// end of Constructors

		/// @name 重载运算符
		/// @{
		value_type& operator[](size_t index) { return _data[index]; };
		bool operator==(const Vector& vec) const;
		/// @}
		// end of overloads


		/// @name Operations
		/// @{
		/// 
		void push_back(value_type val);
		void pop_back() { --_size; };

		size_t size() const { return _size; };
		size_t capacity() const { return _capacity; };
		bool empty() { return _size == 0; };
		void clear();

		value_type front() const { return _data[0]; };
		value_type back() const { return _data[_size - 1]; };

		void insert(iterator it, value_type val);
		void erase(iterator it);
		/// @}
		// end of Operations

		/* 迭代器 */
		iterator begin() { return _data; };
		iterator end() { return _data + _size; };

	};

	template<typename T>
	inline Vector<T>::Vector(int n, value_type val)
	{
		_data = new value_type[n];
		_size = n;
		_capacity = 2 * n;
		for (size_t i = 0; i < n; i++)
		{
			_data[i] = val;
		}
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		if (_data != nullptr)
			clear();
	}

	template <typename T>
	Vector<T>::Vector(const Vector& vec)
	{
		_size = vec._size;
		_capacity = vec._capacity;
		_data = new value_type[_capacity];
		for (int i = 0; i < _size; i++)
		{
			_data[i] = vec._data[i];
		}
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector& vec)
	{
		if (this == &vec)
			return *this;
		value_type* temp = new value_type[vec._capacity];
		for (int i = 0; i < vec._size; i++)
		{
			temp[i] = vec._data[i];
		}
		delete[]_data;
		_data = temp;
		_size = vec._size;
		_capacity = vec._capacity;
		return *this;
	}

	template <typename T>
	void Vector<T>::push_back(value_type val)
	{
		if (_capacity == 0)
		{
			_capacity = 1;
			_data = new value_type[1];
		}
		else if (_size + 1 > _capacity)
		{
			_capacity *= 2;
			value_type* temp = new value_type[_capacity];
			for (int i = 0; i < _size; i++)
			{
				temp[i] = _data[i];
			}
			delete[]_data;
			_data = temp;
		}
		_data[_size] = val;
		_size++;
	}

	template <typename T>
	void Vector<T>::insert(iterator it, value_type val)
	{
		if (it - _data > _size || it - _data < 0)
			throw std::out_of_range("out_of_range");

		int index = it - _data;
		if (0 == _capacity) {
			_capacity = 1;
			_data = new value_type[1];
			_data[0] = val;
		}
		else if (_size + 1 > _capacity)
		{
			_capacity *= 2;
			value_type* temp = new value_type[_capacity];
			for (int i = 0; i < index; ++i) {
				temp[i] = _data[i];
			}
			temp[index] = val;
			for (int i = index; i < _size; ++i) {
				temp[i + 1] = _data[i];
			}
			delete[] _data;
			_data = temp;
		}
		else {
			for (int i = _size - 1; i >= index; --i) {
				_data[i + 1] = _data[i];
			}
			_data[index] = val;
		}
		++_size;
	}

	template <typename T>
	void Vector<T>::erase(iterator it)
	{
		if (it - _data > _size || it - _data < 0)
			throw std::out_of_range("out_of_range");

		size_t index = it - _data;
		for (int i = index; i < _size - 1; i++)
		{
			_data[i] = _data[i + 1];
		}
		_size--;
	}

	template<typename T>
	inline void Vector<T>::clear()
	{
		delete[]_data;
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}


	template <typename T>
	bool Vector<T>::operator==(const Vector& vec) const
	{
		if (_size != vec._size)
			return false;
		for (int i = 0; i < _size; i++)
		{
			if (_data[i] != vec._data[i])
				return false;
		}
		return true;
	}
	template<typename T>
	template<typename InputIterator>
	inline Vector<T>::Vector(InputIterator first, InputIterator last)
	{
		size_t offset = static_cast<size_t>(last - first);
		_data = new T[offset]();
		_size = offset;
		_capacity = 2 * offset;
		size_t index = 0;
		for (auto fir = first; fir != last; fir++)
		{
			_data[index++] = *fir;
		}
	}
}
#endif // !_VECTOR_H_

