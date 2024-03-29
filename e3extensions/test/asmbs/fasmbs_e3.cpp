#include <iostream>
// #include "../../src/e3extensions/secureint.h"
#include "../../src/e3extensions/bigint.h"

#define KEYSIZE 2048
#define ENCSIZE (2*KEYSIZE)
#define LEN 28

using namespace std;

void bubbleSort(SecureInt[], int);
void printArray(SecureInt[], int);

// Driver program to test above functions
int main()
{
#if KEYSIZE == 256
	/* key 256 */
	Unumber pri("e5f7bb45339f08ac97bfdf1e4ae08cff89467a2de492fabc6dd6e403cf9ea500a93f159a1da147f6303d4349958c25d8f78a7b1416fa6e86c25c317f2470a51", 16);
	Unumber pub("e5f7bb45339f08ac97bfdf1e4ae08d0c71bb20e53c248fa0c49db1070d3c3d30441fbc3675ef10c1c9a675b8897544d0177a421a876d52a27c2020409a2a2ee", 16);
	Unumber mod("ce9524c4b6e24e86b959ac6966f4f27657c890598834a9d554c16af4ac7d0876b65bc2559ec7ddc18c051544875fd26621466f4ef67d56139376e5039d1fe9", 16);
#elif KEYSIZE == 512
	/* key 512 */
	Unumber pri("cd34507feb6bbdcab6cd421e99ba62a6f205efe4c81c5bdda8ec31cb256a88d59dcede7d085d32fdeb12bc5fcb88191e52e5f81c06bc39e9fc776e5bc4a307eca2b41a868e4dfca89171e753a0ab95226a4a4756ce7470b57ca2357310f3978615d3f06642e7782fe547526327b21b122d9a919772b16c7c49170e5da460da68", 16);
	Unumber pub("cd34507feb6bbdcab6cd421e99ba62a6f205efe4c81c5bdda8ec31cb256a88d769ac7118be85f1026097e60410d02a2d216d42877c35533841e3db2bf87ce2958c07e8a1b3bdebd45269f74880bdf2c4dabce6373a3ec6ce18f0c5b7113e7dcc3a1d74f7245c97ac8d50aa50fccb213e0829b2050f63c2056c6ca974d004253b", 16);
	Unumber mod("a47cd39dac5264ca8722fc73e7644991fdecc650f5a024a1bcbbe83e91ad57dd6bc94dd5de036a54bc6db65dece999aa3e28d3fa0bea047e91ee0b6811cefdd3cdb27f7cf728e7ad5cfb45b163ae2f233acd4bf0abd226b1324aa980dd39f0204fb3d122b8f5ab23e5a9087c2d63b967d31f92d49b101a6c950f3ffaf8e36ab9", 16);
#elif KEYSIZE == 1024
	/* key 1024 */
	Unumber pri
("5c4a4820a6c0f7554d5a04f96f6eda6087ed29d62351ebb5e0672a82f7929567443405b69bfc4d6cb86c0ab311cc0ae135b2576b4eafae41da00814e8d1b960ad1ed2adaf60f968d7a18bb0d6d638db25477237744019311769b81acff01f36b01ff4dc6a07f83e1ccedecd98afdb41a49a833897cf8f8c8fbd0fa2e2da5a3f84cd2530cbf4be645c4077461b180a491c55f41c796d7321417095ae84166df7f1170dae57141a8ce91ca9a5982342654ebe2503eca9f4d436688a6e8da8f9424769677d8029d3343107d6cefbab2aab4d2a84f0218df1ae4b5f9b6df380acaff5b3997ace18cf28df636e16c8eb376dc1706d947872ff79f562c540cdd109188", 16);
	Unumber pub("5c4a4820a6c0f7554d5a04f96f6eda6087ed29d62351ebb5e0672a82f7929567443405b69bfc4d6cb86c0ab311cc0ae135b2576b4eafae41da00814e8d1b960c06578d61b62f21eebe868993a68d937cd7046d9258a5ce002ea1f9147844709acddce06256a841e64273167dd045c529182f7df4f2721217413d66fe617f7e2b5a447648b296ac9e2234f0a7ece6a96fd758cbb771573b14f0f6d13393654b5a932d967055df05691de1a8f5c9096a30a9b01f8f264aa1ab3182c37910912ece47576ee071654a376a60781e89a2e6b04b06062a14e2557ce8608bc96717aa2ca4e46123310b156aed32fa0210c6ad5768ca0d413f7178cc0e81ff6c323ca285", 16);
	Unumber mod("214579653f0d7b4af4e60eaab0d42340f578c293b29cbe69535aba25fc09e2dedd0633093a4be8d1ed0e351c999fe3486ad56e448492e01421c8ed0c3ffc5d337bece0e75289ba03eb285d5bf9946c7a73455858079f80a3016f678e701c2f97512269fe9a66d1aa2ae182f505a0f8494cfa562399cd9fe1adcb2d492600514ef62ea5257baaa74e9f65d99452edda55e9ab9d1a0120a272697e9cf2652a8f4a71dd1d550391c319ccac111e9bf3cc08823f98b1a67b08101c60146c4e11efd178165bfbc9ea9762709735c4ece9af00b9bba297762d2d433bf908fcde2aa1ce60bbfcbc90623ec6660f5c3542d88510d710e480891f9f052d287e6f02d85b39", 16);
#else
	/* key 2048 */
	Unumber pri("7f244bce50c4bbb1f9c295a5ea5cf9adddd248c186b41805c1ef1dbc7de49b797bf97ad1b3434eebbf1e3f7891052e0cf6ea704038bc5c856aecd7e50b460541ff337786d65bdc7c087bcbcf5e2660ec685e10738e142584b5a0288ef753803784acd1cece0c9a4adf0bcdf56601552a707688eb555c933563fe77bcae51d2d2a6d745818cdc70b8ee76caad1cd34642597a6a5c68cdf10d9ba43e49cefa1c549d10497e0ce1eed7f2f03983dcaa6df126e7ca69c14b1534be1ed46bef1b4a0bd9c8c350c7700546ac76d6697afce2a295dda2b898e8b24cfb1fe4b16e1a288f5193d8492a6571546edd93178d9494d306c3f430cace335d0a938257836e4f40225d6f9c25bd385feef6d3fabf882a230607de55bb1520a65d7f3aa4fbf032dd5275651c9dae0b0a2209a02b37e4a7d14618c05c90ef8f0935e4a6897a1e6c8a56707a862e8c925d71279fa810d392793861d1c4330ae216ff4fb831096b0f7ac5cc4776cc311bcff646748b88422592483c7bc6ec991414abe0ec661dd5a5d845398a47f39f59e11c2da975f62dbd2ff19f6dfefa943f8e7b8a6e8edec00a3977f315ee5737ba1e1b5b04730f0cfe15f61caeeb7362a6720ad6c205e07645df4b295553ced06dd0e837085d5370082a3431e47146f46ad7a8099869b12be1904e148c0bc1905ee175855de8a9d624feb2d627d58c79062ed68baf27c8f303c", 16);
	Unumber pub("7f244bce50c4bbb1f9c295a5ea5cf9adddd248c186b41805c1ef1dbc7de49b797bf97ad1b3434eebbf1e3f7891052e0cf6ea704038bc5c856aecd7e50b460541ff337786d65bdc7c087bcbcf5e2660ec685e10738e142584b5a0288ef753803784acd1cece0c9a4adf0bcdf56601552a707688eb555c933563fe77bcae51d2db9a120159dbad83c4a652213a9ccbc47e97efee120aeac8b1377ebf046e6bc649e4052e726c69ae6880551088caa0385228130b2dca52e23a4fecd6879a32a90f206eebbcc968bb5af353becd0d9d3f4abeb24469e32c61387b875b290241fb8c0f6d02048cf1519bc7302d5be215a5bfef389ae8225fc841615a4f5ac10bf31043593744843822e3befb6f81b12982f172216ea995c5e59c6bcb13b9547237745fe8901491fe83d16e008a67d87826e0189deb7e54353e29d0495c940072e5fc59e49778440543afe1d675d44b5509b2bfe4ed2339d71f615cbc542f0fde50c3759f1826970a3f0d35bc308fbd34765e2afcdff741d37ba436d1e8419855ccafb4247a50c8ac6ae1cd6968f5d6404101c672b38bae662e0826a52d2168ec6901b6e2cf7d0968f3aeac2bc826d11c8ae0010ff6df95a99b698ea0e09a8bb6c4c8c07e8a1b3bdebd45269f74880bdf2c4dabce6373a3ec6ce18f0c5b7113e7dcc3a1d74f7245c97ac8d50aa50fccb213e0829b2050f63c2056c6ca974d004253b", 16);
	Unumber mod("3f25085c1c9c7328bbf13679dc47c652d4d3245f7e320bcbe9a199a31571ad6545004cb83a14cc61b5e580892838c17bc83ba24b27d22ab825f52fb19e694d155a14e306bf23c0e5598104153560b1bf8e599feba521129c1cd43e1aac93ad82ce0c3a01e43470c03cd035d65a6d1bb344e3dada151eaba9c167cb2290a93745f24ade4d92a5bbf271b7ee9f327671a5e5202e043208d001512d452ee9d613e43fcbafcbe152cbb95c460b785f7c4e55e2d9d69e3239f1a0186dd763a38902cae0ecf74f09df40c33481fb55cd3939dbcce6656891513ee3dc867c8a853c2639b988283a801e75855a88266ce7d1241ca9b22689e60fd76bdda69b357a4dae3ed68087b4a576a5233dfa96ef663d3c9eb24f486b29a2c9c77d9a3abec21d371e77916b0c06e5c4ec7643f3b2119e99d97237d07b90a73ba6ff431413dbbfc6778ed5af98d863802f16c36674acbda5f6c9d613612595beb8a329ae11f721d92b018085e0678dfe8a4dba3478cbd0bfdf766999db16972900f6fce4d8fad39c71866d2ab062870b6cc286ef5003f3595b6a74327776e1c75cdb5ba616fe876494843750b97627e0e9f75275a3fb5d90018fbb70473143d4e9971fea92559348576e5c4ff276958b375d1da370461b3dae09137b12b5aae5e5d8a62fe42a74910eb83a0e98e9d443c7a845051a7a21929d2e99ea26046e5c0ab53dcc4cea2761", 16);
#endif

	SecureInt::setKey(pri, pub, mod, ENCSIZE, ENCSIZE);

	SecureInt a[LEN];
	for ( size_t i=0; i<LEN; i++ ) a[i] = SecureInt::randomp2(ENCSIZE);

	bubbleSort(a, LEN);

	cout << "Sorted array is:  " << a[0].str() << '\n';
	// printArray(a, LEN);
}

