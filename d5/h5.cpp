#include <iostream>
#include "Queue.hpp"

using namespace MercedesKK;
using namespace std;

int main() 
{
    /// q1���������� q2��֮
    Queue<int> q1, q2;
    int n;
    cin >> n;
    while (n--)
    {
        int m;
        cin >> m;
        if (m % 2)
            q1.push(m);
        else
            q2.push(m);
    }

    int i = 0;    ///< i��Ŀ����Ϊ�˷�ֹ���һ����������ո�

    /// ����
    /// 
    /// ����������� 1.����ȫ����ż����ʣ��
    ///              2.����ȫ����ż��ûʣ��
    /// 
    /// ��Ϊ��ѭ����q1������Сѭ��q2
    while (!q1.empty())
    {
        int cnt = 2;
        // ������������
        while (cnt-- && !q1.empty())
        {
            if (i++)
                cout << " ";
            cout << q1.front();
            q1.pop();
        }
        // ����һ��ż��
        if (!q2.empty())
        {
            cout << " " << q2.front();
            q2.pop();
        }
    }

    /// ʣ���ż������

    while (!q2.empty())
    {
        if (i++)
            cout << " ";
        cout << q2.front();
        q2.pop();
    }

    return 0;
}
