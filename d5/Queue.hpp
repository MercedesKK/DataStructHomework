/*
* @file Queue
* @author MercedesKK
* @date 2022-9-10
* @brief the mini Queue written by me
* @email 2455650395@qq.com
*/
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
		static const int default_size = 10;
	public:
		Queue() :begin(0), end(0), capacity(default_size) { data = new value_type[default_size]; };
		~Queue() { delete[]data; };
	private:
		value_type* data;	///< Ԫ��˳������
		int begin;			///< ͷָ�루ͬ��������
		int end;			///< βָ��
		size_t capacity;	///< ����������   ��size�����ɺ���ʵ�֣����ٵ�������size���ݣ�

	public:
		void push(const value_type& e);
		void pop();

		value_type& front() const	{ return data[begin]; };
		value_type& back() const	{ return data[end - 1]; };


		/// @attention sizeָ��������Ԫ����������
		size_t size() const			{ return end - begin; };

		bool empty() const			{ return begin == end; };

		/// @brief ��size����capacityʱ������ģ��STL
		void extend();
	};

	template <typename T>
	void Queue<T>::push(const value_type& e)
	{
		extend();
		data[end++] = e;
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
		if (sz == capacity - 1)
		{
			value_type* tmp = new value_type[capacity << 1];

			for (int i = begin, j = 0; i != end; i++, j++)
				tmp[j] = data[i];

			begin = 0;
			end = sz;
			delete[]data;
			data = tmp;
			capacity <<= 1;
		}
	}
}
#endif
