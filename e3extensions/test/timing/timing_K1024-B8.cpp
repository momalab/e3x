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
	Cryptosystem cs("101148260960181002668465067371052798930555527660321255597393841844510496135417717026660407878375873963428791934417616190571258802530550575375474560999819972811109186168636626745086878889358259885538434863668621759343704662487495859285375377671849493630095380801109502316392864479934114819020126507139313720649","8","3128254829893779002387828605002623825442444921580754048531245041671497860236326669587139414671858304060077260884559318310663373184561026262673804625476524133807762385570385449070683729147397810361595139433722459442674384921940766471082677629865948382258814626060102096228488392779523232844098041262720720251832552122327288777054539921611003741121175921065473273615245144659700646742462547849449138146615342752039127869275965241729486481519992068194810209503467637077457911775757411300891193819540984249482396082333753240438373585531012286520881938965010138117357382036763515652507265085750662493425787496372337132068","1369361233619631939878553354606045043333661944405373856034782183338425553307813976490122035240318268143271678547420323733170832602123067983646639283196249951075885186348628335600358501006693595696364148055998541450619008873480555220946007962918023657301680080687487500175652272629705019888210127222423581649185895725830767969296151672709260161142559066328532402615622194045380553628502704385096035810339096811793075589193530641654968385580390691894472826634433069503372395371515832421649481139019173843756492122665884228440490499190730946196842122304321545537677896877271060470432264352835521348966022729722102788550","2584732453512816882905418408276152166447422956071610063105778506605460648449485347816749527194348290631626598589766721356959431954588295506839603828171018381299703578168881466042671026189746952172083968036351655601040179650226681473501719091130333303856009429484790690286175241141638636564153317234788304072897223862319005610551922768335237348840414575156720125294162885903893450659707371641644851284647436396215790639305898333740518890712581082533177726526138552386677571236669541582084397423126092476214951472729628988790203684683171064422048678932674884806373909633131296938036236172878502787901464329314762700118", libgDir, gFunctionName);
	e = PAPI_get_real_cyc();
	cout << "Cryptosystem cs: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt a("2986871836313320621486357607589431376918817592727303218759613609025676549120658968135425465917936479419218896386532552137212131576810489030153197192984901235765237370740160076391893839521464730824450217623899592730082255498617563167399284223653005630041646012447332032480883628559768477187400393160121589576370946350017828585072262338500860324686474424390930673553905246481686095926753892963011255415118200169624624455511129851272537957416299844306833616677859732581877333310067053872029894085240931613328252279376820457974842393988960184659793698340736010570927121089459415526118174035905746980899617094271996922078",cs);
	e = PAPI_get_real_cyc();
	cout << "SecureInt a: " << (e-s) << " cycles\n";

	s = PAPI_get_real_cyc();
	SecureInt b("9877400954356183207057814841887583343958433404352973499379001549805969821521440812972622691114322976915618470029789389370478424044418442674044396732800581188883449361758362026964881085557309054928277872890963218939756020130440859951580076799342205992831764762226334989629503415535052909651480932071820626338926211629166974121327298577508234484099866327400794457312982740297231192632129339834221608466370701962176257340297942224966129023453362961542874519906830590312903092182757509851782671114757604225813242227903898165085712954578385763556897909712190490090063512466288267321511174388036628448084789800809731086933",cs);
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

