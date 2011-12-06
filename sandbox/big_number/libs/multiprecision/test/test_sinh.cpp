///////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2002 - 2011.
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_
//
// This work is based on an earlier work:
// "Algorithm 910: A Portable C++ Multiple-Precision System for Special-Function Calculations",
// in ACM TOMS, {VOL 37, ISSUE 4, (February 2011)} (C) ACM, 2011. http://doi.acm.org/10.1145/1916461.1916469

#ifdef _MSC_VER
#  define _SCL_SECURE_NO_WARNINGS
#endif

#include <boost/detail/lightweight_test.hpp>
#include <boost/array.hpp>
#include "test.hpp"

#if !defined(TEST_MPF_50) && !defined(TEST_MPF) && !defined(TEST_BACKEND) && !defined(TEST_MPZ) && !defined(TEST_CPP_FLOAT) && !defined(TEST_MPFR) && !defined(TEST_MPFR_50) && !defined(TEST_MPQ)
#  define TEST_MPF_50
//#  define TEST_MPF
#  define TEST_BACKEND
#  define TEST_CPP_FLOAT

#ifdef _MSC_VER
#pragma message("CAUTION!!: No backend type specified so testing everything.... this will take some time!!")
#endif
#ifdef __GNUC__
#pragma warning "CAUTION!!: No backend type specified so testing everything.... this will take some time!!"
#endif

#endif

#if defined(TEST_MPF_50)
#include <boost/multiprecision/gmp.hpp>
#endif
#if defined(TEST_MPFR_50)
#include <boost/multiprecision/mpfr.hpp>
#endif
#ifdef TEST_BACKEND
#include <boost/multiprecision/concepts/mp_number_architypes.hpp>
#endif
#ifdef TEST_CPP_FLOAT
#include <boost/multiprecision/cpp_float.hpp>
#endif

