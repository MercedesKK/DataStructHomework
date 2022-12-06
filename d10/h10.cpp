#include "Sort.hpp"
#include <iomanip>

using namespace MercedesKK;
using namespace std;

int main()
{
	cout << "**" << setw(10) << ' ' << "�����㷨�Ƚ�" << setw(10) << ' ' << "**" << endl;
	cout << "====================================" << endl;
	cout << "**" << setw(9) << ' ' << "1 --- ð������" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "2 --- ѡ������" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "3 --- ֱ�Ӳ�������" << setw(5) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "4 --- ϣ������" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "5 --- ��������" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "6 --- ������" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "7 --- �鲢����" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "8 --- ��������" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "9 --- �˳�����" << setw(9) << ' ' << "**" << endl;
	cout << "====================================" << endl;

	Sort<int> solution;
	int num;

	while (1)
	{
		cout << "������Ҫ����������ĸ���: ";
		cin >> num;
		if (!cin || num <= 0 || num > 0x3f3f3f3f)
		{
			cin.clear();
			cin.ignore(0x3f3f3f3f, '\n');
			cout << "���벻��������������" << endl;
			continue;
		}

		solution.generateVec(num);
		break;
	}

	while (1)
	{
		cout << endl << "��ѡ�������㷨��";
		int id;
		cin >> id;
		if (!cin || id < 0 || id > 9)
		{
			cin.clear();
			cin.ignore(0x3f3f3f3f, '\n');
			cout << "�����������������" << endl;
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
