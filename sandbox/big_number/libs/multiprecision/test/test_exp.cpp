///////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2002 - 2011.
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_
//
// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifdef _MSC_VER
#  define _SCL_SECURE_NO_WARNINGS
#endif

#include <boost/detail/lightweight_test.hpp>
#include <boost/array.hpp>
#include "test.hpp"

#if !defined(TEST_MPF_50) && !defined(TEST_MPF) && !defined(TEST_BACKEND) && !defined(TEST_MPZ) && !defined(TEST_CPP_FLOAT) && !defined(TEST_MPFR) && !defined(TEST_MPFR_50) && !defined(TEST_MPQ)
#  define TEST_MPF_50
//#  define TEST_MPF
#  define TEST_BACKEND
#  define TEST_CPP_FLOAT

#ifdef _MSC_VER
#pragma message("CAUTION!!: No backend type specified so testing everything.... this will take some time!!")
#endif
#ifdef __GNUC__
#pragma warning "CAUTION!!: No backend type specified so testing everything.... this will take some time!!"
#endif

#endif

#if defined(TEST_MPF_50)
#include <boost/multiprecision/gmp.hpp>
#endif
#if defined(TEST_MPFR_50)
#include <boost/multiprecision/mpfr.hpp>
#endif
#ifdef TEST_BACKEND
#include <boost/multiprecision/concepts/mp_number_architypes.hpp>
#endif
#ifdef TEST_CPP_FLOAT
#include <boost/multiprecision/cpp_float.hpp>
#endif

