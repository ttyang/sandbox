
//          Copyright Christopher Kormanyos 2002 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} � ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

// Automatically generated file
#include <e_float/e_float_functions.hpp>
#include "../test_case_real.h"

namespace test
{
  namespace real
  {
    class TestCase_case_00125_acosh : public TestCaseReal
    {
    public:
      TestCase_case_00125_acosh() { }
      virtual ~TestCase_case_00125_acosh() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00125_acosh");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.resize(51u);
        for(INT32 k = static_cast<INT32>(0); k < static_cast<INT32>(data.size()); k++)
        {
          data[static_cast<std::size_t>(k)] = ef::acosh(static_cast<INT32>(1 + k) + ef::euler_gamma());
        }
      }
      virtual const std::vector<e_float>& control_data(void) const
      {
        static const std::tr1::array<e_float, 51u> a =
        {{
           e_float("1.0285086381580059724648521881450233854592353892526624251851657462931927383039348335593016707406686548222557154227471698632566262300465453058594268331189327347890663156807668081465657656106964150327698842296753843981121685442781713100352668484470895242164301542005982076014301290897802422355945773151620962678904056863575344206054434641458085396846130639907200880694784122760431708756689587090832415017"),
           e_float("1.5998952585502979579066109588222402286156315995679236286040980309585312278572165501747874076322007888282288013114338457109811905028094817350185050497525524201686073634885690242006269712859859744723010396160081390342037961276096325525064102178566328429951058962523946632287913158650573133284905179952013508200896036973793078712615115554798706580635793411320529716140637081774844203278630519890100588606"),
           e_float("1.9475965692617128982713749493219579295008845111303735694126064026850900863008037070410130277929094649088533086859272800290007451486185163777345220067755992539018965375469459170859527587399635667027808364358198176382964323715294561448283740734444906138928512895972325790271112959731803252753393982196542096036057882330252886731462504649835124388394109148897549691010480496632247402659601608260891579193"),
           e_float("2.2020859707794185196005583808112296598227236104249997140933384246102828884745313667770330190689683162610271609597433876779393535773039810482025634558289770079008181291988590044857636310554247541007430610221040704986899844549397902570622360181401301234753915581026996681199028232570598131929126853505580281221218197590162193514583760499385906228719487221330034190258649506402309572011989168502768357362"),
           e_float("2.4037009780422786910796069075698293145836374766899590155805038401275457621369234882397613509451520746425522803237322685917658998052720797678965993078119018977369578242926594763397413103559616486144390051708439501085828661499970220752613969408924899393623040458805604873780229594977671804117812245019685619183909660968358154379155796076278078621822470419925679654354185592982106061103120863020124741234"),
           e_float("2.5709288939450912383610857079756700078475326916486803493726295501081945836817095501407952430558787952940503229208835117202181569619079496711527033702367045563212207700096733545323204320361207263606684670021539238820856185894852251777788202129813254235244933420440107860023719558203116246727224413077403239255290890934496129339794228783247391318799246613304238147934670605383154194800480315145884610404"),
           e_float("2.7139099439152982342206521604269807225881062423291877264147439400773786308000537370352269301803666255772252632908037588475473280671359812653269651121212495838847409042321776289234833825961164020571489743459454633640664416266479377959801929453716583912541164027294659072076651122124524629222526926493926543673352187421223201113384808711918879738797597725762031275319496568613820935105919768877569842397"),
           e_float("2.8388408857308575350280835363404949063908967057546828203676148828926722486573209306267242512716741865427689041009875330909329488943045842869066034511004746789857003391324556373945451567962770333796439147052202326065877385836372276257853103280255906944287553295936856259208665808392403786372163169153228746773612177821559922055752196780445374538051823567879094512649908612062564667166335217399455227384"),
           e_float("2.9497972826575276988791790749466454097480363277086160023667326815618686546036736416541668185922837463594593559969592418840999976232377989365438151254978679578785528307289427035820064080364919105050500987819420228846255078973581102681119918549070160271060745593359358676682240560618527865965361827355533474144456784011665280551770404199784660375664981942132892082552228287988128449648368705818551593605"),
           e_float("3.0496072880911753035855078739681096885445769464995853390429974943228006607036707209408876372152507362993603352107254016963820990708929713732600845816525666104672707200842044025800547981638241209767484557607085237847210009288208267039056848584243030432428237801516615421107148306484632258901879576884957469717474023921986491239976626805449805604127160335226323185194972443727401981592579379103914010028"),
           e_float("3.1403157127091102468811433276401399118487572181379160716133585114705495849509085799990484155563926093359895057874588368310296804195402755058865581133073383501335465606477734961832492223014326067883177119229463928433262335198745538131114234482566992662430452861539361654856174981879636046552277055140130062613006695219708791831468033786011391619291318554727953142191072090172482448071939743170421994578"),
           e_float("3.2234499028100511715982114319519865505162130910171743372113247354009601592407532966731111607217797422239112853323917856912151252756411104150023739780059001607039463489474012785867520117192738370950184415490832022572873689665042011381320182016323770239581351659716237176829869936115116304036283691178389782463244767873084078681678649766508690315283356331583178266007108123082634496678219711598924561112"),
           e_float("3.3001812985598880823619176124706015232669707613831514054398880293394107381673894554612075318064665053733925559429412413063857545155201291521106601791381739990158279696141865635120170103970321062206597812623534352093926905402565935222340209792594415372919982662908601579532664341173820885066706652718507693700060454818714277162468494734875009278681436840301329649895695141898051499334635514161073389689"),
           e_float("3.3714283406833192563634676603990532009053034251853147655550686313813723678630717284787988101216580123415476564776218645337805243678518619886974588214284305973986447866728877991111872497109956167008572663589559585501983081236077833516052077860446233073616196621555878062724539982944073197113606715218099401743921585014946610602837613287910864867233299476644018803451362405238184356644529783308110820725"),
           e_float("3.4379246049493664683699737400914068524952318612235335007570857543378064802181585232145196511187365353094754170580836140908477130464581755992434057856653464703290352527439114441461072539969706349041820856155900183197246196220695740854752329730767970133678613958760495308962910631538640811349098589083454984119618296460321932361319372789343879967815991128835296190752565226978951017529889998315825583076"),
           e_float("3.5002653998089797018238421571114261386063430706681971130797229882449633675459181332132975649850783290679418125025557153218202774540237328200272780972471877913213119333192969046187320782147822379404357828257501421669421273111716993096659827841548797917904369863996577211780077776923836275358924862334804886015250039720834152193495702054995527968388158941743097751914024048857763872735504555384626570192"),
           e_float("3.5589405253970116460080871624944051187385840079735356626826062962342258541343880351739571089275497764931315503233951503847382277768263759337947594512863213784477253165049430351406675520797422245961892046403225274279713934342803454022856902197832198874799142806522795531433353754146116275267529826496959715131937740677669855214139207943422462326932039333863376042827906344137454295968106835579468530389"),
           e_float("3.6143578572049747418233042912385965373736509161632910113310470763890808089861599696353085525366691067617099796662831580309927727042449554421102026575267613443987722838092553662800490629147366987853063235667132737551380784704743504287035639094913148581065386565462550152627313996306981922241307763013067159859354378513802783170129441425863505949771439794893321996805949803283916820495818528661191788636"),
           e_float("3.6668606792377795796867377450122154261995091316624280151574003014130105035931789707128938167355469742514473896645826381118614422227027749937517806696649519426402637646487776208838578633040441139188701151867423810882715664244176352655794626029291352358908161334452378058751261660264655534895227869938878498730211330607738074408829384241923875124279165061531264603731981090670137427645017056158640822415"),
           e_float("3.7167406571782858116946792792697336286491697084085762621783909849172528238871948798386505385562288097551243488443607227533110845799331842607962041306380444165303828800359692812786456793048509037493581221175950133516700488439087502535755818733248022499003252354406698153564928118833024890869744882963493317909051680313104728028571961609098318087621195581118193606819892938871661590130768628013630597168"),
           e_float("3.7642477061884577922213258801696034548079529245689188625826006598009214163515580038466424512389273348863750011211007068945371406360578788282929932452311648401173917282384486255728882342257447442158235233547133122412857843897937755671348577891178548010535419999553416438454401930671316428001046097511957797443807106931321134263382219410974426619309536517341042450728973940281031031114924366681231428629"),
           e_float("3.8095976055838293583453938722911279641777293267329818326360095240634260818708390754510296796560582909070188391695205751692738767744393567411515668485290794905141506524822145445775010669659889733092427084767232440215503689380057987706810908719721567398404103309382842324803972299280915968535681569290441920251675535109125789433896925934631102669946202721973130693158369996150877937438242192454503497419"),
           e_float("3.8529779514062588351386993180509123678137544898731562572009379053121787606356501487867490701544709280346633711357433244235445176077465308247010280504307640352534679324969005349290830536342375873550040738362071639690370985736145929079708881182689217094309807411786436206448358441579143006907449679107142532798300306323521142415493010286579199387563550384444800311657909645858344841082529932836339729211"),
           e_float("3.8945528644538448139866735013350813365856418775130605003933676463052456889151224026791815175393951744504379072620333978824224340205195910057038770943644497667209604344806725117264284836630567369901011523611257617352565526475008528778594441795728464540661290259149187364327478716569117241957043416649962939491528875233044356711891351315586143326430988794090258439825278266685260411036487733473860845427"),
           e_float("3.9344667537548591757769048375191263510368256574817481894266366844607647764363813364982172773635002475541852994652822309839310991834991316900102949625123156817772191926260105323537995565815531560019548991904905731203082259346377191907725871050803625362705235517370118142476608979451200838381974019374300730592909870287914377247456067943191885127902758734837170026632215037884790149270853466580315614545"),
           e_float("3.9728473543017387102496861415134151638670052754415044976948412237205014988128498954549033148564796747681000908059604131026958849233189969363374692436390236743546421252803147160758847058570585869512315895446973738472292083522905249371511271568205088572610120531881787262846947854366777723023378761459131395781980462955168823852788706448855039135859917702771903550441757745672434746520518178053733664755"),
           e_float("4.0098082008757916545631734222574244160430377323032170438635345973413494923682007338274507023265754500472945436863347346025691540875112438751188775443916036677925081142342466132989410256876617799343998473082534473719230762010104190329499867125076194345002215545025253251695199387404700492763333528774904083648479417014340235196135213856405898761197772147686509143636432361425037757186487087268285357057"),
           e_float("4.0454506591718504977509459328563129116769996762661747898514394569378066297184870624369561979350353471933956947393268319177557517285036851749887033616396280026655714926670009505470193224724053385600376760327810719141027673832762622217273574860027519227474792906223962920872622307494129593810732370813758935215603478487782492274746733801258460782790324707455772482361462545997806826346386116324002935951"),
           e_float("4.0798656060679480569346660724826807886189322789888967358376204853321065513089240669626037220876868685056526861341172219762169685351894469830490062287702225347355063277526206145957608231235848584284019216827977086027888268364556059970673410715231064685273875201324445076659608281257571832484688707903651655010841860879231450301816517974607186045383198532179503827674714459061445104652657320777017359774"),
           e_float("4.1131348293839495408097755438082457018225167732584034681469793937300868044928533836366341894149033852966197337260493914325474624524109709894942136879447123089672796738020225607077298846115624750973130826109107984417610279900107349064656011920150564657510180996033805448224136278543570516679728445501775830097138906523349504856102183948927912904505429482002892254276098515807092030891278032612205082187"),
           e_float("4.1453322015415980386883674464877184371643095012748869383130222411106736284168156930699521455239260069518387112670530491034734888732952298801262426623378376340406311141638987405893212553621594372674051669741314099462313960501130422572864218082834822230691177014609886820825735029871028273146308376356769777730943982265892534075240032860821586242310674370129076858731298234064576956830811301233545939318"),
           e_float("4.1765246696035487398659281116023946766332385499003993851065354246468251201462398958024582666876761720619145103651619393226648960706641353202675320864558855709851764405820950554698482615264001671149199289495527252977333460555436775595178989766039915777078552346288672908251688858078975760423066476116503093771448604648749611784548406193500872740293616047257497653701163183241083839504507839959988977224"),
           e_float("4.2067730951364879593924070374933209360321216842079221681432186262623246159355248541768554187246938668883476218374379770122248926330112700517405539302537706059858027262849632158906267618508042158126500533333448905819646687468875662143542876377058931516250805768674653711874115367136292901443316687537507491558784442163312552501495627499513168385364526711156515463351089850358204411954595143067857660022"),
           e_float("4.2361329704423508151965190576838702662171459931054772976150363571637907179186839633339663632759956617233237006991887096441798743421466369728266674818494800636409659934122799122947392925326886974047281118585621136129635490568516233766765163176119114753938134438842105992944404188107237067082093001361403265977252541403902789389585612719409851667743971429939790942262814301233920194732099861868864543921"),
           e_float("4.2646550323821077625827624844752162673278099980978221254360153957275984134578929982958570859743717278034547463187284986269495379239926696390996586825148889399597924057305056857549154031365513128003267574275572474070303172093927448166234615824371527448253848124652090388616823349389310255552896788994197426731126272051440586400539175011699161352212128356573179643929794183145581818907392555301933449799"),
           e_float("4.2923857908820155696950366419740060052628342746297060350858408631002495862651451888981636022782487171240780026483088717561191341746742265689422837179910704250777749248445425293543283008776179946655399319042762128614417692913900769834726105330030034529137328385761245989725261435642731970786881852038757990377525792186941421807556252539987640153379500744077549010935467678355720761193788088975089851041"),
           e_float("4.3193679859735910712089159855233693443034037725636146938366527775956685416644352130290991221337778072370551287889447395472021774140238725416747911137056068942676022709490747892212369223696690440057109014855432824559618511143965233534323289876965288870245307285240229070029092432920206529639401537786143986448083697717104576205780913476794166673591279879348856144630074292552882693749711459575409803496"),
           e_float("4.3456409846631299369136305669277984797344703333865873023123486468830112815852023408018714885419876506975028092197426719997687657864624868034085131904712047446489150376497776165036791530794861131906128231898929100624465852744585008262975953281839038458093367790046060428458301806215914343317773722963470279440311915415643962597930771272216027172419113063316366816330785045251707287198875035966078114511"),
           e_float("4.371241126896325063558076795957837400751497422652636843976719247631116772662684557393194574329415559466258216576359655944298454945125095877680126029091464264602460905052993123708681141645514368548988184708232237405030198717880161912601688462578264900411164876098750780858236429928385951969157670823119112938718467423757849022072944901791267910058141656993148274408358807794345018478313443199186531677"),
           e_float("4.3962020282600202247887506973137761118309477763725429444814657557518089169871287444668118420698959675957767142929530029551802317493660924754474931541381590937837239041117908775970518818146618757004131292089127659715783292405755418584081167722071618242630006110741877453339121780133097046497084534675452177035504050668097986917918325095188278541059412588030259642272281935779894774228836622184332090482"),
           e_float("4.4205548457568984312685848616462248380747971875094860131653803027093758443717412658184885328066137553901764644814966443409548350749992584860664426515041274963878996554238420609809840301599123853345653351659966900273804006977737236751104342813890658339330302895996072568961389935078218720949441387631809427457360187986529594676245009750751408885391983173885821373502376643039466479994590640160785061544"),
           e_float("4.4443285119318353137371054493000772272339979283546025297684047704403843226045525518809782952976796070797134659952493275545650920872426744533167708466841026734686278228999885837349952377771172267693630321348745916653470151865346295120912809230086703353255469809460900091665047458822887098978121854193148974616012870197536267037616679743934599585243377639598241903882033655337787141117788500906423744751"),
           e_float("4.4675499417685045748913239831785560176622892236717871208936874291149482592848159924021805914354262987772249544686556207932892951602956767255128927806372525313864767393408030747683601105018255159557853794201797261133233633597930906844555383626737775841690721578000024021844706782157932772062903176166643272184484311315805330106321238076182157387075613136085444012000846289017037918462145558393466168932"),
           e_float("4.490244216071260502646552512755499003934603195383365803628575729184841606207486657984245523807023047871445344857260953639192748271760010871975071818050721065636791628557591309368858454864532482299983344905672048821520233755262327440972257523492792871099159424731652300586182493379628387954227479081646564953766556996327772145359943772229885417244857929478648843177624516477773223925999344802714486863"),
           e_float("4.5124347444689790629568119155729327339070084241218054084016397446872853278198932192840886795035335746716455584255137038750606220677961266683890096281416469133685514570541913030655577339039806586844601341320082785550291920835358339092078785383300831303843786641828492897016528864887846369501169334144807406553747978568490632402592353707143188302311047063306357900491177119893508853543346656421495169671"),
           e_float("4.5341434106998812522000704020947712270595741389876510805896216771498103973001406551084346058320043119043505192560604539318014508489626516040636065830278092588237472210184834813960402204904757604172470772144167575193461214033762244468539063962484866314217218748032207624766647977727480110295427684959889991359462321703183741867557797275236975856163359768240612177762474008677499763311045446680299947148"),
           e_float("4.5553907024400853932016279547557475112935451889174429835821028752838367947469997857441676348375905150023302400306496756510108808361624588596160063658488934761573302459941695270074144673297825804523752843759026374305670094195521221338348852695902571328875703807039071723454276571737943701753327553007281158264451716371815537958217665201130215340125885734121855256847583968716950411520406945808396172329"),
           e_float("4.576195827608461963190847535395397536606338268016513914594128633005031327733835233742275572320038315199603420605327339753396280783370839081999189796720967580618709161732023425180993401412783211508514405770739841489284753961300777020097680788595815382369886338163464627983742065837989452380045374812118226866845403350371439192774669344880365148409943390522762204425410737573162191291026308542470340871"),
           e_float("4.5965768188041405031208453582460480684917946499803107686283290596493315856399626690285561146043217177887789999580035474615746204108183967591975184285575487014062415572321837371800882736066303813394043639606068646991845031263088456197762264256990481913398970668163370689213012050040719107123648915059360439806871057273954740868848610018749565316320274659715076341170753668782662261559113952731043526466"),
           e_float("4.6165506273010224719099331551442629756556451722784853415622349623566615733663553121563390362673337238255084860141615853017101732900045830760777977638397204966648816527915224153815405179807512374376836388352782343943375140764100713284620781115967127305898851720169581299863220212469759195628921433426242127796303440473802763718736486779109145557619804801639170979637448475887996875565663305600412359469"),
           e_float("4.6361332078280742141895628803797490902587043395960647448142017573727472213883189891053821460863319976273326398220407346255802031139209080751203605019073458350978143896660477470677913550485794536151076920241979793737541287333329972180743173509763293047227979686251653956055773495012570943505993977793564720979978978687370041930613837245744046449716538337484570488741053711874189786506794081972691077423"),
        }};
        static const std::vector<e_float> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_00125_acosh(const bool b_write_output)
    {
      return TestCase_case_00125_acosh().execute(b_write_output);
    }
  }
}
