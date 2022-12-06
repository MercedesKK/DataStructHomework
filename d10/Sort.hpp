#ifndef SORT_H
#define SORT_H

#include <chrono>
#include <iostream>
#include <random>
#include "Vector.hpp"

using namespace std::chrono;
using std::cin;
using std::cout;
using std::endl;

namespace MercedesKK
{
	/// @brief 8�ַ�����������
	/// @notion ������ÿ��ѡ��һ��Ҫ���´����µ�Sort����
	/// @attention ģ���������Ƚ���������
	template <typename T>
	class Sort
	{
	public:
		Sort() :durationTime(0), count(0) {}

		void mySwap(T& a, T& b);
		/// @brief �����������Ϊn������������ΪT����Χ��0-1e5
		void generateVec(const int& n);
		
		// ���������£�
		void bubbleSort();
		void selectionSort();
		void insertSort();
		void shellSort();
		void quickSort();
		void heapSort();   
		void mergeSort();
		void baseSort();

	private:
		system_clock::time_point start;
		system_clock::time_point end;

		double durationTime;
		int count;

		int maxbit(Vector<int> data, int n);
		void __quickSort(int begin, int end);
		void __mergeSort(Vector<int>& tmp, int l, int r);

	public:
		Vector<T> vec;
	};


	template<typename T>
	inline void Sort<T>::mySwap(T& a, T& b)
	{
		T temp;
		temp = a;
		a = b;
		b = temp;
		count++;
	}

	template<typename T>
	inline void Sort<T>::generateVec(const int& n)
	{
		vec.clear();

		std::default_random_engine e(time(0));
		std::uniform_int_distribution<int> u(1, 10000000);

		for (int i = 0; i < n; i++)
			vec.push_back(u(e));
	}


	template<typename T>
	inline void Sort<T>::bubbleSort()
	{
		start = system_clock::now();
		for (int i = 0; i < vec.size() - 1; i++)
			for (int j = 0; j < vec.size() - i - 1; j++)
				if (vec[j] > vec[j + 1])
					mySwap(vec[j], vec[j + 1]);

		end = system_clock::now();
		durationTime = duration_cast<microseconds>(end - start).count();

		cout << "ð����������ʱ�䣺" << durationTime << " ΢��" << endl;
		cout << "ð�����򽻻�������" << count << " ��";
		cout << endl;

		count = 0;
	}

	template<typename T>
	inline void Sort<T>::selectionSort()
	{
		start = system_clock::now();
		for (int i = 0; i < vec.size() - 1; i++)
		{
			int itemp = i;
			for (int j = i + 1; j < vec.size(); j++)
			{
				if (vec[j] < vec[itemp])
					itemp = j;
			}
			if (i != itemp)
			{
				mySwap(vec[i], vec[itemp]);
			}
		}

		end = system_clock::now();
		durationTime = duration_cast<microseconds>(end - start).count();

		cout << "ѡ����������ʱ�䣺" << durationTime << " ΢��" << endl;
		cout << "ѡ�����򽻻�������" << count << " ��";
		cout << endl;

		count = 0;
	}

	template<typename T>
	inline void Sort<T>::insertSort()
	{
		start = system_clock::now();
		for (int i = 0; i < vec.size() - 1; i++)
		{
			int end = i;
			T temp = vec[end + 1];

			while (end >= 0)
			{
				if (vec[end] > temp)
				{
					vec[end + 1] = vec[end];
					end--;
					count++;
				}
				else
					break;
			}
			vec[end + 1] = temp;
		}

		end = system_clock::now();
		durationTime = duration_cast<microseconds>(end - start).count();

		cout << "������������ʱ�䣺" << durationTime << " ΢��" << endl;
		cout << "�������򽻻�������" << count << " ��";
		cout << endl;

		count = 0;
	}
	template<typename T>
	inline void Sort<T>::shellSort()
	{
		start = system_clock::now();

		int gap = vec.size();
		while (gap > 1)
		{
			gap /= 2;
			for (int i = 0; i < vec.size() - gap; i++)
			{
				int end = i;
				T temp = vec[end + gap];
				while (end >= 0)
				{
					if (temp < vec[end])
					{
						vec[end + gap] = vec[end];
						end -= gap;
						count++;
					}
					else
						break;
				}
				vec[end + gap] = temp; 
			}
		}

		end = system_clock::now();
		durationTime = duration_cast<microseconds>(end - start).count();

		cout << "ϣ����������ʱ�䣺" << durationTime << " ΢��" << endl;
		cout << "ϣ�����򽻻�������" << count << " ��";
		cout << endl;

		count = 0;
	}


	template<typename T>
	inline void Sort<T>::quickSort()
	{
		 
		start = system_clock::now();

		__quickSort(0, vec.size() - 1);

		end = system_clock::now();

		durationTime = duration_cast<microseconds>(end - start).count();

		cout << "������������ʱ�䣺" << durationTime << " ΢��" << endl;
		cout << "�������򽻻�������" << count << " ��";
		cout << endl;

		count = 0;
	}

