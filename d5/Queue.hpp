/* @author 张靖凯 */
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
		static const int _default_size = 10;
	public:
		Queue() :begin(0), _end(0), _capacity(_default_size) { _data = new value_type[_default_size]; };
		~Queue() { delete[]_data; };
	private:
		value_type* _data;	///< 元素顺序容器
		int begin;			///< 头指针（同迭代器）
		int _end;			///< 尾指针
		size_t _capacity;	///< 容器的容量   （size的求法由函数实现，不再单独设置size数据）

	public:
		void push(const value_type& e);
		void pop();

		value_type& front() const	{ return _data[begin]; };
		value_type& back() const	{ return _data[_end - 1]; };


		/// @attention size指的是容器元素数量个数
		size_t size() const			{ return _end - begin; };

		bool empty() const			{ return begin == _end; };

		/// @brief 当size超过_capacity时翻倍，模拟STL
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
			begin++;  // 循环后移
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
