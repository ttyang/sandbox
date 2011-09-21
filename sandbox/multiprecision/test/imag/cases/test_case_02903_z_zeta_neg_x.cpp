
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
    class TestCase_case_02903_z_zeta_neg_x : public TestCaseImag
    {
    public:
      TestCase_case_02903_z_zeta_neg_x() { }
      virtual ~TestCase_case_02903_z_zeta_neg_x() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_02903_z_zeta_neg_x");
        return str;
      }
      virtual void e_float_test(std::vector<mp_complex>& data) const
      {
        data.resize(26u);
        for(boost::int32_t k = static_cast<boost::int32_t>(0); k < static_cast<boost::int32_t>(data.size()); k++)
        {
          data[static_cast<std::size_t>(k)] = boost::multiprecision::riemann_zeta(mp_complex((-103 * mp_float(2 * k)) / 227, k + boost::multiprecision::euler_gamma()));
        }
      }
      virtual const std::vector<mp_complex>& control_data(void) const
      {
        static const boost::array<mp_complex, 26u> a =
        {{
           mp_complex(mp_float("-0.24901506594157280728497287578903486235675039336165025995086134402450015431088581212466284642424472414104204903005735320743532088449681692340749182240515251924994768453034792601212503379414239840811246191186123330112772492681134009659080607656247450281093533938732643134847936910756173002571202926499242845151013509459404995521325493734854770883823768083681890926695264785937823161816308219791388063872"), mp_float("-0.38602138794912402123386762073632313787176277369984568869921243597115319113134262241428911365779347306511485873655385341222864539909468412998633992732586091819153224916111251410670857668387095677871202859326309411631984871597417564074522788897224248121652152721664628539673855426914816859369379345216819589648303281775738233727952730026190428191236895974204323091545457792147902417858496030224460178918")),
           mp_complex(mp_float("0.11493807906679944660034753629394648258707104397480580326434742608394723742762986411156001939065294139383924571782034435542458105882390430418877594355660263027244937089708487055862956579115189696325216336999808249687248537482107315900090129422880538572901278280496389727321174337987561722629984757200221576917722231812935505222447084999226613176791977556522315022600894439769302721685637488329380960931"), mp_float("-0.11929276632667341716772709353355464835395670064020583544421941098889570721552860572031618028652628709635859593471402405941061269301108575504473069842265574757410440727169365988852694795587868100657272582071218469931629998173909140173636032484541745825098810994013185051973093852992030832046589217256952057920642460027602847206048107688834740142393160261277334955450227142266519733947800751933599984697")),
           mp_complex(mp_float("0.1357743758547323920052184167656578042689496150501695932599977941645217525146460862382657340065376129738631605791430197176225667190926001370961007665768203094594770559348986584133023984770867533786068801744337275976867870991272680049791380875791438732818865310907791111018618692809919801679877377165244225625482436623010282651413083524047394337009224345372204636244422368837909274884797774979915908101"), mp_float("0.06291451260953938798577528403305649220346313044913905622831652412691347065774930364057403853389727697586251996748595356324403620595341205073876048607770795252497033608269373417544480795990714451996309077616351984232789760958528455991403701021840720052722709463980454098642458302376960939661415381642945494655343793918316953144291243818204904323892674874014789158232523124998810797532532451943173933117")),
           mp_complex(mp_float("0.03254398335988718854678355495152525494081148104963045052168178620703790179506964470765937865389383928857556301301907349704377375485652164562552140626311929857752325946197385019940789773964279036228526415224721592661654046389027137577316130245238464792059355366267971463990122898487028189495250708724427617932672355282884564823533190186589212308779935665358105722007592750542865832992094931937710544535"), mp_float("0.21378728645098103635922264984955066386823956438837309355818634186645655809746629750195960905237669099384045739678348366666763928326044393926700023636717994619649904762143246382892430078225365706942240319350225038655740195556193378224032014527288083537156432315004855142330508158163476048501691477252657104328396059179672864772905108395257347594590155027945498502090408582771675039319255659426317747383")),
           mp_complex(mp_float("-0.23707436046131209539724555489168040252958912217729479572579198758337512007702008055361976716438971992717477777014496040310796102171944444263100649242513102504505220763203533706406339267100526526180851162034164665861992489850231707866531041584030444421932140975037660336952395265534550819795005791937614817999587183406848863550482840482860370616092472341476385877293787174412385808168759322263720799449"), mp_float("0.33512331202592032697513039931142865955378385277573514518255255393569606733202795346080979619920493431523043144168081206760109404450852601185612247494616843340587747835609592904773914193957620439850189183717333545727526252037786537940522216488211732923808180099502530493592645977368989160222311555276276909134305625736883522969197234590045707073389524863243413444785872550826802516573079741589181645596")),
           mp_complex(mp_float("-0.87840392266648355680895101969440546871732389317799757380007560618285927892542598034153270113591374669453976713564648238865415690044814281125805128585963766383139119426339712667447188283476658925923866666277316005568028645675560380170033587150115878396285330150910497465474100057601716232004998344011634053826491884568871643611397806837824737672115546985599975042514527363496372965600603251026208137202"), mp_float("0.34974540506882773433927812551956948546631008462422417622453621442007406692588504268098583590506910885921318924531151335301039484865388490877856904353755756350699000094219848667755630026154719854715943325835189253493870066318122262217057700249558041819269281615889435235766824999340033459469324669598272515805742229650580796613641862865063351800709662917810875576839661457199109290588519237614258832885")),
           mp_complex(mp_float("-2.5372024850913869130723125407975847251264207037451356452881575310527133158680658360637657965653105949140359769865151241531454191524219463402928971722776387928303582241631729932688272764672721467439043991981552955644599508824644723778585280857072041597767350255123368308881926068533613928110296085479583327073603874798170272643758014149849579418379014924658268682645535157118063692627068843027404897721"), mp_float("-0.0716219607948455300912108250483131657761286741791134913613460520775560438794337215691778968995713159024208984983700424066394384654126300475025787172407328373835202279421149866633890037297432047621485759530521709719450852452401806243036151827560559625318247546978365318284847894491692261949308608899184368248406178542520682325695455044318890987860769556390134947290394021360075791547929196088538924971")),
           mp_complex(mp_float("-7.4526186281968985639046084659224914234169596249343065300288814534427524115286929548522946470506459223124125256048586477082901004779007436937717640111652462898202317786775690488892687736795476879462274928839941413515746818716327595545210837909008270986924668090921819777855318399134525542107443519776446818100729964761968879351366011395507762141289324678857503719827583464707700011161809645371870773671"), mp_float("-2.1798833828883014152135820124713445521880833254543637003734061689664259019505638021837381752490050583060261094810045584452042159823233576011953289135718417599889073821087968053551992559561292188581660077056092314052044872360659653270878913092164577562373394292360964789226962160446664132561156641295446709125080199918275570304631557597775834142250613738224909109052926855889889921375360065435052654942")),
           mp_complex(mp_float("-24.502154793943064053113886597333030407920832653251955227926675835152803273723232633538783198300069316215752550431427629030944768127398335248306281018264694531726166649991005258958012792897397210263076237794536151510954476782368843281536681169122697657877051820863570873618558487557518276717371363676368122674759278529483247838020576993249832813395535066663109810108688251250722379137834004900973177399"), mp_float("-10.552330894360856575107698194989286105753409625484215921582064792732594379505074128938499637311697694834221568081195335979605924584130809718705445631247977200430034327157893696133766967706273619533609396999279602089560459747107619367524466670986909891471089398513007099100474666146335099470159521194385307201103783384617169108977373049914732999777681702327782988460181683092169652971467596565994537858")),
           mp_complex(mp_float("-93.382300641652843384039060342960191979050484485307795183046545507859335971645697559878519722335409756103743233607787220978716250800403405830956333440417066978651809029168903534819531123850205555382529884664241726986616571260101080154747481397867946319100294046426867888748941161538437656553570517604846437621802914658635526153529001142088984205501446275198226602864536101186052980997543249438108433899"), mp_float("-40.540385238487073303481506969193918899946985707022492260654752607796303396360469608495332837716208525263409417287676987635200512521364788426235408719690163541082951333580450121824990083240449418852481691009862149822933679517954277828204424414121335606109869006392332086724923796961294818760070450635927303373443122263000043117304025956860453540714487034666709769905509437704008745245343744540587014632")),
           mp_complex(mp_float("-407.44149746722939613062889470842476496337562378280639679932350082875016855313273648618629079722360262161026582114812502204254944410108013381003159380665743390004078566159889772380929958367165137791106171723695700331921578064446372373558723219332478770186085440537451755687064215002132420380346776897542653159913101423485363283757429877801758370483491324909902104149684123507758888470342112377319196953"), mp_float("-128.90524220509900720828271654900143348835684767817075129066564007109458645475917682477994200782561738550667025484892254833177338351912510143410401746189330472769182104409575950575932312365962996264475954456673587311009043333566775041716541553076617480630436996890995478977942622630856384006235087799348944128657165272968222432326858838774784062931571951807502174182107657092569581165663545147922385844")),
           mp_complex(mp_float("-1944.9782973384025323743337037555522368383794535888995233225656412990301358476451488872030541557689073619761196088859420418181989396452220920730927727079606628273412351793869696252472306570325357836031534546830981390689292017827124333182483934683140384669884571797678810768045275278470639985034199692442720819981793620578229613982464373576170354297165735472765277156898885780579251904510161409908823721"), mp_float("-210.8708265752790538318586458444749028988660843779982903231180692813360435544946216768859724335199648587856666331138849774716989228170132969315932164885858646377643117931049328323133534048705611748992580748722715671076752017022836822828966947649289825115199953047214352928131531766215517159026875421687810549901968747337417895537265423291649954210287403274537577769956162526885558372590703445834867339")),
           mp_complex(mp_float("-9541.7199234273553202011776390631275274643054760413735310745545709021524294212340467314794143075111155332624388762255266951657891129358511889863639933448840035817243815343626635779629496334231530121582227186853182196539176742327353973108682906417218450763201854031360950716531982753409770297445667898502887447595173708129652512812749581274503553170645300764843110197557690668124613762913543520981803691"), mp_float("1706.2162910714897487363251871475009893346168133525846819261305685399964072320326384198081519731418465546363127360609774141201567893874144899995151286002803771938459589609628398156912629310136279641873619522525962807928000949094372181534085502334522932879645289023725101430674077762972311068954998072241978441726388423649558400753898155657574508155272092292757030835126471551678505778228767890687030074")),
           mp_complex(mp_float("-44254.659913756154490572647101697450001484111551311410220511720488073850576429993290599802335308509503966295882749644278894178586320912644501186003604523518676848369341069809707728260697559063267279178977471082721324861198630813174326266015981582467499144919396086287970053584732807899756938606726921609861358245063822975376011839211562552186481966536610543703541048353295613143339127576381740638652612"), mp_float("26609.46720202186613334188277443786330647243403991665525663951463854986271524740349011932050924763660258125062361855376536047489576922498828873594179689950352534497793857637107625801026611812515233462573985283736235080749906959082835392152454703257305241312587653040806518291567042750654310639603094905955874618038904560853519255668014498780255701840018004091726546947314725414881992113711029651923997")),
           mp_complex(mp_float("-164008.56484449087813628301030597689229983734072712589960339748250865066013024512812334938379155179617199113044526296518165396591991134400389224611379927271344362672260535635322802008319192135234418167271051035986532960138554904185506981003671992177089503897335544292604408136225328367597841093227307192975285596630613905423677718319172036538235502962715173058499331608575715295625569657562169560423244"), mp_float("244208.67315003876655335018317927762271353601115668407004550586149413032989445106733625240276221848217261986073768292152554992364668151660537226147199820773215844539937755830812041306664830247277441343476938070825738700289032101251905786853366124069214149210909889652593635754817895608336737529204329064684612058035265427493188600518568854566664993961946320219634232596374685649204590712975659591984854")),
           mp_complex(mp_float("-151006.2490323117144397356259374608139384342756498385705188505615702538106345360603861514555398430754772602129188607123058975783319684690836614802598549230079998551602742951804775099765340640217138047499655472797956270238284932526899784957348454718070272731326296086417255496057976699471765490652980071934213062444009804154631764144023208973732111566084017673085997635824318452304944836829847655202049"), mp_float("1.7772612644053884461296433541043604631222692127193884514190476527205868724746390201847433393462615757401731441531162059385986354688383259188976807195869004986892773785512585851676187063459144940575880484257567759322329928982719381086761937717194217679426073558487227870562594154009589781403338511152825855966209661234622014625219132086307394769946222244810778056798693162328263580997177123511098332669e6")),
           mp_complex(mp_float("5.3563706499280273256990002440913160207376653067115006146345846496425090327745616614728373204215030034640574277272007772632896685111560495659293200650528966230974775451177647542626720310327721518625086374923579169864018681607270696829729458650925107783371685586432635404242461207324360072613079115496092953883582063214499628068656823744234518468574070793893813763385308341768803785655016988014237567819e6"), mp_float("1.01366735188041665732963536791977018396867766733288597729349785670936302567772790841093754613026095847024282419912095123913000503793009827708331494782751367976701679569123568059412110032452521693054331913451238327904672923030065916647794645397016256989158989812100026545506172322988441249553742270727015215412227041443262299877390139487681930043745113105834811965542719502276588580120893504521351719862e7")),
           mp_complex(mp_float("6.9980516277819693339685211314050881267044933975449574845026377186745923664324896573270170807761195767925619492038241988013321875782255517109498195908728902723904942042168056544092288448629250075594618551022406825996851013552446747159142482095295718969685233729586062379138954570334142795585042752432709414592757410018731655880717021030425897626729368649360874906567611420540263442976281214643229572172e7"), mp_float("3.4099855708594028753483579839406982022009775371443608642810980879751603582115940666340436586928324004738075848352253337603612850180499556308071332742263410987340207522842382797835638629576775970345553121734728070746760179528262884250768724942635819463095943783311743090368721948246302456746196596705296797741651846505201168128510407772400934607137637862561219395319875989201585352007328442814287900766e7")),
           mp_complex(mp_float("5.4136509085596141180656881080440224859251993165662767406659651181944532816332257861775117591619005566733007565896521617551439927690099406323815196803846667310450922934148636566208314769845382215731916432013554531856509960195037537800998966715984000934106944498842069440194451309294230637235194708155455779169192020301422544173004370004386908655351223181290779775130832991080241913825106653175087992949e8"), mp_float("-1.2949045258244371127184254976887270738828471561700518611225568923672425989931958885938260754088099671025441367968285688595996648268410395106601792620903116830518279125021740045026419045021037947452614197696423582261296881327835985142653811581798523583112962783099085081962728795931389473328213485676507180013475605551578584053163861102147080514707462556787884819925667006712317532877329680492844322897e8")),
           mp_complex(mp_float("2.3391830108117226865528042105802050390534688207985105929781259299378980944321801367693370882278870385747529632844793408850567944239221823020852935862865956436243673385941526799722724434358141610211307899356840272946855642582813312725728050637131862914330916834403154212460038491247974544314868895223050080323691910399877784725403371972751142528810035291019082349450915455332910603443350540083689320869e9"), mp_float("-3.4639673650011527613391888472772238621637769294471471999969063167305563775045590356838611754502813843055726744201955868979595238432065560268645380149992696662096334179862192811159183582582190144903961719634654298780650996471448908073512991299604773649221852781125849698821133459590338702255653882428897145866791771893624866469394487632595850683178078455840029329739775803141558951555430875708701317247e9")),
           mp_complex(mp_float("-6.506985412453989154585441515625240053999811404639004646639063518245989363539937061299471983253178474966453843229974771797433537994813422960615573849321602991784669235571794464894594371454127861157284324732949455285012054524768183200027511260348485943989556058628953212491928051298302243574334089566237473873098985106046655181465569877273929294647380396588329921163220749177920609447008503115578125898e9"), mp_float("-3.2227875865612696906291285357455939330127035698653023897662225043749913146071051784740191604057972895508066929540539985069984489429580808657320252088532822367917862151580649345923998749746029808290666735487251894508411627600847746334742591024395227896008363690690844438113021902030124657764398336367887625528514377031369427398323571290578453907283141015094175742190834360747622263786759874707559683434e10")),
           mp_complex(mp_float("-2.3324641859761530082333288230997512621353384325146417683849695504123167531106152670720772706309985507813418292102269192163074175625096476300164792913701293376324818227505499305978239630110672731294713525167597190679324877741602424166605641673424377819688274266521103561230570348468551437254826132005449625947541287341298003169487103018552193159559682611999920551405621462206639863046843682879234107645e11"), mp_float("-1.365913908090325385922863720169110028713674608764738945404222708302431250482685379562787353522836801875908603986543211508543060240047810789735296217740906133048740758429337428485880786201852497535514741138734414305805414144417506648379042156447807867430451159426697943573941496513190814177886918941773671952653803294758151434434681086485076904776522212468222182241366009190935348257905748517715365e11")),
           mp_complex(mp_float("-2.1705052417331367741245606850494477302525500254665024082468865650564576831368937045655178856030674111751030720452000155393913703733131463121969637965701752953370012143664955007785788811476834971808899771667678930682536637204047969625582976626742473192735877822418844366029937737792096361581163446900815678252576532608497414485375933458250413331652670321838466303388624977301972976287585286832593993748e12"), mp_float("8.130034028059944747277016075879961245994156037174195347084017120850273567906434337998426767865912711430347988241809968866568240321833925687812996907126131445910670394244231994239476396478289705377874543537709644124249240290651114360661529567395659383039274356814429557225481067695747712403535088824464971371448005753740526952877057617973129312667471248729542273774557470997124134851203014791165668463e11")),
           mp_complex(mp_float("-5.716644492161516539227712160569961088171327023451054239128900854012219957598265227097719803022614926291967266351212109939239881352046668848069367916026069362047168513234482084777192093631969762623211272659358339730895077980649235560808282659038655224553229986048078756642794187261934856268247819478888701515443750226635069654831173566165842292938615818093633112551881752607432213183423717911895355025e12"), mp_float("1.9885500889961772806958333760295392854856139934956210242641713285121215416608075370056255973654898281627777623736453750850316185508283639954486647850168569469502682375670928414664141901731117199715920482647846345372446439094055312881664357671060308582940281278418220555728792675120884610944949256496583488087968291897954859391722373953970167580046908105720627060400162581522146984425446658627871898514e13")),
           mp_complex(mp_float("1.2292899393314644862239723281590389374173402769751655846711617052120071419284294830673664970194673966962712718349875284408019545982960015865327244396089390059490543489697497247308383511615103775272891812180033539628455218953538873455026714900510247857358205652636786987031509587735836251092678637025377762248445288218684320748992806288202754606903070353475120954330324563128394342081457526058719452799e14"), mp_float("1.4744393147228402493374194890998403749223482332311353613256234433670490963040441048623015346530308426495922654654920936226822078178023266161777563084255685941318451992751953132746377985385090603198932138511272234632447182123645763999892101402498580203887837508788130277743628283031807328304698425718534852579764928417591424208175066371750558817379620556022816141302567980922901749201541738760743174194e14")),
           mp_complex(mp_float("1.8300891067810951572054484388282920849197178386122823145750707909164100679106254526360705941023063398160116241527040212674590206442229446145533544861402477451742353245624471821842129514566496958926248759352972005936924256029376839924786896165163094227975479415559177620098420758627818455165148531233292395651517832244325079177284841672916138471458878737677331766480526135244418177912687511915120873705e15"), mp_float("-2.574978372878736825731796657082972791470484680507750284569253770750792818503303519111554687969761464149180843965703776280656102765507815228887653610674518962883870296260726414435146559110378245562044283435699080914874882773516507680122294607075683672331572586094474233729199582826651687232625564576222539989528127213422951344986419180197048042295566365797657515407390836963030782272009298551881709985e14")),
        }};
        static const std::vector<mp_complex> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_02903_z_zeta_neg_x(const bool b_write_output)
    {
      return TestCase_case_02903_z_zeta_neg_x().execute(b_write_output);
    }
  }
}
