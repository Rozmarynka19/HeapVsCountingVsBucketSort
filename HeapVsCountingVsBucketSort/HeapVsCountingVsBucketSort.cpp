//ALGO2 IS1 213A LAB05
//Monika Rozmarynowska
//rm44478@zut.edu.pl

#include <iostream>
#include "HeapSort.h"
#include "CountingSort.h"
#include "BucketSort.h"
#include <cmath>
#include <time.h>
#include <ctime>

struct Test
{
	double number;
	char character;

	bool operator==(const Test &object)
	{
		return ((number = object.number) && (character = object.character));
	}
	bool operator >(const Test& object)
	{
		return (number > object.number);
	}
	bool operator <(const Test& object)
	{
		return (number < object.number);
	}
};
string ToString(int* array, int size)
{
	string outcome = "";

	for (int i = 0; i < size; i++)
		outcome = outcome + to_string(array[i]) + " ";

	return outcome;
}
template <class T>
string ToString(T* array, int size)
{
	string outcome = "";

	for (int i=0;i<size;i++)
		outcome = outcome + "{"+ to_string(array[i].number) + ", "+elementToString(array[i].character)+"} ";

	return outcome;
}
void Copy(int* targetArray, int* sourceArray, int size)
{
	for (int i = 0; i < size; i++)
		targetArray[i] = sourceArray[i];
}
template<class T>
void Copy(T* targetArray, T* sourceArray, int size)
{
	for (int i = 0; i < size; i++)
	{
		targetArray[i].number = sourceArray[i].number;
		targetArray[i].character = sourceArray[i].character;
	}
}
bool AreArraysEqual(int* array1, int* array2, int* array3, int size)
{
	bool AreEqual = true;
	//checking array1 & array2
	for (int i = 0; i < size && AreEqual==true; i++)
	{
		if (array1[i] == array2[i]) continue;
		else AreEqual = false;
	}
	if (!AreEqual) { 
		cout << "Array1 and Array2 are not equal." << endl;
		return AreEqual;
	}
	//checking array1 & array3
	for (int i = 0; i < size && AreEqual == true; i++)
	{
		if (array1[i] == array3[i]) continue;
		else AreEqual = false;
	}
	if (!AreEqual) cout << "Array1 and Array3 are not equal" << endl;
	else cout << "All arrays are equal." << endl;

	return AreEqual;
}
template<class T>
bool AreArraysEqual(T* array1, T* array2, int size)
{
	bool AreEqual = true;
	//checking array1 & array2
	for (int i = 0; i < size && AreEqual == true; i++)
	{
		if (array1[i] == array2[i]) continue;
		else AreEqual = false;
	}
	if (!AreEqual) cout << "Array1 and Array2 are not equal" << endl;
	else cout << "Arrays are equal." << endl;

	return AreEqual;
}

void MainForInts();
void MainForFloatingPointObjects();

int main()
{
	//srand(time(NULL));

	//const double m_double = (double)pow(2, 30);

	//int size = 10;
	//Test* tab = new Test[size];

	//for (int i = 0; i < size; i++)
	//{
	//	Test testowyObiekt;
	//	testowyObiekt.number = ((rand() << 15) + rand()) / m_double ;
	//	testowyObiekt.character = 'a' + rand() % 26;
	//	tab[i] = testowyObiekt;
	//}
	//
	//cout<<ToString(tab, size)<<endl;
	///*Test* tab2 = new Test[size];
	//Test* tab3 = new Test[size];
	//Copy(tab2, tab, size);
	//Copy(tab3, tab, size);
	//cout << ToString(tab2, size) << endl;
	//cout << ToString(tab3, size) << endl;
	//AreArraysEqual(tab, tab2, tab3, size);*/


	///*BinaryHeap<Test>* binaryHeap = new BinaryHeap<Test>(tab, size, true);
	//binaryHeap->HeapSort();
	//cout << ToString(tab, size)<<endl;*/

	///*CountingSort(tab, size, m);
	//cout << ToString(tab, size) << endl;*/

	//BucketSort(tab, size, 1.0);
	//cout << ToString(tab, size) << endl;
	//delete[] tab;

	MainForInts();
	//MainForFloatingPointObjects();
}


