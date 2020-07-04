#include <stdio.h>

void swap(int*, int*);
void quickSort( int[], int, int);
int partition( int[], int, int);


void main() 
{
	int a[] = { 7, 12, 2, 0, 1, 15, 4, 11, 9};

	int i;
	printf("\n\nUnsorted array is:  ");
	for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);

	quickSort(a, 0, 8);

	printf("\n\nSorted array is:  ");
	for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);

}



void quickSort( int a[], int l, int r)
{
   int j;

   if( l < r ) 
   {
   	// divide and conquer
        j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
	
}

int partition( int a[], int l, int r) {
	int pivot = a[r];
	int i = l - 1;
	printf("partition l: %d\tr: %d\n", l, r);
	for (int j = l; j < r; j++)
	{
		if (a[j] < pivot) swap(&a[++i], &a[j]);
	}
	
    	if (a[r] < a[i+1]) swap(&a[i+1], &a[r]);

    	return i + 1;
}

void swap(int *a, int *b)
{
	printf("::: %d\t%d\n", *a, *b);
	int aux = *a;
	*a = *b;
	*b = aux;
}

