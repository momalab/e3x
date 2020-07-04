unsigned Unumber::HW_NUMWORDS = 32;

void Unumber::mfer_e0(unsigned m[])
{
	__asm__ ("le3.mfer %0,xe0(0)" : "=r"(m[31]));
	__asm__ ("le3.mfer %0,xe0(1)" : "=r"(m[30]));
	__asm__ ("le3.mfer %0,xe0(2)" : "=r"(m[29]));
	__asm__ ("le3.mfer %0,xe0(3)" : "=r"(m[28]));
	__asm__ ("le3.mfer %0,xe0(4)" : "=r"(m[27]));
	__asm__ ("le3.mfer %0,xe0(5)" : "=r"(m[26]));
	__asm__ ("le3.mfer %0,xe0(6)" : "=r"(m[25]));
	__asm__ ("le3.mfer %0,xe0(7)" : "=r"(m[24]));
	__asm__ ("le3.mfer %0,xe0(8)" : "=r"(m[23]));
	__asm__ ("le3.mfer %0,xe0(9)" : "=r"(m[22]));
	__asm__ ("le3.mfer %0,xe0(10)" : "=r"(m[21]));
	__asm__ ("le3.mfer %0,xe0(11)" : "=r"(m[20]));
	__asm__ ("le3.mfer %0,xe0(12)" : "=r"(m[19]));
	__asm__ ("le3.mfer %0,xe0(13)" : "=r"(m[18]));
	__asm__ ("le3.mfer %0,xe0(14)" : "=r"(m[17]));
	__asm__ ("le3.mfer %0,xe0(15)" : "=r"(m[16]));
	__asm__ ("le3.mfer %0,xe0(16)" : "=r"(m[15]));
	__asm__ ("le3.mfer %0,xe0(17)" : "=r"(m[14]));
	__asm__ ("le3.mfer %0,xe0(18)" : "=r"(m[13]));
	__asm__ ("le3.mfer %0,xe0(19)" : "=r"(m[12]));
	__asm__ ("le3.mfer %0,xe0(20)" : "=r"(m[11]));
	__asm__ ("le3.mfer %0,xe0(21)" : "=r"(m[10]));
	__asm__ ("le3.mfer %0,xe0(22)" : "=r"(m[9]));
	__asm__ ("le3.mfer %0,xe0(23)" : "=r"(m[8]));
	__asm__ ("le3.mfer %0,xe0(24)" : "=r"(m[7]));
	__asm__ ("le3.mfer %0,xe0(25)" : "=r"(m[6]));
	__asm__ ("le3.mfer %0,xe0(26)" : "=r"(m[5]));
	__asm__ ("le3.mfer %0,xe0(27)" : "=r"(m[4]));
	__asm__ ("le3.mfer %0,xe0(28)" : "=r"(m[3]));
	__asm__ ("le3.mfer %0,xe0(29)" : "=r"(m[2]));
	__asm__ ("le3.mfer %0,xe0(30)" : "=r"(m[1]));
	__asm__ ("le3.mfer %0,xe0(31)" : "=r"(m[0]));
}

