unsigned Unumber::HW_NUMWORDS = 16;

void Unumber::mfer_e0(unsigned m[])
{
	__asm__ ("le3.mfer %0,we0(0)" : "=r"(m[15]));
	__asm__ ("le3.mfer %0,we0(1)" : "=r"(m[14]));
	__asm__ ("le3.mfer %0,we0(2)" : "=r"(m[13]));
	__asm__ ("le3.mfer %0,we0(3)" : "=r"(m[12]));
	__asm__ ("le3.mfer %0,we0(4)" : "=r"(m[11]));
	__asm__ ("le3.mfer %0,we0(5)" : "=r"(m[10]));
	__asm__ ("le3.mfer %0,we0(6)" : "=r"(m[9]));
	__asm__ ("le3.mfer %0,we0(7)" : "=r"(m[8]));
	__asm__ ("le3.mfer %0,we0(8)" : "=r"(m[7]));
	__asm__ ("le3.mfer %0,we0(9)" : "=r"(m[6]));
	__asm__ ("le3.mfer %0,we0(10)" : "=r"(m[5]));
	__asm__ ("le3.mfer %0,we0(11)" : "=r"(m[4]));
	__asm__ ("le3.mfer %0,we0(12)" : "=r"(m[3]));
	__asm__ ("le3.mfer %0,we0(13)" : "=r"(m[2]));
	__asm__ ("le3.mfer %0,we0(14)" : "=r"(m[1]));
	__asm__ ("le3.mfer %0,we0(15)" : "=r"(m[0]));
}

void Unumber::mfer_e1(unsigned m[])
{
	__asm__ ("le3.mfer %0,we1(0)" : "=r"(m[15]));
	__asm__ ("le3.mfer %0,we1(1)" : "=r"(m[14]));
	__asm__ ("le3.mfer %0,we1(2)" : "=r"(m[13]));
	__asm__ ("le3.mfer %0,we1(3)" : "=r"(m[12]));
	__asm__ ("le3.mfer %0,we1(4)" : "=r"(m[11]));
	__asm__ ("le3.mfer %0,we1(5)" : "=r"(m[10]));
	__asm__ ("le3.mfer %0,we1(6)" : "=r"(m[9]));
	__asm__ ("le3.mfer %0,we1(7)" : "=r"(m[8]));
	__asm__ ("le3.mfer %0,we1(8)" : "=r"(m[7]));
	__asm__ ("le3.mfer %0,we1(9)" : "=r"(m[6]));
	__asm__ ("le3.mfer %0,we1(10)" : "=r"(m[5]));
	__asm__ ("le3.mfer %0,we1(11)" : "=r"(m[4]));
	__asm__ ("le3.mfer %0,we1(12)" : "=r"(m[3]));
	__asm__ ("le3.mfer %0,we1(13)" : "=r"(m[2]));
	__asm__ ("le3.mfer %0,we1(14)" : "=r"(m[1]));
	__asm__ ("le3.mfer %0,we1(15)" : "=r"(m[0]));
}

void Unumber::mfer_e2(unsigned m[])
{
	__asm__ ("le3.mfer %0,we2(0)" : "=r"(m[15]));
	__asm__ ("le3.mfer %0,we2(1)" : "=r"(m[14]));
	__asm__ ("le3.mfer %0,we2(2)" : "=r"(m[13]));
	__asm__ ("le3.mfer %0,we2(3)" : "=r"(m[12]));
	__asm__ ("le3.mfer %0,we2(4)" : "=r"(m[11]));
	__asm__ ("le3.mfer %0,we2(5)" : "=r"(m[10]));
	__asm__ ("le3.mfer %0,we2(6)" : "=r"(m[9]));
	__asm__ ("le3.mfer %0,we2(7)" : "=r"(m[8]));
	__asm__ ("le3.mfer %0,we2(8)" : "=r"(m[7]));
	__asm__ ("le3.mfer %0,we2(9)" : "=r"(m[6]));
	__asm__ ("le3.mfer %0,we2(10)" : "=r"(m[5]));
	__asm__ ("le3.mfer %0,we2(11)" : "=r"(m[4]));
	__asm__ ("le3.mfer %0,we2(12)" : "=r"(m[3]));
	__asm__ ("le3.mfer %0,we2(13)" : "=r"(m[2]));
	__asm__ ("le3.mfer %0,we2(14)" : "=r"(m[1]));
	__asm__ ("le3.mfer %0,we2(15)" : "=r"(m[0]));
}

