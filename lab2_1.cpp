//============================================================================
// Name         : lab2_1
// Author       : Tianze Li
// Version      : 1.0
// Date Created : 30/01/25
// Date Modified: 01/02/25
// Description  : Find the minimum and the maximum values in an Array using a 
//				  function (findMinMax) that takes the array, its size and
//				  two variables min and max by references. 
//============================================================================
#include<iostream>
#include<cstdlib>
#include <ctime>
using namespace std;

/**
 * Finds the minimum and maximum values in an array.
 */
void findMinMax(int arr[], int size, int& min, int& max);

int main(void)
{
	//Declare variables
	int size;
	int min, max;
	//Prompt user to enter the size of the dynamic array
	cout << "Enter size of the array: ";
	cin >> size;
	// Handle invalid size inputs
    if (size <= 0) {
        cout << "Invalid array size. Exiting." << endl;
        return 1;
    }
	//Create a dynamic array
	int *arr = new int[size];
	// Seed for random number generation
	srand(time(0));
	//Populate the array with random values
	for (int i = 0; i < size; i++){
		arr[i] = rand() % 101;
		cout << "array[" << i << "]=" << arr[i] << endl;
	}
	//Call the function finMinMax()
	findMinMax(arr, size, min, max);
	//Print the values of array followed by min and max values
	cout << "Min : " << min << endl;
	cout << "Max : " << max << endl;
	//Do Necessary cleanup, e.g. delete dynamically allocated memory.
	delete[] arr;
	return 0;
}

/**
 * @brief Finds the minimum and maximum values in an array.
 * 
 * @param arr The array of integers.
 * @param size The number of elements in the array.
 * @param min Reference variable to store the minimum value found.
 * @param max Reference variable to store the maximum value found.
 */
void findMinMax(int array[], int arraySize, int& min, int& max)
{
	//validates the size
	if (arraySize <= 0){
		cout<<"array is empty!"<<endl;
	}
	//set up max and min
	min = array[0];
	max = array[0];
	// use a for loop to check the each element in array and determine the max and min
	for (int i = 1; i < arraySize; i++){
		if (array[i] < min) {
			min = array[i];
		}
		if (array[i] > max) {
			max = array[i];
		}	
	}
}

