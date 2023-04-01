#include<iostream>
#include <vector>
#include "../SEM2_AlgorithmsLab¹1/BPlusTree.h"
#include "../SEM2_AlgorithmsLab¹1/OBSTree.h"
#include "../SEM2_AlgorithmsLab¹1/PerfectHash.h"
using namespace std;


void PerfectHashExample()
{
	cout << "Enter number Of elements to contain: ";
	int numberOfElements;
	cin >> numberOfElements;
	cout << endl;
	FixedSet fs;
	
	vector<int> inputVector;
	

	for (int i = 0; i < numberOfElements; ++i)
	{
		int elemValue;
		cout << "Enter a element to add: ";
		cin >> elemValue;
		inputVector.push_back(elemValue);
	}
	
	fs.Initialize(inputVector);
	
	cout << "\nEnter number Of elements for search: ";
	int numberOfElementsForSearch;
	cin >> numberOfElementsForSearch;
	cout << endl;
	for (int i = 0; i < numberOfElementsForSearch; ++i)
	{
		cout << "Enter a element for search: ";
		int elem;
		cin >> elem;
		if (fs.Contains(elem))
		{
			cout << "Yes" << endl;
		}
		else
		{
			cout << "No" << endl;
		}
	}


}

void PerfectHashExampleString()
{

	FixedSet fs;

	vector<int> inputVector;
	string elemValue = "hddddddd";
	fs.StringInitialize(elemValue);

	if (fs.StringContains(elemValue ))
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}

	if (fs.StringContains(elemValue+"ddd"))
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "No" << endl;
	}
	


}

void bPlusTreeExample()
{
	BPlusTree<string> t(3);
	cout << "Enter count of elements B+ tree = ";
	int count = 0;
	string element;
	cin >> count;
	for (size_t i = 0; i < count; i++)
	{
		cout << "Enter a element = ";
		cin >> element;
		
		t.Insert(element);
	}
	cout << "Tree: \n\n";
	t.Print();
	cout << "\nSorted Elements:\n";
	t.PrintSorted();
	cout << "\nChoose the elemt to delete:  ";
	cin >> element;
	t.Remove(element);
	cout << "\nSorted Elements without deleted element:\n";
	t.PrintSorted();

}



void OBSTreeExample()
{
	
	double keys[] = { 1, 2, 3};
	double freq[] = { 34, 8, 50 };
		int n = sizeof(keys) / sizeof(keys[0]);
		print(keys, freq, n);
		cout << "\n\nCost of Optimal BST is " << optimalSearchTree(keys, freq, n)<<endl<< endl;
		
}

int main()
{
	setlocale(LC_ALL, "Rus");
	//PerfectHashExample();
	//PerfectHashExampleString();
	//bPlusTreeExample();
	//OBSTreeExample();
	system("pause");
	return 0;
}