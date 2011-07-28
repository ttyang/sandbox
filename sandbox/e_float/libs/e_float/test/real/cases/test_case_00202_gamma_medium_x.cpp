
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// Automatically generated file
#include <e_float/e_float_functions.hpp>
#include "../test_case_real.h"

namespace test
{
  namespace real
  {
    class TestCase_case_00202_gamma_medium_x : public TestCaseReal
    {
    public:
      TestCase_case_00202_gamma_medium_x() { }
      virtual ~TestCase_case_00202_gamma_medium_x() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00202_gamma_medium_x");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.resize(51u);
        for(INT32 k = static_cast<INT32>(0); k < static_cast<INT32>(data.size()); k++)
        {
          data[static_cast<std::size_t>(k)] = ef::gamma(ef::third() + k);
        }
      }
      virtual const std::vector<e_float>& control_data(void) const
      {
        static const std::tr1::array<e_float, 51u> a =
        {{
           e_float("2.6789385347077476336556929409746776441286893779573011009504283275904176101677438195409828890411887894191590492000722633357190845695044722599777133677084697681672898230500032183425503222471569418175554499527287843947794413057658284016123191415964665260337275840205806355139432410320158394153827008552405210323387989550693638926386839167072816915423096273318811864774965222910556444090780096341646353274"),
           e_float("0.89297951156924921121856431365822588137622979265243370031680944253013920338924793984699429634706292980638634973335742111190636152316815741999257112256948992272242994101666773944751677408238564727251848331757626146492648043525527613387077304719882217534457586134019354517131441367733861313846090028508017367744626631835645463087956130556909389718076987577729372882583217409701854813635933654472154510913"),
           e_float("1.1906393487589989482914190848776345085016397235365782670890792567068522711856639197959923951294172397418484663111432281492084820308908765599900948300926532302965732546888903192633556987765141963633579777567683486199019739136737015118276973962650962337927678151202580602284192182364514841846145337134402315699283550911419395078394150740921251962410265010363916384344428987960247308484791153929620601455"),
           e_float("2.7781584804376642126799778647144805198371593549186826232078515989826552994332158128573155886353068927309797547260008656814864580720787119733102212702161908706920042609407440782811632971451997915145019480991261467797712724652386368609312939246185578788497915686139354738663115092183867964307672453313605403298328285459978588516253018395482921245623951690849138230137000971907243719797846025835781403395"),
           e_float("9.2605282681255473755999262157149350661238645163956087440261719966088509981107193761910519621176896424365991824200028856049548602402623732443674042340539695689733475364691469276038776571506659717150064936637538225992375748841287895364376464153951929294993052287131182462210383640612893214358908177712018010994427618199928628387510061318276404152079838969497127433790003239690812399326153419452604677984"),
           e_float("40.12895582854403862759968026809805195320341290438097122411341198530502099181311729682789183584332178389192979048667917095480439437447028405892541834756720146555117265803297001961680318098621921076502813920959989793002949116455808799122980113337916936116365599109017906695783291093225372622219354367520780476425196788663573896792102657125310846590126355344875522130900140386601870637466648176279536046"),
           e_float("214.02109775223487268053162809652294375041820215669851319527153058829344528966995891641542312449771618075695888259562224509229010333050818164760223118702507448293958750950917343795628363192650245741348340911786612229349061954430980261989227271135556992620616528581428835710844219163868653985169889960110829207601049539539060782891214171334991181814007228506002784698134082061876643399822123606824192245"),
           e_float("1355.4669524308208603100336446113119770859819469924239169033863603925251535012430731372976797884855358114607395897722742189178373210932184837681474641844921383919507208935580984403897963355345155636187282577464854411921072571139620832593177271719186095326390468101571595950201338803783480857274263641403525164813998041708071829164435641845494415148871244720468430308818251972521874153220678284321988422"),
           e_float("9940.0909844926863089402467271496211652972009446111087239581666428785177923424492030068496517822272626173787569916633442720641403546836022142997480706862756815409719532194260552295251731272531141332040072234742265687421198855023886105683299992607364699060196766078191703634809817894412192953344600036959184541969318972525860080539194706866959044425055794616768488931333847798493743790284974085027915095"),
           e_float("82834.091537439052574502056059580176377476674538425906032984722023987648269520410025057080431518560521811489641597194535600534502955696685119164567255718964012841432943495217126912709776060442617776700060195618554739517665712519905088069416660506137249216830638398493086362341514912010160794453833364132653784974432477104883400449328922389132537020879828847307074109444873165411453158570811737523262579"),
           e_float("773118.18768276449069535252322274831285644896235864178964119073889055138384885716023386608402750656487024056998824048233227165536091983572777886929438671033078652004080595535985118529124323079776591586722849243984423549821331685244748864788883139061432602375262505260213938185413917876150074823577806523810199309470311964557840419373660896523701219487840257486602502148548287717356281332757621688378407"),
           e_float("7.988887939388566403851976073301732566183305944372631826292304301869030966438190655749949534950901170325819223211818317433473772062838302520381649375329340084794040421661538718462248009513384910247797294694421878390433481537607475290716028184591036348035578777125543555440279159438180535507731769706674127053928645265569670976843335278292640782459347076826606948925222016656397460149071051620907799102e6"),
           e_float("9.0540729979737085910322395497419635750077467369556494031312782087849017619632827431832761396110213263692617863067274264246036083378834095230992026253732520960999124778830772142572144107818362316141702673203447955091579457426218053294781652758698411944403226140756160294989830473632712735754293390008973439944524646343122937737557799820649928867872600204034878754485849522105837881689471918370288389823e7"),
           e_float("1.1166690030834240595606428778015088409176220975578634263861909790834712173088048716592707238853592969188756203111630492590344450283389538411822349904627010918523225389389128564250564439964264685657476663028425247794628133082566893239689737173572804139809731224026593103048745758414701237409696184767773390926491373048985162320965461977880157893704287358497635046386588107726386672075034869932335568078e9"),
           e_float("1.4888920041112320794141905037353451212234961300771512351815879721112949564117398288790276318471457292251674937482173990120459267044519384549096466539502681224697633852518838085667419253285686247543302217371233663726170844110089190986252982898097072186412974965368790804064994344552934983212928246357031187901988497398646883094620615970506877191605716477996846728515450810301848896100046493243114090771e10"),
           e_float("2.1340785392260993138270063886873280070870111197772501037602760933595227708568270880599396056475755452227400743724449385839324949430477784520371602039953843088733275188610334589456634263042816954812066511565434918007511543224461173746962608820605803467191930783695266819159825227192540142605197153111744702659516846271393865768956216224393190641301526951795480310872146161432650084410066640315130196772e11"),
           e_float("3.272253760146685614534743129320569610866750383658450159099090009817934915313801535025240728659615836008201447371082239162029825579339926959790312312792922606939102195586917970383350586999898599737850198440033354094485103294417379974534266685826223198302762720166607578937839868169522821866130230143800854407792583094947059417906619821073622564999567465941973647667062411419673012942876884848319963505e12"),
           e_float("5.3446811415729198370734137778902636977490256266421352598618470160359603616792091738745598568107058654800623640394343239646487151129218807009908434442284402580005335861252993516261392920998343795718219907853878116876590020475483872917393022535161645572278457762721257122651384513435539423813460425682080621993945523884135303825808123744202501894992935277052236245228686053187992544733655785855892737248e13"),
           e_float("9.2641139787263943842605838816764570760983110861797011170938681611289979602439625680492370851385568334987747643350194948720577728623979265483841286366626297805342582159505188761519747729730462579244914506946722069252756035490838713056814572394280185658615993455383512345929066489954935001276664737848939744789505574732501193298067414489951003284654421146890542825063055825525853744205003362150214077897e14"),
           e_float("1.6984208960998389704477737116406837972846903657996118714672091628736496260447264708090267989420687528081087067947535740598772583581062865338704235833881487930979473395909284606278620417117251472861567659606899046029671939839987097393749338272284700704079598800153643930086995523158404750234055201938972286544742688700958552104645692656491017268853310543596599517928226901346406519770917283060872580948e16"),
           e_float("3.2836137324596886761990291758386553414170680405459162848366043815557226103531378435641184779546662554290101664698569098490960328256721539654828189278837543333226981898757950238805332806426686180865697475240004822324032417023975054961248720659750421361220557680297044931501524678106249183785840057082013087319835864821853200735648339135882633386449733717620092401327905342603052604890440080584353656499e17"),
           e_float("6.6766812560013669749380259908719325275480383491100297791677622424966359743847136152470409051744880527056540051553757166931619334122000463964817318200303004777561529860807832152237510039734261901093584866321343138725532581282082611754539065341492523434481800616603991360719766845482706673697874782733426610883666258471101508162484956242961354552447791892494187882700074196626206963277228163854852434881e18"),
           e_float("1.4243586679469582879867788780526789392102481811434730195557892783992823412020722379193687264372241179105395210998134862278745457946026765645827694549397974352546459703639004192477335475143309205566631438148553202928113617340177623840968333939518404999356117464875518156953550260369644090388879953649797676988515468473834988407996790665165088971188862270398760081642682495280257485499142008289035186108e20"),
           e_float("3.1810676917482068431704728276509829642362209378870897436745960550917305620179613313532568223764671966668715971229167859089198189412793109942348517826988809387353760004793776029866049227820057225765476878531768819872787078726396693244829279131591104498561995671555323883862928914825538468535165229817881478607684546258231474111192832485535365368988459070557230849001990906125908384281417151845511915641e21"),
           e_float("7.4224912807458159673977699311856269165511821884032094019073907952140379780419097731575992522117567922227003932868058337874795775296517256532146541596307221903825440011185477403020781531580133526786112716574127246369836517028258950904601651307045910496644656566962422395680167467926256426582052202908390116751263941269206772926116609132915852527639737831300205314337978780960452896656640020972861136496e22"),
           e_float("1.8061395449814818854001240165885025496941209991781142877974650935020825746568647114683491513715274861075237623664560862216200305322152532422822325121768090663264190402721799501401723506017832491517954094366370963283326885810209678053453068484714504887516866431294189449615507417195389063801632702707708261742807559042173648078688374889009524115059002872283049959822241503367043538186449071770062876547e24"),
           e_float("4.5755535139530874430136475086908731258917731979178895290869115702052758557973906023864845168078696314723935313283554184281040773482786415471149890308479163013602615686895225403551032881911842311845483705728139773651094777385864517735414440161276745715042728292611946605692618790228318961630802846859527596415112482906839908466010549718824127758149473943117059898216345141863176963405670981817492620587e25"),
           e_float("1.2048957586743130266602605106219299231515002754517109093262200468207226420266461919617742560927390029543969632498002601860674070350467089407402804447899512926915355464215742689601771992236785142119310709175076807061454958044944323003659135909136209704961251783721145939499056281426790659896111416339675600389312953832134509229382778092623686976312694805020825773196970887357303267030160025211939723421e27"),
           e_float("3.2933817403764556062047120623666084566141007529013431521583347946433085548728329246955162999868199414086850328827873778419175792291276711046900998824258668666901971602189696684911510112113879388459449271745209939301310218656181149543334971484972306526894088208837798901297420502566561137049371204661779974397455407141167658560312926786504744401921365800390257113405053758776628929882437402245968577351e28"),
           e_float("9.3312482643999575509133508433720572937399521332204722644486152514893742388063599533039628499626565006579409265012309038854331411491950681299552830002066227889555586206204140607249278650989324933968439603278094828020378952859179923706115752540754868492866583258373763553676024757271923221639885079875043260792790320233308365920886625895096775805443869767772395154647652316533781968000239306363577635828e29"),
           e_float("2.7371661575573208816012495807224701394970526257446718642382604737702164433831989196358291026557125735263293384403610651397270547370972199847868830133939426847602971953819881244793121737623535313964075616961574482885977826172026110953793954078621428091240864422456303975744967262133097478347699623430012689832551827268437120670126743595895054236263535131879902578696644679516576043946736863199982773176e31"),
           e_float("8.3027373445905400075237903948581594231410596314255046548560567704363232115957033895620149447223281396965323266024285642571720660358615672871868784739616261437729014926586973109205802604124723785691029371450109264754132739388479203226508327371818331876763955414784122059759734028470395684321355524404371825825407209380925932699384455574214997849999389900035704488713155527866947333305101818373281078635e32"),
           e_float("2.6015243679717025356907876570555566192508653511799914585215644547367146062999870620627646826796628171049134623354276168005805806912366244166518885885079761917155091343663918240884484815959080119516522536387700902956294925008390150344305942576503077321386039363299024912058049995587390647754024730980036505425294258939356792245807129413254032659666475502011187406463455398731643497768931903090294737972e34"),
           e_float("8.411595456441838198733546757812966402244464635481972382553058403648710560369958167336272473997576441972553528217882627655210544234998418947174439769509123019880146201118000231219316757160102571977008953432023291955868692419379481944658921433069328333914819394133351388232102831906589642773801329683545136754178477057058696159477638510285470559958827078983617261423183912256564730945287981999195298611e35"),
           e_float("2.803865152147279399577848919270988800748154878493990794184352801216236853456652722445424157999192147324184509405960875885070181411666139649058146589836374339960048733706000077073105585720034190659002984477341097318622897473126493981552973811023109444638273131377783796077367610635529880924600443227848378918059492352352898719825879503428490186652942359661205753807727970752188243648429327333065099537e37"),
           e_float("9.6266036890389926052172812894970615492353317494960350600329446175090798635345076803959562757972263724797001489604656738720742895133870794617663032917715519005295006523906002646176625109721173879292435800388711007939386146577342960033318767511793424265914044177303910331989621298486525911744615217489461009520042570764116189380688529617711496408417687681701397547398660329158463031929406905101901750771e38"),
           e_float("3.4013999701271107205101060556222950807298172181552657212116404315198748851155260470732378841150199849428273859660312047681329156280634347431574271630926150048537568971780120934982407538768148104016660649470677889471916438457327845878439297854167009907289628942647381650636332858798572488816430710179609556697081708336654386914509947131591395397640916314201160466747526649635990271281723773136005285272e40"),
           e_float("1.2358419891461835617853385335427672126651669225964132120402293567855545415919744637699430978951239278625606169009913377324216260115297146233471985359236501184301983393080110606376941405752427144459386702641012966508129639306162450669166278220347346932981898515828548666397867605363481337603303158031924805599939687362317760578938614124478206994476199594159754969584934682701076465232359637572748586982e42"),
           e_float("4.6138100928124186306652638585596642606166231776932759916168562653327369552767046647411208988084626640202263030970343275343740704430442679271628745341149604421394071334165746263807247914809061339315043689859781741630350653409673149164887438689296761883132421125759915021218705726690330327052331789985852607573108166152652972828037492731385306112711145151529751886450422815417352136867475980271594724734e43"),
           e_float("1.7686272022447604750883511457812046332363722181157557967864615683775491661894034548174296778765773545410867495205298255548433936698336360387457685714107348361534394011430202734459445034010140180070766747779583000958301083807041373846540184830897092055200761431541300758133837195231293292036727186161243499569691463691850306250747705547031034009872605641419738223139328745909984985799199125770777977815e45"),
           e_float("6.9566003288293912020141811734060715573963973912553061340267488356183600536783202556152233996478709278616078814474173138490506817680123017524000230475488903555368616444958797422207150467106551374945015874599693137102650929641029403796391393668195228750456328297395782981993092967909753615344460265567557764974119757187944537919607641818322067105498915522917637011014693067245940944143516561365060046071e46"),
           e_float("2.8058287992945211181457197399404488614832136144729734740574553636994052216502558364314734378579746075708485121837916499191171083130982950401346759625113857767332008632800048293623550688399642387894489736088542898631402541621881859531211195446172075596017385746616299136070547497056933958188932307112248298539561635399137630294241748866723233732551229260910113594442592870455862847471218346417240885249e48"),
           e_float("1.1597425703750687288335641591753855294130616273154957026104148836624208249487724123916756876479628377959507183693005486332350714360806286165889993978380394543830563568224019961364400951205185520329722424249931064767646383870377835272900627451084457913020519441934736976242492965450199369384758686939729296729685475964976887188286589531578936609454508094509513619036271719788423310288103583185792899236e50"),
           e_float("4.9095768812544576187287549405091320745152942223022651410507563408375814922831365457914270777097093466695247077633723225473618024127413278102267641175143670235549385772148351169775964026768618702729158262658041507516369691717932835988612656209590871831786865637523719866093220220405843997062145108044854022822335181585068822430413229017017498313357417600090274320586883613770992013552971835486523273433e51"),
           e_float("2.1274833152102649681157938075539572322899608296643148944553277476962853133226925031762850670075407168901273733641280064371901143788545753844315977842562257102071400501264285506902917744933068104515968580485151319923760199744437562261732151024156044460440975109593611941973728762175865732060262880152770076556345245353529823053179065907374249269121547626705785538920982899300763205872954462044160085154e53"),
           e_float("9.4318426974321746919800192134892103964854930115117960320852863481201982223972700974148637970667638448795646885809674952048761737462552842043134168435359339819183208888938332413936268669203268596687460706817504184995336885533673192693679202873758463774621656319198346276083530845646338078800498768677280672733130587733982215535760525522692505093105527811728982555883024186900050212703431448395776377517e54"),
           e_float("4.2757686895025858603642753767817753797400901652186808678786631444811565274867624441614049213369329430120693254900385978262105320983023955059554156357362900718029721362985377360984441796705481763831648853757268563864552721441931847354467905302770503577828484198036583645157867316693006595722892775133700571639019199772738604376211438236953935642207839274650472092000304298061356096425555589939418624474e56"),
           e_float("1.9811061594695314486354475912422225926129084432179888021171139236096025244021999324614509468861122635955921208103845503261442132055467765844260092445578143999353770898183224843922791365806873217241997302240867767923909427601428422607570129456950333324393864345090283755589811856734426389351606985811947931526078895894702220027644633049788656847556298863921385402626807658101761658010507423338597296006e58"),
           e_float("9.3772358214891155235411185985465202717010999645651469966876725717521186155037463469842011485942647143524693718358202048770826091729214091662831104242403214930274515584733930927901212464819199894945453897273440768173171290646761200342498612762898244402130957900094009776458442788542951576264273066176553542556773440568257174797517929768999642411766481289227890905766889581681671847916401803802693867764e59"),
           e_float("4.5323306470530725030448739892974847979888649828731543817323750763468573308268107343756972218205612786036935297206464323572565944335786810970368367050494887216299349199288066615152252691329279949223636050348829704617032790479267913498874329502067484794363296318378771391954914014462426595194398648652000878902440496274657634485466999388349827165687132623126813937787329964479474726492927538504635369419e61"),
           e_float("2.2359497858795157681688045013867591670078400582174228283213050376644496165412266289586772960981435641111554746621855732962465865872321493412048394411577477693374345604982112863475111327722444774950327118172089320944402843303105503992778002554353292498552559517066860553364424247134797120295903333334987100258537311495497766346163719698252581401738985427409228209308416115809874198403177585662286782247e63"),
        }};
        static const std::vector<e_float> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_00202_gamma_medium_x(const bool b_write_output)
    {
      return TestCase_case_00202_gamma_medium_x().execute(b_write_output);
    }
  }
}
