#include <iostream>
#include "Queue.hpp"
#include <assert.h>

using namespace MercedesKK;
using namespace std;

int main() 
{
    /// q1是奇数队列 q2反之
    Queue<int> q1, q2;
    int n;
    cin >> n;
    assert(cin);
    while (n--)
    {
        int m;
        cin >> m;

        assert(cin);

        if (m % 2)
            q1.push(m);
        else
            q2.push(m);
    }

    int i = 0;    ///< i的目的是为了防止最后一个数据输出空格

    /// 出队
    /// 
    /// 有两种情况： 1.奇数全出，偶数有剩余
    ///              2.奇数全出，偶数没剩余
    /// 
    /// 因为大循环是q1，里面小循环q2
    while (!q1.empty())
    {
        int cnt = 2;
        // 弹出两个奇数
        while (cnt-- && !q1.empty())
        {
            if (i++)
                cout << " ";
            cout << q1.front();
            q1.pop();
        }
        // 弹出一个偶数
        if (!q2.empty())
        {
            cout << " " << q2.front();
            q2.pop();
        }
    }

    /// 剩余的偶数出队

    while (!q2.empty())
    {
        if (i++)
            cout << " ";
        cout << q2.front();
        q2.pop();
    }

    cin.clear();
    cin.ignore(1024, '\n');

    cout << endl << "Enter to Exit";
    cin.get();

    return 0;
}
