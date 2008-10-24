// Copyright Kevin Sopp 2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/unit_test.hpp>
#include "prerequisite.hpp"

BOOST_AUTO_TEST_CASE_TEMPLATE(add_positive_numbers1, mp_int_type, mp_int_types)
{
  mp_int_type x("123456");
  mp_int_type y("987777");
  mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "1111233");
  x = 999U;
  y = 123456U;
  z = x + y;
  BOOST_CHECK_EQUAL(z, "124455");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_positive_numbers2, mp_int_type, mp_int_types)
{
  const mp_int_type x("21474836470");
  const mp_int_type y("1234567845600");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "1256042682070");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_positive_numbers3, mp_int_type, mp_int_types)
{
  const mp_int_type x("0xffffffffffffffff");
  const mp_int_type y("0xffffffffffffffff");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "0x1fffffffffffffffe");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_positive_numbers4, mp_int_type, mp_int_types)
{
  const mp_int_type x("0xffffffffffffffff");
  const mp_int_type y("0xffffffff");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "0x100000000fffffffe");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_negative_numbers, mp_int_type, mp_int_types)
{
  const mp_int_type x("-123456");
  const mp_int_type y("-987777");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "-1111233");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_mixed_numbers1, mp_int_type, mp_int_types)
{
  const mp_int_type x("-123456");
  const mp_int_type y("987777");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "864321");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_mixed_numbers2, mp_int_type, mp_int_types)
{
  const mp_int_type x("123456");
  const mp_int_type y("-987777");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "-864321");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_mixed_numbers3, mp_int_type, mp_int_types)
{
  const mp_int_type x("-123456");
  const mp_int_type y("123456");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "0");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_mixed_numbers4, mp_int_type, mp_int_types)
{
  const mp_int_type x("123456");
  const mp_int_type y("-123456");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "0");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_mixed_numbers5, mp_int_type, mp_int_types)
{
  const mp_int_type x("1000");
  const mp_int_type y("-12345678901000");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "-12345678900000");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_mixed_numbers6, mp_int_type, mp_int_types)
{
  const mp_int_type x("-12345678901000");
  const mp_int_type y("1000");
  const mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "-12345678900000");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_large_and_small, mp_int_type, mp_int_types)
{
  mp_int_type x("123456789");
  mp_int_type y("123");
  mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "123456912");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_small_and_large, mp_int_type, mp_int_types)
{
  mp_int_type x("123");
  mp_int_type y("123456789");
  mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z, "123456912");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(add_large_and_large, mp_int_type, mp_int_types)
{
  mp_int_type x(
    "76563204409879018101322737668344063995824904757312285775560614771886933079"
    "77822556905976720912850551355328340715074887289899094852653102687850101285"
    "85715275531977696497398396067715769512450915961775500023723324150851793075"
    "51871751151095323159497918186624088118225730504044262785072662119470825604"
    "40835072257208973943520251201155002832786969323087571220195329601804141972"
    "71293425859967733061169954398382700046379970842289727254846347411792122453"
    "98890529530611217475343335863666953662801553948341581412563112340543629531"
    "01094529771464590172847457807673685591148055046712881378811934516545088775"
    "38198087116656466935095055228728162461388333618793883566996616940381738437"
    "03453867953392241443573580380271627517797446062394044787118140775664622031"
    "49144609407766890328547643707523663509662747376486271392344480900673178645"
    "33198519112197059826509662943577383543858946941049753393431035706592040680"
    "43848484065292542884106550381079282660840705126574766636237650938379223350"
    "073087806800887586256085275775217219429527000017403144");
  
  mp_int_type y(
    "29156720459736055974643337783563754269574952607968485689453462316428566668"
    "95504701770860331979649536167161534866285341319360225416010322271645564229"
    "97610536562445338176729838019564690253931232562709745122032537539983616770"
    "01864876491464203683664927984801289460556480278145114367860332493722569194"
    "34026051618152579992400234314328079213866348120156368725488604236521299603"
    "05243915357553896356662519397274629471920043679673543282319268893065423613"
    "03777840501083119668898860689222271939900089123195611475211708096094521743"
    "23436842195705603262202927396682954198215622617086455718070601797199587530"
    "86110222151397352239086193648500251298495752840008363650931395221675337916"
    "21665907282124706187656074325458499695895652068822763794228458103499408841"
    "68233732651102406546734395563663969020820490032431359396293047454261598159"
    "68165818673838448637209074584819780088546111644065538550490486693301185614"
    "61602638472505490238203390055056474763248195271964604045005807592301719483"
    "66411676459481184297663915491569500245585996483678005964410842919747216111"
    "69086269285356198998091850661544255466466926579668887000118948737207396398"
    "39189399212362197497646493143022100680619252808094160907526003969639965485"
    "31238493375062268758735445211914107215235958346264702774326161208396163240"
    "36339482493382189215697343908873498104516190541170342091008828518924813674"
    "46253090923280613514725437269574928515018666111820866090440006060807129643"
    "38626199608899966829344884873038261232122027815715568990196536130996880104"
    "97887027262726591236620461428328000537452828616386217063092509908555188454"
    "27278763741671312528892659532960085933913140197210561287118971031419725940"
    "702202830556069344716729071140147820999566475298895832");
  mp_int_type z = x + y;
  BOOST_CHECK_EQUAL(z,
    "29156720459736055974643337783563754269574952607968485689453462316428566668"
    "95504701770860331979649536167161534866285341319360225416010322271645564229"
    "97610536562445338176729838019564690253931232562709745122032537539983616770"
    "01864876491464203683664927984801289460556480278145114367860332493722569194"
    "34026051618152579992400234314328079213866348120156368725488604236521299603"
    "05243915357553896356662519397274629471920043679673543282319268893065423613"
    "03777840501083119668898860689222271939900089123195611475211708096094521743"
    "23436842195705603262202927396682954198215622617086455718070601797199587530"
    "86110222151397352239086193648500251298495752840008363650931395221675337916"
    "98229111692003724288978811993802563691720556826135049569789072875386341921"
    "46056289557079127459584946918992309735895377322330454248946150142111699445"
    "53881094205816145134607470652535549600997027605841038574213810844152978690"
    "13474389623600813397701308241680562881473925776008866830078469711772545088"
    "07246748716690158241184166692724503078372965806765577184606172521551358084"
    "40379695145323932059261805059926955512846897421958614254965296148999518852"
    "38079928742973414972989829006689054343420806756435742320089116310183595016"
    "32333023146526858931582903019587792806384013392977584153138095724941252015"
    "74537569610038656150792399137601660565904524159964225658005445459306552111"
    "49706958876672854958299017649846556032816112174214910877558146836471751674"
    "87770809016666857157892528580561924741784775192201840382541017031670058750"
    "31085546374923651063130124371905384081311775557435970456523545615147229134"
    "71127247806963855412999209914039368594753845323785327923356621969798949290"
    "775290637356956930972814346915365040429093475316298976");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(increment1, mp_int_type, mp_int_types)
{
  mp_int_type x("0");
  for (int i = 0; i < 10; ++i)
    ++x;
  BOOST_CHECK_EQUAL(x, "10");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(increment2, mp_int_type, mp_int_types)
{
  mp_int_type x("-4");
  for (int i = 0; i < 10; ++i)
    ++x;
  BOOST_CHECK_EQUAL(x, "6");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(increment3, mp_int_type, mp_int_types)
{
  mp_int_type x("-130");
  for (int i = 0; i < 10; ++i)
    ++x;
  BOOST_CHECK_EQUAL(x, "-120");
}

BOOST_AUTO_TEST_CASE_TEMPLATE(increment4, mp_int_type, mp_int_types)
{
  mp_int_type x("120");
  for (int i = 0; i < 10; ++i)
    ++x;
  BOOST_CHECK_EQUAL(x, "130");
}

