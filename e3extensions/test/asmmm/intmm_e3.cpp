#include <iostream>
#include <cstdlib>

#define T 7
#define M T*1

using namespace std;

void printMatrix(int m[M][M])
{
    for ( int i=0; i<M; i++ )
    {
        for ( int j=0; j<M; j++ ) cout << m[i][j] << " ";
        cout << "\n";
    }
}

int main()
{
    int a[M][M], b[M][M], c[M][M];
    for ( int i=0; i<M; i++ )
    {
        for ( int j=0; j<M; j++ )
        {
            a[i][j] = rand();
            b[i][j] = rand();
            c[i][j] = 0;
        }
    }
    // printMatrix(a);
    // cout << '\n';
    // printMatrix(b);
    // cout << '\n';

	asm("l.debug");

    int t = T;
    for ( int i=0; i<M; i+=t )
	{
        for ( int j=0; j<M; j+=t )
		{
			// c[i][j] = 0;
            for ( int k=0; k<M; k+=t )
			{
				// c[i][j] += a[i][k] * b[k][j];
                int minI = i+t;// < M ? i+t : M;
                for ( int l=i; l<minI; l++ )
                {
                    int minJ = j+t;// < M ? j+t : M;
                    for ( int m=j; m<minJ; m++ )
                    {
                        int sum = 0;
                        int minK = k+t;// < M ? k+t : M;
                        for ( int n=k; n<minK; n++ )
                        {
                            // cout << l << ',' << m << ',' << n << '\n';
                            sum += a[l][n] * b[n][m];
                        }
                        c[l][m] += sum;
                    }
                }
			}
		}
	}

    asm("l.debug");
    // printMatrix(c);
    cout << c[0][0] << '\n';
}
