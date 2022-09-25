/* @author �ž��� */
#ifndef _QUEUE_H_
#define _QUEUE_H_

namespace MercedesKK
{
	/// @brief �򵥶���
	/// @detail ���๹�캯��ֻʵ�ֵ�һ�� ������δʵ��
	template <typename T>
	class Queue
	{
	public:
		using value_type = T;
		static const int _default_size = 10;
	public:
		Queue() :begin(0), _end(0), _capacity(_default_size) { _data = new value_type[_default_size]; };
		~Queue() { delete[]_data; };
	private:
		value_type* _data;	///< Ԫ��˳������
		int begin;			///< ͷָ�루ͬ��������
		int _end;			///< βָ��
		size_t _capacity;	///< ����������   ��size�����ɺ���ʵ�֣����ٵ�������size���ݣ�

	public:
		void push(const value_type& e);
		void pop();

		value_type& front() const	{ return _data[begin]; };
		value_type& back() const	{ return _data[_end - 1]; };


		/// @attention sizeָ��������Ԫ����������
		size_t size() const			{ return _end - begin; };

		bool empty() const			{ return begin == _end; };

		/// @brief ��size����_capacityʱ������ģ��STL
		void extend();
	};

	template <typename T>
	void Queue<T>::push(const value_type& e)
	{
		extend();
		_data[_end++] = e;
	}

	template <typename T>
	void Queue<T>::pop()
	{
		if (!empty())
		{
			begin++;  // ѭ������
		}
	}

	template<typename T>
	void Queue<T>::extend()
	{
		size_t sz = size();
		if (sz == _capacity - 1)
		{
			value_type* tmp = new value_type[_capacity << 1];

			for (int i = begin, j = 0; i != _end; i++, j++)
				tmp[j] = _data[i];

			begin = 0;
			_end = sz;
			delete[]_data;
			_data = tmp;
			_capacity <<= 1;
		}
	}
}
#endif
