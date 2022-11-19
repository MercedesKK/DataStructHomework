#include <stdio.h>
#include <iostream>
#include "Vector.hpp"

using namespace MySTL;

class KeyPath
{
public:
    static const int MAXN = 100;
    static const int INF = 0x3f3f3f3f;

public:
    struct Edges
    {
        int a;
        int b;
    };

    struct Point
    {
        int earlytime;  ///< 最早时间
        int lasttime;   ///< 最晚时间
        int indegree;   ///< 入度
        int outdegree;  ///< 出度
    } Points[MAXN];

private:
    int checkpoints;  ///< 顶点数
    int activities;   ///< 边数
    int G[MAXN][MAXN];///< 邻接矩阵
    int totaltime = 0;///< 总任务时间

    Vector<Edges> inputEdges; ///< 存按输入顺序的边

public:
    void carry()
    {
        std::cout << "为类似OJ便于测试数据，本题无输入提示，输入方式如下：\n";
        std::cout << "第一行输入任务交接点n和任务数量m\n";
        std::cout << "第2行至第m + 1行每行为3个正整数，分别是该任务开始和完成设计的交接点编号以及完成该任务所需要的时间，整数间用空格分隔\n";
        scanf_s("%d %d", &checkpoints, &activities);
        InitGraph();
        InitPoints();
        InsertActivities();
        totaltime = EarlytimeCheck();
        if (totaltime == 0)
            printf("\n0");
        else
        {
            printf("\n%d\n", totaltime);
            LasttimeCheck();
        }
    }

private:
    void InitGraph()
    {
        int i, j;
        for (i = 1; i <= checkpoints; i++)
            for (j = 1; j <= checkpoints; j++)
                G[i][j] = 0;
        return;
    }

    void InitPoints()
    {
        int i;
        for (i = 1; i <= checkpoints; i++)
        {
            Points[i].earlytime = 0;
            Points[i].lasttime = INF;
            Points[i].indegree = 0;
            Points[i].outdegree = 0;
        }
        return;
    }

    void InsertActivities()
    {
        int i, point1, point2, time;
        for (i = 1; i <= activities; i++)
        {
            scanf_s("%d %d %d", &point1, &point2, &time);
            G[point1][point2] = time;
            Points[point1].outdegree++;
            Points[point2].indegree++;
            inputEdges.push_back({ point1, point2 });
        }
        return;
    }

    int EarlytimeCheck()
    {
        int i, Queue[MAXN], top = 0, rear = 0, point, maxtime = 0;
        for (i = 1; i <= checkpoints; i++)
        {
            if (!Points[i].indegree)
            {
                Points[i].indegree--;
                Queue[++top] = i;
            }
        }

        while (top != rear)
        {
            point = Queue[++rear];
            for (i = 1; i <= checkpoints; i++)
            {
                if (G[point][i])
                {
                    Points[i].indegree--;
                    if (!Points[i].indegree) Queue[++top] = i;
                    if (Points[i].earlytime < Points[point].earlytime + G[point][i])
                    {
                        Points[i].earlytime = Points[point].earlytime + G[point][i];
                        if (Points[i].earlytime > maxtime)
                            maxtime = Points[i].earlytime;
                    }
                }
            }
        }
        if (top != checkpoints)
            return 0;
        else
            return maxtime;
    }

    void LasttimeCheck()
    {
        int i, j, Queue[MAXN], top = 0, rear = 0, check, point, maxtime = 0;
        for (i = 1; i <= checkpoints; i++)
        {
            if (!Points[i].outdegree)
            {
                Queue[++top] = i;
                Points[i].lasttime = totaltime;
                Points[i].outdegree--;
            }
        }

        while (top != rear)
        {
            point = Queue[++rear];
            for (i = 1; i <= checkpoints; i++)
            {
                if (G[i][point])
                {
                    Points[i].outdegree--;
                    if (!Points[i].outdegree)  Queue[++top] = i;

                    if (Points[point].lasttime - G[i][point] < Points[i].lasttime)
                        Points[i].lasttime = Points[point].lasttime - G[i][point];
                }
            }
        }

        int cnt = 0;
        for (i = 1; i <= checkpoints; i++)
        {
            Vector<Edges> temp;
            if (Points[i].lasttime == Points[i].earlytime)
            {
                for (j = checkpoints; j >= 1; j--)
                {
                    if (G[i][j] && Points[j].lasttime == Points[j].earlytime && Points[i].lasttime == Points[j].lasttime - G[i][j])
                    {
                        //printf("%d->%d", i, j);
                        temp.push_back({ i, j });
                    }
                }
            }
            // 逆序输出
            for (auto it = inputEdges.end(); it >= inputEdges.begin(); it--)
            {
                for (auto it2 = temp.begin(); it2 != temp.end(); it2++)
                {
                    if (it->a == it2->a && it->b == it2->b)
                    {
                        printf("%d->%d\n", it->a, it->b);
                    }
                }
            }
        }
        return;
    }
};




int main()
{
    KeyPath solution;
    solution.carry();
    system("pause");
    return 0;
}
