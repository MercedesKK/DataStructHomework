#include <iostream>
#include "Priority_queue.hpp"
#include "Vector.hpp"
#include <assert.h>

using namespace MercedesKK;
using namespace std;

int main() 
{
	int n, cost, sum = 0, a;
	// �������ȶ��У�С����ǰ��
	Priority_queue<int, Vector<int> ,greater<int>> q; 
	cin >> n;
	assert(cin);
	for (int i = 0; i < n; i++) 
	{
		cin >> cost;
		q.push(cost);
	}

	// ���в�Ϊ��
	while (q.size() > 1) 
	{
		a = q.top();
		q.pop();
		a += q.top();
		q.pop();
		q.push(a);
		sum += a;
	}
	cout << sum;

	cin.clear();
	cin.ignore(1024, '\n');

	cout << endl << "Enter to Exit";
	cin.get();

	return 0;
}