void Unumber::mfer_e3(unsigned m[])
{
	__asm__ ("le3.mfer %0,we3(0)" : "=r"(m[15]));
	__asm__ ("le3.mfer %0,we3(1)" : "=r"(m[14]));
	__asm__ ("le3.mfer %0,we3(2)" : "=r"(m[13]));
	__asm__ ("le3.mfer %0,we3(3)" : "=r"(m[12]));
	__asm__ ("le3.mfer %0,we3(4)" : "=r"(m[11]));
	__asm__ ("le3.mfer %0,we3(5)" : "=r"(m[10]));
	__asm__ ("le3.mfer %0,we3(6)" : "=r"(m[9]));
	__asm__ ("le3.mfer %0,we3(7)" : "=r"(m[8]));
	__asm__ ("le3.mfer %0,we3(8)" : "=r"(m[7]));
	__asm__ ("le3.mfer %0,we3(9)" : "=r"(m[6]));
	__asm__ ("le3.mfer %0,we3(10)" : "=r"(m[5]));
	__asm__ ("le3.mfer %0,we3(11)" : "=r"(m[4]));
	__asm__ ("le3.mfer %0,we3(12)" : "=r"(m[3]));
	__asm__ ("le3.mfer %0,we3(13)" : "=r"(m[2]));
	__asm__ ("le3.mfer %0,we3(14)" : "=r"(m[1]));
	__asm__ ("le3.mfer %0,we3(15)" : "=r"(m[0]));
}

void Unumber::mter_e0(unsigned m[]) {
	__asm__ ("le3.mter we0(0),%0" : : "r"(m[15]));
	__asm__ ("le3.mter we0(1),%0" : : "r"(m[14]));
	__asm__ ("le3.mter we0(2),%0" : : "r"(m[13]));
	__asm__ ("le3.mter we0(3),%0" : : "r"(m[12]));
	__asm__ ("le3.mter we0(4),%0" : : "r"(m[11]));
	__asm__ ("le3.mter we0(5),%0" : : "r"(m[10]));
	__asm__ ("le3.mter we0(6),%0" : : "r"(m[9]));
	__asm__ ("le3.mter we0(7),%0" : : "r"(m[8]));
	__asm__ ("le3.mter we0(8),%0" : : "r"(m[7]));
	__asm__ ("le3.mter we0(9),%0" : : "r"(m[6]));
	__asm__ ("le3.mter we0(10),%0" : : "r"(m[5]));
	__asm__ ("le3.mter we0(11),%0" : : "r"(m[4]));
	__asm__ ("le3.mter we0(12),%0" : : "r"(m[3]));
	__asm__ ("le3.mter we0(13),%0" : : "r"(m[2]));
	__asm__ ("le3.mter we0(14),%0" : : "r"(m[1]));
	__asm__ ("le3.mter we0(15),%0" : : "r"(m[0]));
}

void Unumber::mter_e1(unsigned m[]) {
	__asm__ ("le3.mter we1(0),%0" : : "r"(m[15]));
	__asm__ ("le3.mter we1(1),%0" : : "r"(m[14]));
	__asm__ ("le3.mter we1(2),%0" : : "r"(m[13]));
	__asm__ ("le3.mter we1(3),%0" : : "r"(m[12]));
	__asm__ ("le3.mter we1(4),%0" : : "r"(m[11]));
	__asm__ ("le3.mter we1(5),%0" : : "r"(m[10]));
	__asm__ ("le3.mter we1(6),%0" : : "r"(m[9]));
	__asm__ ("le3.mter we1(7),%0" : : "r"(m[8]));
	__asm__ ("le3.mter we1(8),%0" : : "r"(m[7]));
	__asm__ ("le3.mter we1(9),%0" : : "r"(m[6]));
	__asm__ ("le3.mter we1(10),%0" : : "r"(m[5]));
	__asm__ ("le3.mter we1(11),%0" : : "r"(m[4]));
	__asm__ ("le3.mter we1(12),%0" : : "r"(m[3]));
	__asm__ ("le3.mter we1(13),%0" : : "r"(m[2]));
	__asm__ ("le3.mter we1(14),%0" : : "r"(m[1]));
	__asm__ ("le3.mter we1(15),%0" : : "r"(m[0]));
}

