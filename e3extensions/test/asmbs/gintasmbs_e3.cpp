#include <iostream>
#include <cstdlib>

#define LEN 1+13*256

using namespace std;

void bubbleSort(unsigned[], int);
void printArray(unsigned[], int);

// Driver program to test above functions
int main()
{
	unsigned a[LEN]; // = {14,13,12,11,10,9,8,7,6,5,4,3,2,1};
	for ( size_t i=0; i<LEN; i++ ) a[i] = rand()%100;
	// printArray(a, LEN);

	asm("l.debug");
	bubbleSort(a, LEN);
	asm("l.debug");
	// cout << "Sorted array is:  ";// << a[0] << '\n';
	printArray(a, LEN);
}

// A function to implement bubble sort
void bubbleSort(unsigned arr[], int n)
{
	int i, j, d;
	unsigned smaller, gtncond;
	unsigned r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,ra,rb,rc,rd;

	int s = 14;
	for (i = 0; i < n-1; i++)
	{
		d = (s-1) * (i / (s-1)) + 1;
		// cout << "i: " << i << "d: " << d << '\n';
		// Last i elements are already in place
		r0 = arr[0];
		for (j = 0; j < n-d; j+=(s-1))
		{
			// cout << j << ' ' << flush;
			r1 = arr[j+1];
			r2 = arr[j+2];
			r3 = arr[j+3];
			r4 = arr[j+4];
			r5 = arr[j+5];
			r6 = arr[j+6];
			r7 = arr[j+7];
			r8 = arr[j+8];
			r9 = arr[j+9];
			ra = arr[j+10];
			rb = arr[j+11];
			rc = arr[j+12];
			rd = arr[j+13];

			gtncond = r0 <= r1;
			smaller = gtncond * r0;
			gtncond = !gtncond;
			smaller += gtncond * r1;
			gtncond = r1 + r0 - smaller;
			r0 = smaller;
			r1 = gtncond;

			gtncond = r1 <= r2;
			smaller = gtncond * r1;
			gtncond = !gtncond;
			smaller += gtncond * r2;
			gtncond = r2 + r1 - smaller;
			r1 = smaller;
			r2 = gtncond;

			gtncond = r2 <= r3;
			smaller = gtncond * r2;
			gtncond = !gtncond;
			smaller += gtncond * r3;
			gtncond = r3 + r2 - smaller;
			r2 = smaller;
			r3 = gtncond;

			gtncond = r3 <= r4;
			smaller = gtncond * r3;
			gtncond = !gtncond;
			smaller += gtncond * r4;
			gtncond = r4 + r3 - smaller;
			r3 = smaller;
			r4 = gtncond;

			gtncond = r4 <= r5;
			smaller = gtncond * r4;
			gtncond = !gtncond;
			smaller += gtncond * r5;
			gtncond = r5 + r4 - smaller;
			r4 = smaller;
			r5 = gtncond;

			gtncond = r5 <= r6;
			smaller = gtncond * r5;
			gtncond = !gtncond;
			smaller += gtncond * r6;
			gtncond = r6 + r5 - smaller;
			r5 = smaller;
			r6 = gtncond;

			gtncond = r6 <= r7;
			smaller = gtncond * r6;
			gtncond = !gtncond;
			smaller += gtncond * r7;
			gtncond = r7 + r6 - smaller;
			r6 = smaller;
			r7 = gtncond;

			gtncond = r7 <= r8;
			smaller = gtncond * r7;
			gtncond = !gtncond;
			smaller += gtncond * r8;
			gtncond = r8 + r7 - smaller;
			r7 = smaller;
			r8 = gtncond;

			gtncond = r8 <= r9;
			smaller = gtncond * r8;
			gtncond = !gtncond;
			smaller += gtncond * r9;
			gtncond = r9 + r8 - smaller;
			r8 = smaller;
			r9 = gtncond;

			gtncond = r9 <= ra;
			smaller = gtncond * r9;
			gtncond = !gtncond;
			smaller += gtncond * ra;
			gtncond = ra + r9 - smaller;
			r9 = smaller;
			ra = gtncond;

			gtncond = ra <= rb;
			smaller = gtncond * ra;
			gtncond = !gtncond;
			smaller += gtncond * rb;
			gtncond = rb + ra - smaller;
			ra = smaller;
			rb = gtncond;

			gtncond = rb <= rc;
			smaller = gtncond * rb;
			gtncond = !gtncond;
			smaller += gtncond * rc;
			gtncond = rc + rb - smaller;
			rb = smaller;
			rc = gtncond;

			gtncond = rc <= rd;
			smaller = gtncond * rc;
			gtncond = !gtncond;
			smaller += gtncond * rd;
			gtncond = rd + rc - smaller;
			rc = smaller;
			rd = gtncond;

			arr[j] = r0;
			arr[j+1] = r1;
			arr[j+2] = r2;
			arr[j+3] = r3;
			arr[j+4] = r4;
			arr[j+5] = r5;
			arr[j+6] = r6;
			arr[j+7] = r7;
			arr[j+8] = r8;
			arr[j+9] = r9;
			arr[j+10] = ra;
			arr[j+11] = rb;
			arr[j+12] = rc;
			r0 = rd;
		}
		// cout << '\n';
		arr[j] = r0;
		// printArray(arr, n);
	}
}


/* Function to print an array */
void printArray(unsigned arr[], int size)
{
	for (int i=0; i < size; i++) cout << arr[i] << " ";
	cout << "\n";
}
