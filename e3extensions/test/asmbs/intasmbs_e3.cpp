#include <iostream>
#include <cstdlib>

#define LEN 1+13*16

using namespace std;

void bubbleSort(int[], int);
void printArray(int[], int);

// Driver program to test above functions
int main()
{
	int a[LEN];
	for ( size_t i=0; i<LEN; i++ ) a[i] = rand();

	asm("l.debug");
	bubbleSort(a, LEN);

	asm("l.debug");
	// cout << "Sorted array is:  " << a[0] << '\n';
	printArray(a, LEN);
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
	int i, j;
	int cond1, cond2, smaller, greater;

	for (i = 0; i < n-1; i++)
	{
		// Last i elements are already in place
		for (j = 0; j < n-i-1; j++)
		{
			cond1 = arr[j] <= arr[j+1];
			cond2 = arr[j+1] < arr[j]; // remove if ternary
			smaller = cond1 * arr[j] + cond2 * arr[j+1];
			//smaller = cond1.ternary(arr[j], arr[j+1]);
			greater = arr[j+1] + arr[j] - smaller;
			arr[j] = smaller;
			arr[j+1] = greater;
		}
	}
}


/* Function to print an array */
void printArray(int arr[], int size)
{
	for (int i=0; i < size; i++) cout << arr[i] << " ";
	cout << "\n";
}
