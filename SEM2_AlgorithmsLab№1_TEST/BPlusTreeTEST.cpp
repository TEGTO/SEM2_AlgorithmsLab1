#include "pch.h"
#include "../SEM2_AlgorithmsLab¹1/BPlusTree.h"
#include<vector>
using namespace std;

namespace BPlusTreeTest
{


	TEST(BPlusTree, Insert_1) {

		//arrange
		BPlusTree<int> t(3);
	
		BPlusTree<int> t1(3);
		
		//act
		t.Insert(4);
		t.Insert(5);
		t.Insert(5);
		t1.Insert(4);
		t1.Insert(5);
		t1.Insert(5);

		//assert
		EXPECT_EQ(t.GetSorted(), t1.GetSorted());
	}
	TEST(BPlusTree, Insert_2) {

		//arrange
		BPlusTree<int> t(3);
	
		BPlusTree<int> t1(3);
		


		//act
		t.Insert(4);
		t.Insert(5);
		t.Insert(5);
		t1.Insert(4);
		t1.Insert(5);
		//assert
		EXPECT_NE(t.GetSorted(), t1.GetSorted());
	}
	TEST(BPlusTree, Insert_3) {

		//arrange
		BPlusTree<int> t(3);
		
		vector<int>vc;
		//act
	
		t.Insert(2);
		t.Insert(3);
		t.Insert(4);
		t.Insert(5);
		vc.push_back(2);
		vc.push_back(3);
		vc.push_back(4);
		vc.push_back(5);
		//assert
		EXPECT_EQ(t.GetSorted(), vc);
	}
	TEST(BPlusTree, Insert_4) {

		//arrange
		BPlusTree<int> t(3);

		vector<int>vc;
		//act
	
		t.Insert(2);
		t.Insert(3);
		t.Insert(4);
		t.Insert(5);
		vc.push_back(2);
		vc.push_back(3);
		vc.push_back(4);
		
		//assert
		EXPECT_NE(t.GetSorted(), vc);
	}
	TEST(BPlusTree, Insert_5) {

		//arrange
		BPlusTree<int> t(8);

		vector<int>vc;
		//act
		
		for (int i = 0; i <= 500; i++)
		{
			vc.push_back(i);
			t.Insert(500-i);
		}
	
		
		//assert
		EXPECT_EQ(t.GetSorted(), vc);
	}
	TEST(BPlusTree, Insert_6) {

		//arrange
		BPlusTree<int> t(8);

		vector<int>vc;
		//act

		for (int i = 0; i <= 50000; i++)
		{
			vc.push_back(i);
			t.Insert(50000 - i) ;
		}
		

		//assert
		EXPECT_EQ(t.GetSorted(), vc);
	}
	TEST(BPlusTree, Insert_7) {

		//arrange
		BPlusTree<int> t(8);

		vector<int>vc;
		//act

		for (int i = 0; i <= 500000; i++)
		{
			vc.push_back(i);
			t.Insert(500000 - i);
		}


		//assert
		EXPECT_EQ(t.GetSorted(), vc);
	}
	TEST(BPlusTree, Insert_8) {

		//arrange
		BPlusTree<int> t(8);

		vector<int>vc;
		//act

		for (int i = 0; i <= 500000; i++)
		{
			vc.push_back(i);
			t.Insert(500000 - i);
		}

		vc.push_back(1);
		//assert
		EXPECT_NE(t.GetSorted(), vc);
	}
	TEST(BPlusTree, Includes_1) {

		//arrange
		BPlusTree<int> t(3);
		//act

		t.Insert(2);
		t.Insert(3);
		t.Insert(4);
		t.Insert(5);
		

		//assert
		EXPECT_TRUE(t.Includes(2));
	}
	TEST(BPlusTree, Includes_2) {

		//arrange
		BPlusTree<int> t(3);
		//act

		t.Insert(2);
		t.Insert(3);
		t.Insert(4);
		t.Insert(5);


		//assert
		EXPECT_FALSE(t.Includes(12));
	}
	TEST(BPlusTree, Includes_3) {

		//arrange
		BPlusTree<int> t(8);

		//act

		for (int i = 0; i <= 500000; i++)
		{
			
			t.Insert(500000 - i);
		}

		
		//assert
		EXPECT_TRUE(t.Includes(12));
	}
	TEST(BPlusTree, Includes_4) {

		//arrange
		BPlusTree<int> t(8);

		//act

		for (int i = 0; i <= 500000; i++)
		{

			t.Insert(500000 - i);
		}


		//assert
		EXPECT_FALSE(t.Includes(-12));
	}
	TEST(BPlusTree, Remove_1) {

		//arrange
		BPlusTree<int> t(8);

		//act+assert

		t.Insert(2);
		t.Insert(3);
		t.Insert(4);
		t.Insert(5);


		
		EXPECT_TRUE(t.Includes(2));
		t.Remove(2);
		EXPECT_FALSE(t.Includes(2));
	}
	}