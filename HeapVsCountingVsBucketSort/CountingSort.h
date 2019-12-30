#pragma once
#include <iostream>
#include <string>
//in place
void CountingSort(int *array, int size, int spread){
		int* counts = new int[spread];
		
	
		for (int i = 0; i < spread; i++) counts[i] = 0;
		for (int i = 0; i < size; i++) counts[array[i]] = counts[array[i]] + 1;
		//for (int i = 1; i < spread; i++)counts[i] = counts[i] + counts[i - 1];
		for (int i = 0,k=0; i <spread && k<size; i++)
		{
			/*out[counts[array[i]]-1] = array[i];
			counts[array[i]] = counts[array[i]] - 1;*/
			for (int j = counts[i]; j > 0; j--,k++)
			{
				array[k] = i;
			}
		}
		/*for (int i = 0; i < size; i++)
		{
			cout << array[i] << " ";
		}
		cout << endl;*/

		delete counts;
}

//template <class T>
//void CountingSort(T *array, int size, int spread)
//{
//	cout << array << endl;
//	T* counts = new T[spread];
//	T *out = new T[size];
//	
//
//	for (int i = 0; i < spread; i++) counts[i] = 0;
//	for (int i = 0; i < size; i++) counts[array[i]] = counts[array[i]] + 1;
//	for (int i = 1; i < spread; i++)counts[i] = counts[i] + counts[i - 1];
//	for (int i = size-1; i >=0; i--)
//	{
//		out[counts[array[i]]-1] = array[i];
//		counts[array[i]] = counts[array[i]] - 1;
//	}
//	for (int i = 0; i < size; i++)
//	{
//		cout << out[i] << " ";
//	}
//	cout << endl;
//
//	array = out;
//	cout << array << endl;
//	delete counts;
//}
