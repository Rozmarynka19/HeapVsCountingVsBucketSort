#pragma once
#include "DynamicArray.h"
#include <iostream>
#include <cmath>

template <class T>
class BinaryHeap
{
	//maximum
	Dynamic_Array<T>* dynamicArray;
	T* array;
	int arrayMaxSize;
	int arrayCurrentSize;
	bool isDynamic;
	bool directionOfRepair;

	int GetParentIndex(int index) { if (index > 0) return floor((index - 1) / 2); }
	int GetLeftChildIndex(int index) { return (2 * index + 1); }
	int GetRightChildIndex(int index) { return (2 * index + 2); }
	bool isLeaf(int index) {

		if (isDynamic)
		{
			if (2 * index + 2 > dynamicArray->currentSize)
				return true;
			else
				return false;
		}
		else
		{
			if (2 * index + 2 > arrayCurrentSize)
				return true;
			else
				return false;
		}

	}
	void HipUp(int index)
	{
		if (isDynamic)
		{
			while ((dynamicArray->getData(index) > dynamicArray->getData(GetParentIndex(index))) && index > 1)
			{
				dynamicArray->Swap(index, GetParentIndex(index));
				index = GetParentIndex(index);
			}
		}
		else
		{
			while (index >= 1 && array[index] > array[GetParentIndex(index)])
			{
				//dynamicArray->Swap(index, GetParentIndex(index));
				T temp;
				temp = array[index];
				array[index] = array[GetParentIndex(index)];
				array[GetParentIndex(index)] = temp;

				index = GetParentIndex(index);
			}
		}

	}
	void HipDown(int index)
	{
		int greater;

		if (isDynamic)
		{
			while (!isLeaf(index))
			{
				if (dynamicArray->getData(GetLeftChildIndex(index)) > dynamicArray->getData(GetRightChildIndex(index)))
					greater = GetLeftChildIndex(index);
				else
					greater = GetRightChildIndex(index);


				if (dynamicArray->getData(greater) > dynamicArray->getData(index))
					dynamicArray->Swap(index, greater);

				index = greater;
			}

		}
		else
		{
			while (!isLeaf(index))
			{
				if ((GetLeftChildIndex(index) <= arrayCurrentSize - 1) && (GetRightChildIndex(index) <= arrayCurrentSize - 1))
				{
					if (array[GetLeftChildIndex(index)] > array[GetRightChildIndex(index)] && (GetLeftChildIndex(index) <= arrayCurrentSize - 1))
						greater = GetLeftChildIndex(index);
					else
						greater = GetRightChildIndex(index);
				}
				else if ((GetLeftChildIndex(index) <= arrayCurrentSize - 1))
					greater = GetLeftChildIndex(index);
				else if ((GetRightChildIndex(index) <= arrayCurrentSize - 1))
					greater = GetRightChildIndex(index);




				if (array[greater] > array[index])
				{
					//dynamicArray->Swap(index, greater);

					T temp;
					temp = array[index];
					array[index] = array[greater];
					array[greater] = temp;
				}


				index = greater;
			}
		}

	}
public:
	BinaryHeap() {isDynamic = true; dynamicArray = new Dynamic_Array<T>; }
	BinaryHeap(T * array, int size, bool directionOfRepair)
	{
		isDynamic = false;

		this->directionOfRepair = directionOfRepair;
		this->array = array;
		arrayMaxSize = arrayCurrentSize = size;

		//array repairing
		//if true top-down; false - bottom-up
		if (directionOfRepair)
		{
			for (int i = 0; i < arrayCurrentSize; i++) {
				HipUp(i);
				//cout<<this->ToString()<<endl;
			}
		}
		else
		{
			for (int i = arrayCurrentSize - 1; i >= 0; i--)
			{
				HipDown(i);
				//cout<<this->ToString()<<endl;
			}

		}
	}
	//only for DynamicArray
	~BinaryHeap() { if (isDynamic) dynamicArray->~Dynamic_Array(); }
	//only for DynamicArray
	void Push(T data)
	{
		dynamicArray->addElement(data);

		HipUp((dynamicArray->currentSize) - 1);
	}
	//only for DynamicArray
	T Pop()
	{
		if ((dynamicArray->currentSize) > 0)
		{
			T temp = dynamicArray->getData(0);
			dynamicArray->Swap(0, (dynamicArray->currentSize) - 1);
			dynamicArray->currentSize = (dynamicArray->currentSize) - 1;

			HipDown(0);

			return temp;
		}
	}

	void HeapSort()
	{
		for (int i = arrayCurrentSize - 1; i >= 0; i--)
		{
			//cout << array[0] << endl;
			T temp;
			temp = array[0];
			array[0] = array[i];
			array[i] = temp;
			//cout <<"\t"<< this->ToString() << endl;

			arrayCurrentSize--;

			HipDown(0);
			//cout<<this->ToString()<<endl;
		}
		arrayCurrentSize = arrayMaxSize;
	}

	string ToString() {

		if (isDynamic)
			return dynamicArray->toString();
		else
		{
			string outcome = "";

			for (int i = 0; i < arrayCurrentSize; i++)
				outcome = outcome + to_string(array[i]) + " ";

			return outcome;
		}
	}
	string ToString(int numberOfElements) 
	{
		if (isDynamic)
			return dynamicArray->toString(numberOfElements);
		else
		{
			string outcome = "";

			for (int i = 0; i < numberOfElements; i++)
				outcome = outcome + array[i] + " ";

			return outcome;
		}
	}
};