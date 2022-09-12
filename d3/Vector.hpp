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
	/// @detail  实现了元素数量超出size时容量翻倍的操作
	template <typename T>
	class Vector
	{
	public:
		using value_type = T;
		using iterator = T*;
	private:
		value_type* data;		///< 动态分配数组
		size_t size;			///< size同STL的size
		size_t capacity;		///< 同STL，capacity >= size 
	public:
		/// 五类构造函数 + 析构函数
		Vector() :data(nullptr), size(0), capacity(0) {}
		~Vector();
		Vector(const Vector& vec);
		Vector& operator=(const Vector& vec);

		/// 运算符重载
		value_type& operator[](size_t index) { return data[index]; };
		bool operator==(const Vector& vec) const;

		/// @param 要插入的值
		void push_back(value_type val);

		void pop_back() { --size; };

		/// @return 返回容器里已有元素的数量
		size_t Size() const { return size; };

		/// @return 返回容器的容量
		size_t Capacity() const { return capacity; };

		bool empty() { return size == 0; };

		/// @return 返回容器头部元素
		value_type front() const { return data[0]; };

		/// @return 返回容器尾部元素
		value_type back() const { return data[size - 1]; };

		/// @param		it 类型为iterator 
		/// @param		val 类型为value_type
		void insert(iterator it, value_type val);

		/// @param		it 类型为iterator 
		void erase(iterator it);

		/// @brief 手动清空Vector
		void clear();

		/// @return 返回容器头部迭代器
		iterator begin() { return data; };

		/// @return 返回容器尾部迭代器
		iterator end() { return data + size; };

	};
	template <typename T>
	Vector<T>::~Vector()
	{
		delete[]data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}

	template <typename T>
	Vector<T>::Vector(const Vector& vec)
	{
		size = vec.size;
		capacity = vec.capacity;
		data = new value_type[capacity];
		for (int i = 0; i < size; i++)
		{
			data[i] = vec.data[i];
		}
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector& vec)
	{
		if (this == &vec)
			return *this;
		value_type* temp = new value_type[vec.capacity];
		for (int i = 0; i < vec.size; i++)
		{
			temp[i] = vec.data[i];
		}
		delete[]data;
		data = temp;
		size = vec.size;
		capacity = vec.capacity;
		return *this;
	}

	template <typename T>
	void Vector<T>::push_back(value_type val)
	{
		if (capacity == 0)
		{
			capacity = 1;
			data = new value_type[1];
		}
		else if (size + 1 > capacity)
		{
			capacity *= 2;
			value_type* temp = new value_type[capacity];
			for (int i = 0; i < size; i++)
			{
				temp[i] = data[i];
			}
			delete[]data;
			data = temp;
		}
		data[size] = val;
		size++;
	}

	template <typename T>
	void Vector<T>::insert(iterator it, value_type val)
	{
		int index = it - data;
		if (0 == capacity) {
			capacity = 1;
			capacity = new value_type[1];
			data[0] = val;
		}
		else if (size + 1 > capacity)
		{
			capacity *= 2;
			value_type* temp = new value_type[capacity];
			for (int i = 0; i < index; ++i) {
				temp[i] = data[i];
			}
			temp[index] = val;
			for (int i = index; i < size; ++i) {
				temp[i + 1] = data[i];
			}
			delete[] data;
			data = temp;
		}
		else {
			for (int i = size - 1; i >= index; --i) {
				data[i + 1] = data[i];
			}
			data[index] = val;
		}
		++size;
	}

	template <typename T>
	void Vector<T>::erase(iterator it)
	{
		size_t index = it - data;
		for (int i = index; i < size - 1; i++)
		{
			data[i] = data[i + 1];
		}
		size--;
	}

	template<typename T>
	inline void Vector<T>::clear()
	{
		delete[]data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}


	template <typename T>
	bool Vector<T>::operator==(const Vector& vec) const
	{
		if (size != vec.size)
			return false;
		for (int i = 0; i < size; i++)
		{
			if (data[i] != vec.data[i])
				return false;
		}
		return true;
	}
}
#endif // !_VECTOR_H_

