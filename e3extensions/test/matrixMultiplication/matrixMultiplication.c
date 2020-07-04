#include <stdio.h>

int main()
{
    	asm("l.debug");
	int a[3][3] = { {1,2,3}, {2,3,4}, {3,4,5} };
	int b[3][3] = { {1,2,3}, {2,3,4}, {3,4,5} };
	int c[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < 3; k++) c[i][j] += a[i][k] * b[k][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) printf("%d ", c[i][j]);
		printf("\n");
	}
    	asm("l.debug");
	return 0;
}

