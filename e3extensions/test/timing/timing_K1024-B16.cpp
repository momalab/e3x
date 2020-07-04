#include <iostream>
#include "../../src/e3extensions/secureint.h"
#include <papi.h>

using namespace std;

string libgDir = "./libg.so";
string gFunctionName = "libg";

int main()
{
	long long s, e;

	s = PAPI_get_real_cyc();
	for (int i = 0; i < 1000000; i++) asm volatile("nop");
	e = PAPI_get_real_cyc();
	cout << "For loop: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	Cryptosystem cs("130187152389290594940045763022498090066728274375053945578087629670312783000886799530281390400518674940533305365761631893967170359549065130841626686230506273559548920873545937214951276946973592350954977904188696962372678744882799008859491971426115640874561470704724285120934564006135290178587400228902562135821","16","16717024782721793485892368159947184021438497174243795962463033105803753074167660958621275208568233208209948718163936720084778980070543706039647639512789665011275754945663350636769156593595892412508160574799239273100078129327720788708139474898696239439365372567443568431103840012544810258342668542296985655681079104685216748617330232546429432198405555921221583452564836511314914926091976951473446247353566033605932522850641946978714476448629750380672704148566891193312076803796862738749351711518392491725208109669004943898969311283541688769427770024175249149037876410438801706066542746382802100567258322100483599038265","13978569845282181645914137732815208805773044110598027505768398132067249368861127768890001098401719045980041606929414869754082521357623199705555873330664587545208678852628033792256699725183805268700054419129081692250331423870080940097850668349933540068018111829980142910067944259740354280787090805366622213143093360350984485830879568912497914672932105478834128233372255628987115226031932245169580854746379754531533293242775366247607924811714497402811886854676279509192536285945025556960472348616958431244728435449223054741264032758613163322843026214886822494828023896052402164446664317722274015823718206118429452089939","11389197427117169388574447846328522509349438718430761666534296410622529618585852117201376451519277366786269037254642999927622512941668810367917534238279622812686540172298745981500602555909619522664708658331096652662078139950953750141656683518008686671329697337047681787018210738971632443074387270982049092446553393552565612655516068669380417101439100462110177201754082688822583879304738227957098253742323179220226657099319454311767112558309470637899466384642491443450805742580044636693382659945834270664621432515252204571458535101150115821062127572664630222814724428458597027792415040027448448061096347228135847034760", libgDir, gFunctionName);
	e = PAPI_get_real_cyc();
	cout << "Cryptosystem cs: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt a("4945400977324111637552903140356718003771108083070569295471688169656484207478279806523950370413898660002556653770925795898498527728755248561560677395753536146360051336227031748819554291244840222191081305286297560586855582642647267159353224497922169633885470435597829058114484621940414765036192319306965964004467429644216370819267677581300851906760149359844144846008213626785448759363898168302684033162397688915214001083738482487583136550666190812566094352708929187228197282113488786185756325184298729298550664289565038209758341044939703921954465052682038151144438415197792637042967413271220929921532099974929348373789",cs);
	e = PAPI_get_real_cyc();
	cout << "SecureInt a: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt b("13644788562788820376085533701904641540372891716387916263075789846048977156849520130136221157673061503613279067492376742403382919470716280331548771057660963836567533719604293714126204172856836221133931966331598781760862645549028438607503480218660172331837226533845049566390056356163716944624309855927887794398636834039482546670628165885089844890823233435852431505346338771491591699714819863119875365157852819158442688452729330950941629792385398497466758894365723181524946530261010733483779929857704294823712728625430602250605143434583813163279313349456719724788750375198638558849400745634269435466554057549963941806318",cs);
	e = PAPI_get_real_cyc();
	cout << "SecureInt b: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt c;
	e = PAPI_get_real_cyc();
	cout << "SecureInt c: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	c = a + b;
	e = PAPI_get_real_cyc();
	cout << "c = a + b: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	c = a * b;
	e = PAPI_get_real_cyc();
	cout << "c = a * b: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	c = SecureInt::G(a,b);
	e = PAPI_get_real_cyc();
	cout << "c = G(a,b): " << (e-s) << " cycles\n";	

	return 0;
}