	template<typename T>
	inline void Sort<T>::heapSort()
	{
		 
		/// @brief down����
		auto f = [this](Vector<T>& rhsVec, int start, int end)
		{
			int dad = start, son = dad * 2 + 1;// ����
			while (son <= end)
			{
				if (son + 1 <= end && rhsVec[son + 1] > rhsVec[son])
					son++;
				if (rhsVec[dad] > rhsVec[son])
					return;
				else
				{
					mySwap(rhsVec[dad], rhsVec[son]);
					dad = son;
					son = dad * 2 + 1;
				}
			}
		};
	
		start = system_clock::now();

		for (int i = vec.size() / 2 - 1; i >= 0; i--)
		{
			f(vec, i, vec.size() - 1);
		}
		// �����������ɴ�С�����vector
		for (int i = vec.size() - 1; i > 0; i--)
		{
			mySwap(vec[0], vec[i]);
			f(vec, 0, i - 1);
		}

		end = system_clock::now();
		durationTime = duration_cast<microseconds>(end - start).count();

		cout << "����������ʱ�䣺" << durationTime << " ΢��" << endl;
		cout << "�����򽻻�������" << count << " ��";
		cout << endl;

		count = 0;
	}
	template<typename T>
	inline void Sort<T>::mergeSort()
	{
		 
		Vector<int> tmp(vec.size());

		start = system_clock::now();

		__mergeSort(tmp, 0, vec.size() - 1);

		end = system_clock::now();
		durationTime = duration_cast<microseconds>(end - start).count();

		cout << "�鲢��������ʱ�䣺" << durationTime << " ΢��" << endl;
		cout << "�鲢���򽻻�������" << count << " ��";
		cout << endl;

		count = 0;
	}

	template<typename T>
	inline void Sort<T>::baseSort()
	{
		start = system_clock::now();

		int d = maxbit(vec, vec.size());
		int* tmp = new int[vec.size()];
		int* cnt = new int[10]; //������
		int i, j, k, n = vec.size();
		int radix = 1;
		for (i = 1; i <= d; i++) //����d������
		{
			for (j = 0; j < 10; j++)
				cnt[j] = 0; //ÿ�η���ǰ��ռ�����
			for (j = 0; j < n; j++)
			{
				k = (vec[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
				cnt[k]++;
			}
			for (j = 1; j < 10; j++)
			{
				count++;
				cnt[j] = cnt[j - 1] + cnt[j]; //��tmp�е�λ�����η����ÿ��Ͱ
			}
			for (j = n - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
			{
				k = (vec[j] / radix) % 10;
				tmp[cnt[k] - 1] = vec[j];
				cnt[k]--;
			}
			for (j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�data��
				vec[j] = tmp[j];
			radix = radix * 10;
		}
		delete[]tmp;
		delete[]cnt;

		end = system_clock::now();
		durationTime = duration_cast<microseconds>(end - start).count();

		cout << "������������ʱ�䣺" << durationTime << " ΢��" << endl;
		cout << "�������򽻻�������" << count << " ��";
		cout << endl;

		count = 0;
	}

	template<typename T>
	inline int Sort<T>::maxbit(Vector<int> data, int n)
	{
		int maxData = data[0];              ///< �����
		/// ������������������λ��
		for (int i = 1; i < n; ++i)
		{
			if (maxData < data[i])
				maxData = data[i];
		}
		int d = 1;
		int p = 10;
		while (maxData >= p)
		{
			maxData /= 10;
			++d;
		}
		return d;

	}

	template<typename T>
	inline void Sort<T>::__quickSort(int begin, int end)
	{
		if (begin > end)
			return;
		int tmp = vec[begin];
		int i = begin;
		int j = end;
		while (i != j) {
			count++;
			while (vec[j] >= tmp && j > i)
				j--;
			while (vec[i] <= tmp && j > i)
				i++;
			if (j > i) {
				mySwap(vec[i], vec[j]);
			}
		}
		vec[begin] = vec[i];
		vec[i] = tmp;
		__quickSort(begin, i - 1);
		__quickSort(i + 1, end);
	}
	template<typename T>
	inline void Sort<T>::__mergeSort(Vector<int>& tmp, int l, int r)
	{
		if (l >= r) return;

		int mid = l + r >> 1;

		__mergeSort(tmp, l, mid), __mergeSort(tmp, mid + 1, r);

		int k = 0, i = l, j = mid + 1;
		while (i <= mid && j <= r)
		{
			count++;
			if (vec[i] <= vec[j]) tmp[k++] = vec[i++];
			else tmp[k++] = vec[j++];
		}
		while (i <= mid) tmp[k++] = vec[i++], count++;
		while (j <= r) tmp[k++] = vec[j++], count++;
		
		for (i = l, j = 0; i <= r; i++, j++) vec[i] = tmp[j];
	}
}

#endif // !SORT_H

