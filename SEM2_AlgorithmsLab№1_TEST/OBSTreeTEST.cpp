#include "pch.h"
#include "../SEM2_AlgorithmsLab¹1/OBSTree.h"
#include<vector>
using namespace std;

namespace OBSTreeTest
{


TEST(OBSTree, optimalSearchTree_1) {

	//arrange
	double keys[] = { 10, 12, 20 };
	double freq[] = { 34, 8, 50 };
	int n = sizeof(keys) / sizeof(keys[0]);
	

	//act+assert

	EXPECT_EQ(142, optimalSearchTree(keys, freq, n));
}
TEST(OBSTree, optimalSearchTree_2) {

	//arrange
	double keys[] = { 10, 12, 20 };
	double freq[] = { 34, 8, 2 };
	int n = sizeof(keys) / sizeof(keys[0]);
	// 1*34 + 2*8 + 3*2 =56

	//act+assert

	EXPECT_EQ(56, optimalSearchTree(keys, freq, n));
}
TEST(OBSTree, optimalSearchTree_3) {

	//arrange
	double keys[] = { 10, 12, 20,5 };
	double freq[] = { 34, 8, 2,200 };
	int n = sizeof(keys) / sizeof(keys[0]);
	// 1*200 + 2*34 + 3*8+ 4*2 =300

	//act+assert

	EXPECT_EQ(300, optimalSearchTree(keys, freq, n));
}
TEST(OBSTree, optimalSearchTree_4) {

	//arrange
	double keys[] = { 10, 12, 20,5 };
	double freq[] = { 5, 8, 2,15 };
	int n = sizeof(keys) / sizeof(keys[0]);
	// 1*15 + 2*8 + 3*5+ 3*2 =52

	//act+assert

	EXPECT_EQ(52, optimalSearchTree(keys, freq, n));
}
TEST(OBSTree, optimalSearchTree_5) {

	//arrange
	double keys[] = { 10, 12, 20,5 };
	double freq[] = { 34, 8, 2,15 };
	int n = sizeof(keys) / sizeof(keys[0]);
	// 1*34 + 2*15 + 3*8+ 4*2 =96

	//act+assert

	EXPECT_EQ(96, optimalSearchTree(keys, freq, n));
}
TEST(OBSTree, optimalSearchTree_6) {

	//arrange
	double keys[] = { 10, 12, 20,5 };
	double freq[] = { 2, 8, 2,15 };
	int n = sizeof(keys) / sizeof(keys[0]);
	// 1*15 + 2*8 + 3*2+ 4*2 =41

	//act+assert

	EXPECT_EQ(43, optimalSearchTree(keys, freq, n));
}
}