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
	int verticesNum;							///< ��������ֻ�ܸ�ֵһ�Σ�
	int edgesNum;								///< ����
	static const int maxWeight = INT_MAX >> 1;	///< ���Ȩֵ
	int** edgeMatrix;							///< �ڽӾ���
	T* verticesList;							///< T�����������±��Ӧ

	bool haveCreateNodeOnce;
	
public:
	// ���ж�̬��Ա�ں�����new����ֻnewһ��
	Graph() :verticesNum(0), edgesNum(0), edgeMatrix(nullptr), verticesList(nullptr), haveCreateNodeOnce(0){}
	virtual ~Graph();	// ���ó�Ա��̬�ڴ��ڴ�����


public:
	int convertToIndex(T nodeName); // ��������ظ������ص�һ�������ֵ
	void createNode();	// ִֻ��һ��new
	void createEdge();  // ִֻ��һ��new

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
	if (verticesList == nullptr) // ��û����
		return -1;

	for (int i = 0; i < verticesNum; i++)
		if (verticesList[i] == nodeName)
			return i;

	return -1; // û�ҵ�
}

template<typename T>
void Graph<T>::createNode()
{
	if (verticesNum)
	{
		cout << "\n�Ѿ����������㣬�����������\n";
		return;
	}
	haveCreateNodeOnce = true;

	if (!verticesList) // ����Ѿ����������������������ǾͲ�Ҫ�ٴ����룬����������Ѿ��̶�
	{
		cout << "�����붥��ĸ����� ";
		int nodenum;
		cin >> nodenum;

		verticesNum = nodenum;
		if (!cin || verticesNum < 2)
		{
			cout << "�����������" << endl;
			verticesNum = 0;
			cin.clear();
			cin.ignore(0x3f3f3f3f, '\n');
			return;
		}
	}

	// ��̬�����ڴ�  Ϊ������Ѿ�������˾Ͱ���ԭ���붥������ٴ�����
	if (verticesList == nullptr)
		verticesList = new (std::nothrow)T[verticesNum + 5];

	__addNode();
}

template<typename T>
void Graph<T>::__addNode()
{
	cout << "����������������(�������Ϊ"<< verticesNum <<")��";
	for (int i = 0; i < verticesNum; i++)
		cin >> verticesList[i];

	if (__judgeNodeRepeat()) // ���ظ�����Ϳ�����������
	{
		haveCreateNodeOnce = false;
	}
}

template<typename T>
void Graph<T>::__initMatrix()
{
	// �����ڽӾ���ռ�
	edgeMatrix = new (std::nothrow)int* [verticesNum];
	for (int i = 0; i < verticesNum; i++)
		edgeMatrix[i] = new (std::nothrow)int[verticesNum];

	// �ڽӾ����ʼ��
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
			cout << "�������ظ�" << endl;
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
		cout << "�޶���!���ȴ�������\n";
		return;
	}

	// ����Ѿ���̬�������Թ�
	if (edgeMatrix == nullptr)
		__initMatrix();

	T start{}, end{};
	int weight = maxWeight;
	int v1, v2;
	while (1)
	{
		cout << "�������������㼰�ߣ�����������0 0 0���� ";
		cin >> start >> end >> weight;

		if (start == '0' || end == '0' || weight == 0)
			break;

		v1 = convertToIndex(start);
		v2 = convertToIndex(end);

		while (v1 == -1 || v2 == -1)             // �ߺϷ��Լ��
		{
			if (v1 == -1)
				cout << "�������" << start << "��㲻���ڣ�\n";
			else if (v2 == -1)
				cout << "�������" << end << "��㲻���ڣ�\n";
			else if (v1 == -1 && v2 == -1)
				cout << "�������" << start << "��" << end << "��㲻���ڣ�\n";

			cout << "�����������������㼰��(����������0 0 0)�� ";
			cin >> start >> end >> weight;
			v1 = convertToIndex(start);
			v2 = convertToIndex(end);
		}

		if (edgeMatrix[v1][v2] != maxWeight && edgeMatrix[v1][v2] > 0)
			cout << "���ظ�����߹�ϵ���˱���Ϣ�������ԣ���������룺\n";

		if (v1 >= 0 && v1 < verticesNum && v2 >= 0 && v2 < verticesNum && edgeMatrix[v1][v2] == maxWeight)
		{
			edgesNum++;
			edgeMatrix[v1][v2] = edgeMatrix[v2][v1] = weight;
		}
	}
}

