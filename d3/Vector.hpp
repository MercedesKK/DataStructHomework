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
	/// @warning 1.ע��iterator��index�����±��0��ʼ
	/// @detail  ʵ����Ԫ����������sizeʱ���������Ĳ���
	template <typename T>
	class Vector
	{
	public:
		using value_type = T;
		using iterator = T*;
	private:
		value_type* data;		///< ��̬��������
		size_t size;			///< sizeͬSTL��size
		size_t capacity;		///< ͬSTL��capacity >= size 
	public:
		/// ���๹�캯�� + ��������
		Vector() :data(nullptr), size(0), capacity(0) {}
		~Vector();
		Vector(const Vector& vec);
		Vector& operator=(const Vector& vec);

		/// ���������
		value_type& operator[](size_t index) { return data[index]; };
		bool operator==(const Vector& vec) const;

		/// @param Ҫ�����ֵ
		void push_back(value_type val);

		void pop_back() { --size; };

		/// @return ��������������Ԫ�ص�����
		size_t Size() const { return size; };

		/// @return ��������������
		size_t Capacity() const { return capacity; };

		bool empty() { return size == 0; };

		/// @return ��������ͷ��Ԫ��
		value_type front() const { return data[0]; };

		/// @return ��������β��Ԫ��
		value_type back() const { return data[size - 1]; };

		/// @param		it ����Ϊiterator 
		/// @param		val ����Ϊvalue_type
		void insert(iterator it, value_type val);

		/// @param		it ����Ϊiterator 
		void erase(iterator it);

		/// @brief �ֶ����Vector
		void clear();

		/// @return ��������ͷ��������
		iterator begin() { return data; };

		/// @return ��������β��������
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

