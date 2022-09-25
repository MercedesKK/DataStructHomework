/* @author �ž��� */
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <iostream>
#include "Vector.hpp"
/// ����STL�����Լ���Vector��ʵ���Լ����ȶ���

namespace MercedesKK
{

	template<typename T, typename compare = std::less<T>>
	class Priority_queue 
	{
	private:
		size_t _size = 0;	///< ������С
		Vector<T> _pq;		///< ��vectorʵ��
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
		//���ֻ��һ��Ԫ�أ�return
		int idx = _size - 1;
		if (idx == 0)
			return;

		//�ϸ���key�����丸�ڵ㣬���ϸ��������ڵ㻻�����棩��idx�ĸ��ڵ���(idx - 1) / 2
		while (idx > 0 && _cmp(_pq[(idx - 1) / 2], key)) 
		{
			_pq[idx] = _pq[(idx - 1) / 2];//�����ڵ㻻������
			idx = (idx - 1) / 2;//����idx��ֱ��idx�ĸ��ڵ����key��ֹͣ
		}
		_pq[idx] = key;//��key�ŵ���ȷ��λ��
	}

	//������Ԫ��ɾ������β��Ԫ���滻��������Ȼ���³���Ԫ��
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
		//��ĩβ��Ԫ�ػ���ͷ����ĩβ��pop��ȥ
		_pq[0] = _pq[_size - 1];
		_pq.pop_back();
		//Ȼ���³��»���ͷ����Ԫ��
		_size--;
		int idx = 0;
		T tmp = _pq[0];
		int leftChild = 2 * (idx + 1) - 1;
		int rightChild = 2 * (idx + 1);
		while (leftChild < _size) 
		{
			//child,��¼�³������ӽڵ㻹�����ӽڵ㣬���ǲ���
			int child = idx;

			if (_cmp(tmp, _pq[leftChild]))
				child = leftChild;

			if (rightChild < _size && _cmp(_pq[child], _pq[rightChild]))
				child = rightChild;

			if (idx == child)
				break;

			_pq[idx] = _pq[child];//��child����ȥ��child��λ����ʱ��tmp
			idx = child;
			leftChild = 2 * (idx + 1) - 1;//���idx�����������ӽڵ㣬�����������˳�
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

	//��ն�
	template<typename T, typename compare>
	inline void Priority_queue<T, compare>::clear()
	{
		_pq.clear();
		_size = 0;
	}
}

#endif // !_PRIORITY_QUEUE_H_