void Unumber::mfer_e1(unsigned m[])
{
	__asm__ ("le3.mfer %0,xe1(0)" : "=r"(m[31]));
	__asm__ ("le3.mfer %0,xe1(1)" : "=r"(m[30]));
	__asm__ ("le3.mfer %0,xe1(2)" : "=r"(m[29]));
	__asm__ ("le3.mfer %0,xe1(3)" : "=r"(m[28]));
	__asm__ ("le3.mfer %0,xe1(4)" : "=r"(m[27]));
	__asm__ ("le3.mfer %0,xe1(5)" : "=r"(m[26]));
	__asm__ ("le3.mfer %0,xe1(6)" : "=r"(m[25]));
	__asm__ ("le3.mfer %0,xe1(7)" : "=r"(m[24]));
	__asm__ ("le3.mfer %0,xe1(8)" : "=r"(m[23]));
	__asm__ ("le3.mfer %0,xe1(9)" : "=r"(m[22]));
	__asm__ ("le3.mfer %0,xe1(10)" : "=r"(m[21]));
	__asm__ ("le3.mfer %0,xe1(11)" : "=r"(m[20]));
	__asm__ ("le3.mfer %0,xe1(12)" : "=r"(m[19]));
	__asm__ ("le3.mfer %0,xe1(13)" : "=r"(m[18]));
	__asm__ ("le3.mfer %0,xe1(14)" : "=r"(m[17]));
	__asm__ ("le3.mfer %0,xe1(15)" : "=r"(m[16]));
	__asm__ ("le3.mfer %0,xe1(16)" : "=r"(m[15]));
	__asm__ ("le3.mfer %0,xe1(17)" : "=r"(m[14]));
	__asm__ ("le3.mfer %0,xe1(18)" : "=r"(m[13]));
	__asm__ ("le3.mfer %0,xe1(19)" : "=r"(m[12]));
	__asm__ ("le3.mfer %0,xe1(20)" : "=r"(m[11]));
	__asm__ ("le3.mfer %0,xe1(21)" : "=r"(m[10]));
	__asm__ ("le3.mfer %0,xe1(22)" : "=r"(m[9]));
	__asm__ ("le3.mfer %0,xe1(23)" : "=r"(m[8]));
	__asm__ ("le3.mfer %0,xe1(24)" : "=r"(m[7]));
	__asm__ ("le3.mfer %0,xe1(25)" : "=r"(m[6]));
	__asm__ ("le3.mfer %0,xe1(26)" : "=r"(m[5]));
	__asm__ ("le3.mfer %0,xe1(27)" : "=r"(m[4]));
	__asm__ ("le3.mfer %0,xe1(28)" : "=r"(m[3]));
	__asm__ ("le3.mfer %0,xe1(29)" : "=r"(m[2]));
	__asm__ ("le3.mfer %0,xe1(30)" : "=r"(m[1]));
	__asm__ ("le3.mfer %0,xe1(31)" : "=r"(m[0]));
}

void Unumber::mfer_e2(unsigned m[])
{
	__asm__ ("le3.mfer %0,xe2(0)" : "=r"(m[31]));
	__asm__ ("le3.mfer %0,xe2(1)" : "=r"(m[30]));
	__asm__ ("le3.mfer %0,xe2(2)" : "=r"(m[29]));
	__asm__ ("le3.mfer %0,xe2(3)" : "=r"(m[28]));
	__asm__ ("le3.mfer %0,xe2(4)" : "=r"(m[27]));
	__asm__ ("le3.mfer %0,xe2(5)" : "=r"(m[26]));
	__asm__ ("le3.mfer %0,xe2(6)" : "=r"(m[25]));
	__asm__ ("le3.mfer %0,xe2(7)" : "=r"(m[24]));
	__asm__ ("le3.mfer %0,xe2(8)" : "=r"(m[23]));
	__asm__ ("le3.mfer %0,xe2(9)" : "=r"(m[22]));
	__asm__ ("le3.mfer %0,xe2(10)" : "=r"(m[21]));
	__asm__ ("le3.mfer %0,xe2(11)" : "=r"(m[20]));
	__asm__ ("le3.mfer %0,xe2(12)" : "=r"(m[19]));
	__asm__ ("le3.mfer %0,xe2(13)" : "=r"(m[18]));
	__asm__ ("le3.mfer %0,xe2(14)" : "=r"(m[17]));
	__asm__ ("le3.mfer %0,xe2(15)" : "=r"(m[16]));
	__asm__ ("le3.mfer %0,xe2(16)" : "=r"(m[15]));
	__asm__ ("le3.mfer %0,xe2(17)" : "=r"(m[14]));
	__asm__ ("le3.mfer %0,xe2(18)" : "=r"(m[13]));
	__asm__ ("le3.mfer %0,xe2(19)" : "=r"(m[12]));
	__asm__ ("le3.mfer %0,xe2(20)" : "=r"(m[11]));
	__asm__ ("le3.mfer %0,xe2(21)" : "=r"(m[10]));
	__asm__ ("le3.mfer %0,xe2(22)" : "=r"(m[9]));
	__asm__ ("le3.mfer %0,xe2(23)" : "=r"(m[8]));
	__asm__ ("le3.mfer %0,xe2(24)" : "=r"(m[7]));
	__asm__ ("le3.mfer %0,xe2(25)" : "=r"(m[6]));
	__asm__ ("le3.mfer %0,xe2(26)" : "=r"(m[5]));
	__asm__ ("le3.mfer %0,xe2(27)" : "=r"(m[4]));
	__asm__ ("le3.mfer %0,xe2(28)" : "=r"(m[3]));
	__asm__ ("le3.mfer %0,xe2(29)" : "=r"(m[2]));
	__asm__ ("le3.mfer %0,xe2(30)" : "=r"(m[1]));
	__asm__ ("le3.mfer %0,xe2(31)" : "=r"(m[0]));
}

