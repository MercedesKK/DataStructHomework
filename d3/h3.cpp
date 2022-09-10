#include <iostream>
#include <string>
#include <cassert>
#include "Vector.hpp"

//using namespace std;		///< ����
using namespace MercedesKK;	///< use my namespace

struct Position
{
	int x;	///< ����x
	int y;	///< ����y
};

/// Ϊ���ⷽ�� ��ȫ�ֱ���
/// maze �Ǵ����Ͻǣ�0,0����ʼ�ģ�
char maze[10][10] = 
{
    "#######",
    "#0#000#",
    "#0#0###",
    "#00000#",
    "#0###0#",
    "#0#0#0#",
    "#######",
}; 
const Position direction[4] = { {0,1}, {0,-1} ,{1,0},{-1,0} };
/// ����λ��
Position exitPos;
/// ���λ��
Position inPos;
/// ����ÿһ������������
Vector<Position> route;
/// �ж��Ƿ�Ϊ����
int tag = 0;

/// @detail ��������
void dfs(int x, int y)
{
    if (x == exitPos.x && y == exitPos.y)
    {
        tag = 1;
        maze[x][y] = 'x';
        route.push_back(exitPos);
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        if (maze[x + direction[i].x][y + direction[i].y] == '0')
        {
            maze[x][y] = 'x';
            Position cur = { x,y };
            route.push_back(cur);

            dfs(x + direction[i].x, y + direction[i].y);

            if (tag == 1)
                return;

            // ����
            route.erase(route.end() - 1);
            maze[x][y] = '0';
        }
    }
}

/// @brief   ��ӡ��ͼ
/// @warning ��dfs֮���ҵ�·��֮���ٰ��������ó�'x'
void printMap()
{
    std::cout << "�Թ���ͼ��" << std::endl << "\t";
    for (int i = 0; i < 7; i++)
        std::cout << i << "��" << "\t";

    std::cout << std::endl;

    for (int i = 0; i < 7; i++)
    {
        std::cout << i << "��" << "\t";
        for (int j = 0; j < 7; j++)
        {
            std::cout << maze[i][j] << "\t";
        }
        std::cout << std::endl << std::endl;
    }
}

/// @detail ��ӡ·��
void printRoute()
{
    std::cout << "�Թ�·��:" << std::endl;
    for (auto it = route.begin(); it != route.end() - 1; it++)
    {
        std::cout << "<" << it->x << "," << it->y << "> " << "---> ";
    }

    std::cout << "<" << (route.end() - 1)->x << "," << (route.end() - 1)->y << ">" << std::endl;
}

/// �����������
void readInOut()
{
    std::cout << "������������꣨������1 1�������Ϊ(1,1)��:";
    while (1)
    {
        std::cin >> inPos.x >> inPos.y;
        assert(inPos.x >= 0 && inPos.x <= 6 && std::cin.good()), assert(inPos.y >= 0 && inPos.y <= 6 && std::cin.good());
        if (maze[inPos.x][inPos.y] == '#')
        {
            std::cerr << "��������괦Ϊ�ϰ�������������" << std::endl;
            continue;
        }
        break;
    }

    std::cout << "������������꣨������5 5�������Ϊ(5,5)��:";
    while (1)
    {
        std::cin >> exitPos.x >> exitPos.y;
        assert(exitPos.x >= 0 && exitPos.x <= 6 && std::cin.good()), assert(exitPos.y >= 0 && exitPos.y <= 6 && std::cin.good());
        if (maze[exitPos.x][exitPos.y] == '#')
        {
            std::cerr << "��������괦Ϊ�ϰ�������������" << std::endl;
            continue;
        }
        break;
    }
}

int main() 
{
    readInOut();
    dfs(inPos.x, inPos.y);
    printMap();
    printRoute();
    return 0;
}

