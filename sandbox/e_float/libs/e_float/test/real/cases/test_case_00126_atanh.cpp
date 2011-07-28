
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
    class TestCase_case_00126_atanh : public TestCaseReal
    {
    public:
      TestCase_case_00126_atanh() { }
      virtual ~TestCase_case_00126_atanh() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00126_atanh");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.resize(51u);
        for(INT32 k = static_cast<INT32>(0); k < static_cast<INT32>(data.size()); k++)
        {
          data[static_cast<std::size_t>(k)] = ef::atanh((e_float(-25 + k) / static_cast<INT32>(26)) + (ef::euler_gamma() / static_cast<INT32>(100)));
        }
      }
      virtual const std::vector<e_float>& control_data(void) const
      {
        static const std::tr1::array<e_float, 51u> a =
        {{
           e_float("-1.8945252679777508235914791847751762330074522577195782220009846970340822667915069501772634084949967027775036589429802203833567116226670568970338942881933562458258346487142226945187594881794416638031731731933156595549817392741820949564929452133301970187596489411454887503530265028004169784414228466928866346261486251168725313178817752083308171429071826063884900430616458661711246050909487720563294024867"),
           e_float("-1.5717568730625962360768601901451038258527431474256501242776045158790829210175002796464820280722182132366994178762908610783801979309017512717425619561763381144932882977009333667751926955763705184328363633810828281894848937051602589339435086915438018902942316520724266369383866230971113903573269067811919114557400904713047425327707643466820891600239380650850055112537953811402607287488283788860133151897"),
           e_float("-1.3706631092739908378791804231003954084668441172144654476679545101162780373101466033910610275336494054474087743458031802887078276273987598615560037008771350361968425549877396059725598129765339995012289403039857646963488870577274473817355302331679437151369299934331937081492257161841464757922727491340158319684185241054249120626229857644021914250584555594336571034181769261319100425867028321931740633888"),
           e_float("-1.2224714315951275731884622850384031092918734409426131047069921202955091500820849368793390130286414881723135975928120055436214550966181932132348775344146360840355978219019023177464745146384492996959737407296538986675933197030214864744199042374966470550900063487037620687163167302601074165939730388487218201430734330352527104192505574763184897801789654614096533443793255782418788815353704743914805872066"),
           e_float("-1.1039689494653266546878885309252133065893922871427605627100735287052902666632505428151897699860030241967157124066909689613784897284524065599614440691446431275200549753309184100698140025598977101007386800340417636154192500616496140825884585620995317465647306581256555840483169420005720451004102457994332206499027210390602057960892619608443835244877969566522289054577004019955197163251383051391056386484"),
           e_float("-1.0044545441088147334982090141310109996254053211891382909254273954841577946445146939266197918918682064154417284913909744579255335642984138926584472349045044809769982364636855188813822942775992616262393244692123030785589556491086180653339904810372819131534843026346899813996391263445457079107567520453729519175103407465026903508443410451709458152286177149336961465488934539066425478277113956311952899896"),
           e_float("-0.91809944806450160507968509926719421793397701601129506497054423491678832820566696620863945812353167393594283359765770133478438784005604917043870913054590359602230717114829868110340632839152352172838766906074135661861780216130591732458769032156388762624876501966671020423971060413663789725252954018156707632980759742534280277107807243784285526895525154528549981534748892521960867373929166807402081573607"),
           e_float("-0.84137286133462912016370437377722557391527006077548679989024953601587274050099653661071822048734972545876665672294079264312910550053457469885183733169985910177738672282158011166234509760264628620283163878286381712914194375366291463110627267583769821092284052817183101371929419864373996745262689129125808913502842053646551901136694297563856600210919144895359113486205381025331230845917679254984130246056"),
           e_float("-0.77197083824218775566758542350576451984503910928325099880344231695098034107009698428490605143956625921518324049404097109237191393796814209340989212860920397970388115756679904482069453638212904704871332034961781721672922306658204547297064795707585345924402105885441977479371595593974833732892876442696744278710354462038139373326420148571052727044037945666861384462101100680438085845714758007017890912459"),
           e_float("-0.70830438942938389226103628203671095058578508624919043241100457589337932341579235337594052723562908289127900180478384977845247685788558617998932580698541372114458395143098726120605407339723332145309487722641158828766507187970051092372325020424968801444346857456805673521021982827998684176358215090664412075830433676381895009085394765459584306902332863538516708968250111151949373292883084717370136750214"),
           e_float("-0.64922931924651948435891166459604527006298311097402614724221866946976727374095436702910331345372393830663520058726586734366250977165782203290673576223479831446991049927009713166922284164802756532612630368717151192763983917617470557104009181727988983728899982571764042714943427842884228226305968909296647210585631530356582671020250065078621947866930791955699519091621975928683891167577939118209752995317"),
           e_float("-0.59389253267249128031856786349988950917074765052178537782684731497950168793198215085551275376525785638095347334381464337601340115873120906654210735093373086749025445129848864267629681913637223959662688388547595917343105902869795522750657909313152225334909660349311504665641839757432032642085273294773825430654569626236655780127476787995942100203930109688649260308288138812920384786398107911158242211336"),
           e_float("-0.54163928753874688792693847953154378210278316337289073302621701691793013842832713527855139275186331761127890791732949030023387668284081530990576466765366438781004171468712125923806783040364852384645107474919323888244866104299950853942636500449804918524717207302257189500014384947502213265987609740143982507487752851811019675555199536969210338020035244637168848665673874542985848104891407640283448475779"),
           e_float("-0.49195448489020132765164563330678684795319809673170769254842932397574142223574266754479688876439252293063596747191715763949473637080090845025235805290627660298390793806123567918272432368565906456904449242048099640269991573860703091119549966656580090344895727506903217490997702076139320240070187841176301072275132754702853546706531458212947126377766377082455276040801409649593897686690335579039249088097"),
           e_float("-0.44442400049290474683780015686700912832468011281584370719264797865896724757544263801387160919715024369659531310290126716069277592781213951968487348773317968829873493315644732976730361771677284524361814570322804017651795902352828314768829813280525233152076152933596338657084231876261421854029323231871318447625420606563761978016691863382221705644076154848363909068098768742955289167320802494939203044135"),
           e_float("-0.39870834250706801257444935988524110119380678491385529549826146353593685074374394112413530753542965515595298931942877772289555175979857513558549299785756474442266412565991581952064122340493476811771499403749060130998048846553181896415207376130969949156769850618368256916207616199461311770232844290729921276262143025575636163507127372118192458469115098175134745202385266415962170057479259005746371314188"),
           e_float("-0.35452417250004321439374440831915078136774455819949041597492122200754998535794754311186903696305160024729848730652236161741641728920822576604759627107801257336472384306635842524335647922905986461464316734879568523605585540652747947718837008361148056473435140108628791476417157411614669729220544421871375778966544820126732097366252762480867772267580096562995098838997340350068034458713836810975772336542"),
           e_float("-0.31163099997923437715192791252197008991908830392226002711268035126045994812850021341487045977331183406719888121216726753379040516535548994811853106682744138885737726199249791826760195154324819335605401830004699771080926106711435811095528162167505138326070364492325448530938083745741449241606489796118059528158686399418690053779123492085431337302574311043320822929763553100367471487559156506184561552059"),
           e_float("-0.26982137053524629125589134368000859463526920706380634305754504803352996889034522199698562639411111509352066285692980253506584514894347633552815559962078278213942554198161361573529053805815561604494612236923046113569963426638815429190723309371873754362257572129728553764814245451555127598374219122915831827822672050068097587917387876699610748871725871899505124430253472440033559443193231330882015912222"),
           e_float("-0.22891346491385335252418323301305721903574426853135165868139488107161875359882649855060841306281996610577043507714420179749997012490158200159228286760182076070238853702650304273595536044564097879836256040500445222623779517938479563672825170660201187913665886303500042899943881458172545747586773449118636829779024546350594192939501222044997900461799567622086855376134212520449581979233755845919242206407"),
           e_float("-0.18874539107044148483962452539108049562605950739121556233874324237284003108532015803932351734722913851157885919201353727415783514636122518844705737042279991012747602806949345579673204148952872149478732310713411165777550153097344075890071456761400639748535285690471258927101581054854355340447760012832986593741543172954100257224868334782268838303129642639069374350855050822560529712121253873512981192919"),
           e_float("-0.14917068020191480331987594366798257463642049218013100358028007494808278782860681845793727996355077949105621101964780456644558710053860679206389985564282289262863945313521563419713425095313293561156531271406873827407862059794224178673963931015760175992409904618030404049949388455697125710621087153903996554699310239351248501712403735965447626172584463708389355271054135458575660616407807281027532569273"),
           e_float("-0.11005464474855034558532992946367617140441291799590633272346369470300089948451548088850779848562951333672046307768236197132011884531112899814287017142812678099786189530885083648028053487143143210013084842204033090067610808043437957839263278819990082680422245184503920065003760084056106498639211714038913022675522477554088120644589867528379465494261566211988560595978371720027996662040619977622880519939"),
           e_float("-0.071271352369458288329895322820321910518387621387471904886753040845222508742556610207614997428474692718624724293494234219486629692654067913942671448590308747933077528686356503740495564748336331489981529007498002049467203305333150356025765749951328687615625861023908490641924464725067250202015290398615939624601003796804114657341880719028798356299969314163744225494264251177501475771030453895849071760027"),
           e_float("-0.032701033194570593176960967424159867439262151609743901281646918928560179614644292214937294254139067353094941343546062435337854735002679985465530661919437769499469679334061701271307466518705721255721164711728935386843748736018368773148696143535617494769008376016264394941445653108067015696054031886593648750000165596263861985613231299331084136919464347644043034073023793409599459734457481230289510806005"),
           e_float("0.0057722207554691385250765314424701402029055419887200752974001016106629261008223551600319961270952411012900554217491512247186235158585613422080610570054108796076834431848890485955118303328412675180202539480287885863954467745637685674728697347784167533761440614497836458268822725675369917889323682081897047014291146056662623460290243668294045527397768718714806369806293863108354786426648129132539998966372"),
           e_float("0.044262578534115316141505364013688545162815968886387326469474011960614866433928457544564083498545949486493015541381480199272619273879483660896633417739878979534155863162953056438401542103997754703392959325502418417733490282040118639225135387198900079222228522579867326263236213199100949788232996928662962441231996698537685518745580535167116015888007193952446630626483612472216230797696789386780024884186"),
           e_float("0.082884514651146407259017646479985086258117464343433916588613923731629621161123688535473719632365422648561228191057434332565325524919129526296255129250328138431220594918079280195279990971213144222114933872562820098879933095885263397540800837952198206212344034483487932681922475360177123492730435399888179708431851143741657690274561543091833844538019803436819680567342722150505890290308739647058592640554"),
           e_float("0.1217548671955795960207425483021358614900843147970591147825252730985495716746779304108583040605380635736259382453706161173470131311972082315653334790285882563987143260143807679559393364073184557114840349963003150752008142107499598422849645867732059632963448081186949558045389305896103311095293653523480267228202651648644916966461172405131934237132521974345735992331042105061914553174017305593570722156"),
           e_float("0.16099500318865073276376195714020256110911005501426067917868735250374407388207114134869388425766761670879817031858224511878065771310200573518985658494245245048988423406619285428183619587229125636966670817856588629065332290066893953714088659088820731943961877272867720953926265928984182942261738179063500317012625625613797214018870277698473372492230395058060627062944585346521626832296327313298658946896"),
           e_float("0.20073319385914212970233274868875581560640093904391902910347822963169483440215931868782569254962997526018639634536391462110405707830358123823810607748056629388859067826343648830303836089336805193542960063250983751273524017285523313772815740299121198933417421691620044489342555473627953819753849276950873940120275932709303039501778590672689387018703111301194763442232690837414679742192675158854749400031"),
           e_float("0.24110732106371081443736403502933959458865703703270483842423117911855237718477095375078324557706050466640840189195036310010771542342902595811771700279244125840532248197023328422739218450317697477528606655009431963175668685727724632716503220970036011072428636416566617878746341856558005866941568793016787951146778504074689695289193249985776873982483454467167675620424391818589079314515966761297903761884"),
           e_float("0.28226806662364542513488243855237188811920801961394719006230256421391231444263940935587926032734673043583400517488196478317335522266920865608846119442041487607228256282935367902843937324137131311816280846316476211504981602083709371584893046826960802590957082701189948181040029126922997246285190893315421108884940056708992990319814388386528385294775661753459649244930557683166900456501152838883751048145"),
           e_float("0.32438278359661197188434814112263645376383300796368345603224559078262213174768160245291418722225732535889445425441978955046230232423520183162572328796667918597119755790623426821243396541038067189548221385017970747490132848346807835086846224742739783518174521856045120241342552342250237624540517640057863876727100790404576759937970174439500142233713886045791094692160232161282202583799526494890187440982"),
           e_float("0.36764032020610093973679656040030769894258076032598532026879050451787851837623281876779910839517104934559509571131245476793370897461112294223097069791036979790869789246990704923016972641128447124450134761607101099714475502253915279996423987874751551839809464243220605216356990242191332207959440596131156606056053353782405658126680752112347316111248571201636101980584863771192511743555312778285555811852"),
           e_float("0.41225717610421314636079674858524577974339769530535673599416985093473152094884668475532212786070109656396734210024110646997739806599101515391338529224200765247029621804347659989314285663073356934778325006846600585105603409229249560068143779385404061823352856605112175476425585941848668876363500496251963802785289099156139730794767931239696567625808583721758455499590853776102969784219301687410366894574"),
           e_float("0.45848553820031277339881961458620286852300055597216222240276525512597168732757783170430622002335250088852717337445220402792871869624428629670478216686893753213091622640491338749053493653312687192142506317186691451499825477387154298130502081001079948480310374129707518873182909245293729856314112335538268536991100432734238754831581382183867194152688544618613764786538110090218647630222418491772354867365"),
           e_float("0.50662400589151819543754124338039458002395162501862620407262637348473736573021443655839614228849954703752400011817439273929686107129980027758334062685989293871782468422087134309251487778368818068697343277761276152283269214967440843623468760599032902855101536074770651052347802720398309604389390412935576542734912329779246514029320028058844182113790702651001494767282106389485006885350535397910234469596"),
           e_float("0.55703223714613858485561165636672527418435700929955882258522063085735247762830209546150949993093151208525168382942741755943196909924894733640612287662905448798208968695503544429691006683973510555227043743115877749762291836755023743371250531996306407301926921250651978425852216595231562358901354322985512643062620612492664684343735660126501768330924915406391127078561449196831270962653650285913168736865"),
           e_float("0.61015144359948099382270576958891281376175897658062925141257291838647089218804211924954472615276351608052522616721536350811304309106843601386980372663700817841407613637205724710060380504243946387527017729305835526549759382584947548307294673625945181505246033588243254628562007135989862819304875123736322124283751540840308424418079826356790868621285492264436401284457131708998454860678178957440487496846"),
           e_float("0.66653385357841757655170912495598801052948577949578794598013766485683149399919600702988263790548684289308419366507330114731478007448480277037870585349839878528510476987656751622171063607650738049803252770931746711749979474138295582185518122616770583522011547333404588397334140218979008329445743257183350026439245195622327002412935110179669786065064256248336355529803951249608580760994410241970183301048"),
           e_float("0.72688637861983576410380825282724094571087509064536805859771802634874145038304595702960351552350954487394420900893967443542412167134680877841022981979324934217943044558243889311612369303389823802228415968176085986105456593234836811196413498421705189483480441570087218838838880198790023783126935379997424380646313664675593189097152372597591570297005052762141985888876792397855378330324678708910535670928"),
           e_float("0.79213765866833306272549063709836388861133164821764843814035544661807233669085657499795119694550109697289435796167905730734028696860457382633591969746863203221658268215352787999426003836824295865735186240058162890238026143550913074428829174971521982766295337459171920434207870138560165955893510301701009475951647688051041924173509772976464668043102181249133326056614514194476059702818927854465182730488"),
           e_float("0.86354540458403088870162042701508802609899641980827779281388336468387611378172848545179206855800237703117326388766251785448832243104557532315563868530221335241681843877589721148152710858450276915094060929055464460904595289810375857484542001554029772756914205394764581565015681888550619597521215330170790900932020526427139889895301895298861962500684224983309849631253769651055627766131046354016026080633"),
           e_float("0.94287720903511522695472096634698746821961701447082715282886430681759116370510305442200977746172475919191766872467452556435722426923628932263016810057491604627665341346370647312792137878641981778339478766977117257033313193972503062049848823807984185816349161511639384323609717039070859731273730786261962440930888961452637816150010957385753400458485079102396957808163728719086277093705222264921629104482"),
           e_float("1.0327349760407099216140308851526758117650434455754556015816531862477885126267713968703270435574116137922434997264335894165317390264620780236263058402737631932063063004174165625830307553949547254235094490595421204087829251984045371695821378899289906314510773673733422142525364986098439491655499728720064067441974847089250723279678569531016878669464170860294279671823807549050173430657469073868328460813"),
           e_float("1.1371863014015513620986972920961467996185902464614212207967072096417681464226600479577377311602159402407006177366151792555740413963387529887058436646530185310378049070444949770636542584826667271864024228789390978708838158611836795677989461494643422449725886461876005332181559841267879321714664946944627924576150730898068371519461986600071760157156493283647973277601700235116463759812832589446615669689"),
           e_float("1.2631346646204410830548882103736262946463729948450283319216541258013873543876610506460001701731124474329238086174400016238727604823996884060192535462443892502594341746193920604528018170599548597992605446058531127380864729565456173728022714231662240425741558506716182702534238125055859380947947672058216263950076100709067081172715571254529483048185293474954001130319460942163307510771562521877483134558"),
           e_float("1.4237930463369322171790450466716998485849659070579583547395528327155766494591321709028255604995555069697767509898644091658838474199070852141503107908914488299079146020784496004941717619733247593923072300435046114117497652111092228484287429692536116970415263570739573669192065312652575704145058924722183587445777094179651212934483870146300325835132250775160251918024482060686231200667421720903294907992"),
           e_float("1.6499377567707229634178205391583573895620604553618816143658836839890991640813664989103153889625613011232279189929537738214010123434985409196947080360318884995453552890935404043608570501176195711664339544425819905604772042865040944001981639283871998465522832931285014334157852308873479268178057779389411298498058679616477491760733137458413954695069693409761463782778062203841902657709000876517957472041"),
           e_float("2.0486862053247291933598068078164300555832447486590480169975525282181606765233611608294710306041951894619779320808882667774269167897018447679895915669085872333378886097667684809013141977645875544369058952103375351663736066924352138015612223989950648763849808609670059374534983391726566489604508066477756665036079917861496985739670671535543315242406536705684866077302400051098585622598120733125735438231"),
        }};
        static const std::vector<e_float> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_00126_atanh(const bool b_write_output)
    {
      return TestCase_case_00126_atanh().execute(b_write_output);
    }
  }
}
