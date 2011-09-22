
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
#include "../test_case_real.h"

using boost::multiprecision::mp_float;

namespace test
{
  namespace real
  {
    class TestCase_case_00052_factorial2 : public TestCaseReal
    {
    public:
      TestCase_case_00052_factorial2() { }
      virtual ~TestCase_case_00052_factorial2() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00052_factorial2");
        return str;
      }
      virtual void mp_float_test(std::vector<mp_float>& data) const
      {
        data.resize(101u);
        for(boost::uint32_t k = static_cast<boost::uint32_t>(0u); k < static_cast<boost::uint32_t>(data.size()); k++)
        {
          data[static_cast<std::size_t>(k)] = boost::multiprecision::factorial2(10u * k);
        }
      }
      virtual const std::vector<mp_float>& control_data(void) const
      {
        static const boost::array<mp_float, 101u> a =
        {{
           mp_float("1."),
           mp_float("3840."),
           mp_float("3.7158912e9"),
           mp_float("4.2849873690624e16"),
           mp_float("2.55108265612582846464e24"),
           mp_float("5.20469842636666622693081088e32"),
           mp_float("2.8481308951595832473664081994186752e41"),
           mp_float("3.550442606428591982434759014119744131301376e50"),
           mp_float("8.97108341211212142020325469195355364998152634499072e59"),
           mp_float("4.20883272902349824802282556768760899347754738396013455736832e69"),
           mp_float("3.4243224702511976248246432895208185975118675053719198827915654463488e79"),
           mp_float("4.5743613929984741762045187511667452512380089785043681472178696974230263693312e89"),
           mp_float("9.5934449818359869548919399476693221851824899426083898963640941952942953954888118173696e99"),
           mp_float("3.04284599363048780608774948110621935176406885710355437072508257054391066901708636919869506322432e110"),
           mp_float("1.414180134172942262166117780415538238776503682860351411148039596894039236167545442519845445066297475858432e121"),
           mp_float("9.37262840292216497287959227832043642481541116118647828814887544508301255129002449990627658603115673287280486776832e131"),
           mp_float("8.652216451902846439782334634661110199534538804281658253980860521541225333550579569336533284938792359299966271463486608375808e142"),
           mp_float("1.08981436813352025539677334714313675052379737603508922626359109403633933688047362343722870502522486348690413473089089611741980864282624e154"),
           mp_float("1.839227279437468473133871545683868854121709232271215890264494219553905123411285218945555668522747684568935589411687623893426277320407809248985088e165"),
           mp_float("4.0921260721752941329733404353122139392926894880596146218101187463726033149648223760409905220198386233589409021984288868196576971334025379663051349240578048e176"),
           mp_float("1.18305033024544857808171402556304773068330423943453950860219552506842483018552459750131300382609551649116952455583587373444882662176634718152559553931916976653860864e188"),
           mp_float("4.386666398938131965159107088472130659978772944934571891064981385686385758917934911370883948709692981635493731326376001450475948257526635964482205599156893421080469794031927296e199"),
           mp_float("2.06166058395762107540226850068131606806143939234418346559690728715197094801826992729453155699692515907233072767421787223730416229746662245593439392715929895397565023705572133766701252608e211"),
           mp_float("1.2150363836515057071220136445938064602748500938461925190595987883976232641654488399311542969561492016334409221074276785039523253777229083127313043993152068576125904032458200535035150944147504889856e223"),
           mp_float("8.89187455044133871186058575184867524496443242680660211990888993250354565047351996110739258699566577266478374102930493538011559785055304265370263175797756452128218252436294036696092865591308485032612143824896e234"),
           mp_float("8.00802307374742648627015986673114910308779136016753884262374978446612673315683452243123403015798494644581841299023116361660590391530546386701668491668724337371292762453078643332728757576447518385985059859467144790016e246"),
           mp_float("8.8022275696304249384155496308868386409735526083886040740068808406455177991424897814062328158673388324677459530674606824441257865239432454555894441429304395045986593661199457417926721517748843390195374981283803471091036265119744e258"),
           mp_float("1.1718661388574355636901295352841144495922563477769221975429814095453928498321145227583527808464754054922588603497411654233551797289064922873850309693299242117028216228079729678993241260507667617207176546609906359951676325888279302260129792e271"),
           mp_float("1.876330688002605836313724761861639980108791882606679002803569457121071243255061798419473601315528592857960251974687064463685002421241826889871720361304334035709379060648742238092295942637682627606000225592223826716598569104296876138892779034807107584e283"),
           mp_float("3.58949496768596024382099251974029553487236095579684159539719292074304945808496030930240840890591043032453180927918805385296851313909317194681313123767864919244377159427797293360774717975961607996005883089102470714453024583238758132074702216331332570120322023424e295"),
           mp_float("8.154414069380594345561496918943236213655122384461722221090152424297122617707057644283318120118997290588054763925204215174621905774628792434674458283281763811619370426193907004908279960748304380260556300122477350953389981838135813430968491267431020995449329126424285544448e307"),
           mp_float("2.187293809968881627384128233798893407469440354663445490635348014084864622150220207599951920842416459219273016884441593284129365591260793732317192881349202688596446338615218387017078124069112769340027084606730825606354299222319053784471423278794218111118947822511426185455534176468992e320"),
           mp_float("6.89057631356510555137579289567606342691071383657846047213943697478963467095201598821910630333509037351988775564977512588904257492490468067445263641186415296635901338167599420250217089644600952463561241085007988115057837369551578777905737683802570528878279595352144965156246099611685573095325696e332"),
           mp_float("2.53665738217211690225590366310652713149867659304170425391407901615500985727113050305934787818138974257221716969186149252682143636293274873787420381062611072630976227160296783821255579549024870342062993632493952848142694591947180566812584700471133422523434177392975502688641022593337925423630093963820531712e345"),
           mp_float("1.08612861998730268219054445789374605918612506951800937660269028862636512609865876263014647200828357135383929219835057149957722537886500414556958714677179787471956188290317904989044415663405563852821137352155310277769683274558398713267680464772806931885524570064834083687668064343189904708396586945459717817083858255872e358"),
           mp_float("5.385043221930653021437114957357694402301225427286612120566624309455711108422640671320205988052307917222788862104098178562364686207197843313256899351641434737755217690733205242408884680973848652330166259493445229718202353224383658554093590904072675986645926321890706409824981133251528863074288052294816937623729171904160195411968e370"),
           mp_float("3.078723199574382302913639852752927378498754127563348334653447754356801402202704925481654228092463647361449405590501253883391239190911882680879338522121477503287678219516829180880416254122007288240136458464186574752089426411849701820260185163873516546935356022573256102233854470971402143752077498219536899770427471124798464673940631696965632e383"),
           mp_float("2.021674469234584295774211352123969964325422135096113002867159495587286972380684974106093454369008100893511226169722197452929568436586750360292378457939347493554479198942104705081310033467371510413364169973134893462855092858722618246447845776128856806001758735606189081985803213188356790820355168443598166819019571453883207550701876080528054211057811456e396"),
           mp_float("1.519109256598694015300093913738966477652925506956742120596193245502852521029727551285498780385620544904235922461933596909990966730043176443657658881457405009954440868659092294818088501977760221576733546314247861148680011029243536912928420302209270229238733999147669971875665600996776421227478190705221189947112158484539431446161571862522865076847778946382091517952e409"),
           mp_float("1.301569115024481105528212583795852097217851249329108011006277151314369093686018440109569616185015033929908693281683693808952571960439156180356558475900862213507597996873570249780766721009585521908859960971487779755600910043820708012769916474176025370004257067128174089642484634114614838126747833232336053166605247506941100175005579905997371555011896268769652770239440226353152e422"),
           mp_float("1.26732433097264260462535288034449499730349890908495463728859664600884456127221109956015403583833011898303014476136281195802304311664272311793434421005325835816257129001333309905897387290571175770046270837443254819717144490623374592975680993991978151545304674525459352916310902330576965589018176066770671712205237344199107875957641178452432566657053835816254238629519900909951190640361472e435"),
           mp_float("1.39786504294426068404236833599182023886467515962158085093784886145878534971552152565159527136876101959434179877012779707214283981906557297541127938679434107629327221014982726436413582590989433610145447486811751849398520051820978528364566887560003670775806738642044108273913442487100798999040115965303506076331524765588099961827097368810380958643359329341009664920490786105545996560495825250752135168e448"),
           mp_float("1.7413324946310412366962408957311764602801711622042531550675119336366712182910744450287273833340413972385533438207589799933771374391239931637132288066948457772267323617440082734334373048295809780101840980610482324367953069736068876526434193182285904984464222991719602066597391062954023512151817448253208625056923701872431722539816400586155284218295814300980343170214560621833568738812198485473595487322e461"),
           mp_float("2.4427658259054710314391718862115445671564172922617535826658581497086869139316669115510882550561734356501320123795415088538073925884099719226638188103492837901025618542693884945342451548150987283454890413821901251590210186743118622877236716439926253756802415875372366965321253329150705821523209235508240514066950189233852209452915531208752111003392309904447126571567230134770450529843681168434408145135e474"),
           mp_float("3.8482970532174674129942351279097490315147436704200376616691860391115977871026240928567258640242717138891518078872403627806980385455456222294763580467704482364233594199504675321444709760742539778054730760975987236100277063622447631867218494002485681112444728442724328018553913650842486970877951413465096522653152187717791423829684101892921503426475734167765010115450330277284247050147800346012414699621e487"),
           mp_float("6.7904602949135314456399977698957910912529756077005303682444143180277727133504405084960170964565008529872091461473859559672603752726804143515885388383108254056781690321811369342311680514830087132456580984727576553699392368659712362919402078086103251164653785948347299444554644159980086813198060083261613368411779521414145698718740802068310175848424735865245753414059684961271854258050208117025490568471e500"),
           mp_float("1.3386950396594313125264134982479697129928632852702583296878451176400698449453877290436165587104316176136367371736036651963426768060138948762201067980540591526266512450476913614647193486094591566032274294654973823006108739492764260303168706409174589994032692531507021947040634895158627769085495346480818207029441089101122722211556654904448035106114906352610699237605733364041305780250273468736205013493e514"),
           mp_float("2.9415161555620015519016757381827086764321698367122272673941869365888077925858248765623565917820337400386314463738085952588863762547278138382417947794259942567573977512249082733445481403359994288533923904059459179274553225841229503309761672944118620689005268732921129924848050993482672285035618582400035461801081090994326952487928760624078146707112301870286935852463311681229338496084778979121659324229e527"),
           mp_float("7.1873313146147551940355565416086183081949626434161471173855828096288690700520019916594985196615434103128140554650673127888687402552727167800570265689253747133130382990686370039106857507098923122795622379330335106541553136548277202798792404110958746542960917864728023976803370587142801384365923493585819955332152678531006397735207876039206289870393047090886157968352470291786985174211907273834818733141e540"),
           mp_float("1.9485530593309098032301617543882193333331597346427866167604511767907120446394647347178490355072487572636125422317845806605500852063283015216232957879669906445496562621047477649461134352505631839749750264320075200695766570986852829781966740755083807042592202754778553047114510543954975876117063338658444372917269755743579648861264494997832928290168700403226823125063093794484345178838348121444963217891e554"),
           mp_float("5.8490496977281839319015739666363991858932901018633052041360197572204145672577381298696790704262303663676524519801978580022635614498055517710209011137393136263367055635637057883605036300944034886758546681615347607881954200152793776217295176207926689449639813914899266715393729384810011730311170527632214914202817276617312085449541343351073318124123217919621131789381895167866839151225650523762487821415e567"),
           mp_float("1.9400100076534080650357021527344993527662013978601915112104339595653647304095141877184271701697977748489766582940256370052384220867949682480465549797398536898598896655219436009877948469131796129872127041483709140490931541044681671933971211086911417637449226270357721203452492708790759609115905463884596140594561304930934650719446845127220956458958475554718245547544952582293896130346148971169604540349e581"),
           mp_float("7.096102094629453310600580592178504914084897257355765826168228870421587485221411964678946710482994530050240369596966769597413192330848181672235833792864021666273925944013356080082037530248887381833553228017971300127607810724057363442020949814281660100843833217804264443322334158644433254914041576860244296872839512073756855148023749576768817384823600234498580938572859166683884341901180624320177514189e594"),
           mp_float("2.857045662548261538876584749942714035702772863505608034403751101160341948079212613476892733892258681255379793366506245332472834153591989509200815628219458002564626904688243959529690411167045331994483941109127193100482640959281632844701409688274218221530395835992443629431783559150684141030551398325630829953245458381811517750787841305041819680251239696277960206535454952784891188035839012647754429769e608"),
           mp_float("1.2638947097264580583258733242339872759851128474264166371033797403809429801722192461240382798289360396642745847311795044644951066473106128171459400582584893073726047355753581310355889593875894762802898226470006742149195505696574097195144453675673863891369891960333612191397011224038584834092162304930802480242229152525922742296906518226620805808081017883710108279065520910958007676864286628439793546004e622"),
           mp_float("6.1326047202611541747957871206270671946133349952651149411004640175051879885793810807672290191504127485464756211735362922227039228167142066749343083182970897096043864432638090502828870398217960794561359535326491404954973928443831971498509581432745919232560200469237718062953391257805737992699462476436773245361912177577891693907035604673534645254622436661486485654052007637135241055917887516699272343222e635"),
           mp_float("3.2582982332763965739702477251284170999752127600531561417544243164729615999249929976376788853133731359348273275516327226097671472156202347828705691576970692224660056244639229620862925570866389101644546611313397561643130192564662918988707729108438861659071026312005323301107847049315338856321925427658407555218250842028206459411707676147928068081847523922839659332960325160523844499606681349292672152885e649"),
           mp_float("1.8925435197639935781028598629125595155639597369149474536295017031168685153810683907575195411415800337263766351461648872020233323127237264762405559826521225024510269841657131825553404050966557816712928632402028085375414615777489975680467943153288754176917335652605483954622407814255962874642402932108975451671814253030908382425201122498472514148067650413138814834644734617356232612227555612230603787162e663"),
           mp_float("1.1998642443294008411847181979372491590037727456266007533779516722346053178161022436183881741966781138486770100432390072872069843740523787255746017465589717038305795295281137304148302368123943052882380731514451392544274673521435573933277667025783726306555872205763398975233945460212104397721190751364991436266167225003124844015506695073926152738962441279578536506345427826839684946344800294350009009412e677"),
           mp_float("8.2907705708682772257778281791824345160986208704655566020181563948642970028242635790470164767859209264077055632398728993877815274819221051001824421344557232903490356224472888547922178319586890784310798280472190154180572151500291485594334493565622495388091085662701502382727792699778788145690087530971801002084147138639619762955828251206264086202761034144880893800544736396767343460312622236284475412843e690"),
           mp_float("6.2345016321232105370670587090887752473893055019399473860725935942900254636762527319719146214736204952389175952858139508642745254955708065568046191622328105551570130034062878965425060872466835783729383396367906043651180775066492868673725405841937300254726536538242373322070194462865479277722979771694166321835228474897349370808180099787435916335507451718021736275597258715043120490087566901918828286446e704"),
           mp_float("5.0949650743969021775696755888884802440938590217122467643028147038867470828734820670698121689425027626118845812486195904986046075341380710511860555017947600259602914729832289332756140679064038836865191330350078161231864530315785809762848052791249272269640982579242902084546622740015944915550139250735928030272955545568992339615243317924179653131861657416030731315087299958988436140007289898727700897925e718"),
           mp_float("4.5187871109357631034044740238707892632715031946342122752825439187783644902870317191467574425200485962207203064574485888962886151434527961027062544298647844482218820111108422706250804789505079766030780697229974668013951723465309034809493977298592784668413161691783426413072142558810584744860454977009687936574878328169820329031734479395259643281362926410745610302466610824769864067309431286842573931392e732"),
           mp_float("4.3438156144087506038810473426724151587388756216743183779442725800912344299810043753256095219064036974597801045437306880463950684462152003703717432722134002889177863185076918105391096048292435638084904598087642646846025282624371780838567431116544351354427439434326640948609941482051549205239286604768442209725642828814632522025902668560228203196634015074670621044785123635438968885212913426715302450107e746"),
           mp_float("4.5199693163291675138290331095774820738157098795999855530787125909095909463180533215296342379392810849524191558462785912601406328422223299709288543403543135387855311300523951222134502902407683806811407355226706747508842766892440477798357995458169755816865721710510590849638369014563303060229997278670326759220917456235927636964418593668236272230619803928034603908156781270492579281410179537086937287956e760"),
           mp_float("5.0848396562063902625916793625101633374471338414309475430973178938992255185062034941262282232024740488825120630190028677639888934175928133218155060810321877005691693249309695544207073791095560497155230426850548338077457508353436798143782271188548976511563705901528835480428345969887719560751554573713952629787691018938846954124433210326306892357546114451324603517677947199272907229328735406224300073185e774"),
           mp_float("6.176981137595130719721448291018070234599616406467595021860079467634542521082762394617455007231442902725780724368577877492757393948049867482510435480516948046781165415579062866242837994966201126136809637248825103965415516669724847367234769103446501683182931331561621129693903929059986388113983617781941152823547330225702564952374779958761363318846898760196229863431305602010013202221149357038762865734e788"),
           mp_float("8.0933409855296608683640092010907253875400259801280252571328977220209654627517226646782000718185374494048321030584505361336585395780643848712239026573022575661167029082860860528726118774845869967100629464779650220219654905157697585061475033775637938419627614501923585449332063601770713524749021071536489985823111275541201903696899329989669624010774265454195991419560501153725176075338217681699073290481e802"),
           mp_float("1.1424634381955847752823441787732953826200277012579505242424336193061805577639928718395947740095262153283081966159389933974055423429803042574547913735443772049542583151486286179704014932816257925687942648386906529642278719765723498169665020759004388519875295952102508024928688021977712824804728347862760436144094450845339901342262869014989637298069000294502015696412468329662302020488942998927156826584e817"),
           mp_float("1.7355791790908727952684371040184940777454797061217384108244803466981857870156148514829339480579500767601367043850764494243996129649344470175253982084209898084477221437269756450726484568908760535521336553163976924376295684256387893764545434506900142282274740534011963415510270786663464241230892411404765734657654100881025732166574586003608790718470771864906666762228232341278962089306308395348921775255e831"),
           mp_float("2.834475442169931447780747142031099651062942885785344978817738120224402083040159798863702517432699617749219568624179197794486981019279682856258822076472247278858039633365651707367821759949898059800023180709429964011977413014324096061898265465842243218001698090173814086604330020076232660706297156466780193668181166868341265730807150577013485347600649072158192442653627866566371760815606353590062623907e845"),
           mp_float("4.9714007941817886856087019088493476590239241817726114865750485112522909172056612971544041849175184033665388373018025417653033474468841261363955337737625690435873143694226450157703541925079996804960685974020686349692553710300591472332535037661442129177692346624876413969587303265876911751710865542647801933720701055658432307018176973999926800484003795474331796100577443063350808737456965494301529211346e859"),
           mp_float("9.3546371308922114575288743084187393571986428930856088316382003871601114488087597462809697250634290784259809114599217641758577621534356414243313911739397536742737400234760394730577249273136633613874390789336289252867522249754632840125286667807942735722349154810755130902247580455045467592725769667471821059150389868240845273636423115004234925288931390388162989828923063884034687609616032461354881257425e873"),
           mp_float("1.8866596863354673394638010035244079953710285792024867214134886311241771352118586739959740795449002335222076043103260516289121764508172219851385460550632564045335075354571005696488905614025051271370731444402206327041768098451104876322967622252053325338162431985586206345388200165152438282896791529155465668391198351542143824377019648608154031585082501682183087233381308482823645409021258016827881043789e888"),
           mp_float("4.0744276135916800669323701602839986873298791820710570705730100736755132321619521941606580006677395440734999938480427343599839162760762350937139773308548028484357151840241835928337607923576768336073791298454542160073263656061069615353610235069963417107218882346409884602239447026374723298895779797630926309107632247335398792463123039646706115361291096061114668838500789027820114139456909014353036642978e902"),
           mp_float("9.4133701465063439365015077220580035648852519073246470315912804790067857101637730082142751736574097685314768917184809057818893558608515129288020194521459718929566805217658683904274993290279591852222520829442164237242986401846315759566555313253227737568826214973347843687982783049622554908456263539395646939129122363390308814088294689433720414631933941189698876265715898188462584382672756290582493581587e916"),
           mp_float("2.3245501276810290756608414053158583069469060339853931817460337444060110792726055457931835346576454519615139802905000930955441034287298454278784456657363401060116769717570740888775402030916345945121005131282730014803291331754864017089522664712111560421503419858818243704068720789310579013048954572820217323904906242605544511412896324167638409334257364451841741821965284818758272593090191254056012054432e931"),
           mp_float("6.1301056672204476051618335741029581868571305829793343903650678030624553241116044104877571875051781488153380374818840542353924620085265556626393218500310485563686419986742663537176681314870602912262800991117272790242163501696083736228270317418371919980145765521174437817945114516557554491519030301523168536883619893992848404476799584753386460317566594503643196639039674270427839440187302111424233118892e945"),
           mp_float("1.7248929322016417529980055476382985949978333612957116303321345339946641407241122613221172558248328635231775301980435649441379227948820159755190904525481386545475097906915917367334851722731058023518466132212002387550624523065709424485717970728300063346936039074705978680103280911257230680559102053412021518453904376079286241149863362733677640247471096894609295953057375621397152714613539522074855512949e960"),
           mp_float("5.1744097102606509274395689615537872110643897836785999105893267651780068137182090842785136187832019959538382047720790106944583297513648195071854973603768970786313878411547060276118974493664145942471588623176363514340134654402106865243665012769894351736456763305994462486075105881415100512046366666176134412857839508958213664889519493149327823097766501459579383254365589542113971890381208298965766649593e974"),
           mp_float("1.6535313881404791632297264170718419711756262574227985301004426541611082971225498864578430982848749943928585204631787164459936159326858038351994339502429464424625117893955636978757117361489755091281783630314463800096928041848465700076038440132553975504667067936407443866841267731926294351302360870436689635368737878997057895972987110721631533431769666148552216243423099815239473706979822229166627375705e989"),
           mp_float("5.624375163811638976263626632446949436648483893003254973749564001408758013510980939901613365484564691108962751821857252925908225652518690413198955259447835648030954762266877556967160900235826972522030622433848490691265998118086609516643372377899422485608597727759460633169958151549084003937824954897309974493258791287937633901201775612194267322675364863610111588013605233922397815969539455968616341605e1003"),
           mp_float("2.034754561477249280155186135877173061182569829042069844258103815835791040022560288036163445918347017662737913492718019346817461416747350495588027064386218888902236930128730611775877303724442873378406340390562657996269360856926840473406892824876024003094631829408951251788634305152441315265586598080378831365174339219465725908383435714395330338098294526300312712854072490508111688919870838327041357249e1018"),
           mp_float("7.8234720701234448536445094704086861032665848658675270470121854189617651957294808328532449632940036585186791333767820993078796677721254232359242584113389074855313883500881327684537212633010861024872347990776967934668933455935521436187845314535879146448126137231350077570389923673693178816182862147385919477322636929113972970704591083897314600240028581689896790220376089772484040524819862394241489162365e1032"),
           mp_float("3.1946147720423485246527118784964878129698778167914488344293652657243006622614701970790825911401009032163095512484705052040461394545233717444339032885897634254866198628422063071183584686161295399674607274691766332588184598775958791716692169111429598309038716684585910625372998973126480798031316338624069630941983625612965394981166494290956717900114591185776603985079887436861835848620072072060575403939e1047"),
           mp_float("1.3843891109898143038501828467687037138150743356729099811098732975833432892107999871142569544735251228853078963304950246178367261756365252258805086515928808184630862259205026761941618167002504480306807995897441384673789674086053723170803044923106482037520667481251357192611938159873207777452533343253274862180601636876498046272846408724687836316667811313335572640276943691475546515359414844600177000682e1062"),
           mp_float("6.3623146563388147292861791225808967313539155972824490523380435792575720447234726933612141368219971774098683068843966543510791861815330943891513782809102370517013412978215201085274156483610324503266252223394556091350835985288288075793779216854291004095709529382996783416260812789911960693524723948677677548484879140708710760863533629448554610431774628769033542109624649696735866852405944723885812689164e1076"),
           mp_float("3.0987962519132833205870405367845603867252215032978998328191547065962019107919977483419516957309108135967822266032113541972893454520249954555144037866021760371743912633219122985875814558858548196473805136898905246791586539908826310853493594648949913445299314355071431472821148982139670651502046094719653237354402751210693943419398620269677820829925951561686297693577262457617478221997007755472893428941e1091"),
           mp_float("1.5984616962848289072098808974832965323765059915283140441705796334787539013722635153037073525631988465495317245972124142955541723197898953744401665608674366762548709525266248934760191754693114821858577902239841322361166260801448833115363593974205881422777068099258482506951511467415875583454807856829816657417569756910405074841678832832553760077967504892524694963708725445617464684208774016229139356549e1106"),
           mp_float("8.7268955542665836665147849310846541843328677778836108451937736375751108508000879027477324536069756721180256154525458519648555690208843568361307400776168008508494202402815454656382610866202077055676076537578651220450532498942918358594838533168280301655301595189576178734718959109561028652165100892304124979916473397037224129547399309436407675496883456399543778142017715777224790869641062669713970741274e1120"),
           mp_float("5.0395180748379128470787362093977431176608529779227944975373612394332271123282204600130371137726688251029896052806088263624400731596739526823078474566727772673289564559620002607554258141142275075352359050112989850896828665011691375241987323441690266433845047426575657183344498721911874559918508142880486352243676787697242206278631137878405850498781451041534978615795870563078357368755722599187133138128e1135"),
           mp_float("3.0762343247487304998836282002177476726949071912553142273518028397321394735950031965297514388030315278840326682000455469188679007830930808602993695157065063263023807190490629045214937663665527992243158551737870353573163169271253149119596097937606724968134493367435231568645463408565580892858319493603534475921857704594211322167032432215791062588718831714084709926214452668311099157312436691219395788085e1150"),
           mp_float("1.983747671546730735989323399676479076699753759188422939221406032826330339297977680380503747607282830758743022298693516546473198042578393928276810446876616032956402467305156405368930705341730882428451206811231624703842402333717066283118553454237428851227317456829802537133211033341906145008137598637241969385612015380779531363198130800371270792503462016869860968598081508237681778544500566296682323211e1165"),
           mp_float("1.3506139582570595238199375645363363267069178296810523978353461730385406342732857611191973675190631143880572647050438890363922283553707626427966581270490551815090826842283972390333620203996911980407642098899804069858676395197274645868155453695332794085218264212873755346547781732406104578396296442504597881408194330410228809345280805564946324227339852511758870733158516599868860585781166281248548203768e1180"),
           mp_float("9.7028778270369493042127521337694952408806067930712571835220225061374033084745422046094373647137699152871580324806930657147204124176560792259364359845773474685456793470194535738209134199657216902874242684984092581592757831727821883569385605594976272575805769078337900773710175956782711148462404616689201223485658367060877231992561579895604811435937979421717251568065876174151341767516331962763173632486e1194"),
           mp_float("7.35100197027394127955116548921395201227836496258564835940899091608248490127552394824409586909000649763292606106894084442052996794915003877786498632113227259825488326272967600527068860915219488879144887178727816445234957255551437504911032993635549507557194796370857554804922070845927850650531312444128254206665824088552090294982728771754002950106263427954994219646746007642132979540678732130036358531e1209"),
           mp_float("5.8698431521326617909587930238644448403149009999131821879679794724874702616493268390512995986720981582734047340526174746696195419385076568375789759245615909688788031747332459431648622277840859042242631677759331740364887165482138970111038724732273694465510860103758427848352673999607355090973140029082655658636265725631785275574535526664261394954976733883358944007972506081824720468552479950131234994013e1224"),
           mp_float("4.9374512491327591000673111282658383449155335657646983985109140400673445523409000897234125790761971034374599590646171593386932113195686093001732588814938025630722031916084893145018974501380042169517550231739694830932878763754623984748903984288066247759217385197331994016610656744467249200150243639969423318908410160044362695408919760345756194880602580638086262446430125180627922395156738190514091209671e1239"),
           mp_float("4.3726306084352333361835594759214902513687341953824539570220274912967769642641585519199018384610676328318022616203599302024603034818345323446978417277623284483716515029374854497882423024542976316408781845229050378009447510600403383940359692267456622682078414361382573912599795683469409750232638654178909035351500746060922539346971061186906518872053144014378735995910687134145182742999897338565944627967e1254"),
           mp_float("4.0749138438878930565119907520643532010121353973906277142065795752037190384978738496951580057051522287824573910167990856433481707942292473053467999934977443753580800503294268956567925786807691808109349877396157478343469113685246627513630833456058307062382027759660739314665046523216560859788618251599022436395541340544811387258804157458687512378491860544509473439428420805609454486310199223354351774048e1269"),
           mp_float("3.9939844265475088613053909446326587694914656127329508841493522644636696537839187866738558479315862976487247301007126872332878676700332343471477213721600529704688522774353670850647903432833459827857728599405109185280700951383704295047693824616521846707926685647497471827289796730078248539404031747833794619813775946880943089952496976077275791371786065550692171942223634397782242065784314665441961507843e1284"),
        }};
        static const std::vector<mp_float> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_00052_factorial2(const bool b_write_output)
    {
      return TestCase_case_00052_factorial2().execute(b_write_output);
    }
  }
}
