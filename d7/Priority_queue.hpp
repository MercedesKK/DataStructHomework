/* @author 张靖凯 */
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <iostream>
#include "Vector.hpp"
/// 仿照STL，用自己的Vector来实现自己优先队列

namespace MercedesKK
{

	template<typename T, typename compare = std::less<T>>
	class Priority_queue 
	{
	private:
		size_t _size = 0;	///< 容量大小
		Vector<T> _pq;		///< 以vector实现
		compare _cmp;		///< function object
	public:
		Priority_queue()  {}
		~Priority_queue() {};

		void push(const T& key);
		void pop();
		T top();
		void clear();
		size_t size()	{ return _size; }
		bool empty()	{ return _size == 0 ? true : false; }
	};

	template<typename T, typename compare>
	void Priority_queue<T, compare>::push(const T& key)
	{
		_pq.push_back(key);
		_size++;
		//如果只有一个元素，return
		int idx = _size - 1;
		if (idx == 0)
			return;

		//上浮，key大于其父节点，即上浮（将父节点换到下面），idx的父节点是(idx - 1) / 2
		while (idx > 0 && _cmp(_pq[(idx - 1) / 2], key)) 
		{
			_pq[idx] = _pq[(idx - 1) / 2];//将父节点换到下面
			idx = (idx - 1) / 2;//更新idx，直到idx的父节点大于key，停止
		}
		_pq[idx] = key;//将key放到正确的位置
	}

	//将顶部元素删除，将尾部元素替换到顶部，然后下沉该元素
	template<typename T, typename compare>
	void Priority_queue<T, compare>::pop()
	{
		if (_size == 0)
			return;
		if (_size == 1) 
		{
			_pq.clear();
			_size = 0;
			return;
		}
		//将末尾的元素换到头部，末尾的pop出去
		_pq[0] = _pq[_size - 1];
		_pq.pop_back();
		//然后下沉新换到头部的元素
		_size--;
		int idx = 0;
		T tmp = _pq[0];
		int leftChild = 2 * (idx + 1) - 1;
		int rightChild = 2 * (idx + 1);
		while (leftChild < _size) 
		{
			//child,记录下沉到左子节点还是右子节点，还是不动
			int child = idx;

			if (_cmp(tmp, _pq[leftChild]))
				child = leftChild;

			if (rightChild < _size && _cmp(_pq[child], _pq[rightChild]))
				child = rightChild;

			if (idx == child)
				break;

			_pq[idx] = _pq[child];//将child浮上去，child的位置暂时给tmp
			idx = child;
			leftChild = 2 * (idx + 1) - 1;//如果idx还存在左右子节点，继续；否则退出
			rightChild = 2 * (idx + 1);
		}
		_pq[idx] = tmp;
	}



	template<typename T, typename compare>
	inline T Priority_queue<T, compare>::top()
	{
		if (empty()) 
			throw("Priority queue is empty!");
		return _pq[0];
	}

	//清空堆
	template<typename T, typename compare>
	inline void Priority_queue<T, compare>::clear()
	{
		_pq.clear();
		_size = 0;
	}
}

#endif // !_PRIORITY_QUEUE_H_
