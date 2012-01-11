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
T atan2_def(T y, T x)
{
   T t;
   t.backend() = boost::multiprecision::default_ops::get_constant_pi<typename T::backend_type>();
   T t2;
   if(x)
      t2 = atan(y / x);
   else
      t2 = y.sign() * t / 2;
   return t2 + (t / 2) * (1 - x.sign()) * T(y.sign() + 0.5).sign();
}

template <class T>
struct is_mpfr_type : public boost::mpl::false_ {};

#ifdef TEST_MPFR_50
template <unsigned Digits10>
struct is_mpfr_type<boost::multiprecision::mp_number<boost::multiprecision::mpfr_float_backend<Digits10> > > : public boost::mpl::true_{};
#endif

template <class T>
void test()
{
   static const boost::array<const char*, 51u> data =
   {{
      "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999966666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666667e-101",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999996666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666668666666666666667e-97",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666686666666666666666666666666666667e-93",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999966666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666866666666666666666666666666666666666666666666667e-89",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999996666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666668666666666666666666666666666666666666666666666666666666666666667e-85",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666686666666666666666666666666666666666666666666666666666666666666666666666666666667e-81",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999966666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666866666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666667e-77",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999996666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666668666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666667e-73",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666686666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666667e-69",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999966666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666866666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666665238095238095238e-65",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999996666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666668666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666665238095238095238095238095238095238095238e-61",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666686666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666665238095238095238095238095238095238095238095238095238095238095238e-57",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999966666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666866666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666665238095238095238095238095238095238095238095238095238095238095238095238095238095238095238e-53",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999996666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666668666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666666665238095238095238095238095238095238095238095238095238095238095238095238095238095238095238095238096349206349206349e-49",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999999999999666666666666666666666666666666666666666666666666666666666666666666666666666666666666666686666666666666666666666666666666666666666666666666666666666666666666666666666666666666665238095238095238095238095238095238095238095238095238095238095238095238095238095238095238206349206349206349206349206349206349206349206349e-45",
         "9.999999999999999999999999999999999999999999999999999999999999999999999999999999966666666666666666666666666666666666666666666666666666666666666666666666666666666866666666666666666666666666666666666666666666666666666666666666666666666666666665238095238095238095238095238095238095238095238095238095238095238095238095238095249206349206349206349206349206349206349206349206349206349206349206349206349206349e-41",
         "9.99999999999999999999999999999999999999999999999999999999999999999999999666666666666666666666666666666666666666666666666666666666666666666666666866666666666666666666666666666666666666666666666666666666666666666666666523809523809523809523809523809523809523809523809523809523809523809523809634920634920634920634920634920634920634920634920634920634920634920634920544011544011544011544011544011544011544e-37",
         "9.999999999999999999999999999999999999999999999999999999999999999666666666666666666666666666666666666666666666666666666666666666686666666666666666666666666666666666666666666666666666666666666665238095238095238095238095238095238095238095238095238095238095238206349206349206349206349206349206349206349206349206349206349206340115440115440115440115440115440115440115440115440115440115440116209346209346209e-33",
         "9.999999999999999999999999999999999999999999999999999999966666666666666666666666666666666666666666666666666666666866666666666666666666666666666666666666666666666666666665238095238095238095238095238095238095238095238095238095249206349206349206349206349206349206349206349206349206349115440115440115440115440115440115440115440115440115440116209346209346209346209346209346209346209346209346209346202679543e-29",
         "9.99999999999999999999999999999999999999999999999666666666666666666666666666666666666666666666666866666666666666666666666666666666666666666666666523809523809523809523809523809523809523809523809634920634920634920634920634920634920634920634920544011544011544011544011544011544011544011544011620934620934620934620934620934620934620934620934554267954267954267954267954267954267954267954268013091483679719e-25",
         "9.999999999999999999999999999999999999999666666666666666666666666666666666666666686666666666666666666666666666666666666665238095238095238095238095238095238095238206349206349206349206349206349206349206340115440115440115440115440115440115440116209346209346209346209346209346209346209279542679542679542679542679542679542679548561895620719150130914836797189738366208428128459088211410192834341441152586663e-21",
         "9.999999999999999999999999999999966666666666666666666666666666666866666666666666666666666666666665238095238095238095238095238095249206349206349206349206349206349115440115440115440115440115440116209346209346209346209346209346202679542679542679542679542679542738366208954444248561895620719149604599047323505527839893164970569113274066834438351466215243304983108499463325146458811824271509689681318218133e-17",
         "9.999999999999999999999996666666666666666666666668666666666666666666666665238095238095238095238096349206349206349206349205440115440115440115440116209346209346209346209345542679542679542679542680130914836797189738366208428128459088211410192834817631628777139613052925311641589740930163598087002528653948764327011735444703713649735994600714288656350334489593033695272837185114343249547095046272603174268e-13",
         "9.999999999999999666666666666666686666666666666665238095238095238206349206349206340115440115440116209346209346209279542679542679548561895620719149604599047323505575458940784018179051162265592202726621494746410579611835097095566286199717626418813764642659343446728207455753397291482030056516178836684094391777365260695851470017381944166954115569576329193296454393446430574957840819236721213626802085619e-9",
         "0.00009999999966666666866666665238095249206349115440116209346202679542738366208428128463850116128619335776637836253560167434464812879197215298894881707269927081030999737549925482008672363799937606915962379247584324159094536421375755997513179578610677454920512897850953612762990732913046921088456079984429888220262137400213929962691532176198436788640624698990926490105259050461938357510947570244880435664081",
         "0.78539816339744830961566084581987572104929234984377645524373614807695410157155224965700870633552926699553702162832057666177346115238764555793133985203212027936257102567548463027638991115573723873259549110720274391648336153211891205844669579131780047728641214173086508715261358166205334840181506228531843114675165157889704372038023024070731352292884109197314759000283263263720511663034603673798537790236",
         "1.5706963267952299525626550249873704896065212085331517483940102693584808194810202180293789115097723406333076648941055516492022741759833189628737308869915412879148320539754700057326930986734751013960313584219296445913757777000240665569182597868494941800236191544832206381775972559949762275927455637707925634113006817837919481411335451596526426779712759369563859151046126747697908496855825977735219514481",
         "1.5707963167948966192313220249730847754318980330208862438222342009158129649367552929648110725556184185509578339104318071142673796252326115673007840833450909541260947278453938016119958041324233151995987794877839930865561434524027270213271053829179745357590596408023867275770197075707094053216000680544580256094089113804288267449089904640326828789035666143699659867092108718279796583028512542392495421779",
         "1.5707963267938966192313216916397514424319180330208862438208054294872415364764378326474936031472490101815502336217205184029120016698547471043186681600526965471042074304163483259318452680435202095109230279463923963492870040904012032740805456738144599352893425202988524603439218707929425378295371082108281620406379082813613862672159901100496534463976107550806601465567059619048829495421806391510160463001",
         "1.5707963267948965192313216916397514420985846996878862438208056294872415364764378306473507460043918673244073765899887723711659699238229101634817272120007484952330785592874771970616254211570733230640365810600043257395046296021443620234312981206088055277773974880349347475097997796620171523611445056144296707974573126845590321623615288317089359131170138395627805178532322154433252386274406088878525130896",
         "1.5707963267948966192213216916397514420985846996875529104874726294872415364764378326473507460043918673044073765899744866568802556381086244491974416088261453206299039561128740224575416159622681282588417758651991386266175167241223840014532761425201608391327088433455208280958809539778973505942839152244275827508237604782514078980809178018719474972957865632271450490908284680846718670522639450168825443945",
         "1.5707963267948966192313206916397514420985846996875529104874722961539082034764378326473507460043918673244073765899744866566802556381086244491960130373975738920584753846844454510289702985019506679413814584048816783091570881436029034819727566620006803196521893628268096302936831517800951527920861130266253182819592915368594665061395258604800061112367475630116742454513973110064559653064241192080164878504",
         "1.5707963267948966192313216915397514420985846996875529104874722961539082031431044993143507460043918673244073765899744866568802556381086244491940130373975738920584753846843025938861131556448078107985386012620245354520143421118568717359410106302546485736203322199696666822417350998320432047401380610785733702300121487566396862863593060802602258914565277827918940256045031718123167711672299800138772937113",
         "1.5707963267948966192313216916397414420985846996875529104874722961539082031431044993140174126710588673244073765899744866568802556381086244491960130373975738920584553846843025938861131556448078107985243155477388211663000563975725860216552963445403628593347290453664920790671319252288686015654237753642876559442969539514448810915541112750654206966513329776061797398902251498342947931452519580358553156893",
         "1.5707963267948966192313216916397514410985846996875529104874722961539082031431044993140174126710585339910740435899744866568802556381086244491960130373975738920584753846843025938861129556448078107985243155477388211663000563975711574502267249159689342879063004739379206504957033538002971729941063150468273384839794936339845636311255398464939921252227615490256602593707446303537753126257714385553358352607",
         "1.5707963267948966192313216916397514420984846996875529104874722961539082031431044993140174126710585339910740432566411533238802556381086244491960130373975738920584753846843025938861131556448078107985243135477388211663000563975711574502267249159689342879061576167950635076385604966574543158512491721896844813411223507768417064883795081004622460934767298029939142275136017732109181697686285814124786923127",
         "1.5707963267948966192313216916397514420985846896875529104874722961539082031431044993140174126710585339910740432566411533235469223047756244491960130373975738920584753846843025938861131556448078107985243155477388211663000563775711574502267249159689342879061576167950635076385604966574400301369634579039701956268380650625559922026652223861765318077624440887081999419104271700363149951654539782378755175984",
         "1.5707963267948966192313216916397514420985846996865529104874722961539082031431044993140174126710585339910740432566411533235469223047752911158626800373975738920584753846843025938861131556448078107985243155477388211663000563975711574502267249157689342879061576167950635076385604966574400301369634579039701956268366364911274207740937938147481032363338726601367713704818557414648864237368825496664469462809",
         "1.5707963267948966192313216916397514420985846996875528104874722961539082031431044993140174126710585339910740432566411533235469223047752911158626797040642405590584753846843025938861131556448078107985243155477388211663000563975711574502267249159689342879061576167930635076385604966574400301369634579039701956268366364911274207740937938147479603791910155172796285133390128843220292808797396925235898034238",
         "1.5707963267948966192313216916397514420985846996875529104774722961539082031431044993140174126710585339910740432566411533235469223047752911158626797040642405587251420513513025938861131556448078107985243155477388211663000563975711574502267249159689342879061576167950635076385604966574200301369634579039701956268366364911274207740937938147479603791910155172796285133389985986077435665940254068093055177095",
         "1.570796326794896619231321691639751442098584699687552910487471296153908203143104499314017412671058533991074043256641153323546922304775291115862679704064240558725142051350969260552780155644807810798524315547738821166300056397571157450226724915968934287906157616795063507638560496657440030136963457903969995626836636491127420774093793814747960379191015517279628513338998598607743566594025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296053908203143104499314017412671058533991074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477798524315547738821166300056397571157450226724915968934287906157616795063507638560496657440030136963457903970195626836636491127418774093793814747960379191015517279628513338998598607743566594025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296153898203143104499314017412671058533991074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477465190982214738821166300056397571157450226724915968934287906157616795063507638560496657440030136963457903970195626836636491127420774093793814747960359191015517279628513338998598607743566594025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296153908202143104499314017412671058533991074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477465190982214405487832967056397571157450226724915968934287906157616795063507638560496657440030136963457903970195626836636491127420774093793814747960379191015517279628513138998598607743566594025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296153908203143004499314017412671058533991074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477465190982214405487832966723064237824450226724915968934287906157616795063507638560496657440030136963457903970195626836636491127420774093793814747960379191015517279628513338998598607743566592025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296153908203143104489314017412671058533991074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477465190982214405487832966723064237824116893391582968934287906157616795063507638560496657440030136963457903970195626836636491127420774093793814747960379191015517279628513338998598607743566594025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296153908203143104499313017412671058533991074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477465190982214405487832966723064237824116893391582635600954573157616795063507638560496657440030136963457903970195626836636491127420774093793814747960379191015517279628513338998598607743566594025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296153908203143104499314017312671058533991074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477465190982214405487832966723064237824116893391582635600954572824283461730507638560496657440030136963457903970195626836636491127420774093793814747960379191015517279628513338998598607743566594025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296153908203143104499314017412661058533991074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477465190982214405487832966723064237824116893391582635600954572824283461730174305227163657440030136963457903970195626836636491127420774093793814747960379191015517279628513338998598607743566594025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296153908203143104499314017412671057533991074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477465190982214405487832966723064237824116893391582635600954572824283461730174305227163324106696803963457903970195626836636491127420774093793814747960379191015517279628513338998598607743566594025406809304089138",
         "1.570796326794896619231321691639751442098584699687552910487472296153908203143104499314017412671058533891074043256641153323546922304775291115862679704064240558725142051350969260552779822311474477465190982214405487832966723064237824116893391582635600954572824283461730174305227163324106696803630124570637195626836636491127420774093793814747960379191015517279628513338998598607743566594025406809304089138",
   }};

   T arg = "1e-100";

   unsigned max_err = 0;
   for(unsigned k = 0; k < data.size(); k++)
   {
      T val = atan(arg);
      T e = relative_error(val, T(data[k]));
      unsigned err = e.template convert_to<unsigned>();
      if(err > max_err)
         max_err = err;
      val = atan(-arg);
      e = relative_error(val, T(-T(data[k])));
      err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
      arg *= 10000;
   }
   std::cout << "Max error was: " << max_err << std::endl;
   BOOST_TEST(max_err < 10);
   BOOST_TEST(atan(T(0)) == 0);

   //
   // And again, but test all the phases of atan2:
   //
   arg = "1e-100";
   unsigned err;
   for(unsigned k = 0; k < data.size(); k++)
   {
      T val = atan2(arg, 1);
      T e = relative_error(val, atan2_def(arg, T(1)));
      err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
      val = atan2(-arg, 1);
      e = relative_error(val, atan2_def(T(-arg), T(1)));
      err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
      val = atan2(arg, -1);
      e = relative_error(val, atan2_def(arg, T(-1)));
      err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
      val = atan2(-arg, -1);
      e = relative_error(val, atan2_def(T(-arg), T(-1)));
      err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
      arg *= 10000;
   }
   //
   // special cases:
   //
   err = relative_error(T(atan2(T(0), T(1))), atan2_def(T(0), T(1))).template convert_to<unsigned>();
   if(err > max_err)
      max_err = err;
   err = relative_error(T(atan2(T(0), T(-1))), atan2_def(T(0), T(-1))).template convert_to<unsigned>();
   if(err > max_err)
      max_err = err;

   T pi;
   pi.backend() = boost::multiprecision::default_ops::get_constant_pi<typename T::backend_type>();

   err = relative_error(T(atan2(T(1), T(0))), T(pi / 2)).template convert_to<unsigned>();
   if(err > max_err)
      max_err = err;

   err = relative_error(T(atan2(T(-1), T(0))), T(pi / -2)).template convert_to<unsigned>();
   if(err > max_err)
      max_err = err;

   T mv = (std::numeric_limits<T>::max)();
   err = relative_error(T(atan2(mv, T(1))), T(pi / 2)).template convert_to<unsigned>();
   if(err > max_err)
      max_err = err;
   err = relative_error(T(atan2(-mv, T(1))), T(pi / -2)).template convert_to<unsigned>();
   if(err > max_err)
      max_err = err;

   if(std::numeric_limits<T>::has_infinity)
   {
      mv = (std::numeric_limits<T>::infinity)();
      err = relative_error(T(atan2(mv, T(1))), T(pi / 2)).template convert_to<unsigned>();
      if(err > max_err)
         max_err = err;
      err = relative_error(T(atan2(-mv, T(1))), T(pi / -2)).template convert_to<unsigned>();
      if(err > max_err)
         max_err = err;
   }
   
   std::cout << "Max error was: " << max_err << std::endl;
   BOOST_TEST(max_err < 2000);
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



