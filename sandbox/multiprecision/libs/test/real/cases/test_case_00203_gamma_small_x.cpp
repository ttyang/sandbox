
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
    class TestCase_case_00203_gamma_small_x : public TestCaseReal
    {
    public:
      TestCase_case_00203_gamma_small_x() { }
      virtual ~TestCase_case_00203_gamma_small_x() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00203_gamma_small_x");
        return str;
      }
      virtual void mp_float_test(std::vector<mp_float>& data) const
      {
        data.resize(51u);
        static const mp_float fifty_three = mp_float(53);
        for(boost::int32_t k = static_cast<boost::int32_t>(0); k < static_cast<boost::int32_t>(data.size()); k++)
        {
          data[static_cast<std::size_t>(k)] = boost::multiprecision::gamma(boost::multiprecision::third() + (k / fifty_three));
        }

      }
      virtual const std::vector<mp_float>& control_data(void) const
      {
        static const boost::array<mp_float, 51u> a =
        {{
           mp_float("2.6789385347077476336556929409746776441286893779573011009504283275904176101677438195409828890411887894191590492000722633357190845695044722599777133677084697681672898230500032183425503222471569418175554499527287843947794413057658284016123191415964665260337275840205806355139432410320158394153827008552405210323387989550693638926386839167072816915423096273318811864774965222910556444090780096341646353274"),
           mp_float("2.5296056905617796055023220367269139209359448814928339100592493419870407085512504166450694794031244540343320637387482441627630442266011865800428106855961544667231474619083731085180556484110309243968076706840774301088338616307658375772058335970485785343174817661898645704024384148126673931301528790225314594822903317949279136489395809092918472237391428189577658119999957945587705045814105700564576100231"),
           mp_float("2.3963887168582965765394180141339788508764219384897922463560738487227880203303677974153653918899292733296750747966000516794834442116537527049714656116623150764488400086912634425923573592335556991985379753931318928726701166457659884165833808458851325837087809663070578941463191152422934095741998773947002626526549486560677413190716958674854139355803156513741210584142206971346731750185971387847278762272"),
           mp_float("2.2769269220707411404098824789511028109960805426969209402384299953640837709588816024365833692089872602102800253102843232615323022889715680516973754138570480236132286523755144803566121559030809296084293103003571674839293830836657631512899108803843778146026654975534710966967640900215374985209007459384288818920543903412505632630802504503123307702023737070309432674923096232826075493570374825055900333351"),
           mp_float("2.1692970184653054875337487830612293501295406944111390724740702789263706811992013522399140952845428708330247108002145522935856490996570635136834723937631672726845754533807329500454557304330708344854663159596161852843228921086150889835567411372009666477928141076733927592584245546597344093149896213555814095993694010432930998020503670258800954793377220936961311237903284785157321722810558193302100216002"),
           mp_float("2.0719165459502912270612135556365163626832842439586331681987165125298261817507137316116979239777371327832826166972169503044979088623180590952238250997134187361853471114806271580926326049280939384862920331729685077202416430911575148535565160144732775596870304864948195401923880196494160221779524291324096177441003496034362159161242136165985427510213138152486749678546329640319894139292301949132315162941"),
           mp_float("1.9834717872408587166422389842404987135360095716841378595852239699687847867321193115701787340590825524916330949152323363466116321671803224113218608229162898516047318297834872212374917336610612622128387159113561705903032628970686620014539282698225419305901736391679372262326933704660950910476708476348691280052410275201788602701909544556627227695738983872166582538824689218125000833454491785976269295647"),
           mp_float("1.9028632234828382329493502437080288075235297614758063043280699598436097611246143215013484065236769632381041799665640842379307035262949725358933760964229440706897156400952433512582566166946427384324751599075886715381616162669661413368605056151232675181648758761902523922957374685135549743911216229540137839548495020143138532833612292342348595356664535308888481048256264934167789024444287782655109044797"),
           mp_float("1.8291637460410649497785084904713231552569444904076184820530348100408541293602531380213256087549893266624804551974546912890534440041479490487115129425032822278015168608998246696279596351673792942752136295850297876813008713045535790554362205275623491333446606106208077732287528252972777685783357069385757399340869615014516820768090958213021302675426951565219823952704978517793785321090008263088956491242"),
           mp_float("1.7615862754982323202369914758099513380488760786216629634057219873688252137452742993929087505966449489826071051848906229621200376618580036531644135810582947569189444649393102814852156182217596427711651245842187277434776082690260607540690140226008824274199993541133433631171788524075909136763267826099111117868992413688985316592308082522789250708870156227527394997205565359487665509068511187414632660971"),
           mp_float("1.6994584073271708545479049555097123721255622380007715476209611601826970848159020790382047560868385527239924202230236718103391170434927616494803941068430548594602874021162509906080111429553676998373776479481884727672640484652083141558359753526340458414367444096264046409739878876246042698742979526354611917085152990371087277375332025384260680155335820969031849552069366729356087352416025952171731671858"),
           mp_float("1.6422023680737494841353609707446395691614054731621010471104607585990466118060473647114859940499668080748859164832875582770497176153113062900974680182477349207019292375528350267316244310656450298926312659047429592397297279409085078430956923489834347132976829006027245848237307451185747182988242209236409102699337488609479528384991017441347921666180702582280892504991871941775334982149273737133248941021"),
           mp_float("1.5893190287060991791970105170244193134398768558130971931013190455123027391802900667942916931929172167500650616164568332070540541282323880668222789186404953702664529284818546486672745911474674484658476636137031776116611014027105669252058789725571907345789637006461703198701497204564942131064386055041362340411042890504924948190239673037663477772334793276561553980509209009951195011464660597879842316814"),
           mp_float("1.5403750487737548270120045950380655933045245425190104407939669193811552909909074571356883325024374613489141788144358778024461386100047099649675067356160599000173094592176930181284074595171071259698516138558155906931492165324078370559102261294707835893241822423557723358250280884482241141111321488811245004153870775913063649385244298859870874069454786472601852887431428912627346926817235714687632090065"),
           mp_float("1.4949924590718716483349806827374363461003964479151716558583332941902494199287498875428227001298786034849291386809645248363044123552548592259216447655648352011026498072537949643034661042869859677563276224063206605071408511365441592268250807463627182052958719938168744814000735414693090557294152812578041480032761063523027196526153438528009824120889083707808515133996507048222440462623030003911535036975"),
           mp_float("1.4528401600711286469356121148768430088630774927618579717876437653167689268019451436457671234091171758734977991058679568837486331285848177365523317749778051846666627666793340088567078928680995788137313271261941587702160515497902014744669242448732087548592460756277813512994701524258736576587647576716516819494912232865976470457030424715486514436062354471467905311647140352065234031217964404272233142018"),
           mp_float("1.4136269376078543281668082578725272597283118055306942655337812967938200035774670289940349283398904717459542347928672714324759612151755854571762198107779964721009799076855591214378016007426825335986670698038907266048507041086869016681418726941461797972680813291488698524083914000290401144757307002153755233796979939711556650251939938404790951211479028956666015786029985302925430526892994181636363065416"),
           mp_float("1.3770956893079427469274265630199865330642984827938811310495025366005377743780305748240023713610551575337253290938685583992699974201637412066598166974475858059475162410401978408824788298009561814881558015623764087631561846307317139061045103227612179673448118460628526188685998267204285937724854596873044513287753683347992060271611597225072980558108340931709808933409583449044839922431913163397342076964"),
           mp_float("1.3430186239859019565447299523719722298137824478447814416920453241643528199753364318479779317756852500378319861010463374876260706706570942472861075768510550604470908779436376674426850418118126520918796226090060679957523028877735767474199954001887514528264565781147934685946348158431423852399620677798650975198969524157953358842285258463841627796306225906038643387185816538973244133106152042859861824403"),
           mp_float("1.311193248147409529865012329310571523427880029768457253316900605480155264616490085794204868534160249592803792087722280253280639553656097959028587359391093356033489121909015586773804887886075973129571372688852135066261208256302974078614502480604095548608196087512160880258928059930446935357561944207580848013011212332753790749394765102575353868312917231809543992862680654400091587931655744771790320151"),
           mp_float("1.2814389932118026641639281998055732513148544441325888577195087608374878322339384489075226251440540211324893986307326610328524042290085572467084699368820142923136542473792984943299695058274307927152876342704336285137575678634618013478361645597006972037232216239335236111607587928975198037327163611349313549821535900183290382626833953514197065203608294203171441103330385421035272418371131071449144201048"),
           mp_float("1.2535943673667637766591461028333873066787234693396303774999337263792225061749396514787585924934212560587765746836396292496312075496418492477674555282635092960468346132792065087577580885989296395996768921813798022461170022375664591597876822852486943288180917283614248531226291685988076357602827744281578957786200050957936906051393178134534758923859103386321940385406557202182751588006948821222570399304"),
           mp_float("1.2275145393885523164353115660144311537644264809468251809901476411206374178589627451249942010025145688566673529587541743461870107540428414746832875895386999728639251776107156594136679153984442902346757087949517753699443248316641486426016618389288571242915241745397805248134692477370683191668457671955961066317260420758895996927584180553456944220118891168844231665924760309345321566462692118597465333281"),
           mp_float("1.2030692799980848382916006705817432489818792175556924634788820910999316700806012877924958708931631009429026295130030993167271006043124711134791072749923688529377813687770778773265942142053894214733851181787355323230870636413562883149017595743631676673309845296418304640970831193281867545616826623577442559776621314441203415635177669543264237604819044229894538164386882196749628534234183891325548878216"),
           mp_float("1.1801412006202528342884029040525191720942936254766350506423817056022674975843148675884937563138520495001294445343039361688211609544003681235642645796147860739577069459470481516284110983311329838778200199082671148173803479170666810215735188693817753680720102469391043783996032202755773675813060971675530857194053030723889698533510777664134927701089114031364607791092677418535345962419222513339179448791"),
           mp_float("1.1586242406945673346159948183091323292426893172280160664963866468577282080252660520816168221099127228621402172991142609002454998308674935256334185046443740145949490975227757852276057201078083688909062772540995116365414223789196081736950765503020687317663792622152634098947505714635619646798281905139946448436513465483044785931430408782851413222450839320894635245604765274891201052223513536425362937288"),
           mp_float("1.138422363640367641933142616307468726165435470469650315363577775901186075117963610983193180677412736008220210530831256655455473450845568297791504074970709510446981565476573049210249195956674756863502664297335127861514522982968032336505433074708039557576142942969323768283061828943511981333313381331723764438792000300790820215609752755454889312448956837141003104890641293913162451740430539139951765507"),
           mp_float("1.1194484287301273750515114044410412576573383435032624171582667414192842190488242819327140022712878440472979685299385152312550302054185309739049793306607984806913133691193692650961639739709009584686686779539364855935023439747199080841490527768254874110961256748187040258333850919905180228342625715397406925659720667626659207523714953800572272029141579851945376524632043308889902934536428147772124614483"),
           mp_float("1.1016232118651033768090941639634292803824576035125626898330763325372736921097158619763946175470152344548856470881505322865977847707971665029631393008713754779458369765530737959392152158430324144128904030420269804570555577893196988322912484746136158685460139136081668062276184791026464525750056984838970229069999955519251580372548263437208378993802433649418934936136791411586764216175939143532242000297"),
           mp_float("1.0848745528807955646408565230413287576174554387072497914562370089663097215098749543965657830937167127663751344666121031220428196618364523599814388615032847821083194335000965460581709791602310894399619250759040655320153655160227116823681040489902008529856411362136562376630085399537601952806028281787054216562054537280753381049047816948542008923203374381827979422503040574046347084150421285208031008257"),
           mp_float("1.0691366107677938743846164860005282246372428700325733426315262386711437563851725806796171025131740248626108276333891076947171841797931332768923187865146035049171683534755907096213116620778181672979884008089431484715461879371146814350534968077628091390538972161079747496764084890245725453889069724548919731422053465829560185024002239431972538531388474413437533657388455415450460000660409082278610754529"),
           mp_float("1.0543492112564305759808774433746607922711818094880621325141600209556415644388350179622509451021473727460017742183219326000995479220071821181536090091169149928275936816652890138105622614562667096349128922496852180150392899874182401077917179157824335230738203141751931021206242332280551172117047019872400812732644445716693102962080742487766046064958384887902628925401953227176186554279128256294146328312"),
           mp_float("1.0404572737212455216366928962252026829855827707874653169657184343822413236944791868235966121175720913641359830896347501924195566627117899422964524538159013641739516919578692524943024277238620097572950308503282872511385377642680619936460651477953866689205117681215382688498743700367797796991603851798622369073572016289015255494991751452718245308645328487611201153134544595865500308842024730595376110732"),
           mp_float("1.0274103064232210760873020964507479317148058761281597871307306670217246436304274720125318986469123875725698790652593388358555899479903070070888539725006457848775485940100225506690047714925024527156939003413160517321694635070839491793063368625273044021957849536511760047604994413860322521007395651976108956652557411026936060226256421137865341567600323855979612187088503802179020554315196932098196337075"),
           mp_float("1.0151619608103260209697214402272410051224719159150429586158306741104815774178856545434939312831094721551119933339747803674033866874976535563642624314814425742918616095891240866207928946807802134300945737989036015479302171467275747960988191122416447078070533469874926144255007180037224309550415919869470298372460193880387875730237308594995070731133678676874058933653914184197781767922702957366101521735"),
           mp_float("1.00366963700837584522107571639229366187802161504798453652314332932289112419372773913081687543895008583564829930058342452832710470447564483762469753028758821662277410948669571160428091117221067291411078624167826435671153987096512554502793712647270596085188215787682913514321420579717061329709789040418850588663060519709148496473465993644817497782383506026943229675657818312787680928878757136817665459"),
           mp_float("0.99289413380883135436057444448136922012029941366540581963603356354755295024489263187414574300403216532995245106604341077155588286648793904860682286753504572993571022583055991049391342403616859850363331344821383802739895943997375629711326878537302174476356067850287212712199732059663633118426956107203233916511634618975515090250561798601063447171067199191353465011470728575367504237424437567292888975074"),
           mp_float("0.9827993374412593590711881018510769158881377926811281452554719358456164135456593495141483514543663947166119193613005420726257604041339712914981555940298481808862230596810308749079623182025169439022159620044069032254570285950490733748853181555210035716322582094947219019628793033406555076871364402029301815331385390374302014368627359897301877340527282829184323882439331791927657944135617975037803275108"),
           mp_float("0.97335194424054349214281897993468546993712269087103006440913989538101284635474178600733367934163394867655935677226335880254798727812040774121240660701486175647278632215414465106398573776068539919601690241992806791764297958702340891478107392238782505253500829470967549738254935530862934256443154308498318771550558357509092760550222686932700565928876386687754738068636338864946253780554223055107140272981"),
           mp_float("0.96452121301058342916813473402085527197119691762487912438297131920426239036746421780597565435318449852018135918974700557369122208327590613942101720664392154796440683295292868873108910057237271474328217315732690869741904635096667970281918656947555575386506969986211960444001478847303256015107439282313080742332986197105239401060835273514082299566764376545020446147165941075282159839862966772888579618362"),
           mp_float("0.95627874346983385414486178675085641871616455895571836585289693451318892719411464057147005935902865838591544652897798628122740345519845310792273812364576795085445214531558968605156822767794303402689954684033195435129924550621428082708593065955431085121976060214146205751807300461356040464923903606022336777823929021503919818877878620419896455040558631778301116727344073827807474648524734262511263416188"),
           mp_float("0.94859827765803447339134529623051110477405686640302162799592002522833547120972222929920683412204376455132333857739127256997425284407704514411518485592914269149727590553423289886318777393866310796880083183967076770351742925300341077096274282247773089150711053530711895779092118739421071321555758119929170304725714147861318954167341296690537225165598870540931587193671046949526928703500386872547066186623"),
           mp_float("0.94145552160289587093269445005684881057041577251288996803620541403189957587500195624869881429271305837288441176868523327442628350811907160182099559603609348745552626484921794894455504719386299717480148106651410916276481219577863133011378210207066589008188213647841390503082793468300402313585961471891204713826420484080620721176265387772277159308681333418814666527213998138614270710451089314708785603208"),
           mp_float("0.93482798490263432436480530488204410859860069026220007834204768766025597880093215342674734180903007006026800010100639665573703514253017212915834146631659495255076034508118722368249484273147708939378331595497797994365334716586174849024064285595707025448106548814254185551306159851050526623262123880137122352792416283365525734333026989821620266091894340014455095529788104630676710646005437968039808665788"),
           mp_float("0.92869483618519825578018744682106784081956209789549425814924001461008803353510655075924450896494994781936243582567191404525061506382329211318466032181576901366671768114494079974919099750305251315066144108086950608679587578040481970318593964527068979627414493043935490261044008216601413302694251377622705949534612454524584028311966589160212189381368447064779716675223311842880154351646758615931608788596"),
           mp_float("0.92303677266613162418257382291519456508028536080141791492828317597442798830560084886763269183858116593434325442677026583489330549983905144044153394660563856741184375240049441787530223055398823359452043331938268409422462932642812346773525786611607232455129258694907129791873077795146359446383882763753068355088996018795011602395147289347112763581801620204698371611369706271813786004169839490824189751506"),
           mp_float("0.91783590225116709987301890678103283987295247339616036330449546469029311011196493223833392502305218466417853158806244233255093475148575344350435270963378219596567513091152883505819113991489064893626942360918898180551911561245373492106412123634570894617688916395312871120695504822934222865886215608259193418696136556261240375607327940011767094050171781107980789653576509018109273283622974815814258875492"),
           mp_float("0.91307563682255337306659597478126875011811051343665543898866107990182277158289915331298590885085642423753910452110702795217115796281621070858410079938671046873853685403602002326193083218204080862072295704773814858806757981274278536035833854445929915890575160977215153584915383263535754344281396361249397611935645741138409207796943418962720734488873990304658529769318468667276858792892297723601879012123"),
           mp_float("0.90874059551455711701582979411541993166564257495013810309616932362808530447601166788535910809635955577343403148414474782637723366143535832908491293853571651879973166866932032600380498526056688796077950764570643981291060392336671291599391843389182016765531892913000218885104502050637104646911914193350835613215682958711934620670904046980822323182899009297393006417434054557092763056799978722872170864434"),
           mp_float("0.90481651692751578157889316539538566781732627636238488294574626818313069919655093442054068707888115079192981881899580221900311645868432060757216124306438465402872425353909865181360135437264685018641691666157109110206858557121393651574714202275181687644499843547260259742323055121908128111806361646130249851745453526528510762501576789388549073992715829514873427210754052140886231110222325592278297166921"),
           mp_float("0.90129017935458091661077799863429705347259932382380620507653947328199060569709856241103587760763012082212960608341737973253407051517830500323669927711705270754220077779446714982463656616675209707309992686241196240633861909638024775512229077991907576449441601393739053972554557842368322344610275221637038520743639233422865476977181520615688466238719362793873010254162088836220082738535179900011390042026"),
        }};
        static const std::vector<mp_float> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_00203_gamma_small_x(const bool b_write_output)
    {
      return TestCase_case_00203_gamma_small_x().execute(b_write_output);
    }
  }
}
