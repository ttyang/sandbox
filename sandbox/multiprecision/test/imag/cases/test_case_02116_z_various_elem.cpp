
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// Automatically generated file
#include <boost/array.hpp>
#include <boost/multiprecision/mp_float_functions.hpp>
#include "../test_case_imag.h"

using boost::multiprecision::mp_float;
using boost::multiprecision::mp_complex;

namespace test
{
  namespace imag
  {
    class TestCase_case_02116_z_various_elem : public TestCaseImag
    {
    public:
      TestCase_case_02116_z_various_elem() { }
      virtual ~TestCase_case_02116_z_various_elem() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_02116_z_various_elem");
        return str;
      }
      virtual void e_float_test(std::vector<mp_complex>& data) const
      {
        data.clear();
        data.push_back(mp_complex(boost::multiprecision::euler_gamma(), boost::multiprecision::golden_ratio()) + static_cast<boost::int32_t>(123));
        data.push_back(mp_complex(boost::multiprecision::euler_gamma(), boost::multiprecision::golden_ratio()) - static_cast<boost::int32_t>(123));
        data.push_back(static_cast<boost::int32_t>(123) + mp_complex(boost::multiprecision::euler_gamma(), boost::multiprecision::golden_ratio()));
        data.push_back(static_cast<boost::int32_t>(123) - mp_complex(boost::multiprecision::euler_gamma(), boost::multiprecision::golden_ratio()));
      }
      virtual const std::vector<mp_complex>& control_data(void) const
      {
        static const boost::array<mp_complex, 4u> a =
        {{
           mp_complex(mp_float("123.57721566490153286060651209008240243104215933593992359880576723488486772677766467093694706329174674951463144724980708248096050401448654283622417399764492353625350033374293733773767394279259525824709491600873520394816567085323315177661152862119950150798479374508570574002992135478614669402960432542151905877553526733139925401296742051375413954911168510280798423487758720503843109399736137255306088933"), mp_float("1.6180339887498948482045868343656381177203091798057628621354486227052604628189024497072072041893911374847540880753868917521266338622235369317931800607667263544333890865959395829056383226613199282902678806752087668925017116962070322210432162695486262963136144381497587012203408058879544547492461856953648644492410443207713449470495658467885098743394422125448770664780915884607499887124007652170575179788")),
           mp_complex(mp_float("-122.422784335098467139393487909917597568957840664060076401194232765115132273222335329063052936708253250485368552750192917519039495985513457163775826002355076463746499666257062662262326057207404741752905083991264796051834329146766848223388471378800498492015206254914294259970078645213853305970395674578480941224464732668600745987032579486245860450888314897192015765122412794961568906002638627446939110669"), mp_float("1.618033988749894848204586834365638117720309179805762862135448622705260462818902449707207204189391137484754088075386891752126633862223536931793180060766726354433389086595939582905638322661319928290267880675208766892501711696207032221043216269548626296313614438149758701220340805887954454749246185695364864449241044320771344947049565846788509874339442212544877066478091588460749988712400765217057517979")),
           mp_complex(mp_float("123.57721566490153286060651209008240243104215933593992359880576723488486772677766467093694706329174674951463144724980708248096050401448654283622417399764492353625350033374293733773767394279259525824709491600873520394816567085323315177661152862119950150798479374508570574002992135478614669402960432542151905877553526733139925401296742051375413954911168510280798423487758720503843109399736137255306088933"), mp_float("1.618033988749894848204586834365638117720309179805762862135448622705260462818902449707207204189391137484754088075386891752126633862223536931793180060766726354433389086595939582905638322661319928290267880675208766892501711696207032221043216269548626296313614438149758701220340805887954454749246185695364864449241044320771344947049565846788509874339442212544877066478091588460749988712400765217057517979")),
           mp_complex(mp_float("122.422784335098467139393487909917597568957840664060076401194232765115132273222335329063052936708253250485368552750192917519039495985513457163775826002355076463746499666257062662262326057207404741752905083991264796051834329146766848223388471378800498492015206254914294259970078645213853305970395674578480941224464732668600745987032579486245860450888314897192015765122412794961568906002638627446939110669"), mp_float("-1.618033988749894848204586834365638117720309179805762862135448622705260462818902449707207204189391137484754088075386891752126633862223536931793180060766726354433389086595939582905638322661319928290267880675208766892501711696207032221043216269548626296313614438149758701220340805887954454749246185695364864449241044320771344947049565846788509874339442212544877066478091588460749988712400765217057517979")),
        }};
        static const std::vector<mp_complex> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_02116_z_various_elem(const bool b_write_output)
    {
      return TestCase_case_02116_z_various_elem().execute(b_write_output);
    }
  }
}
