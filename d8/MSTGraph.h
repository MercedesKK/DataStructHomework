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
		cout << "还未创建结点，请先创建结点" << endl;
		return;
	}
	if (MyBase::edgeMatrix == nullptr)
	{
		cout << "还未创建边，请先创建边" << endl;
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
		cout << "还未创建结点，请先创建结点" << endl;
		return;
	}
	if (MyBase::edgeMatrix == nullptr)
	{
		cout << "还未创建边，请先创建边" << endl;
		return;
	}
	if (!edgesCanBePrinted)
	{
		cout << "未生成最小生成树！" << endl;
		return;
	}
	cout << "最小生成树的顶点及边为：\n";
	for (int i = 0; i < MyBase::verticesNum - 1; i++)
	{
		cout << edges[i].start << "--<" << edges[i].weight << ">-->" << edges[i].end << "    ";
	}
	cout << endl;
}

template<typename T>
inline void MSTGraph<T>::__createPrimTree()
{
	cout << "请输入最小生成树的起始顶点： ";
	char tagStart;     // 起始点
	cin >> tagStart;

	/// 初始化
	int k = MyBase::convertToIndex(tagStart);
	int n = MyBase::verticesNum;

	int* dist = new (std::nothrow)int[n]; // 在本函数delete
	int* st   = new (std::nothrow)int[n];
	int* pre  = new (std::nothrow)int[n];
 	edges = new Edgenode[n];  // 在析构函数去delete
	int res = 0;
	int cnt = 0; // edges的下标

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
		cout << "不能生成最小生成树\n";
		edgesCanBePrinted = false;
	}
	else
	{
		cout << "生成Prim最小生成树！\n";
		edgesCanBePrinted = true;
	}

}
