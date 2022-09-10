#include <iostream>
#include <string>
#include <cassert>
#include "Vector.hpp"

//using namespace std;		///< 别用
using namespace MercedesKK;	///< use my namespace

struct Position
{
	int x;	///< 坐标x
	int y;	///< 坐标y
};

/// 为解题方便 开全局变量
/// maze 是从左上角（0,0）开始的！
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
/// 出口位置
Position exitPos;
/// 入口位置
Position inPos;
/// 储存每一个经过的坐标
Vector<Position> route;
/// 判断是否为出口
int tag = 0;

/// @detail 回溯深搜
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

            // 回溯
            route.erase(route.end() - 1);
            maze[x][y] = '0';
        }
    }
}

/// @brief   打印地图
/// @warning 先dfs之后找到路线之后，再把坐标设置成'x'
void printMap()
{
    std::cout << "迷宫地图：" << std::endl << "\t";
    for (int i = 0; i < 7; i++)
        std::cout << i << "列" << "\t";

    std::cout << std::endl;

    for (int i = 0; i < 7; i++)
    {
        std::cout << i << "行" << "\t";
        for (int j = 0; j < 7; j++)
        {
            std::cout << maze[i][j] << "\t";
        }
        std::cout << std::endl << std::endl;
    }
}

/// @detail 打印路线
void printRoute()
{
    std::cout << "迷宫路径:" << std::endl;
    for (auto it = route.begin(); it != route.end() - 1; it++)
    {
        std::cout << "<" << it->x << "," << it->y << "> " << "---> ";
    }

    std::cout << "<" << (route.end() - 1)->x << "," << (route.end() - 1)->y << ">" << std::endl;
}

/// 输入输出坐标
void readInOut()
{
    std::cout << "请输入入口坐标（如输入1 1代表入口为(1,1)）:";
    while (1)
    {
        std::cin >> inPos.x >> inPos.y;
        assert(inPos.x >= 0 && inPos.x <= 6 && std::cin.good()), assert(inPos.y >= 0 && inPos.y <= 6 && std::cin.good());
        if (maze[inPos.x][inPos.y] == '#')
        {
            std::cerr << "输入的坐标处为障碍，请重新输入" << std::endl;
            continue;
        }
        break;
    }

    std::cout << "请输入出口坐标（如输入5 5代表入口为(5,5)）:";
    while (1)
    {
        std::cin >> exitPos.x >> exitPos.y;
        assert(exitPos.x >= 0 && exitPos.x <= 6 && std::cin.good()), assert(exitPos.y >= 0 && exitPos.y <= 6 && std::cin.good());
        if (maze[exitPos.x][exitPos.y] == '#')
        {
            std::cerr << "输入的坐标处为障碍，请重新输入" << std::endl;
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