void Unumber::mfer_e3(unsigned m[])
{
	__asm__ ("le3.mfer %0,xe3(0)" : "=r"(m[31]));
	__asm__ ("le3.mfer %0,xe3(1)" : "=r"(m[30]));
	__asm__ ("le3.mfer %0,xe3(2)" : "=r"(m[29]));
	__asm__ ("le3.mfer %0,xe3(3)" : "=r"(m[28]));
	__asm__ ("le3.mfer %0,xe3(4)" : "=r"(m[27]));
	__asm__ ("le3.mfer %0,xe3(5)" : "=r"(m[26]));
	__asm__ ("le3.mfer %0,xe3(6)" : "=r"(m[25]));
	__asm__ ("le3.mfer %0,xe3(7)" : "=r"(m[24]));
	__asm__ ("le3.mfer %0,xe3(8)" : "=r"(m[23]));
	__asm__ ("le3.mfer %0,xe3(9)" : "=r"(m[22]));
	__asm__ ("le3.mfer %0,xe3(10)" : "=r"(m[21]));
	__asm__ ("le3.mfer %0,xe3(11)" : "=r"(m[20]));
	__asm__ ("le3.mfer %0,xe3(12)" : "=r"(m[19]));
	__asm__ ("le3.mfer %0,xe3(13)" : "=r"(m[18]));
	__asm__ ("le3.mfer %0,xe3(14)" : "=r"(m[17]));
	__asm__ ("le3.mfer %0,xe3(15)" : "=r"(m[16]));
	__asm__ ("le3.mfer %0,xe3(16)" : "=r"(m[15]));
	__asm__ ("le3.mfer %0,xe3(17)" : "=r"(m[14]));
	__asm__ ("le3.mfer %0,xe3(18)" : "=r"(m[13]));
	__asm__ ("le3.mfer %0,xe3(19)" : "=r"(m[12]));
	__asm__ ("le3.mfer %0,xe3(20)" : "=r"(m[11]));
	__asm__ ("le3.mfer %0,xe3(21)" : "=r"(m[10]));
	__asm__ ("le3.mfer %0,xe3(22)" : "=r"(m[9]));
	__asm__ ("le3.mfer %0,xe3(23)" : "=r"(m[8]));
	__asm__ ("le3.mfer %0,xe3(24)" : "=r"(m[7]));
	__asm__ ("le3.mfer %0,xe3(25)" : "=r"(m[6]));
	__asm__ ("le3.mfer %0,xe3(26)" : "=r"(m[5]));
	__asm__ ("le3.mfer %0,xe3(27)" : "=r"(m[4]));
	__asm__ ("le3.mfer %0,xe3(28)" : "=r"(m[3]));
	__asm__ ("le3.mfer %0,xe3(29)" : "=r"(m[2]));
	__asm__ ("le3.mfer %0,xe3(30)" : "=r"(m[1]));
	__asm__ ("le3.mfer %0,xe3(31)" : "=r"(m[0]));
}

