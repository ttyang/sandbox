// Copyright Paul A. Bristow 2011
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#include "examples.h"

// Provide main to drive the examples at multiprecision/libs/multiprecision/example/.

int main(int, char**)
{
  using namespace examples;
  nr_001::basic_usage_real();
  nr_002::basic_usage_imag();
  nr_005::recursive_trapezoid_j0_test();
  nr_005::recursive_trapezoid_j0(99.9); // Need some sensible values?
  nr_008::gauss_laguerre_airy_a(0.1);

} // int main(int, char**)


/*

------ Build started: Project: examples, Configuration: Release Win32 ------
  examples.cpp
  Generating code
  Finished generating code
  examples.vcxproj -> I:\boost-sandbox\multiprecision\libs\multiprecision\build\Release\examples.exe
  Elapsed time: 0.015
  +9.44587307982832716739183866499248322976133941375615e+019
  +2.09698382372188863116098818362833127700701734985386e+021
  +4.86500247103478162429349258601772856265628025166097e+022
  +1.17733059799041715307902520581629031216281982090195e+024
  +2.96687310693585122575914351865705158665030594867292e+025
  +7.77320754017193021148895601888147515702380158552306e+026
  +2.11431245092676501752499603713576124271047403126227e+028
  +5.96236111161347734942048882472284670444353676815961e+029
  +1.74100944459113538603078273681907123769751273630261e+031
  +5.25784852266522886581296386519359513784648846363387e+032
  +1.64044873907155140613364472594040168300810440065377e+034
  +5.28224493981039552775033601752809341928609617010513e+035
  +1.75370532001705131521311155781932701520298392847490e+037
  +5.99767219445831549802884152774209839199420503538417e+038
  +2.11118061244932705530615221776521863398196017245523e+040
  +7.64247381706656394020827102831009145501469582428792e+041
  +2.84300025994876178575747682253135402126546684663511e+043
  +1.08602609930042700215935614620697723612340833541461e+045
  +4.25722230925767384846467609313135076560376067482528e+046
  +1.71140336832158488708279978943880300777271179127976e+048
  +7.05098187748492973478113513248786839202357258007261e+049
  Elapsed time: 0.359
  (+3.63810064570506362129185557588738994466463233970151e-001,+4.58043407324450726185754704284951303162020532725223e-001)
  (-3.03804685656726177745224235069494955310479225115672e-001,+2.03958868952789926120616721920074854927952518206331e-001)
  (+1.81766810313790583769173825645643363315294290990890e+000,+3.20984069557630893763274720362853365543357398251682e+000)
  (+3.76137534939215304869987181230767070083038911101276e+000,-1.78579731391204087117855401192746421006323344625127e+000)
  (-1.73460627816191468753736391578905370575918407601057e-001,-4.40382456699559019775574266063837328897652749138239e-001)
  (+1.91952736533350987979784396941574996439877483142963e+000,-6.17231428208379122810380941251168889665148812742544e-001)
  (-1.08238020410574790920165871025228794858704172050553e-001,-4.22320956415409466325223322115323174856923120641602e-001)
  (+9.76016184362798953554072279046243226680447275391847e-001,-1.92304350734967116578965390907545697718867056479786e-001)
  (+1.07774403899516945981543185834029866952803976629211e-001,+7.53771818307352644815486476323978371048898700061450e-001)
  (+2.06650065780626729769874354769145419905709089802511e+000,-1.93370853070835233077502717764161597109061933398617e-001)
  (-1.11446391785785709443790361912967137579417134310212e-002,-2.30254590292808943195442904981270765625843934939329e-001)
  (+7.25356492400088667613963979070715540642253634412744e-001,-5.20312623067742889256891872504372312013439954585365e-003)
  (-7.18312522125451929903412228721973643493165887117494e-002,+2.37016260335712384690121577854176265791713614274100e+000)
  (+5.03091274397895374333989698579302846823401162420066e+000,+3.22795836313041882489082280192057930188514413022260e-001)
  (+2.63199766288982618849903558162745311434814675958182e-001,-2.78618903721406874516761992543488256084524401691380e+000)
  (+7.32662408026359986314202507395896832945061708273308e-001,+8.88338486930972669581009019001006670441312053599635e-002)
  (+8.72631358684603188668889620469197572180472158004398e-002,-6.03844935779761575590814019422378300289522986124475e-001)
  (+7.44654486880417765181565861200570968951773329767789e-001,+1.22306102517083291112180806745464541050282869487968e-001)
  (-1.06411274080354336263752932582585565650760948440100e-001,+5.89784088032966820596499884870223538100111626726026e-001)
  (+1.69946231529488226154248636831247411662121812131515e+000,+3.28037710916811421619267805840796036132663885114308e-001)
  (-2.28279290149888745494570993272712698730843273823878e-001,+1.12994519234025745091725123546628658839123049981433e+000)
  finding approximate roots...
  calculating abscissa and weight for index: 0
  calculating abscissa and weight for index: 1
  calculating abscissa and weight for index: 2
  calculating abscissa and weight for index: 3
  calculating abscissa and weight for index: 4
  calculating abscissa and weight for index: 5
  calculating abscissa and weight for index: 6
  calculating abscissa and weight for index: 7
  calculating abscissa and weight for index: 8
  calculating abscissa and weight for index: 9
  calculating abscissa and weight for index: 10
  calculating abscissa and weight for index: 11
  calculating abscissa and weight for index: 12
  calculating abscissa and weight for index: 13
  calculating abscissa and weight for index: 14
  calculating abscissa and weight for index: 15
  calculating abscissa and weight for index: 16
  calculating abscissa and weight for index: 17
  calculating abscissa and weight for index: 18
  calculating abscissa and weight for index: 19
  calculating abscissa and weight for index: 20
  calculating abscissa and weight for index: 21
  calculating abscissa and weight for index: 22
  calculating abscissa and weight for index: 23
  calculating abscissa and weight for index: 24
  calculating abscissa and weight for index: 25
  calculating abscissa and weight for index: 26
  calculating abscissa and weight for index: 27
  calculating abscissa and weight for index: 28
  calculating abscissa and weight for index: 29
  calculating abscissa and weight for index: 30
  calculating abscissa and weight for index: 31
  calculating abscissa and weight for index: 32
  calculating abscissa and weight for index: 33
  calculating abscissa and weight for index: 34
  calculating abscissa and weight for index: 35
  calculating abscissa and weight for index: 36
  calculating abscissa and weight for index: 37
  calculating abscissa and weight for index: 38
  calculating abscissa and weight for index: 39
  calculating abscissa and weight for index: 40
  calculating abscissa and weight for index: 41
  calculating abscissa and weight for index: 42
  calculating abscissa and weight for index: 43
  calculating abscissa and weight for index: 44
  calculating abscissa and weight for index: 45
  calculating abscissa and weight for index: 46
  calculating abscissa and weight for index: 47
  calculating abscissa and weight for index: 48
  calculating abscissa and weight for index: 49
  calculating abscissa and weight for index: 50
  calculating abscissa and weight for index: 51
  calculating abscissa and weight for index: 52
  calculating abscissa and weight for index: 53
  calculating abscissa and weight for index: 54
  calculating abscissa and weight for index: 55
  calculating abscissa and weight for index: 56
  calculating abscissa and weight for index: 57
  calculating abscissa and weight for index: 58
  calculating abscissa and weight for index: 59
  calculating abscissa and weight for index: 60
  calculating abscissa and weight for index: 61
  calculating abscissa and weight for index: 62
  calculating abscissa and weight for index: 63
  calculating abscissa and weight for index: 64
  calculating abscissa and weight for index: 65
========== Build: 1 succeeded, 0 failed, 0 up-to-date, 0 skipped ==========


*/