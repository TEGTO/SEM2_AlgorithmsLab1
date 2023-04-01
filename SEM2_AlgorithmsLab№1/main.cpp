#include<iostream>
#include "BPlusTree.h"
#include <vector>
using namespace std;



int main()
{
	setlocale(LC_ALL, "Rus");

	BPlusTree<int> t(3);

	t.Insert(4);
	t.Insert(5);
	t.Insert(5);
	t.Insert(6);
	t.Insert(2);
	t.Insert(8);
	t.Insert(10);
	t.Print();
	t.PrintSorted();
	for (auto var : t.GetSorted())
	{
		cout << var << endl;
	}
	
	system("pause");
	return 0;
}