void Unumber::mter_e0(unsigned m[]) {
	__asm__ ("le3.mter xe0(0),%0" : : "r"(m[31]));
	__asm__ ("le3.mter xe0(1),%0" : : "r"(m[30]));
	__asm__ ("le3.mter xe0(2),%0" : : "r"(m[29]));
	__asm__ ("le3.mter xe0(3),%0" : : "r"(m[28]));
	__asm__ ("le3.mter xe0(4),%0" : : "r"(m[27]));
	__asm__ ("le3.mter xe0(5),%0" : : "r"(m[26]));
	__asm__ ("le3.mter xe0(6),%0" : : "r"(m[25]));
	__asm__ ("le3.mter xe0(7),%0" : : "r"(m[24]));
	__asm__ ("le3.mter xe0(8),%0" : : "r"(m[23]));
	__asm__ ("le3.mter xe0(9),%0" : : "r"(m[22]));
	__asm__ ("le3.mter xe0(10),%0" : : "r"(m[21]));
	__asm__ ("le3.mter xe0(11),%0" : : "r"(m[20]));
	__asm__ ("le3.mter xe0(12),%0" : : "r"(m[19]));
	__asm__ ("le3.mter xe0(13),%0" : : "r"(m[18]));
	__asm__ ("le3.mter xe0(14),%0" : : "r"(m[17]));
	__asm__ ("le3.mter xe0(15),%0" : : "r"(m[16]));
	__asm__ ("le3.mter xe0(16),%0" : : "r"(m[15]));
	__asm__ ("le3.mter xe0(17),%0" : : "r"(m[14]));
	__asm__ ("le3.mter xe0(18),%0" : : "r"(m[13]));
	__asm__ ("le3.mter xe0(19),%0" : : "r"(m[12]));
	__asm__ ("le3.mter xe0(20),%0" : : "r"(m[11]));
	__asm__ ("le3.mter xe0(21),%0" : : "r"(m[10]));
	__asm__ ("le3.mter xe0(22),%0" : : "r"(m[9]));
	__asm__ ("le3.mter xe0(23),%0" : : "r"(m[8]));
	__asm__ ("le3.mter xe0(24),%0" : : "r"(m[7]));
	__asm__ ("le3.mter xe0(25),%0" : : "r"(m[6]));
	__asm__ ("le3.mter xe0(26),%0" : : "r"(m[5]));
	__asm__ ("le3.mter xe0(27),%0" : : "r"(m[4]));
	__asm__ ("le3.mter xe0(28),%0" : : "r"(m[3]));
	__asm__ ("le3.mter xe0(29),%0" : : "r"(m[2]));
	__asm__ ("le3.mter xe0(30),%0" : : "r"(m[1]));
	__asm__ ("le3.mter xe0(31),%0" : : "r"(m[0]));
}

