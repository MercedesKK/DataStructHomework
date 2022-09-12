/*
* @file Vector
* @author MercedesKK
* @date 2022-9-9
* @brief the mini Vector written by me
* @email 2455650395@qq.com
*/
#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace MercedesKK
{
	/// @warning 1.注意iterator和index都是下标从0开始
	/// @detail  实现了元素数量超出_size时容量翻倍的操作
	template <typename T>
	class Vector
	{
	public:
		using value_type = T;
		using iterator = T*;
	private:
		value_type* _data;		///< 动态分配数组
		size_t _size;			///< _size同STL的_size
		size_t _capacity;		///< 同STL，_capacity >= _size 
	public:
		/// 五类构造函数 + 析构函数
		Vector() :_data(nullptr), _size(0), _capacity(0) {}
		~Vector();
		Vector(const Vector& vec);
		Vector& operator=(const Vector& vec);

		/// 运算符重载
		value_type& operator[](size_t index) { return _data[index]; };
		bool operator==(const Vector& vec) const;

		/// @param 要插入的值
		void push_back(value_type val);

		void pop_back() { --_size; };

		/// @return 返回容器里已有元素的数量
		size_t Size() const { return _size; };

		/// @return 返回容器的容量
		size_t capacity() const { return _capacity; };

		bool empty() { return _size == 0; };

		/// @return 返回容器头部元素
		value_type front() const { return _data[0]; };

		/// @return 返回容器尾部元素
		value_type back() const { return _data[_size - 1]; };

		/// @param		it 类型为iterator 
		/// @param		val 类型为value_type
		void insert(iterator it, value_type val);

		/// @param		it 类型为iterator 
		void erase(iterator it);

		/// @brief 手动清空Vector
		void clear();

		/// @return 返回容器头部迭代器
		iterator begin() { return _data; };

		/// @return 返回容器尾部迭代器
		iterator end() { return _data + _size; };

	};
	template <typename T>
	Vector<T>::~Vector()
	{
		delete[]_data;
		_data = nullptr;
		_size = 0;
		_capacity = 0;
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
		int index = it - _data;
		if (0 == _capacity) {
			_capacity = 1;
			_capacity = new value_type[1];
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
}
#endif // !_VECTOR_H_

