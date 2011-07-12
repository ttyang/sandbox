
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} � ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// Automatically generated file
#include <e_float/e_float_functions.hpp>
#include "../test_case_imag.h"

namespace test
{
  namespace imag
  {
    class TestCase_case_02911_z_zeta_crit_strip : public TestCaseImag
    {
    public:
      TestCase_case_02911_z_zeta_crit_strip() { }
      virtual ~TestCase_case_02911_z_zeta_crit_strip() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_02911_z_zeta_crit_strip");
        return str;
      }
      virtual void e_float_test(std::vector<ef_complex>& data) const
      {
        data.resize(5u);
        INT32 ten_pow_k = static_cast<INT32>(1);
        for(INT32 k = static_cast<INT32>(0); k < static_cast<INT32>(data.size()); k++)
        {
          const e_float x = ef::half();
          const e_float y = ef::euler_gamma() + ten_pow_k;
          data[static_cast<std::size_t>(k)] = efz::riemann_zeta(ef_complex(x, y));
          ten_pow_k *= static_cast<INT32>(10);
        }
      }
      virtual const std::vector<ef_complex>& control_data(void) const
      {
        static const std::tr1::array<ef_complex, 5u> a =
        {{
           ef_complex(e_float("0.3681013139970567763015339688046027859045663264618427166495486130525128525669532094649215364456148121569510436310015139364427722590160928250391834575740557783063068498906911544014166704659878600325501355140166324819014349469669095085363655293497409908515076728426910881589718781510798466598805016487774524317050409703582470241257001838834960492322629306530544430730900659656869056520947072012390633013"), e_float("-0.45201341366157588621685725506618271791969546991216661904329444316679549071761899622503338670642101873363874711984571274110860552807555955003886738723886771662593758033345139071522549901070311477680204850464079434684030372752137768488543347283418027225210784146576140328833226468442291349880701980453097454969440313075862542245520911313773620328872716183109290047316816733536294604848494344966979169755")),
           ef_complex(e_float("1.50592013755220009166084682382342440449770096691823866255235734500601819702141317582464452820693156606192777115234944317975528855988196312666239875768070987722245649803023126836702729427588237019169902854808466913483302221140017645274971274899027806194295823919627999759345280458419867354988903002086117733951267270743750677739704963370773842792164494138252304910657883924167479721062961911818122311"), e_float("-0.3315331087697970828527529772547052942821896373376292709159962262578968139736666113805777470348927582152272358245302021493652090036340490567825345966926081057892158612233123224156437455551723699322635126531259760892310519117827573465171991420794310578036144306760964307466023763412868414731329642302561854344424794613845736273788820534867093883909781378181808237354639249243381327489753561687093711703")),
           ef_complex(e_float("1.4665463847642891807130950731411511477792846100682082803968051957535985970195564090070968843926802186031821292713955433221530852919668648378425018429635037238638963182444858917610848265210440587521235064698928004924455388328290846065268616675516683304554781990666223111599691202219024406798583985014632324403408243254676838842118685802872505058519118184387176724005520341501420549678713205860471613626"), e_float("-1.5315106178208988736144710587361650785211089606721842765122927394573255071343704974237787082715789695648519297431111281176453323662095399828830449886462414943106727000589707582177155376173289008939869948995039007852876927937643917236001656406526151557194409581899834763997662457280242706142713118609573273175869511971753040145800064522659126276067769207543819523548447980592775048444534138007159370096")),
           ef_complex(e_float("2.4784085121669604539976865158733361716278824609574651367484130834743644270519153622781177345170867273368314929186419194846744339316295351998421814674878292325476518689158045011102508127445357793390765393407389703454220021587870414079030440033643256675158701426146417202942900692261284454219198228913362604765478239130807271872596451944712579083053658084289570927318497547938267861035748755004241768173"), e_float("-0.6531526258615378751094442827290676211889257354523377630839233642936839047956842394849691713916110150968475860005130414230394305902685670695429207876348796209295656557149589823621232665099700069766884571170426773755310049742929953410087939954954553397622196185980901495379884813656740526833809827903058713326638137106765122088814381900336743608050113236561019369950101400419853168841511998821837646116")),
           ef_complex(e_float("-0.060586474545240572082568260357220307300984903125546311852104204588679926681093501932161205358309392594472758954338298445996519850511619750646086121316073246295357108827206618967955250603705971204491789092187495130950124369414327846150538826858734644913025898183787214252477186645069902524926159011649179951281221072151096256110483258620975890646854306584100530075238747951475775925493488909148806872678"), e_float("-0.12603412886220991936091147500359740474021748877451005486259702924742896907215443727945157762438751432849060714805304465198841404186979396596446501751337667378159015631343484674960266782320521700607781405301629909001980811283653229645608770744170608013942540336067075581129413376415178585988804580393269560973109606675937325030251394840387385311285215032864801340562086209871196598237293330683509067968")),
        }};
        static const std::vector<ef_complex> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_02911_z_zeta_crit_strip(const bool b_write_output)
    {
      return TestCase_case_02911_z_zeta_crit_strip().execute(b_write_output);
    }
  }
}
