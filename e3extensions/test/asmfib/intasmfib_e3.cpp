#include <iostream>

using namespace std;

#define SIZE 32
#define MAX_NUM 100000000
#define NUM 7

int main()
{
	cout << "----------------------------------\n";
	asm("l.debug");
	int num=NUM, f1=0, f2=1, fi=1, i=1, result=0;
	int zero=0, one=1;
	int counter=0, tmp1, tmp2, tmp3;
	do {
		// result += (i == num) * fi;
		// fi = f1 + f2;
		// f1 = f2;
		// f2 = fi;
		// ++i;
		asm("l.xor %0,%1,%2" : "=r"(tmp1) : "r"(i), "r"(num));
		asm("l.srl %0,%1,%2" : "=r"(tmp2) : "r"(one), "r"(tmp1));
		asm("l.mul %0,%1,%2" : "=r"(tmp3) : "r"(tmp2), "r"(fi));
		asm("l.add %0,%1,%2" : "=r"(result) : "r"(result), "r"(tmp3));
		asm("l.add %0,%1,%2" : "=r"(fi) : "r"(f1), "r"(f2));
		asm("l.or %0,%1,%2" : "=r"(f1) : "r"(f2), "r"(f2));
		asm("l.or %0,%1,%2" : "=r"(f2) : "r"(fi), "r"(fi));
		asm("l.addi %0,%1,1" : "=r"(i) : "r"(i));
	} while (++counter < MAX_NUM);
	asm("l.debug");
	cout << "fib( " << num << " ) = " << result << "\n";
	return 0;
}
