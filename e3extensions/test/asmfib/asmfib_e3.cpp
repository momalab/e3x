#include <iostream>
//#include "../../src/e3extensions/secureint.h"
#include "../../src/e3extensions/bigint.h"

using namespace std;

#define SIZE 32
#define MAX_NUM 10000
#define NUM 7

int main()
{
	asm("l.debug");

	/* key 256 *
	Unumber pri("e5f7bb45339f08ac97bfdf1e4ae08cff89467a2de492fabc6dd6e403cf9ea500a93f159a1da147f6303d4349958c25d8f78a7b1416fa6e86c25c317f2470a51", 16);
	Unumber pub("e5f7bb45339f08ac97bfdf1e4ae08d0c71bb20e53c248fa0c49db1070d3c3d30441fbc3675ef10c1c9a675b8897544d0177a421a876d52a27c2020409a2a2ee", 16);
	Unumber mod("ce9524c4b6e24e86b959ac6966f4f27657c890598834a9d554c16af4ac7d0876b65bc2559ec7ddc18c051544875fd26621466f4ef67d56139376e5039d1fe9", 16);

	SecureInt::setKey(pri, pub, mod, 512, 512);

	/* key 2048 */
	Unumber pri("7f244bce50c4bbb1f9c295a5ea5cf9adddd248c186b41805c1ef1dbc7de49b797bf97ad1b3434eebbf1e3f7891052e0cf6ea704038bc5c856aecd7e50b460541ff337786d65bdc7c087bcbcf5e2660ec685e10738e142584b5a0288ef753803784acd1cece0c9a4adf0bcdf56601552a707688eb555c933563fe77bcae51d2d2a6d745818cdc70b8ee76caad1cd34642597a6a5c68cdf10d9ba43e49cefa1c549d10497e0ce1eed7f2f03983dcaa6df126e7ca69c14b1534be1ed46bef1b4a0bd9c8c350c7700546ac76d6697afce2a295dda2b898e8b24cfb1fe4b16e1a288f5193d8492a6571546edd93178d9494d306c3f430cace335d0a938257836e4f40225d6f9c25bd385feef6d3fabf882a230607de55bb1520a65d7f3aa4fbf032dd5275651c9dae0b0a2209a02b37e4a7d14618c05c90ef8f0935e4a6897a1e6c8a56707a862e8c925d71279fa810d392793861d1c4330ae216ff4fb831096b0f7ac5cc4776cc311bcff646748b88422592483c7bc6ec991414abe0ec661dd5a5d845398a47f39f59e11c2da975f62dbd2ff19f6dfefa943f8e7b8a6e8edec00a3977f315ee5737ba1e1b5b04730f0cfe15f61caeeb7362a6720ad6c205e07645df4b295553ced06dd0e837085d5370082a3431e47146f46ad7a8099869b12be1904e148c0bc1905ee175855de8a9d624feb2d627d58c79062ed68baf27c8f303c", 16);
	Unumber pub("7f244bce50c4bbb1f9c295a5ea5cf9adddd248c186b41805c1ef1dbc7de49b797bf97ad1b3434eebbf1e3f7891052e0cf6ea704038bc5c856aecd7e50b460541ff337786d65bdc7c087bcbcf5e2660ec685e10738e142584b5a0288ef753803784acd1cece0c9a4adf0bcdf56601552a707688eb555c933563fe77bcae51d2db9a120159dbad83c4a652213a9ccbc47e97efee120aeac8b1377ebf046e6bc649e4052e726c69ae6880551088caa0385228130b2dca52e23a4fecd6879a32a90f206eebbcc968bb5af353becd0d9d3f4abeb24469e32c61387b875b290241fb8c0f6d02048cf1519bc7302d5be215a5bfef389ae8225fc841615a4f5ac10bf31043593744843822e3befb6f81b12982f172216ea995c5e59c6bcb13b9547237745fe8901491fe83d16e008a67d87826e0189deb7e54353e29d0495c940072e5fc59e49778440543afe1d675d44b5509b2bfe4ed2339d71f615cbc542f0fde50c3759f1826970a3f0d35bc308fbd34765e2afcdff741d37ba436d1e8419855ccafb4247a50c8ac6ae1cd6968f5d6404101c672b38bae662e0826a52d2168ec6901b6e2cf7d0968f3aeac2bc826d11c8ae0010ff6df95a99b698ea0e09a8bb6c4c8c07e8a1b3bdebd45269f74880bdf2c4dabce6373a3ec6ce18f0c5b7113e7dcc3a1d74f7245c97ac8d50aa50fccb213e0829b2050f63c2056c6ca974d004253b", 16);
	Unumber mod("3f25085c1c9c7328bbf13679dc47c652d4d3245f7e320bcbe9a199a31571ad6545004cb83a14cc61b5e580892838c17bc83ba24b27d22ab825f52fb19e694d155a14e306bf23c0e5598104153560b1bf8e599feba521129c1cd43e1aac93ad82ce0c3a01e43470c03cd035d65a6d1bb344e3dada151eaba9c167cb2290a93745f24ade4d92a5bbf271b7ee9f327671a5e5202e043208d001512d452ee9d613e43fcbafcbe152cbb95c460b785f7c4e55e2d9d69e3239f1a0186dd763a38902cae0ecf74f09df40c33481fb55cd3939dbcce6656891513ee3dc867c8a853c2639b988283a801e75855a88266ce7d1241ca9b22689e60fd76bdda69b357a4dae3ed68087b4a576a5233dfa96ef663d3c9eb24f486b29a2c9c77d9a3abec21d371e77916b0c06e5c4ec7643f3b2119e99d97237d07b90a73ba6ff431413dbbfc6778ed5af98d863802f16c36674acbda5f6c9d613612595beb8a329ae11f721d92b018085e0678dfe8a4dba3478cbd0bfdf766999db16972900f6fce4d8fad39c71866d2ab062870b6cc286ef5003f3595b6a74327776e1c75cdb5ba616fe876494843750b97627e0e9f75275a3fb5d90018fbb70473143d4e9971fea92559348576e5c4ff276958b375d1da370461b3dae09137b12b5aae5e5d8a62fe42a74910eb83a0e98e9d443c7a845051a7a21929d2e99ea26046e5c0ab53dcc4cea2761", 16);

	SecureInt::setKey(pri, pub, mod, 4096, 4096);

	/**/

	SecureInt num = SecureInt::encrypt(NUM); // E1
	// SecureInt f1 = SecureInt::encrypt(0);  // E2
	// SecureInt f2 = SecureInt::encrypt(1);  // E3
	// SecureInt fi = SecureInt::encrypt(1); // E4
	// SecureInt i = SecureInt::encrypt(1);  // E5
	// SecureInt result = SecureInt::encrypt(0); // E0

	unsigned length = Unumber::HW_NUMWORDS;
	unsigned anum[length], aresult[length];
	SecureInt::exportArray(anum, length, num);
	cout << "----------------------------------\n";
	Unumber::mter_e1(anum);
	asm("l.debug");
	asm("le.esub ze0,ze1,ze1");
	asm("le.eor ze2,ze0,ze0");
	asm("le.eor ze3,ze0,ze0");
	asm("le.einc ze3");
	asm("le.eor ze4,ze3,ze3");
	asm("le.eor ze5,ze3,ze3");

	int counter = 0;
	do {
		// // result += (i == num) * fi;
		// // fi = f1 + f2;
		// // f1 = f2;
		// // f2 = fi;
		// // ++i;
		asm("le.eeq ze6,ze5,ze1; \
			 le.emulu ze7,ze6,ze4; \
			 le.eadd ze0,ze0,ze7; \
			 le.eadd ze4,ze2,ze3; \
			 le.eor ze2,ze3,ze3; \
			 le.eor ze3,ze3,ze4; \
			 le.einc ze5");
	} while (++counter < MAX_NUM);
	asm("l.debug");
	Unumber::mfer_e0(aresult);
	SecureInt result = SecureInt::importArray(aresult, length);
	// cout << "fib( " << num.str() << " ) = " << result.str() << "\n";
	return 0;
}
