#include "pch.h"
#include "../SEM2_AlgorithmsLab¹1/PerfectHash.h"
#include "gtest/gtest.h"
using namespace std;

namespace PerfectHashTEST
{
	TEST(PerfectHash, Initialize50000_Expect_Initialized) {


		int numberOfElements = 50000;
		srand(time(NULL));

		FixedSet fs;

		vector<int> inputVector;
		for (int i = 0; i < numberOfElements; ++i)
		{
			inputVector.push_back(rand() % 100);
		}

		fs.Initialize(inputVector);

	}
	TEST(PerfectHash, Initialize5000000_Expect_Initialized) {


		int numberOfElements = 5000000;
		srand(time(NULL));

		FixedSet fs;

		vector<int> inputVector;
		for (int i = 0; i < numberOfElements; ++i)
		{
			inputVector.push_back(rand() % 100);
		}

		fs.Initialize(inputVector);

	}
	TEST(PerfectHash, Contains1_Expect_AllTrue) {

	
		int numberOfElements=50000;
		srand(time(NULL));
	
		FixedSet fs;

		vector<int> inputVector;
		for (int i = 0; i < numberOfElements; ++i)
		{
			inputVector.push_back(rand()%100);
		}
	
		fs.Initialize(inputVector);


		int numberOfElementsForSearch = inputVector.size();

		
		for (int i = 0; i < numberOfElementsForSearch; i++)
		{
			EXPECT_TRUE(fs.Contains(inputVector[i]));
			
			
		}	
		
	}
	TEST(PerfectHash, Contains2_Expect_AllFalse) {


		int numberOfElements = 50000;
		srand(time(NULL));

		FixedSet fs;

		vector<int> inputVector;
		for (int i = 0; i < numberOfElements; ++i)
		{
			inputVector.push_back(i);
		}

		fs.Initialize(inputVector);


		int numberOfElementsForSearch = inputVector.size();


		for (int i = 0; i < numberOfElementsForSearch; i++)
		{
			EXPECT_FALSE(fs.Contains(inputVector[i]+ numberOfElements));
		}



	}
	TEST(PerfectHash, Contains3_Expect_AllTrue) {


		FixedSet fs;

		vector<int> inputVector;
		string elemValue = "hdgdhg";
		fs.StringInitialize(elemValue);

		EXPECT_TRUE(fs.StringContains(elemValue));
	}
	TEST(PerfectHash, Contains4_Expect_AllFalse) {


		FixedSet fs;

		vector<int> inputVector;
		string elemValue = "hdgdhg";
		fs.StringInitialize(elemValue);

		EXPECT_FALSE(fs.StringContains("FFGGD"));
	}
	TEST(PerfectHash, Contains5_Expect_AllTrue) {


		int numberOfElements = 5000000;
		srand(time(NULL));

		FixedSet fs;

		vector<int> inputVector;
		for (int i = 0; i < numberOfElements; ++i)
		{
			inputVector.push_back(i);
		}

		fs.Initialize(inputVector);


		int numberOfElementsForSearch = inputVector.size();


		for (int i = 0; i < numberOfElementsForSearch; i++)
		{
			EXPECT_TRUE(fs.Contains(inputVector[i]));


		}

	}
	TEST(PerfectHash, Contains6_Expect_AllFalse) {


		int numberOfElements = 5000000;
		srand(time(NULL));

		FixedSet fs;

		vector<int> inputVector;
		for (int i = 0; i < numberOfElements; i++)
		{
			inputVector.push_back(i);
		}

		fs.Initialize(inputVector);


		int numberOfElementsForSearch = inputVector.size();


		for (int i = 0; i < numberOfElementsForSearch; i++)
		{
			EXPECT_FALSE(fs.Contains(inputVector[i] + numberOfElements));
		}

	}
}
