#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <algorithm>
#include <climits>

using std::cin;
using std::cout;
using std::endl;

/// @biref T represents the point type
template <typename T = char>
struct EdgeNode
{
	T start;
	T end;
	int weight;

	EdgeNode() :start(T()), end(T()), weight(0) {}
	EdgeNode(T rstart, T rend, int rweight) : start(rstart), end(rend), weight(rweight) {}
};

template<typename T = char>
class Graph
{
protected:
	int verticesNum;							///< 定点数（只能赋值一次）
	int edgesNum;								///< 边数
	static const int maxWeight = INT_MAX >> 1;	///< 最大权值
	int** edgeMatrix;							///< 邻接矩阵
	T* verticesList;							///< T类型与数组下标对应

	bool haveCreateNodeOnce;
	
public:
	// 所有动态成员在函数内new，且只new一次
	Graph() :verticesNum(0), edgesNum(0), edgeMatrix(nullptr), verticesList(nullptr), haveCreateNodeOnce(0){}
	virtual ~Graph();	// 所用成员动态内存在此析构


public:
	int convertToIndex(T nodeName); // 顶点可以重复，返回第一次输入的值
	void createNode();	// 只执行一次new
	void createEdge();  // 只执行一次new

private:
	void __addNode();
	void __initMatrix();

	bool __judgeNodeRepeat();
};



#endif // !GRAPH_H

template<typename T>
inline Graph<T>::~Graph()
{
	if (verticesList != nullptr)
		delete[] verticesList;

	if (edgeMatrix != nullptr)
	{
		for (int i = 0; i < verticesNum; i++)
			delete[] edgeMatrix[i];
		delete[] edgeMatrix;
	}
}

template<typename T>
int Graph<T>::convertToIndex(T nodeName)
{
	if (verticesList == nullptr) // 还没建立
		return -1;

	for (int i = 0; i < verticesNum; i++)
		if (verticesList[i] == nodeName)
			return i;

	return -1; // 没找到
}

template<typename T>
void Graph<T>::createNode()
{
	if (verticesNum)
	{
		cout << "\n已经创建过顶点，无需继续创建\n";
		return;
	}
	haveCreateNodeOnce = true;

	if (!verticesList) // 如果已经输入过顶点个数建立过表那就不要再次输入，即顶点个数已经固定
	{
		cout << "请输入顶点的个数： ";
		int nodenum;
		cin >> nodenum;

		verticesNum = nodenum;
		if (!cin || verticesNum < 2)
		{
			cout << "顶点输入错误" << endl;
			verticesNum = 0;
			cin.clear();
			cin.ignore(0x3f3f3f3f, '\n');
			return;
		}
	}

	// 动态申请内存  为了如果已经申请过了就按照原输入顶点个数再次输入
	if (verticesList == nullptr)
		verticesList = new (std::nothrow)T[verticesNum + 5];

	__addNode();
}

template<typename T>
void Graph<T>::__addNode()
{
	cout << "请输入各顶点的名称(顶点个数为"<< verticesNum <<")：";
	for (int i = 0; i < verticesNum; i++)
		cin >> verticesList[i];

	if (__judgeNodeRepeat()) // 有重复顶点就可以重新输入
	{
		haveCreateNodeOnce = false;
	}
}

template<typename T>
void Graph<T>::__initMatrix()
{
	// 申请邻接矩阵空间
	edgeMatrix = new (std::nothrow)int* [verticesNum];
	for (int i = 0; i < verticesNum; i++)
		edgeMatrix[i] = new (std::nothrow)int[verticesNum];

	// 邻接矩阵初始化
	for (int i = 0; i < verticesNum; i++)
		for (int j = 0; j < verticesNum; j++)
			edgeMatrix[i][j] = maxWeight;
}

template<typename T>
inline bool Graph<T>::__judgeNodeRepeat()
{
	T* temp = new (std::nothrow)T[verticesNum];
	//memcpy(temp, verticesList, sizeof verticesList);
	if (temp != nullptr)
	{
		for (int i = 0; i < verticesNum; i++)
			temp[i] = verticesList[i];

		std::sort(temp, temp + verticesNum);
		if (std::unique(temp, temp + verticesNum) != temp + verticesNum)
		{
			cout << "顶点有重复" << endl;
			return true;
		}

		delete[] temp;
	}

	return false;
}

template<typename T>
void Graph<T>::createEdge()
{
	if (verticesNum == 0)
	{
		cout << "无顶点!请先创建顶点\n";
		return;
	}

	// 如果已经动态创建就略过
	if (edgeMatrix == nullptr)
		__initMatrix();

	T start{}, end{};
	int weight = maxWeight;
	int v1, v2;
	while (1)
	{
		cout << "请输入两个顶点及边（结束请输入0 0 0）： ";
		cin >> start >> end >> weight;

		if (start == '0' || end == '0' || weight == 0)
			break;

		v1 = convertToIndex(start);
		v2 = convertToIndex(end);

		while (v1 == -1 || v2 == -1)             // 边合法性检测
		{
			if (v1 == -1)
				cout << "你输入的" << start << "结点不存在！\n";
			else if (v2 == -1)
				cout << "你输入的" << end << "结点不存在！\n";
			else if (v1 == -1 && v2 == -1)
				cout << "你输入的" << start << "、" << end << "结点不存在！\n";

			cout << "请重新输入两个顶点及边(结束请输入0 0 0)： ";
			cin >> start >> end >> weight;
			v1 = convertToIndex(start);
			v2 = convertToIndex(end);
		}

		if (edgeMatrix[v1][v2] != maxWeight && edgeMatrix[v1][v2] > 0)
			cout << "你重复输入边关系，此边信息将被忽略！请继续输入：\n";

		if (v1 >= 0 && v1 < verticesNum && v2 >= 0 && v2 < verticesNum && edgeMatrix[v1][v2] == maxWeight)
		{
			edgesNum++;
			edgeMatrix[v1][v2] = edgeMatrix[v2][v1] = weight;
		}
	}
}