// A function to implement bubble sort
void bubbleSort(SecureInt rr[], int n)
{
	int s = 14;
	unsigned length = Unumber::HW_NUMWORDS;
	unsigned arr[n][length];
	for ( size_t i=0; i<n; i++ )
		SecureInt::exportArray(arr[i], length, rr[i]);

	asm("l.debug");
	int i, j;
	for (i = 0; i < n-1; i++)
	{
		Unumber::mter_e0(arr[0]);
		Unumber::mter_e1(arr[1]);
		Unumber::mter_e2(arr[2]);
		Unumber::mter_e3(arr[3]);
		Unumber::mter_e4(arr[4]);
		Unumber::mter_e5(arr[5]);
		Unumber::mter_e6(arr[6]);
		Unumber::mter_e7(arr[7]);
		Unumber::mter_e8(arr[8]);
		Unumber::mter_e9(arr[9]);
		Unumber::mter_e10(arr[10]);
		Unumber::mter_e11(arr[11]);
		Unumber::mter_e12(arr[12]);

		// Last i elements are already in place
		for (j = 0; j < n-s+1; j++)
		{
			// rd = arr[j+s-1];
			Unumber::mter_e13(arr[j+s-1]);

			asm("le.eleu ze15,ze0,ze1");
			asm("le.emulu ze14,ze15,ze0");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze1");
			asm("le.eadd ze15,ze1,ze0");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze0,ze14,ze14");
			asm("le.eor ze1,ze15,ze15");

			Unumber::mfer_e0(arr[j]);

			asm("le.eleu ze15,ze1,ze2");
			asm("le.emulu ze14,ze15,ze1");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze2");
			asm("le.eadd ze15,ze2,ze1");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze1,ze14,ze14");
			asm("le.eor ze2,ze15,ze15");

			asm("le.eleu ze15,ze2,ze3");
			asm("le.emulu ze14,ze15,ze2");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze3");
			asm("le.eadd ze15,ze3,ze2");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze2,ze14,ze14");
			asm("le.eor ze3,ze15,ze15");

			asm("le.eleu ze15,ze3,ze4");
			asm("le.emulu ze14,ze15,ze3");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze4");
			asm("le.eadd ze15,ze4,ze3");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze3,ze14,ze14");
			asm("le.eor ze4,ze15,ze15");

			asm("le.eleu ze15,ze4,ze5");
			asm("le.emulu ze14,ze15,ze4");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze5");
			asm("le.eadd ze15,ze5,ze4");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze4,ze14,ze14");
			asm("le.eor ze5,ze15,ze15");

			asm("le.eleu ze15,ze5,ze6");
			asm("le.emulu ze14,ze15,ze5");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze6");
			asm("le.eadd ze15,ze6,ze5");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze5,ze14,ze14");
			asm("le.eor ze6,ze15,ze15");

			asm("le.eleu ze15,ze6,ze7");
			asm("le.emulu ze14,ze15,ze6");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze7");
			asm("le.eadd ze15,ze7,ze6");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze6,ze14,ze14");
			asm("le.eor ze7,ze15,ze15");

			asm("le.eleu ze15,ze7,ze8");
			asm("le.emulu ze14,ze15,ze7");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze8");
			asm("le.eadd ze15,ze8,ze7");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze7,ze14,ze14");
			asm("le.eor ze8,ze15,ze15");

			asm("le.eleu ze15,ze8,ze9");
			asm("le.emulu ze14,ze15,ze8");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze9");
			asm("le.eadd ze15,ze9,ze8");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze8,ze14,ze14");
			asm("le.eor ze9,ze15,ze15");

			asm("le.eleu ze15,ze9,ze10");
			asm("le.emulu ze14,ze15,ze9");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze10");
			asm("le.eadd ze15,ze10,ze9");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze9,ze14,ze14");
			asm("le.eor ze10,ze15,ze15");

			asm("le.eleu ze15,ze10,ze11");
			asm("le.emulu ze14,ze15,ze10");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze11");
			asm("le.eadd ze15,ze11,ze10");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze10,ze14,ze14");
			asm("le.eor ze11,ze15,ze15");

			asm("le.eleu ze15,ze11,ze12");
			asm("le.emulu ze14,ze15,ze11");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze12");
			asm("le.eadd ze15,ze12,ze11");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze11,ze14,ze14");
			asm("le.eor ze12,ze15,ze15");

			asm("le.eleu ze15,ze12,ze13");
			asm("le.emulu ze14,ze15,ze12");
			asm("le.elnot ze15,ze15");
			asm("le.emacu ze14,ze15,ze13");
			asm("le.eadd ze15,ze13,ze12");
			asm("le.esub ze15,ze15,ze14");
			asm("le.eor ze12,ze14,ze14");
			asm("le.eor ze13,ze15,ze15");

			asm("le.eor ze0,ze1,ze1");
			asm("le.eor ze1,ze2,ze2");
			asm("le.eor ze2,ze3,ze3");
			asm("le.eor ze3,ze4,ze4");
			asm("le.eor ze4,ze5,ze5");
			asm("le.eor ze5,ze6,ze6");
			asm("le.eor ze6,ze7,ze7");
			asm("le.eor ze7,ze8,ze8");
			asm("le.eor ze8,ze9,ze9");
			asm("le.eor ze9,ze10,ze10");
			asm("le.eor ze10,ze11,ze11");
			asm("le.eor ze11,ze12,ze12");
			asm("le.eor ze12,ze13,ze13");
		}

		Unumber::mfer_e0(arr[j]);
		Unumber::mfer_e1(arr[j+1]);
		Unumber::mfer_e2(arr[j+2]);
		Unumber::mfer_e3(arr[j+3]);
		Unumber::mfer_e4(arr[j+4]);
		Unumber::mfer_e5(arr[j+5]);
		Unumber::mfer_e6(arr[j+6]);
		Unumber::mfer_e7(arr[j+7]);
		Unumber::mfer_e8(arr[j+8]);
		Unumber::mfer_e9(arr[j+9]);
		Unumber::mfer_e10(arr[j+10]);
		Unumber::mfer_e11(arr[j+11]);
		Unumber::mfer_e12(arr[j+12]);
	}

	asm("l.debug");
}


/* Function to print an array */
void printArray(SecureInt arr[], int size)
{
	for (int i=0; i < size; i++) cout << arr[i].str() << " ";
	cout << "\n";
}