void Unumber::mter_e1(unsigned m[]) {
	__asm__ ("le3.mter xe1(0),%0" : : "r"(m[31]));
	__asm__ ("le3.mter xe1(1),%0" : : "r"(m[30]));
	__asm__ ("le3.mter xe1(2),%0" : : "r"(m[29]));
	__asm__ ("le3.mter xe1(3),%0" : : "r"(m[28]));
	__asm__ ("le3.mter xe1(4),%0" : : "r"(m[27]));
	__asm__ ("le3.mter xe1(5),%0" : : "r"(m[26]));
	__asm__ ("le3.mter xe1(6),%0" : : "r"(m[25]));
	__asm__ ("le3.mter xe1(7),%0" : : "r"(m[24]));
	__asm__ ("le3.mter xe1(8),%0" : : "r"(m[23]));
	__asm__ ("le3.mter xe1(9),%0" : : "r"(m[22]));
	__asm__ ("le3.mter xe1(10),%0" : : "r"(m[21]));
	__asm__ ("le3.mter xe1(11),%0" : : "r"(m[20]));
	__asm__ ("le3.mter xe1(12),%0" : : "r"(m[19]));
	__asm__ ("le3.mter xe1(13),%0" : : "r"(m[18]));
	__asm__ ("le3.mter xe1(14),%0" : : "r"(m[17]));
	__asm__ ("le3.mter xe1(15),%0" : : "r"(m[16]));
	__asm__ ("le3.mter xe1(16),%0" : : "r"(m[15]));
	__asm__ ("le3.mter xe1(17),%0" : : "r"(m[14]));
	__asm__ ("le3.mter xe1(18),%0" : : "r"(m[13]));
	__asm__ ("le3.mter xe1(19),%0" : : "r"(m[12]));
	__asm__ ("le3.mter xe1(20),%0" : : "r"(m[11]));
	__asm__ ("le3.mter xe1(21),%0" : : "r"(m[10]));
	__asm__ ("le3.mter xe1(22),%0" : : "r"(m[9]));
	__asm__ ("le3.mter xe1(23),%0" : : "r"(m[8]));
	__asm__ ("le3.mter xe1(24),%0" : : "r"(m[7]));
	__asm__ ("le3.mter xe1(25),%0" : : "r"(m[6]));
	__asm__ ("le3.mter xe1(26),%0" : : "r"(m[5]));
	__asm__ ("le3.mter xe1(27),%0" : : "r"(m[4]));
	__asm__ ("le3.mter xe1(28),%0" : : "r"(m[3]));
	__asm__ ("le3.mter xe1(29),%0" : : "r"(m[2]));
	__asm__ ("le3.mter xe1(30),%0" : : "r"(m[1]));
	__asm__ ("le3.mter xe1(31),%0" : : "r"(m[0]));
}

void Unumber::mter_e2(unsigned m[]) {
	__asm__ ("le3.mter xe2(0),%0" : : "r"(m[31]));
	__asm__ ("le3.mter xe2(1),%0" : : "r"(m[30]));
	__asm__ ("le3.mter xe2(2),%0" : : "r"(m[29]));
	__asm__ ("le3.mter xe2(3),%0" : : "r"(m[28]));
	__asm__ ("le3.mter xe2(4),%0" : : "r"(m[27]));
	__asm__ ("le3.mter xe2(5),%0" : : "r"(m[26]));
	__asm__ ("le3.mter xe2(6),%0" : : "r"(m[25]));
	__asm__ ("le3.mter xe2(7),%0" : : "r"(m[24]));
	__asm__ ("le3.mter xe2(8),%0" : : "r"(m[23]));
	__asm__ ("le3.mter xe2(9),%0" : : "r"(m[22]));
	__asm__ ("le3.mter xe2(10),%0" : : "r"(m[21]));
	__asm__ ("le3.mter xe2(11),%0" : : "r"(m[20]));
	__asm__ ("le3.mter xe2(12),%0" : : "r"(m[19]));
	__asm__ ("le3.mter xe2(13),%0" : : "r"(m[18]));
	__asm__ ("le3.mter xe2(14),%0" : : "r"(m[17]));
	__asm__ ("le3.mter xe2(15),%0" : : "r"(m[16]));
	__asm__ ("le3.mter xe2(16),%0" : : "r"(m[15]));
	__asm__ ("le3.mter xe2(17),%0" : : "r"(m[14]));
	__asm__ ("le3.mter xe2(18),%0" : : "r"(m[13]));
	__asm__ ("le3.mter xe2(19),%0" : : "r"(m[12]));
	__asm__ ("le3.mter xe2(20),%0" : : "r"(m[11]));
	__asm__ ("le3.mter xe2(21),%0" : : "r"(m[10]));
	__asm__ ("le3.mter xe2(22),%0" : : "r"(m[9]));
	__asm__ ("le3.mter xe2(23),%0" : : "r"(m[8]));
	__asm__ ("le3.mter xe2(24),%0" : : "r"(m[7]));
	__asm__ ("le3.mter xe2(25),%0" : : "r"(m[6]));
	__asm__ ("le3.mter xe2(26),%0" : : "r"(m[5]));
	__asm__ ("le3.mter xe2(27),%0" : : "r"(m[4]));
	__asm__ ("le3.mter xe2(28),%0" : : "r"(m[3]));
	__asm__ ("le3.mter xe2(29),%0" : : "r"(m[2]));
	__asm__ ("le3.mter xe2(30),%0" : : "r"(m[1]));
	__asm__ ("le3.mter xe2(31),%0" : : "r"(m[0]));
}

