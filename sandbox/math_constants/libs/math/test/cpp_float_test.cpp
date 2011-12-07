// Copyright John Maddock 2011.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef _MSC_VER 
#  pragma once
#  pragma warning (disable :4127) // expression is constant
#  pragma warning (disable :4996) // use -D_SCL_SECURE_NO_WARNINGS
#  define _SCL_SECURE_NO_WARNINGS
#endif

#include <boost/math/constants/constants.hpp>
#include <boost/math/constants/info.hpp>
#include <boost/multiprecision/cpp_float.hpp>
#include <boost/detail/lightweight_test.hpp>



template <class T>
T brent_gamma()
{
   T n = 3 + boost::math::tools::digits<T>() / 4;
   T lnn = log(n);
   T term = 1;
   T N = -lnn;
   T D = 1;
   T Hk = 0;
   T one = 1;

   for(unsigned k = 1;; ++k)
   {
      term *= n * n;
      term /= k * k;
      Hk += one / k;
      N += term * (Hk - lnn);
      D += term;

      if(term < D * boost::math::tools::epsilon<T>())
         break;
   }
   return N / D;
}

template <class T>
T eg()
{
   T n = boost::math::tools::digits<T>() * 4;
   T k_fact = 1;
   T A = 0;
   T B = 1;
   T H = 0;
   T n_k = 1;

   for(unsigned k = 1;; ++k)
   {
      H += T(1) / k;
      k_fact *= k;
      n_k *= n;
      T term = n_k / (k_fact * k_fact);
      A += term * H;
      B += term;

      if((term < B * boost::math::tools::epsilon<T>()) && (term * H < A * boost::math::tools::epsilon<T>()))
         break;
   }
   return A / B - log(n) / 2;
}

boost::multiprecision::mp_number<boost::multiprecision::cpp_float<1000> > log2 = 
   "6.931471805599453094172321214581765680755001343602552541206800094933936219696947"
   "15605863326996418687542001481020570685733685520235758130557032670751635075961930"
   "72757082837143519030703862389167347112335011536449795523912047517268157493206515"
   "55247341395258829504530070953263666426541042391578149520437404303855008019441706"
   "41671518644712839968171784546957026271631064546150257207402481637773389638550695"
   "26066834113727387372292895649354702576265209885969320196505855476470330679365443"
   "25476327449512504060694381471046899465062201677204245245296126879465461931651746"
   "81392672504103802546259656869144192871608293803172714367782654877566485085674077"
   "64845146443994046142260319309673540257444607030809608504748663852313818167675143"
   "86674766478908814371419854942315199735488037516586127535291661000710535582498794"
   "14729509293113897155998205654392871700072180857610252368892132449713893203784393"
   "53088774825970171559107088236836275898425891853530243634214367061189236789192372"
   "31467232172053401649256872747782344535348e-1";

boost::multiprecision::mp_number<boost::multiprecision::cpp_float<1000> > pi = 
   "3.141592653589793238462643383279502884197169399375105820974944592307816406286208"
   "99862803482534211706798214808651328230664709384460955058223172535940812848111745"
   "02841027019385211055596446229489549303819644288109756659334461284756482337867831"
   "65271201909145648566923460348610454326648213393607260249141273724587006606315588"
   "17488152092096282925409171536436789259036001133053054882046652138414695194151160"
   "94330572703657595919530921861173819326117931051185480744623799627495673518857527"
   "24891227938183011949129833673362440656643086021394946395224737190702179860943702"
   "77053921717629317675238467481846766940513200056812714526356082778577134275778960"
   "91736371787214684409012249534301465495853710507922796892589235420199561121290219"
   "60864034418159813629774771309960518707211349999998372978049951059731732816096318"
   "59502445945534690830264252230825334468503526193118817101000313783875288658753320"
   "83814206171776691473035982534904287554687311595628638823537875937519577818577805"
   "32171226806613001927876611195909216420199";

