#include <iostream>

using namespace std;

#define MAX_NUM 10000000
#define NUM 5

int main()
{
	cout << "----------------------------------\n";
	asm("l.debug");
	int num=NUM, fact=1, i=1, result=0;
	int one=1, tmp;
	int counter=0;
	do {
		// fact *= i;
		asm("l.mul %0,%1,%2" : "=r"(fact) : "r"(fact), "r"(i));
		// result += (i == num) * fact;
		asm("l.xor %0,%1,%2" : "=r"(tmp) : "r"(i), "r"(num));
		asm("l.srl %0,%1,%2" : "=r"(tmp) : "r"(one), "r"(tmp));
		asm("l.mul %0,%1,%2" : "=r"(tmp) : "r"(tmp), "r"(fact));
		asm("l.add %0,%1,%2" : "=r"(result) : "r"(result), "r"(tmp));
		// ++i;
		asm("l.addi %0,%1,1" : "=r"(i) : "r"(i));
	} while (++counter < MAX_NUM);
	asm("l.debug");
	cout << "fib( " << num << " ) = " << result << "\n";
	return 0;
}
