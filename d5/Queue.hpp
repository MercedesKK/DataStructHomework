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
	/// @brief 简单队列
	/// @detail 五类构造函数只实现第一个 其他暂未实现
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
		value_type* data;	///< 元素顺序容器
		int begin;			///< 头指针（同迭代器）
		int end;			///< 尾指针
		size_t capacity;	///< 容器的容量   （size的求法由函数实现，不再单独设置size数据）

	public:
		void push(const value_type& e);
		void pop();

		value_type& front() const	{ return data[begin]; };
		value_type& back() const	{ return data[end - 1]; };


		/// @attention size指的是容器元素数量个数
		size_t size() const			{ return end - begin; };

		bool empty() const			{ return begin == end; };

		/// @brief 当size超过capacity时翻倍，模拟STL
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
			begin++;  // 循环后移
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
