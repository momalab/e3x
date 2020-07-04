#include <iostream>
#include <stdlib.h>
#include <gmp.h>

#define SIZE 32
#define LEN 6

using namespace std;

void bubbleSort(mpz_t[], int);
void printArray(mpz_t[], int);
void e3_randomp2(mpz_t, unsigned);
 
// Driver program to test above functions
int main()
{
	mpz_t a[LEN];
	e3_randomp2(a[0], SIZE);
	e3_randomp2(a[1], SIZE);
	e3_randomp2(a[2], SIZE);
	e3_randomp2(a[3], SIZE);
	e3_randomp2(a[4], SIZE);
	e3_randomp2(a[5], SIZE);

	printArray(a, LEN);

	asm("l.debug");
	
	bubbleSort(a, LEN);

	cout << "Sorted array is:  ";
	printArray(a, LEN);

	asm("l.debug");
	return 0;
}

// A function to implement bubble sort
void bubbleSort(mpz_t arr[], int n)
{
	int i, j;
	mpz_t cond1, cond2, smaller, greater, aux;
	mpz_init(cond1);
	mpz_init(cond2);
	mpz_init(smaller);
	mpz_init(greater);
	mpz_init(aux);

	for (i = 0; i < n-1; i++)
	{
		// Last i elements are already in place   
		for (j = 0; j < n-i-1; j++)
		{
			mpz_set_ui(cond1, mpz_cmp(arr[j], arr[j+1]) <= 0);
			mpz_set_ui(cond2, mpz_cmp(arr[j+1], arr[j]) < 0);
			mpz_mul(smaller, cond1, arr[j]);
			mpz_mul(aux, cond2, arr[j+1]);
			mpz_add(smaller, smaller, aux);
			mpz_add(greater, arr[j+1], arr[j]);
			mpz_sub(greater, greater, smaller);
			mpz_set(arr[j], smaller);
			mpz_set(arr[j+1], greater);
		}
	}
}


/* Function to print an array */
void printArray(mpz_t arr[], int size)
{
	for (int i=0; i < size; i++) gmp_printf("%Zd ", arr[i]);
	cout << "\n";
}

void e3_randomp2(mpz_t r, unsigned limit)
{
	gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state, rand());
	mpz_init(r);
	mpz_urandomb(r, state, limit);
}