void Unumber::mter_e3(unsigned m[]) {
	__asm__ ("le3.mter xe3(0),%0" : : "r"(m[31]));
	__asm__ ("le3.mter xe3(1),%0" : : "r"(m[30]));
	__asm__ ("le3.mter xe3(2),%0" : : "r"(m[29]));
	__asm__ ("le3.mter xe3(3),%0" : : "r"(m[28]));
	__asm__ ("le3.mter xe3(4),%0" : : "r"(m[27]));
	__asm__ ("le3.mter xe3(5),%0" : : "r"(m[26]));
	__asm__ ("le3.mter xe3(6),%0" : : "r"(m[25]));
	__asm__ ("le3.mter xe3(7),%0" : : "r"(m[24]));
	__asm__ ("le3.mter xe3(8),%0" : : "r"(m[23]));
	__asm__ ("le3.mter xe3(9),%0" : : "r"(m[22]));
	__asm__ ("le3.mter xe3(10),%0" : : "r"(m[21]));
	__asm__ ("le3.mter xe3(11),%0" : : "r"(m[20]));
	__asm__ ("le3.mter xe3(12),%0" : : "r"(m[19]));
	__asm__ ("le3.mter xe3(13),%0" : : "r"(m[18]));
	__asm__ ("le3.mter xe3(14),%0" : : "r"(m[17]));
	__asm__ ("le3.mter xe3(15),%0" : : "r"(m[16]));
	__asm__ ("le3.mter xe3(16),%0" : : "r"(m[15]));
	__asm__ ("le3.mter xe3(17),%0" : : "r"(m[14]));
	__asm__ ("le3.mter xe3(18),%0" : : "r"(m[13]));
	__asm__ ("le3.mter xe3(19),%0" : : "r"(m[12]));
	__asm__ ("le3.mter xe3(20),%0" : : "r"(m[11]));
	__asm__ ("le3.mter xe3(21),%0" : : "r"(m[10]));
	__asm__ ("le3.mter xe3(22),%0" : : "r"(m[9]));
	__asm__ ("le3.mter xe3(23),%0" : : "r"(m[8]));
	__asm__ ("le3.mter xe3(24),%0" : : "r"(m[7]));
	__asm__ ("le3.mter xe3(25),%0" : : "r"(m[6]));
	__asm__ ("le3.mter xe3(26),%0" : : "r"(m[5]));
	__asm__ ("le3.mter xe3(27),%0" : : "r"(m[4]));
	__asm__ ("le3.mter xe3(28),%0" : : "r"(m[3]));
	__asm__ ("le3.mter xe3(29),%0" : : "r"(m[2]));
	__asm__ ("le3.mter xe3(30),%0" : : "r"(m[1]));
	__asm__ ("le3.mter xe3(31),%0" : : "r"(m[0]));
}

void Unumber::hw_modmul()
{
	__asm__ ("le3.modmul xe0,xe1,xe2,xe3");	
}

void Unumber::hw_modexp()
{
	__asm__ ("le3.modexp xe0,xe1,xe2,xe3");
}

void Unumber::hw_gcd()
{
	__asm__ ("le3.gcd xe0,xe1,xe2");
}

void Unumber::hw_inv()
{
	__asm__ ("le3.inv xe0,xe1,xe2");
}

void Unumber::hw_gfun()
{
	__asm__ ("le3.gfun xe0,xe1,xe2,xe3");
}

