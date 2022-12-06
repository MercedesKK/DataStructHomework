#include "Sort.hpp"
#include <iomanip>

using namespace MercedesKK;
using namespace std;

int main()
{
	cout << "**" << setw(10) << ' ' << "排序算法比较" << setw(10) << ' ' << "**" << endl;
	cout << "====================================" << endl;
	cout << "**" << setw(9) << ' ' << "1 --- 冒泡排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "2 --- 选择排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "3 --- 直接插入排序" << setw(5) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "4 --- 希尔排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "5 --- 快速排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "6 --- 堆排序" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "7 --- 归并排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "8 --- 基数排序" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "9 --- 退出程序" << setw(9) << ' ' << "**" << endl;
	cout << "====================================" << endl;

	Sort<int> solution;
	int num;

	while (1)
	{
		cout << "请输入要产生随机数的个数: ";
		cin >> num;
		if (!cin || num <= 0 || num > 0x3f3f3f3f)
		{
			cin.clear();
			cin.ignore(0x3f3f3f3f, '\n');
			cout << "输入不合理，请重新输入" << endl;
			continue;
		}

		solution.generateVec(num);
		break;
	}

	while (1)
	{
		cout << endl << "请选择排序算法：";
		int id;
		cin >> id;
		if (!cin || id < 0 || id > 9)
		{
			cin.clear();
			cin.ignore(0x3f3f3f3f, '\n');
			cout << "输入错误，请重新输入" << endl;
		}

		if (id == 1)
			solution.generateVec(num), solution.bubbleSort();
		else if (id == 2)
			solution.generateVec(num), solution.selectionSort();
		else if (id == 3)
			solution.generateVec(num), solution.insertSort();
		else if (id == 4)
			solution.generateVec(num), solution.shellSort();
		else if (id == 5)
			solution.generateVec(num), solution.quickSort();
		else if (id == 6)
			solution.generateVec(num), solution.heapSort();
		else if (id == 7)
			solution.generateVec(num), solution.mergeSort();
		else if (id == 8)
			solution.generateVec(num), solution.baseSort();
		else if (id == 9)
			break;
	}

	system("pause");

	return 0;
}