template <class T>
void test()
{
   static const boost::array<T, 51u> data =
   {{
      T("1.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"),
      T("9.47747587596218770242116751705184563668845029215054154915126374673142219159548534317576897266130328412495991561490384353e76"),
      T("8.98225489794452370997623936390755615068333094834545092387689795875746440121970819499035111276893290879203289092353747850e153"),
      T("8.51291041070124257524798251795398355552294928156627848633073113916721592074889256105483993631579761345100284245144410506e230"),
      T("8.06809030516483860484254925989129017112482132468761563276276594763374886826841745433660192438855214332469192411759402790e307"),
      T("7.64651312322841630493169711336894888932951818957138997327518186691187347879142222644283389432604713409023263917264358401e384"),
      T("7.24696436606255985380192585665173794455118215150711210905481870053193336336731228464367470327868286988180495111406609690e461"),
      T("6.86829299533155197480610865771404565313986987801060270120621935139741577246731459024227828759564450034267891072352816870e538"),
      T("6.50940811722948585242669672360741252715012399316164518226061001845519670701239429603657927628755169479689062519606799624e615"),
      T("6.16927583978348964454665652571294215251327375137123272041877979478545511090085756858225302357977159539777447847855503405e692"),
      T("5.84691629437043896753869572004324228849833391140408095171257918435296982661233664069534601413835876272500275725690968474e769"),
      T("5.54140081286660645835370762406928689330724181979654545550204201113926269281603301564114980528619942840737770415885783439e846"),
      T("5.25184925229805200184933663459660562493261505058724212670923083643709964294855282715531768162298567379648573804433968486e923"),
      T("4.97742745928448409225535325233998957076879979440190164347796593390995994951755710667491911026476108957070504003155645761e1000"),
      T("4.71734486697204622371883518659702954552385115723942808636490157561056417525827884479573988899517566587636669779645610803e1077"),
      T("4.47085221753216236037602345430121605512330975424643767098987010800161616413051148037751552110081034066081309007796182114e1154"),
      T("4.23723940366531198300986713567588008777043812458400705569721660157434941774066620870256745107265536124077734836797938268e1231"),
      T("4.01583342289144005397455901781647949754375366066998182220342540048111140676724909947493787596336610499122085983712119281e1308"),
      T("3.80599643873362813900306284477369187319506389058898599816705625750135796510808933786432614186155972485637939057212164098e1385"),
      T("3.60712394320959592074309301816510372687695286650188776957291994751966018917404878612237961367128638199290387601511358836e1462"),
      T("3.41864301533745457066062991907289263038319874930395315315257927161138360206596116102724713069518697248463965164712972907e1539"),
      T("3.24001067063873569456703204286462007769933831045558617578289414699244767403736057931834775727420762410328297596596814910e1616"),
      T("3.07071229688386868087623659761166306563170839771162347830514606977592027644137144160294469813988158463967740978461420862e1693"),
      T("2.91026017157373047094077218552378456052150304677863670611408570458991015300131731261787644801415538043027268185097710615e1770"),
      T("2.75819205688636078700279174380111581147323147951670302427494196210176478494486073721584055059489736040565979466551070179e1847"),
      T("2.61406986804110104534167739704643351039975992759905579635058824027507742375380077276380178376470686987855503581867681046e1924"),
      T("2.47747841124391945459619002346303925269640785743990333362087223895627681769816204236257960940497519376881830373722711456e2001"),
      T("2.34802418757813746316913800667907927718925648696508255347624141597281474683823345136640610924639820192825966082309575303e2078"),
      T("2.22533425939475124828943430510333464605535146852848680647615867629953075390889821397228584866395924176189346073006180260e2155"),
      T("2.10905517593659363154553947631071808925462553114068144748077359132255993441363479041540672158497404660986163617828972963e2232"),
      T("1.99885195510122536266653916064141606295420554580140619900425370702471778604391774578696867899999534265169574306808906810e2309"),
      T("1.89440711840917173277691572886942144916664047407963356271198286654087884646102070148271284410118233470318337745546895603e2386"),
      T("1.79541977639739687088375911648976940254141946934175300605485966288703931992861387257771264702798405630917098672594899744e2463"),
      T("1.70160476180317540861346545791118106171203487587101437710693054174454895160403997508137760007058856854991413121389834429e2540"),
      T("1.61269180804119796097157014527479883521656118500417752963675677684343588976915851637637232001139108420659882326614772004e2617"),
      T("1.52842477060722969066998464046690349841548269556677423378408183476489015878816585045578141383463708674469365281537792914e2694"),
      T("1.44856088916530600122626623629347336702026699647293500058111037526381692645547938577338582002157148103479049071921438452e2771"),
      T("1.37287008819265239873777879432333192404914357037749380145412895230166352318128978403808382142784030558123748263528360645e2848"),
      T("1.30113431416759441771790128053911040907207490879890145597562380328956450092799014856149474809345424672958343296615764490e2925"),
      T("1.23314690739099822369963411660419632130352733806319401863570442920347696015409870236230656305563674376063778482449716744e3002"),
      T("1.16871200663155636468514484039368694043851858077879103221831997264419096417014996945143145495038265243932745953706526253e3079"),
      T("1.10764398487979357804590117089134596938734185016144401218934115168561552640448889215089150481162977776214124397487013110e3156"),
      T("1.04976691458528698318220729857405616816444374000182094405930946710168752954926612218474430081526312018810817657409158490e3233"),
      T("9.94914060836531582868347569174220216007647278536863127198023584205669825317884219144692385409156165042162234017403353704e3309"),
      T("9.42927401023380446961314339401657458785389811652244742482194123119943160577946366372207045050095290781679375214307398844e3386"),
      T("8.93657169598281164656322298275337750103095739790107943666668184304335665562867744740310577868880098719252549186849812451e3463"),
      T("8.46961426624835911826517103631490619655296714141872141145089865045804196205328364155921945616925875458926717336478525196e3540"),
      T("8.02705648870740089929294815816002943860908317454595055392168733404583122074223427054310572378841634984243492063192095337e3617"),
      T("7.60762342267101369970765191988545810374824800500875923752736467467657167098026707905341603949108433696304383346239333297e3694"),
      T("7.21010674617694221027190468649359000420209460539838589305387835463807416706224777302997789297329446308541513638035437482e3771"),
      T("6.83336127500041943234365059231968669406267422759442985746460610830503287734479988530512309065240678799786759250323660701e3848"),
   }};

   T pi = "3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609";

   unsigned max_err = 0;
   for(unsigned k = 0; k < data.size(); k++)
   {
      T val = exp(sqrt((pi * (100 * k)) * (100 * k)));
      T e = relative_error(val, data[k]);
      unsigned err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
      val = exp(-sqrt((pi * (100 * k)) * (100 * k)));
      e = relative_error(val, T(1/data[k]));
      err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
   }
   std::cout << "Max error was: " << max_err << std::endl;
   BOOST_TEST(max_err < 5000);

   static const boost::array<boost::array<T, 2>, 10> exact_data =
   {{
      {{ std::ldexp(1.0, -50), "1.00000000000000088817841970012562676935794497867573073630970950828771105957980924149923657574337470594698012676100224953" }},
      {{ std::ldexp(1.0, -20), "1.00000095367477115374544678824955687428365188553281789775169686343569285229334215539516690752571791280462887427635269562" }},
      {{ std::ldexp(1.0, -10), "1.00097703949241653524284529261160650646585162918174419940186408264916250428896869173656853690882467186075613761065459261" }},
      {{ 0.25, "1.28402541668774148407342056806243645833628086528146308921750729687220776586723800275330641943955356890166283174967968731" }},
      {{ 0.5, "1.64872127070012814684865078781416357165377610071014801157507931164066102119421560863277652005636664300286663775630779700" }},
      {{ 0.75, "2.11700001661267466854536981983709561013449158470240342177913303081098453336401282000279156026661579821888590471901551426" }},
      {{ 10, "22026.4657948067165169579006452842443663535126185567810742354263552252028185707925751991209681645258954515555010924578367" }},
      {{ 10.5, "36315.5026742466377389120269013166179689315579671275857607480190550842856628099187749764427758174866310742771977376827512" }},
      {{ 25, "7.20048993373858725241613514661261579152235338133952787362213864472320593107782569745000325654258093194727871848859163684e10" }},
      {{ 31.25, "3.72994612957188849046766396046821396700589012875701157893019118883826370993674081486706667149871508642909416337810227575e13" }},
   }};

   max_err = 0;
   for(unsigned k = 0; k < exact_data.size(); k++)
   {
      T val = exp(exact_data[k][0]);
      T e = relative_error(val, exact_data[k][1]);
      unsigned err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
      val = exp(-exact_data[k][0]);
      e = relative_error(val, T(1/exact_data[k][1]));
      err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
   }
   std::cout << "Max error was: " << max_err << std::endl;
   BOOST_TEST(max_err < 10);

   BOOST_TEST(exp(T(0)) == 1);
}


int main()
{
#ifdef TEST_BACKEND
   test<boost::multiprecision::mp_number<boost::multiprecision::concepts::mp_number_backend_float_architype> >();
#endif
#ifdef TEST_MPF_50
   test<boost::multiprecision::mpf_float_50>();
   test<boost::multiprecision::mpf_float_100>();
#endif
#ifdef TEST_MPFR_50
   test<boost::multiprecision::mpfr_float_50>();
   test<boost::multiprecision::mpfr_float_100>();
#endif
#ifdef TEST_CPP_FLOAT
   test<boost::multiprecision::cpp_float_50>();
   test<boost::multiprecision::cpp_float_100>();
#endif
   return boost::report_errors();
}



