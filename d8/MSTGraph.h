#pragma once
#include "Graph.h"
#include <cstring>

template <typename T>
class MSTGraph : public Graph<T>
{
public:
	using MyBase = Graph<T>;
	using Edgenode = EdgeNode<T>;

private:
	Edgenode* edges;
	bool edgesCanBePrinted;

public:
	MSTGraph() : MyBase(), edges(nullptr), edgesCanBePrinted(false) {}
	virtual ~MSTGraph() { if (edges) delete[] edges; }

public:
	void createPrimTree();
	void printPrimTree();

private:
	void __createPrimTree();
};

template<typename T>
void MSTGraph<T>::createPrimTree()
{
	if (MyBase::verticesNum == 0)
	{
		cout << "��δ������㣬���ȴ������" << endl;
		return;
	}
	if (MyBase::edgeMatrix == nullptr)
	{
		cout << "��δ�����ߣ����ȴ�����" << endl;
		return;
	}


	if (MyBase::edgeMatrix && MyBase::verticesNum)
		__createPrimTree();
}

template<typename T>
void MSTGraph<T>::printPrimTree()
{
	if (MyBase::verticesNum == 0)
	{
		cout << "��δ������㣬���ȴ������" << endl;
		return;
	}
	if (MyBase::edgeMatrix == nullptr)
	{
		cout << "��δ�����ߣ����ȴ�����" << endl;
		return;
	}
	if (!edgesCanBePrinted)
	{
		cout << "δ������С��������" << endl;
		return;
	}
	cout << "��С�������Ķ��㼰��Ϊ��\n";
	for (int i = 0; i < MyBase::verticesNum - 1; i++)
	{
		cout << edges[i].start << "--<" << edges[i].weight << ">-->" << edges[i].end << "    ";
	}
	cout << endl;
}

template<typename T>
inline void MSTGraph<T>::__createPrimTree()
{
	cout << "��������С����������ʼ���㣺 ";
	char tagStart;     // ��ʼ��
	cin >> tagStart;

	/// ��ʼ��
	int k = MyBase::convertToIndex(tagStart);
	int n = MyBase::verticesNum;

	int* dist = new (std::nothrow)int[n]; // �ڱ�����delete
	int* st   = new (std::nothrow)int[n];
	int* pre  = new (std::nothrow)int[n];
 	edges = new Edgenode[n];  // ����������ȥdelete
	int res = 0;
	int cnt = 0; // edges���±�

	if (dist != nullptr && st != nullptr && pre != nullptr)
	{

		for (int i = 0; i < n; i++)
		{
			dist[i] = MyBase::maxWeight;
			st[i] = 0;
			pre[i] = 0;
		}

		dist[k] = 0;
		for (int i = 0; i < n; i++)
		{
			int t = -1;
			for (int j = 0; j < n; j++)
			{
				if (!st[j] && (t == -1 || dist[j] < dist[t]))
					t = j;
			}
			if (t != k)
				edges[cnt++] = Edgenode(MyBase::verticesList[pre[t]], MyBase::verticesList[t], MyBase::edgeMatrix[pre[t]][t]);

			st[t] = 1;
			res += dist[t];

			for (int j = 0; j < n; j++)
			{
				if (dist[j] > MyBase::edgeMatrix[t][j] && !st[j])
				{
					dist[j] = MyBase::edgeMatrix[t][j];
					pre[j] = t;
				}
			}
		}

		delete[] dist;
		delete[] st;
		delete[] pre;
	}
	if (res >= MyBase::maxWeight >> 1)
	{
		cout << "����������С������\n";
		edgesCanBePrinted = false;
	}
	else
	{
		cout << "����Prim��С��������\n";
		edgesCanBePrinted = true;
	}

}
