
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
    class TestCase_case_02115_z_various_elem_trans_log : public TestCaseImag
    {
    public:
      TestCase_case_02115_z_various_elem_trans_log() { }
      virtual ~TestCase_case_02115_z_various_elem_trans_log() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_02115_z_various_elem_trans_log");
        return str;
      }
      virtual void e_float_test(std::vector<mp_complex>& data) const
      {
        data.clear();
        data.push_back(boost::multiprecision::log10(mp_complex(boost::multiprecision::euler_gamma() * boost::multiprecision::thousand(), boost::multiprecision::golden_ratio() * boost::multiprecision::hundred())));
        data.push_back(boost::multiprecision::loga (mp_complex(boost::multiprecision::third(), boost::multiprecision::catalan()), mp_complex(boost::multiprecision::euler_gamma() * boost::multiprecision::thousand(), boost::multiprecision::golden_ratio() * boost::multiprecision::hundred())));
      }
      virtual const std::vector<mp_complex>& control_data(void) const
      {
        static const boost::array<mp_complex, 2u> a =
        {{
           mp_complex(mp_float("2.7777638181068445125215622989826132241825343670322476620967690612086041831575860265883304255870852729464431034889963628180559218041882509751876119253680022807165174683369224716099521572755267649806869902602443171749308616330603703094964445517485476822272538224243994961983467823172043665926206725784592880775007722845264705345837706718695747256245731728041533797136322128615667890849838198485795043753"), mp_float("0.1186938500047589760133099355202950179174515493530137722972013228091808664814949203390521077245126436151868864181077048487971618591058234860434265179830490371616928909064900092918733183436052404189625739397248342361153453242429014438073561239232501370586633960458360265550149839879936813754899149719775222998620431101913267519448098081424016950028351133686451901483400857358986369704287804974461084761")),
           mp_complex(mp_float("0.1139875760921956110095442254766507883484153247446259323527620960143342887191395307123080912587035634101190634167239946464153961517524967858183947836476934982500568344803973918954346789919528898872049523505727844706272295712373397843078340237763440721249051879241616979700149655854321934675908660006261496514688771026599682904118354773948353781855437237597134777077453022667901823314854971212828171471"), mp_float("-5.2374054228785873675424933946726490208297570478077766544558323980538272610142631466154533847901983625595279004885702368429396356537679477008894989627938084244044749438916951096383248235728882816905302834209608735997234673100912397813874921996324282347461251917360029426471614913684695769255306656663055156718313649575198395185390424375042330663662523536789973202205694024245960561314046643707780063748")),
        }};
        static const std::vector<mp_complex> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_02115_z_various_elem_trans_log(const bool b_write_output)
    {
      return TestCase_case_02115_z_various_elem_trans_log().execute(b_write_output);
    }
  }
}