boost::multiprecision::mp_number<boost::multiprecision::cpp_float<1000> > euler = 
   "5.772156649015328606065120900824024310421593359399235988057672348848677267776646"
   "70936947063291746749514631447249807082480960504014486542836224173997644923536253"
   "50033374293733773767394279259525824709491600873520394816567085323315177661152862"
   "11995015079847937450857057400299213547861466940296043254215190587755352673313992"
   "54012967420513754139549111685102807984234877587205038431093997361372553060889331"
   "26760017247953783675927135157722610273492913940798430103417771778088154957066107"
   "50101619166334015227893586796549725203621287922655595366962817638879272680132431"
   "01047650596370394739495763890657296792960100901512519595092224350140934987122824"
   "79497471956469763185066761290638110518241974448678363808617494551698927923018773"
   "91072945781554316005002182844096053772434203285478367015177394398700302370339518"
   "32869000155819398804270741154222781971652301107356583396734871765049194181230004"
   "06546931429992977795693031005030863034185698032310836916400258929708909854868257"
   "77364288253954925873629596133298574739302e-1";

/*
template <class T>
void test()
{
   T p = boost::math::constants::pi<T>();
   T err = fabs((p - T(pi)) / T(pi)) / boost::math::tools::epsilon<T>();
   unsigned e = err.template convert_to<unsigned>();
   BOOST_TEST(e < 30);
}
*/
template <unsigned N>
void test()
{
   typedef boost::multiprecision::mp_number<boost::multiprecision::cpp_float<N> > mp_t;
   mp_t val = boost::math::constants::euler<mp_t>();
   mp_t err = fabs((val - mp_t(euler)) / (mp_t(euler) * std::numeric_limits<mp_t>::epsilon()));
   unsigned error = err.template convert_to<unsigned>();
   BOOST_TEST(error < 30);

   val = boost::math::constants::pi<mp_t>();
   err = fabs((val - mp_t(pi)) / (mp_t(pi) * std::numeric_limits<mp_t>::epsilon()));
   error = err.template convert_to<unsigned>();
   BOOST_TEST(error < 30);

   val = boost::math::constants::ln_two<mp_t>();
   err = fabs((val - mp_t(log2)) / (mp_t(log2) * std::numeric_limits<mp_t>::epsilon()));
   error = err.template convert_to<unsigned>();
   BOOST_TEST(error < 30);
}

int main()
{
   boost::math::constants::print_info_on_type<boost::multiprecision::cpp_float_50>();
   boost::math::constants::print_info_on_type<boost::multiprecision::cpp_float_100>();
   boost::math::constants::print_info_on_type<boost::multiprecision::mp_number<boost::multiprecision::cpp_float<300> > >();

   test<15>();
   test<30>();
   test<50>();
   test<100>();
   test<200>();
   test<300>();
   test<500>();

  return boost::report_errors();
} //int main()


/*

Output:

  Information on the Implementation and Handling of 
  Mathematical Constants for Type class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<50> >
  
  Checking for std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<50> >> specialisation: yes
  std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<50> >>::digits reports that the radix is 10.
  std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<50> >>::digits reports that the precision is 
  50 decimal digits.
  std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<50> >>::digits reports that the precision is 
  166 binary digits.
  boost::math::policies::precision<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<50> >, struct boost::math::policies::policy<struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy> reports that the compile time precision is 
  169 binary digits.
  The constant will be constructed from a string (and the result cached).
  
  Information on the Implementation and Handling of 
  Mathematical Constants for Type class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<100> >
  
  Checking for std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<100> >> specialisation: yes
  std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<100> >>::digits reports that the radix is 10.
  std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<100> >>::digits reports that the precision is 
  100 decimal digits.
  std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<100> >>::digits reports that the precision is 
  332 binary digits.
  boost::math::policies::precision<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<100> >, struct boost::math::policies::policy<struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy> reports that the compile time precision is 
  335 binary digits.
  The constant will be constructed from a string (and the result cached).
  
  Information on the Implementation and Handling of 
  Mathematical Constants for Type class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<300> >
  
  Checking for std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<300> >> specialisation: yes
  std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<300> >>::digits reports that the radix is 10.
  std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<300> >>::digits reports that the precision is 
  300 decimal digits.
  std::numeric_limits<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<300> >>::digits reports that the precision is 
  996 binary digits.
  boost::math::policies::precision<class boost::multiprecision::mp_number<class boost::multiprecision::cpp_float<300> >, struct boost::math::policies::policy<struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy,struct boost::math::policies::default_policy> reports that the compile time precision is 
  1000 binary digits.
  No errors detected.
  The constant will be calculated (and the result cached).



*/



