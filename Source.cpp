//Chad Huntebrinker
//CS 303

#include <iostream>
#include <time.h>

using namespace std;

//The four sorting methods
void bubbleSort(int *array, int size, int &bubbleTotal);
void shellSort(int *array, int size, int &shellTotal);
void quickSort(int *array, int low, int high, int &quickTotal);
void mergeSort(int *array, int low, int high, int &mergeTotal);

int main() {
	int randArray1[1000], randArray2[1000], randArray3[1000], randArray4[1000];
	int bubbleTotal = 0, shellTotal = 0, quickTotal = 0, mergeTotal = 0;

	srand(time(NULL));

	//Have one array store the random numbers, then have that array store it in three other arrays so
	//each function will have the same elements in an array.
	for (int i = 0; i < 1000; ++i) {
		randArray1[i] = rand() % 100000;
		randArray2[i] = randArray1[i];
		randArray3[i] = randArray1[i];
		randArray4[i] = randArray1[i];
	}

	//Calls to the four different functions
	bubbleSort(randArray1, 1000, bubbleTotal);
	shellSort(randArray2, 1000, shellTotal);
	quickSort(randArray3, 0, 999, quickTotal);
	mergeSort(randArray4, 0, 999, mergeTotal);

	//Output the totals
	cout << "Bubble total swaps: " << bubbleTotal << endl;
	cout << "Shell total swaps:  " << shellTotal << endl;
	cout << "Quick total swaps:  " << quickTotal << endl;
	cout << "Merge total swaps:  " << mergeTotal << endl;

}

//This method does the bubble sort.
void bubbleSort(int *array, int size, int &bubbleTotal) {
	for (int i = 0; i < (size - 1); i++) {
		for (int j = 0; j < (size - i - 1); j++) {
			
			//If spot lower is greater than the spot higher
			if (array[j] > array[j + 1]) {
				swap(array[j + 1], array[j]); //Swap the elements.
				++bubbleTotal; //Increase the bubble sort swap counter.
			}
		}
	}
}

//Shell sort function
void shellSort(int *array, int size, int &shellTotal) {
	for (int gapSize = size / 2; gapSize > 0; gapSize = gapSize / 2) {
		for (int i = gapSize; i < size; i += 1) {
			int temp = array[i];
			int j;

			for (j = i; j >= gapSize && array[j - gapSize] > temp; j -= gapSize) {
				array[j] = array[j - gapSize];
				++shellTotal; //Increase the shell sort swap total
			}

			array[j] = temp;
			++shellTotal; //Increase the shell sort swap total
		}
	}
}

void quickSort(int *array, int low, int high, int &quickTotal) {
	if (low < high) {
		int pivot = array[high];
		int temp = (low - 1); //temp is the index of smaller element.

		for (int i = low; i <= high - 1; i++)
		{
			//If current element is smaller than the pivot.
			if (array[i] < pivot)
			{
				++temp;							//Increase index of smaller element.
				swap(array[temp], array[i]);	//Swap the two places.
				++quickTotal;					//Increase the quick sort swap total
			}
		}
		++temp;	//Increase temp by one so you can swap the pivot and a number that is greater than the pivot.
		swap(array[temp], array[high]);
		++quickTotal; //Increase the quick sort swap total

		//Call the function again, ranging from the lowest position to 1 before the pivot because the pivot
		//is now in the right spot.  The second function is from 1 after the pivot to the highest position.
		quickSort(array, low, temp - 1, quickTotal);
		quickSort(array, temp + 1, high, quickTotal);
	}
}

void mergeSort(int *array, int low, int high, int &mergeTotal) {
	if (low < high) {
		int middle = low + (high - low) / 2;

		//Call the same function multiple times so you can split the original array to smaller arrays.
		mergeSort(array, low, middle, mergeTotal);
		mergeSort(array, middle + 1, high, mergeTotal);

		//Get the size of the two different arrays.
		int size1 = middle - low + 1;
		int size2 = high - middle;

		//Create new temp arrays
		int* tempLow = new int[size1];
		int* tempHigh = new int[size2];

		//Copy data to temp arrays tempLow[] and tempHigh[]
		for (int i = 0; i < size1; i++)
			tempLow[i] = array[low + i];
		for (int j = 0; j < size2; j++)
			tempHigh[j] = array[middle + 1 + j];

		//Combine the temp arrays back into the orginal array
		int initial1 = 0; //Initial index of first subarray
		int initial2 = 0; //Initial index of second subarray
		int initialMerged = low; //Initial index of merged subarray

		//This loop will continue going while inital index of first array is smaller than the initial index of
		//of the second array and while the initial index of the second array is smaller than than the size of
		//the second subarray
		while (initial1 < size1 && initial2 < size2)
		{
			//If element in tempLow is smaller than element in tempHigh
			if (tempLow[initial1] <= tempHigh[initial2])
			{
				array[initialMerged] = tempLow[initial1];
				++initial1;
				++mergeTotal;	//Increase merge swap total
			}
			else
			{
				array[initialMerged] = tempHigh[initial2];
				++initial2;
				++mergeTotal;	//Increase merge swap total
			}
			++initialMerged;
		}

		//Insert the remaining elements of tempLow
		while (initial1 < size1)
		{
			array[initialMerged] = tempLow[initial1];
			++initial1;
			++initialMerged;
			++mergeTotal;
		}

		//Insert the remaining elements of tempHigh
		while (initialMerged < size2)
		{
			array[initialMerged] = tempHigh[initial2];
			++initial2;
			++initialMerged;
			++mergeTotal;
		}

		//Delete the temp arrays
		delete[] tempLow;
		delete[] tempHigh;
	}
}