void MainForInts()
{
	srand(time(NULL));
	cout.precision(numeric_limits<double>::max_digits10);

	const int MAX_INDEX = 7; // maksymalny rzad wielkosci sortowanych danych
	const int M = (int)pow(10, 7); // sortowane liczby ze zbioru {0 , ... , m - 1}
	for (int i = 1; i <= MAX_INDEX; i++)
	{
		const int N = (int)pow(10, i); // rozmiar tablicy z danymi
		int* array1 = new int[N];

		for (int j = 0; j < N; j++)
			array1[j] = ((rand()<<15)+rand()) % M;
		cout << "Size: 10^" << i << endl;
		cout<<"Array1 before sorting (first 10 elements): "<<endl<<ToString(array1, 10)<<endl;

		int* array2 = new int[N];
		int* array3 = new int[N];
		Copy(array2, array1, N);
		Copy(array3, array1, N);
		/*****************************************************************************************************************/
		//CountingSort (in place)
		clock_t start = clock();
		CountingSort(array1, N, M);
		clock_t stop = clock();

		double result = (stop - start) / (double)CLOCKS_PER_SEC;
		cout <<endl<<"Array1 after CountingSort (first 10 elements): "<<endl<< ToString(array1, 10)<<endl;
		cout << "Time: " << result << endl;

		/*****************************************************************************************************************/
		//HeapSort (in place)
		start = clock();
		BinaryHeap<int>* binaryHeap = new BinaryHeap<int>(array2, N, false);
		binaryHeap->HeapSort();
		stop = clock();

		result = (stop - start) / (double)CLOCKS_PER_SEC;
		cout <<endl<<"Array2 after HeapSort (first 10 elements): "<<endl<< ToString(array2, 10)<<endl;
		cout << "Time: " << result << endl;

		/*****************************************************************************************************************/
		//BucketSort (in place)
		start = clock();
		BucketSort(array3, N, M);
		stop = clock();

		result = (stop - start) / (double)CLOCKS_PER_SEC;
		cout <<endl<<"Array3 after BucketSort (first 10 elements): "<<endl<< ToString(array3, 10)<<endl;
		cout << "Time: " << result << endl;
		/*****************************************************************************************************************/
		//Equality test of sorted arrays
		cout << endl;
		AreArraysEqual(array1, array2, array3, N);

		/*****************************************************************************************************************/
		cout << "/*****************************************************************************************************************/" << endl;
		delete binaryHeap;
		delete[] array1, array2, array3;
		getchar();
	}
}

void MainForFloatingPointObjects()
{
	srand(time(NULL));
	cout.precision(numeric_limits<double>::max_digits10);

	const int MAX_INDEX = 7; // maksymalny rzad wielkosci sortowanych danych
	const double M_DOUBLE = (double)pow(2, 30); // mianownik przy ustalaniu losowej liczby zmiennoprzecinkowej
		for (int i = 1; i <= MAX_INDEX; i++)
		{
			const int N = (int)pow(10, i); // rozmiar tablicy z danymi

			Test* array1 = new Test[N];
			for (int j = 0; j < N; j++)
			{
				Test tmp;
				tmp.number = ((rand() << 15) + rand()) / M_DOUBLE; // przykladowy sposob wylosowania pola typu double(ktore bedzie stanowilo klucz sortowania)
				tmp.character = 'a' + rand() % 26; // przykladowy sposob wylosowania pola typu char
				array1[j] = tmp;
			}
			cout << "Size: 10^" << i << endl;
			cout << "Array1 before sorting (first 10 elements): " << endl << ToString(array1, 10) << endl;

			Test* array2 = new Test[N];
			Copy(array2, array1, N);

			/*****************************************************************************************************************/
			//HeapSort (in place)
			clock_t start = clock();
			BinaryHeap<Test>* binaryHeap = new BinaryHeap<Test>(array1, N, false);			
			binaryHeap->HeapSort();
			clock_t stop = clock();

			double result = (stop - start) / (double)CLOCKS_PER_SEC;
			cout << endl << "Array1 after HeapSort (first 10 elements): " << endl << ToString(array1, 10) << endl;
			cout << "Time: " << result << endl;

			/*****************************************************************************************************************/
			//BucketSort (in place)
			start = clock();
			BucketSort<Test>(array2, N, 1.0);
			stop = clock();

			result = (stop - start) / (double)CLOCKS_PER_SEC;
			cout << endl << "Array2 after BucketSort (first 10 elements): " << endl << ToString(array2, 10) << endl;
			cout << "Time: " << result << endl;

			/*****************************************************************************************************************/
			//Equality test of sorted arrays
			AreArraysEqual(array1, array2, N);

			/*****************************************************************************************************************/
			cout << "/*****************************************************************************************************************/" << endl;
			delete[] array1, array2;
			getchar();
		}
}