template <class T>
void test()
{
   static const boost::array<T, 51u> data =
   {{
      T("0.33937643772780730649735035088117439284797964277099188367427256402032493952288848579083622213428182842627923924487560393743204013166230906610274533504451302298480596207257724471359936027198954417317381228420986152562253196896619001418292769103034561794393400788635610424360775622370491149170501475453034747306600304507650361914904138327962144190354572359428689767990353722392457982930942617983634601752"),
      T("5.9746833446871871874685235810964396457491766537010251792063372398172074828151074989468673672535421045923659313715467371148678693662985453590831122722616951299822923837410906027605763677066945998696776562438704017846907508677186762421899376364636371743116519071733413775650991880222096045615827530741679305666041641331859757012015389431793705875600863391408448065773828563483223117178640044499399723744"),
      T("383.32826140718915582837967448860824902040431804683461630967288341613741467095168380744762629948507973653220772087887989292128183196493611623766470283358542341824134250511562240487252437079958429586344329111208041197054162309164204144237855212391474938076935722386012246677813568519769393617755607372817372398764101401294149353978426057544810680225593132066193858006901125069663362991172745649465725272"),
      T("180470.88334757918167934673473709881208559849920820465419382707969109187448281704429118605409224039018180517847684905660962429505828088398660499158213746722168139372781263849989865384042531846290813274318773753295025006473736660333640052386121946183935053629928496714560749082485275242374067168149435272169334475060524974384307351757201698786200303374802146857634893509516262245925287553380389076772488"),
      T("6.2781497954189513207977998975338639259302378413658035459603622432839117790845430762753614618299222131433987986511235061633658516824123179660244932375967566163895461895213509376427850290780942550513918615228886566287592461085762554208269169000672149592375451149457664991726947185145469263932975075681560662428417041932848357447220175607720561540370653825438750168143857523868718856189519864027430308779e8"),
      T("1.6137831147508521132232267071463247985636947830692243664921522457394294988129666666745854084767325882717254318322908201512400243137564101564235450151960593110176457803621675408660678871179456625850704076654060872094257085919134755925910859520026379969099492921728083639989029675808598278170215911879751320574053132699172028082102336989338403081942130794464992491330850160862146024982135931859868176809e13"),
      T("3.065121004865094886953119667134247741359538615435533822684602797608029400610449009335078883525336625519599034934744634528257351124420564267197918749480389135525897886434344884370577475363556341414615470556433033106705280531443046669163916446454890662947185057748542735928453570069226294801221403438864013368364219717148075652123561545773399076318560221173734215703610924057158101731263882232550297741e18"),
      T("4.3016893602106215864771434464025735547192956887049374680649926707919814241961779812200280749930256501997849507695395125441756421661413154730888574483309057229943886742437071251707738990393977398403536175642762242808350076543018009682725019125106175929448866428526984370017465117236484653179596869643117790492866002064306593104169410537341890174831622159415936125041593936992634719906123727028419057537e24"),
      T("4.4608685929681360001024935791890661655506049487122331222491789265929503651540405036031990380918459104583255735620288691363060079360758406339887417913286769718423759522832754263499878135869223253358698774066131403822428286318351390574838877307934317251880890827523325360658275060099119902102399714992704146743744108968362755624325107486994088414126705458507082103811086372240878942983212662081104875997e31"),
      T("3.4181315955816806472569357441100390029536003312981931954091744304974491527743599822230006760631204302243855667216955365986192324833652299336285826148922073950348547795494738267861098328516497599288314822606511466743212319770180141969147554023326883651348621187276823849839283609071336923316655316828855943689100621619083822127788284160652232283630351386798636794979234576432977468152969056493038423561e39"),
      T("1.9352946282727908101414530212785249763640776919052480158881659190625166733449770912626442628329346416132299268886589920690636914906717492301836773331460154604580407945460359957380672599434023197425489039882987443681919056322268437224184910074985583829184831034293865504101338027818555871946080687710035062238789949143319550108801094190098446234092310048150477274502060870736716324117412815209633124145e48"),
      T("8.0964449511890098565841496436016431651692307764702784234901741408135381374668439020986470675941110923614446905696410406066640351065195237123718468440597743167713019447544827353458477844468727834630038609140168354634397475741840053079910210908251252223665806813131724262334693137656218010287981601097259534068903471812189212459231851835393208367369054618963204727992168556204168791513644815218096463093e57"),
      T("2.5028257092625174549175008952222569141816383637904981644379473858250736896174216539673733521627607209322019413420937570273676341726636306931304501320694017061891400181233108050930610234076339285157392030024769366663118692571469493256243952018705693924919037621083041696227375589264811876761430035546270312014570431860268644276406457398485042029556392894799022733858611415899182421526634018060028309384e68"),
      T("5.7168370213792649967466315312864179662895170192695050789061362839510836418124645968032989149068311018994324517420345278843446068634292140996241291031113395887824145000873531937856827299256489358571593850210528248202703396455363364446996158929674989959483681393263782486430231288067231095140919741928337466492665857902913114664767450432510739209971738097074002526312039248809036478310948111740897528204e79"),
      T("9.6487261169670031207955841899729386502708125098394777808615183927342163909284025992243201020435915122698808649711566042372911206942311277943247994427354130507790526857797833309691667375441761513692598664419973302444660838882173718713387158013802112502169254860961105745895124415352002289485483908952674562396552790441656755711709645516914188860464353624992313010889765422981069429049436524222321550149e91"),
      T("1.2032977660238608232537005158851668311089986235965463249220377778638489972355974848209035082333822309902237165042868213438627625544096344578102199846440476859557339736747791529782018329078191477783605471526120462726353510147373798347292650122930289404816748193194907382572774906323766342758092979989633448828636445074016110331338699464788279882402189027828261039788079556739180915346692779065476431369e105"),
      T("1.1088306081278288754492401130897590262404571813281460605683836139669281218442501421935533170636990866165181664561596333701204545493730707210930818738817252706131805203538144119244917164949716209095542194899833868499263375700313934257155600824601418042452138211549248837967344874095248283887929145923103153332810091693393888809653081365270947112297406471162377655179657693898463736926911943490619163092e119"),
      T("7.5499880591625965663868042832675300901799245732418501707646792135512053284835138294796976048691668315442427834949618514094329533376442442492757936744857569785450769927581802961191319878260712808001736830227501518832554201816224207300614310712430470538022948957433004823102746037654096845266998518623332118892916505020627868405618942429551700207476696585635930562973459491424179233918050890206232214765e133"),
      T("3.798536358006797624025033016530070695826982685154937173246022092345982280900791849578041210970037835270398289956157015064696375146357207576854029748413680946201805214954504282866534528711715039215051307866373994662368105368505465037259587291440042344663580680646178313958620437868058550744621854406871361710599007951099013146571208384054250556080476992977623024059268095813712424244902009427293468485e149"),
      T("1.4121319341572581270215359848706630542776633675711529687593487346259283960708095601494823112486631023721124235640943167173029348028743563902367757599140008654691320430919753414890689949599421028277624880392344132646738394546195638261279687543208503932172926275294218429086816560213399180179494004109164546844899632385177835442946174653663068675983237955855108059376913611877439522917217336109804190399e166"),
      T("3.8790307719997974510664339744260233373881096199933152202662556556779783775106563986911859526413282055258612522499767709123313205863879946518297779104337686883587019222829967005608205535314284003183828513113021722123872387036435113517356676447376715595408179555267871947671679098986651665719279348025058713817796876795915844151719103197410787508530261619841035613531487094949084263218956635085585632719e183"),
      T("7.8733605373835840397434523264038598405672829925651165847065668324385430746087633348848905637835428739401439679896923081980364912472282573695612463537585283007941057172128277340402716645674443632827653710173742423648839359547777694778576675604645880219833375227941998426325886558435214355022240854563558864080627758653439429917072753785194675103766900514602432580639079224631229479607396935864512990879e201"),
      T("1.1808262995038900942517891457926200063018079695348469762725520377876370005771518954251015338402886097689762895044056273430051256244413916763438966705458118354189107806216991150264176024521937328179762640422127608560103802431672144866013216405157197709788484197720057702118788168789816074560208078260433548283881535909071116553897893659656781376448427981358955547508806938614921874867135186509274509121e221"),
      T("1.3085817499987842655130548827168955655838432140245228169691892267707778790498773914833199368916114043966197329562444577848635313938483757629541576533880917215885485474416704968999200090496252044959849927443732134176975867869986011315975625868009065373046224716063168977788103866885720471095547385342868632018951910603936835789387464412366605713487321530237148912677199033012777178113821791621549557963e241"),
      T("1.0715308148006899161903881353829644069217121138682658034413051575604561649576261428568888094218620444635013220705511245290719605273316790249367622122178650529000528086055415007045458486410501636380119413632657994999412652188430063128470336817401482172580366374079331295129200936246446347832380606353293858222758687479612927181530236387227215663399410099251455256898414199913458340065553949424990477448e262"),
      T("6.483319651006309502237640505955012384293570932602353784849377890534620180296272226076424490097577093511886503973590409376477611667988893542117173598716788837179265384921201772013611631892729250835822804494742316330406688475091973437669111728949960922002370308207819760146543720499389938855072810566961589413895110830251224194598788696990065693705615156654866578134664648091752361824241438921952031149e283"),
      T("2.8985391304542768293172709775230767981477721528885408305355619530690119426207269563049756824939397157221877775531212262059946098575425050827283362457005503261796116156917077778477251551070762614233325253060283603452216492681531839154649232080928787066338399915850327381614672456102374248950210248266796072457623370079195574322846594267768883120374288952014885152055438195794090975578878933873824774214e306"),
      T("9.57524433627083921372674145950563946532138741951042299439035158875449060589509856903496678820625880407684156184675763001790613289835869844325821965070261880894138207436003366195024403902162467929095155787852409710735775347490909311196315332711680552044467458169615366116872469435840608534489425322247278926672059747911266981024366989976214521515026692183039600169984107883592297128416659318858313127e329"),
      T("2.3372734503362369375381009524197350830316472034721759761797536237738670471009423543542251572488229045699598160834162677357730620072441755506075897500940629883044875771104686291523502165266242030847074909362622098365719455332359938746138629161304717385265309980898079489959955157644566232440805137701071311495653330606071611331941246434767948905863368638163788562679785940566685500460815077065003612487e354"),
      T("4.2155879126937199240969909448599186868484717887298729605150033299123534992857332918168135230843738695925698383815575417820480732378749635394939513838137876524333991937836847074991505476867647762082587225838063325020413513077128321581439429001485977751765798011101092072613053687422983352140468569171564773941232256057064161142341661775359191159220450305300322654184921617310753474842253496677498824723e379"),
      T("5.6181811613375701248970224378256740494692066242437602652469740512738297599235414593999616891945156186827736326184687322137498447792007445397397290336810468925670064733464757082986791232916898141597610692740388799796632396708149027243436859752526805112778790645096555770227809873695589969805678601106157556386974221647669590827712353133603091803570183764883405340587430017053183637835511899658145649708e405"),
      T("5.532511069282205350923830187073466127274584467195468607886763750877294392993663821432158885753563495238131394373865428654052604326264330104646257659760161386620716716703631608643312613245804625511813964275109451513736558514977338129201153666764317441936156609643185133981728847167450887861106642311329612564652645663234240748195490808151911497393974690166034839217817023634217121406163178148652748479e432"),
      T("4.0256666306761331240653217136731531623017017695713942917027851762705346357330788586411431378972009980532310757689380174461664677676028378924382554201434975574729861177781849023768222381429947872325368088023224591306630434887529215459580760863075907686248521168590309636468448648513752893851767315693469638980874648457114335557202115472595647478331668869318302753802858726588719006447471192697846325955e460"),
      T("2.1644237346681663424601781769159797919834245365230735589058796985974745594485988855971413936820871935714602237643458356241187573307428309041919648027960168541647193436225977495680484218384107820095589356463058222584008532497069179993678533431131233629312850771528970443634604290143149079209513868130585713006080733488491160321145735562062411305931183571279530201672366980412430529846635995189699318073e489"),
      T("8.5987580981195983662047247216936066485731760315371506386077056691409579856014763032619539539935299716110411688793466397984311640631361934500807639285587334983206556915704635831992012926186843826981296831658998834850783404713050829093753126189556625095994621605300047199962332098857236359801681157419606676412198783092816364336047306243999363335004760439115355072350465422891365411868472688286678516314e518"),
      T("2.5241673163187127276134610716954724162270290228773641734420864618245211926017624829840685860130579257772126398622324109858115624706486522844752512951837805396709793171502497523431473021570806024043139443284538862368635312799539108264084028032731295487282188616820261689634926427135060887942797635147693849950058672753458576476491733064455826768562371858057444914175251596852571637211466017938478085247e549"),
      T("5.475067911823387661325942057081957044927796274441278042805014835144678321092623034147031518807063234976073102574257079170283458172046752719724152941316842521196069804425876507927418423409523739261726681120662097159943049401039490818332686968135012747332468921142470970507219403290422458185430415836291605355383658657658638112408092789126678938878667507151950931633694006471359998448912249374833586727e580"),
      T("8.7750549689950256776639468724574158629603320014390275681028674550826357080136422399476213432791376656222763800628593282303459051561266270006921840049305819767639184391149913915312831894296821356222752594264134130151457242713539248421883837353442181724530706933220158507240760325182068001553294949268596178418634164323874971937997072367419479635154591248667559627811893588163238012665671798461211917208e612"),
      T("1.0392000158337773273751156576416024664653679689973856373456304843339302977923254238376497044027728158058903302390909588333829463843362779584402914847447592731182614369968957680281500946805571235013941407979569788567794900810257154433592958167545186687137810101848000107335074486050959387974516414654638879740966175786016492797845169374594168995878543584318334800124941205910589727264397237600733483158e646"),
      T("9.0936326753636727240574546678839170665019169110943878894933093211555976995701468041449327370073681898690638466136204694745206283652338526673125958055131610409923286526192661778126811265116493171283319361595267283588121098349703951929669281966675596890266483864217591555707552765565756842701056144290075867893520379419521775913047964393758374891516340929062076304350159966063972713118995033247759001609e679"),
      T("5.8798281636930489964162009429009257867906792508058801627042121953599912951265315933723440185825519080102988056836911095299854840387008575164090793635997912930561430335216151607097220208013034399895832350235280120270626904356196935166701773768680311063264380891331021514518757839220818506905997847228783439015252768055166165941582030353226255576433910936297965207260585437762430381969160714956727596198e714"),
      T("2.8091881292911108404345975896815558958477835260737794579417284512413473388968057587088555041266297486841923628702282019643659456724373332519583025947015025975126598748630623031951723754960589046233996595466021913942587558326660593063197905288573353559106884645285531497626940379800500474282446929237914568534665868703742731713632349090897884403966643055728471509474896855575286123275564417626861566706e750"),
      T("9.917129372597671132067673866739246238179742417231064062960232866725337575281938597212073697168000155027158148165861617400080837699968785505107579831803685516054837447325150388867488754170677228096524224392410232206238263933144338637103531441623303187445874039234973380151391274490746625993568552049954630793219419614845431626975962881182662815760423226111647056071831411664335144052772436215105801395e786"),
      T("2.5869027163543111121878679987081647715187872826677398475096738640583659800068967379551376322170347537454918190603891312949716382621902484616361664158953484778255247083652726854621059785392022847887382779010079407502679229021085320675903109573769331277413372272363218896397965662581357886739691376204316908974081821980432178065394228926767529685562155837452626029223937027004015040825450642409597700449e824"),
      T("4.9861251931207080923785686798881789193813879610842675205361210155894774686328710893906543682447029206928934967525495260314937837003448878215156341411477636831113484416124080974502217578408248150338565305116223944900839866528622960352723938548713319425798453345402992146078868053263606234074443024155243450623634720912438841022969909473424559262711669905282193529250216454066716533180418518228387188393e862"),
      T("7.1012569014339068241101751233953234216522840280342406520909288232012799547871960723719836516359548198842749536961644100550279020276709043358260853581760590386456213180291689322352732545965831405519844109680619067101311180959399339922706596098526969148981173519865139508665631317310424178378833370605922449094745510812618563813537347841030916512147874232760564378443782164868016244561788356251308121716e901"),
      T("7.4730215360486642135431754747074885377840195683583018254892502245011973712084221116813364423492802080799768174534590613188275471080608467087354983850284805514875889145266688973752185071777341375422809910165581997555433091939959406569831183459872344778707098094941193489061532160249775856426569696127193453339548371679229676272663084782830276508737129506676031759345288056484158647796152349867328841634e941"),
      T("5.8109375364209112227579654658730977030869454388607076903639465992296616832002964138000947668837140543325908222688655359602408511410663722770167244801973012245657865182739637159804595049180263175014778215232564251739259624759589953677661356104554831551073263668188283861123521688445132164147762321111597028523130093864153999974376790494383016372210442340324038686843345053322425194077414241243050491297e982"),
      T("3.33875955701899627718146291382268063073604182131575843695486667154496711979350813988644889979275310892951143249901398447859083674739840084454465850475774696325142148671937407108540250845900941142800157345665761403930889797424808979569550325271558518404559007551625637761142662107757913763221912282957681784053564387104062317729788737215450574233690655931888608424916152893688106181220341997128198692e1024"),
      T("1.4174672877823334709610117319768830739080734407353905145632612088824955720198734996604261250019291955883620333545750761619015467840567122066622229379056280064206319780047687015558007624774062399477328822231085767309831266032616053065858739373818651687128093335640388513396191118537181280334430292439188737524362269789272308905723812818882228503013875816702686587035844437102478263525616196832018321602e1067"),
      T("4.4466189016791091516801723880812533528438597080549410911235655611382010503145789286158745555771483577943662768773465284793798720178177605712848440200402906836390133865748188969184005230383247111166918721449908133920663776952786683837038180436264738937354101153867171804315769471050303182129269442292354388037298125177941217926845803005587166270803697433886463469168814941555804311717400657004050157245e1110"),
   }};

   T eg = "5.77215664901532860606512090082402431042159335939923598805767234884867726777664670936947063291746749514631447249807082480960504014486542836224173997644923536253500333742937337737673942792595258247094916008735203948165670853233151776611528621199501507984793745085705740029921354786146694029604325421519e-1";

   unsigned max_err = 0;
   for(unsigned k = 0; k < data.size(); k++)
   {
      const T x = eg + k;
      T val = boost::multiprecision::sinh(x * x);
      T e = relative_error(val, data[k]);
      unsigned err = e.template convert_to<unsigned>();
      if(err > max_err)
         max_err = err;
      val = boost::multiprecision::sinh(-x * x);
      e = relative_error(val, T(-data[k]));
      err = e.template convert_to<unsigned>();
      if(err > max_err)
         max_err = err;
   }

   boost::array<T, 50> small_values = 
   {{
      "8.223167319358299807036616344469138485821440027829633696917375433348917938654659351596020080036406671343718039863220496616e-01",
      "2.526123168081683079141251505420579055197542874276608074880949653019810769068593790606537020961198741487692473633089323967e-01",
      "8.342981744595282037256218647969712476322487890550784823763249893556153270975172951404094950587944959561849750490537201329e-02",
      "2.778135016068299789938671680845480653984976507019542653788637161116587306168290886761259072846829249121589698206609261524e-02",
      "9.259391565199916442789400306996794489540862711193761818262415211084389468754315525525896238827358889826875006042447587516e-03",
      "3.086424653287772358219607529932097884435043040527155440187640095572710676452654803730003577747633690318001961509535020849e-03",
      "1.028806765851002064810061084014826478832745077469708149635730407866217436751337520417458090265791086156438275231514030381e-03",
      "3.429355348425226988441198390119109217716503769838753365112550442738406326637684639052252898314646892490045395290022292013e-04",
      "1.143118429558603374406653541544292690548937361618336125287018361332072426474632105217297150810234138626767253281422813482e-04",
      "3.810394757818873406266877296641684693312194735341898368873067089928172619067423751257049691985638480762032673977695116880e-05",
      "1.270131585666421832817527834137477593266387525701388601975733237436369505733715799310429349744168792375082834509467436523e-05",
      "4.233771952120219947940459634636576539101577724347428305072378100562649548884420218224692461748739725090626754420296122389e-06",
      "1.411257317369659013704209000288436132710449162963127340562961271337242582661013580874165903770246169179192268836124421074e-06",
      "4.704191057897475365825409916786898392364235667906752767514580467152163619657508910797742266406961516358439252434955007668e-07",
      "1.568063685965773714045928492719360014894368531987759414833778466374819836545157375950693756664550256136222396871173634254e-07",
      "5.226878953219226673524993193392503058475862017726848548717100658392470633650387274004511940515056405069137033934323251644e-08",
      "1.742292984406408185991240874995689487745140228031202510923711784729440494088066989430128101759261047316736074663327672115e-08",
      "5.807643281354693692124967044009687283114597355717062156493618245876910131607338183944830908381903728560328284173507220743e-09",
      "1.935881093784897887701686451485601671131342930785061493703969418728524594573922282309665275558709040519461560600768780392e-09",
      "6.452936979282992955422916851920785543106383715381924626175995859924351552325880931187614903984801793287071578640505194508e-10",
      "2.150978993094330985008279519046512957825521218238790792201835497215534851989750722105234826300738623838446309250309905466e-10",
      "7.169929976981103283311786261663531258230547972690500493476881079295129579131280734024784107219045379345460886663104148486e-11",
      "2.389976658993701094435441884684454421835327948893136184573938864819002944442339456827931472237274353903634036758669394620e-11",
      "7.966588863312336981450798799860506345287566898810744342680146925029151178981033890759916168189916177504592939240995619757e-12",
      "2.655529621104112327150241298135440075805848488054800577703768668100658036999584228451100239039042920681377381394421710121e-12",
      "8.851765403680374423834128412864530361591097252230621965426275532533242581680245794741067906285298655116802944992368126680e-13",
      "2.950588467893458141278042461784956914687338675140497707333871358819185395356569206661450997145748756956497959702280685427e-13",
      "9.835294892978193804260141412430145318398649753331401112621871794012928366988233744354238387090649589382104704221708773516e-14",
      "3.278431630992731268086713799445120869198593899364655036314007566906378666339665297288092596796135684816883503781385164489e-14",
      "1.092810543664243756028904599641030626636532928735904320784337625844108091213506619051042206148385975354700234586478575025e-14",
      "3.642701812214145853429681998738987398752764686754626492252324567456938623579239392678142797020213493844816454129960310753e-15",
      "1.214233937404715284476560666243942169089106312534317920490462975351305354471020532764015606315872085933262687299655265697e-15",
      "4.047446458015717614921868887478923169619805517194433471908835726595116905187672132801369948377551282604828733616045843751e-16",
      "1.349148819338572538307289629159608313551890152969010184597042496758528297346351553643241208769191557898925543369605617734e-16",
      "4.497162731128575127690965430532015584807024576774799020494128293451281927637267192489558050090835454302448780391749096414e-17",
      "1.499054243709525042563655143510671412452985626833998379862387948592418229228808284088934491020852037924756758483008288052e-17",
      "4.996847479031750141878850478368904541825005460277179305602161748681654262243578435201096986093377131577325573917436618470e-18",
      "1.665615826343916713959616826122968174447164290616980189746184851537351248309665330601503343215376981550822569162631313560e-18",
      "5.552052754479722379865389420409893912541965834349657578615232567585047309856390957625702896178052275806406957076143469634e-19",
      "1.850684251493240793288463140136631304096139902769381795814754672989850701401641374814254071564872119933498619234778448524e-19",
      "6.168947504977469310961543800455437680289164351695283493312025632359317744715643192414807145394613572397590534364339391526e-20",
      "2.056315834992489770320514600151812560095228784236601072113743484455321300338926430301421880927367590178440922006775473367e-20",
      "6.854386116641632567735048667172708533650333231531203539518552950777817440179277823487619201513258000884052637516041835420e-21",
      "2.284795372213877522578349555724236177883428507451482660054557452824460619777642844796449091646418601791047308814504431261e-21",
      "7.615984574046258408594498519080787259611422468149787192854095139994568043598766360557598146279482678180281335390895949036e-22",
      "2.538661524682086136198166173026929086537140604567639372655275057673980680372673609490963070062819520295998328327889923353e-22",
      "8.462205082273620453993887243423096955123801934429554813185698344472203995997708879527322555715697860578416576045982358004e-23",
      "2.820735027424540151331295747807698985041267308484077168753311108116374235508697904826049959781116012127075951788533527897e-23",
      "9.402450091415133837770985826025663283470891027171945709804152456669015193736201020401750153196590359525341207466344738924e-24",
      "3.134150030471711279256995275341887761156963675682933328476437810109959425395050019306074135780459168092270327572635795510e-24",   
   }};

   max_err = 0;
   T v = 0.75;
   for(unsigned k = 0; k < small_values.size(); ++k)
   {
      T val = boost::multiprecision::sinh(v);
      T e = relative_error(val, small_values[k]);
      unsigned err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
      val = boost::multiprecision::sinh(-v);
      e = relative_error(val, T(-small_values[k]));
      err = e.template convert_to<unsigned>();
      if(err > max_err)
      {
         max_err = err;
      }
      v /= 3;
   }

   std::cout << "Max error was: " << max_err << std::endl;
   BOOST_TEST(max_err < 2000);
}


int main()
{
#ifdef TEST_BACKEND
   test<boost::multiprecision::mp_number<boost::multiprecision::concepts::mp_number_backend_float_architype> >();
#endif
#ifdef TEST_MPF_50
   test<boost::multiprecision::mpf_float_50>();
   test<boost::multiprecision::mpf_float_100>();
#endif
#ifdef TEST_MPFR_50
   test<boost::multiprecision::mpfr_float_50>();
   test<boost::multiprecision::mpfr_float_100>();
#endif
#ifdef TEST_CPP_FLOAT
   test<boost::multiprecision::cpp_float_50>();
   test<boost::multiprecision::cpp_float_100>();
#endif
   return boost::report_errors();
}



