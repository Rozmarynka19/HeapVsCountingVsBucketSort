#pragma once
#include <cmath>
#include "LinkedList.h"
#include "HeapSort.h"
#include "DynamicArray.h"
void BucketSort(int* array, int size, int spread)
{
	Linked_List<int>** Buckets = new Linked_List<int> *[size];
	for (int i = 0; i < size; i++) Buckets[i] = new Linked_List<int>();
	
	double bucketWidth = spread / size;
	
	
	for (int i = 0,bucketNumber; i < size; i++)
	{
		bucketNumber = (int)(array[i] / bucketWidth);
		//(*(Buckets + bucketNumber))->AddInOrder(array[i], Compare);
		(*(Buckets + bucketNumber))->addToHead(array[i]);
	}

	//sorting list's element in each bucket
	int currentBucketSize, currentBucketSizeIterator;
	for (int bucketNumber=0; bucketNumber < size; bucketNumber++)
	{
		currentBucketSize = (*(Buckets + bucketNumber))->size;
		
		int *tempArray=new int[currentBucketSize];
		//adding elements from current bucket's list to temporary array
		for (currentBucketSizeIterator = 0; currentBucketSizeIterator < currentBucketSize; currentBucketSizeIterator++)
		{
			//tempArray[currentBucketSizeIterator] = (*(Buckets + bucketNumber))->GetDataOfElement(currentBucketSizeIterator);
			tempArray[currentBucketSizeIterator] = (*(Buckets + bucketNumber))->GetDataOfElement(0);
			(*(Buckets + bucketNumber))->RemoveFromHead();

		}
		delete Buckets[bucketNumber];
		Buckets[bucketNumber] = new Linked_List<int>();

		//binary heap done in temporary array
		BinaryHeap<int>* tempBinaryHeap = new BinaryHeap<int>(tempArray, currentBucketSize, true);
		tempBinaryHeap->HeapSort();

		//adding sorted elements from temporary array to current bucket's list
		for (currentBucketSizeIterator = 0; currentBucketSizeIterator < currentBucketSize; currentBucketSizeIterator++)
		{
			(*(Buckets + bucketNumber))->addToTail(tempArray[currentBucketSizeIterator]);
		}

		
		delete tempBinaryHeap;
		delete[] tempArray;
	}

	for (int bucketNumber = 0,arrayIndex=0,currentBucketSize,currentBucketSizeIterator; bucketNumber < size; bucketNumber++)
	{
		currentBucketSize= (*(Buckets + bucketNumber))->size;
		currentBucketSizeIterator = 0;
		while (currentBucketSizeIterator < currentBucketSize)
		{
			array[arrayIndex] = (*(Buckets + bucketNumber))->GetDataOfElement(currentBucketSizeIterator);
			currentBucketSizeIterator++;
			arrayIndex++;
		}
	}

	//releasing Buckets array
	for (int bucketNumber = 0; bucketNumber < size; bucketNumber++)
		delete Buckets[bucketNumber];
	delete Buckets;
}
template<class T>
void BucketSort(T* array, int size, double spread)
{
	Linked_List<T>** Buckets = new Linked_List<T> * [size];
	for (int i = 0; i < size; i++) Buckets[i] = new Linked_List<T>();

	double bucketWidth = spread / size;


	for (int i = 0, bucketNumber; i < size; i++)
	{
		bucketNumber = (int)(array[i].number / bucketWidth);
		(*(Buckets + bucketNumber))->AddInOrder(array[i], Compare);
	}


	for (int bucketNumber = 0, arrayIndex = 0, currentBucketSize, currentBucketSizeIterator; bucketNumber < size; bucketNumber++)
	{
		currentBucketSize = (*(Buckets + bucketNumber))->size;
		currentBucketSizeIterator = 0;
		while (currentBucketSizeIterator < currentBucketSize)
		{
			array[arrayIndex] = (*(Buckets + bucketNumber))->GetDataOfElement(currentBucketSizeIterator);
			currentBucketSizeIterator++;
			arrayIndex++;
		}
	}

	//releasing Buckets array
	for (int bucketNumber = 0; bucketNumber < size; bucketNumber++)
		(*(Buckets + bucketNumber))->~Linked_List();

	delete Buckets;
}