void Unumber::mter_e2(unsigned m[]) {
	__asm__ ("le3.mter we2(0),%0" : : "r"(m[15]));
	__asm__ ("le3.mter we2(1),%0" : : "r"(m[14]));
	__asm__ ("le3.mter we2(2),%0" : : "r"(m[13]));
	__asm__ ("le3.mter we2(3),%0" : : "r"(m[12]));
	__asm__ ("le3.mter we2(4),%0" : : "r"(m[11]));
	__asm__ ("le3.mter we2(5),%0" : : "r"(m[10]));
	__asm__ ("le3.mter we2(6),%0" : : "r"(m[9]));
	__asm__ ("le3.mter we2(7),%0" : : "r"(m[8]));
	__asm__ ("le3.mter we2(8),%0" : : "r"(m[7]));
	__asm__ ("le3.mter we2(9),%0" : : "r"(m[6]));
	__asm__ ("le3.mter we2(10),%0" : : "r"(m[5]));
	__asm__ ("le3.mter we2(11),%0" : : "r"(m[4]));
	__asm__ ("le3.mter we2(12),%0" : : "r"(m[3]));
	__asm__ ("le3.mter we2(13),%0" : : "r"(m[2]));
	__asm__ ("le3.mter we2(14),%0" : : "r"(m[1]));
	__asm__ ("le3.mter we2(15),%0" : : "r"(m[0]));
}

void Unumber::mter_e3(unsigned m[]) {
	__asm__ ("le3.mter we3(0),%0" : : "r"(m[15]));
	__asm__ ("le3.mter we3(1),%0" : : "r"(m[14]));
	__asm__ ("le3.mter we3(2),%0" : : "r"(m[13]));
	__asm__ ("le3.mter we3(3),%0" : : "r"(m[12]));
	__asm__ ("le3.mter we3(4),%0" : : "r"(m[11]));
	__asm__ ("le3.mter we3(5),%0" : : "r"(m[10]));
	__asm__ ("le3.mter we3(6),%0" : : "r"(m[9]));
	__asm__ ("le3.mter we3(7),%0" : : "r"(m[8]));
	__asm__ ("le3.mter we3(8),%0" : : "r"(m[7]));
	__asm__ ("le3.mter we3(9),%0" : : "r"(m[6]));
	__asm__ ("le3.mter we3(10),%0" : : "r"(m[5]));
	__asm__ ("le3.mter we3(11),%0" : : "r"(m[4]));
	__asm__ ("le3.mter we3(12),%0" : : "r"(m[3]));
	__asm__ ("le3.mter we3(13),%0" : : "r"(m[2]));
	__asm__ ("le3.mter we3(14),%0" : : "r"(m[1]));
	__asm__ ("le3.mter we3(15),%0" : : "r"(m[0]));
}

void Unumber::hw_modmul()
{
	__asm__ ("le3.modmul we0,we1,we2,we3");	
}

void Unumber::hw_modexp()
{
	__asm__ ("le3.modexp we0,we1,we2,we3");
}

void Unumber::hw_gcd()
{
	__asm__ ("le3.gcd we0,we1,we2");
}

void Unumber::hw_inv()
{
	__asm__ ("le3.inv we0,we1,we2");
}

void Unumber::hw_gfun()
{
	__asm__ ("le3.gfun we0,we1,we2,we3");
}

