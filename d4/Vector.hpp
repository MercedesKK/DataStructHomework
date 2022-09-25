/* @author �ž��� */
#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace MercedesKK
{
	/**
	* @brief ����ʵ�ֵ�vector����
	* @details ʵ����Ԫ����������_sizeʱ���������Ĳ���
	* �򻯣���������Vector����ֱ��ʵ��
	*/
	template <typename T>
	class Vector
	{
	public:
		using value_type = T;
		using iterator = T*;

	private:
		value_type* _data;		///< ��̬����ʵ�ֵ�����
		size_t _size;			///< ����Ԫ������
		size_t _capacity;		///< ��������

	public:

		/// @name Constructors
		/// @{
		Vector() :_data(nullptr), _size(0), _capacity(0) {}
		~Vector();
		Vector(const Vector& vec);
		Vector& operator=(const Vector& vec);
		/// @} 
		/// end of Constructors

		/// @name ���������
		/// @{
		value_type& operator[](size_t index) { return _data[index]; };
		bool operator==(const Vector& vec) const;
		/// @}
		/// end of overloads


		/// @name Operations
		/// @{
		/// 
		void push_back(value_type val);
		void pop_back() { --_size; };

		size_t Size() const { return _size; };
		size_t capacity() const { return _capacity; };
		bool empty() { return _size == 0; };
		void clear();

		value_type front() const { return _data[0]; };
		value_type back() const { return _data[_size - 1]; };

		void insert(iterator it, value_type val);
		void erase(iterator it);
		/// @}
		/// end of Operations

		/* ������ */
		iterator begin() { return _data; };
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

