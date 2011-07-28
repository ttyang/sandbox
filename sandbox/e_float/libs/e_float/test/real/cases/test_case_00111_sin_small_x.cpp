
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
    class TestCase_case_00111_sin_small_x : public TestCaseReal
    {
    public:
      TestCase_case_00111_sin_small_x() { }
      virtual ~TestCase_case_00111_sin_small_x() { }
    private:
      virtual const std::string& name(void) const
      {
        static const std::string str("TestCase_case_00111_sin_small_x");
        return str;
      }
      virtual void e_float_test(std::vector<e_float>& data) const
      {
        data.resize(51u);
        for(INT32 k = static_cast<INT32>(0); k < static_cast<INT32>(data.size()); k++)
        {
          data[static_cast<std::size_t>(k)] = ef::sin((ef::euler_gamma() + k) / 53);
        }
      }
      virtual const std::vector<e_float>& control_data(void) const
      {
        static const std::tr1::array<e_float, 51u> a =
        {{
           e_float("0.010890646307437399028563191160252839599929232814970922208664909237494716181484215717644776933044418903207919912063594159099133490979634344811936925144447725948305353257042599564404885434349760121009797816724142318243738364307036155852011004353462651092012819894667485840322627440332163428546845499107471983896711023161969130462687924045508477090891879273259947713367290982391204265694893491531721581439"),
           e_float("0.029754394000520972141380267705677256353702996169858414168445272181777338962866552847084800544086743338130195210005002660881957584567978770485056322086472328896988088721899728258224129935989180857437073412730903070983582129359565450458299328041955729258476583848159389714290107649243089149974776893563078190705561325124542669960182002956940545214147678093802442811362846262655415145897575707676223535749"),
           e_float("0.04860754948595027759689273751438643634234576398271158524070718139962965653841137425728738193533514318422431877217110239554743968609870039776938201724688048349972662394084789924867267405853696017478160702683117974766657840965270625814482422398422216605490620054574252910928068433847115132429726072853170339113804838625536981361490008602432476302086066307320875870985443111858828925332085101376920451257"),
           e_float("0.067443401266329792365583268418977022587089806595860818790246293104463576184436096833111903064801552379988362224633198052490234517656318474005568709048710308123967082103235230201516378834855764348740505470176912466587139988300259624310153055247378188811239571439869254255368050758213303082097176168650573121101094016896349982672715603054645687782535250201448606757920212668324401846105554332382154705308"),
           e_float("0.086255244004175604199645786226683865650130764638142939010554245919172299560583634262067769465886944689883333394099120765964771092069938753689253686543017871063587988437235057514131760587649504670117933814486942187589706655157340717185354058186603027300571692666150552274324933749082047517987509942119060274537912867956274549119040817359639741746006374702951412541338483858389306953539029174581171144916"),
           e_float("0.10503638090893519164596691292161072193010174143933600597680115817738720676321226654184308409972393036413684625874294713490753271261380987552528236660688624108474124469034444076627315674234385578608111398112242272762722849083801773818689342174907858373883192220827687618321085007917387951532673599267211035785307947515638810735621964273183425401191468313574763898720597251843424536611952986478638938787"),
           e_float("0.12378012612096459891996422671239906394195356627713556749926735466337892925173796651675302282473738808218327028589606894825728784823540605065317506645900565980161901287116410208049542818796994171203890952761651470187834173644651508025088970034800067245131759655003164127161058084682831906406941473650395873577925901419536540828468001386512234321890242266327761400155849351025221609783793228816606096155"),
           e_float("0.14247980709161433833827358255114404185333478069639957369769805221957506649654851981837061160249376538785737485777248817812720592537597263252706422066438137522011148566625861552209380620325080441618503257506798981598559897331754555335688284111417797211888381141445522536739542765207936516297907076923899840216864191777039028622886076254231994264908278499537587536902686114072117102531777746791366147472"),
           e_float("0.16112876695857673825462942280040873226725445145336882995544646098546697397681955191516861690559627281570477802647683153249828731761062718487424104325152088763220776831248566486363299448443795266104568555186977695939803420793575204146124697832793773870449082377964029658283741910741804550762511379894890589132658450368609377005630322641674351408014813725947288936865021810537922503050280596331958949813"),
           e_float("0.17972036691564914131189073707203611766536704952071818203835281740755093560444625679032703078557333645546302532200674729781663838075105196332695024246509042831095553050804767663788014113177991938252225120228302734228632787082072480689719322299247090887229731260135165819595797392665106642595359433094386743214852929965104946276195924300495453775467378376551444126292108291215861133471208854009513721707"),
           e_float("0.19824798857606934571352609051549058593435535174283382080060738672122306773474119459815363636791069253463660528114022041674780565798655265640072669329819802234483545444085426470661233958030668844326674768815456315879868376252722369574694411591080512527683145774214215193268992508938562109669843137270238454905091555179756374512457742554641355319960601765568460966738628365652972463731882673979926092423"),
           e_float("0.2167050363285819704223187876642169717474346025766606244643176750460657731203611217470241676182041675112171974414875203007374497968642376196256262296063879827128970901451226217571636202438144440234868076467587220541438440149682254317134405302648426790500751310485432990930185087578150399032543990173811106465656404530116032387260432178319507278340110997943206401370789106214680733463126804159766688178"),
           e_float("0.23508493968539701289801441539326267060915175918342580386836036980227948313782327655061004506711767031388143537081826986030990557707922203603349984851809173788402101756510017046639631528282698404857654444279509591873678208318484036337040837844539190863615310872984455261973647897667843302241773795592355085118273592671348602240382153223466391512738221253451636183066773121830262978729780866153048605159"),
           e_float("0.2533811556212047542679161173582151227103672187769971543582388259784795155332622779547839459016647290250036005712168909799523370471647322112833886051217950625710683025675691585734514265087749450457714578451290681140064635291501640395753290532318406110106892218388811781561305402570000283806458134435822529043797962340420841850011846648265787470508569124672250211852546600514370101687713861131209463861"),
           e_float("0.27158717090241435065755609312085387589073221253701701142877476904254125053252466469600403650634482409879186635717002370089097070045821182432642232618427944489732133359996899812980722107011126957850576210476679069162561257167921627603536603943342268770727524690332400255408587654094512383349857596775777725888982277559281982571487656535560758087235441872907962373375423740325723506626374882319859924962"),
           e_float("0.28969650440578692965912855479777150523900698183973110358010443581781966348171378962307935462457921708108325003566673849851640304571019200113280406744551445148200341554501141174444530008329262826786160080931309057528673711507934822659456861163197618813727062179453555460400169858233923358238607875306523866767536243361049306545596678120228677505849040202788510059415993219975440657979707947898632705847"),
           e_float("0.30770270942563778634443222550824378057595253208974144909939396933701715445493088586920897452838893301853350676955400357197838773823140696209649573828382477454711986806154497998912926265388494228459988323524548750870702083339285969468391846533348589851520262990720843670148790211009236063622194282315540801467216625666505663699480592080398449845511909092071640909885054719301078547683325662349532658001"),
           e_float("0.32559937596878634249263192973385963275552570142977727375619908690982968889531407133936548327912894149757305868454394002531385820341045863161146695151908269553629121372700695833373968533510661265854738947940689721812230819575490874211279007289828369964583273676393398981064015459284982970048174649094549631109312941188691838118955683939990881732219088392629316401227525790752712758279892546851835776728"),
           e_float("0.34338013303643689435259984865624959352259286039436985939426483729323987764837568376066164703227630278807584950278626035763399164177429894322425866236150336898079573258157833074772287354310049676029566569737995054499018518699450946056626536479822852758163848528920078247789349605898976290484284018984355696648190967701849464571286257873661615051036433297599097073117151941857301740816310919312668936753"),
           e_float("0.36103865089217782674224266392907326208964452822379102503439414768728197653534265911503054023760783622236800804794470785631737993143180071550223728801984904852623160397230839644629077782630949486339104760008566935013234195735777070582106661423219379374522941522832331186147905332977726043795737008218909226025962294880541867964419424128310806148008435847967256901208159302482322730929744194185143496647"),
           e_float("0.37856864331529191294683302986737462527422720295203122486985051910813389831630458742420433021640718832999264813674938157273375290592788753133996741859965258034273428657399863159488519434113093863042179261649202584979828347495161391780592433454809420632605178105958049630938532568156789806946629309375790343585791884755866400295470651281289167454617624179556306285775538273640784278475358303871406797294"),
           e_float("0.3959638698385755489557710011250921602780605301308457595569865098132061251227321128681128349835212212508810246299921462519655630208347321575504292305860152320513799100372630595769065936291506594220617567642210250680560302662459931036815131767702563357378794733903424219866581554015722958062178902473414883933807190920961687912191470152974845756609418554739641361171541363409996648143043979357302190703"),
           e_float("0.41321813796987028521091431473013916161596830805293649687424341688961507413716621591649879163383882641673238540682782626959358955002216003316726344623613626809950993449214457071292961126188761860214007662067345193545393653191742497646193189677890657992964660139924463087072704096969748995358605459064076775540679952182100013584273877612509536257834358450242426357122974687246428904315337788603554112487"),
           e_float("0.43032530539651581726649227346608528709372859200683817125277384462849187532000288969537766724897319030479860713591459932866508254904869456423088312945970943686450425589907227275358186473310644458353392107693439475272544181726520566221333846008220008702070460626739342310039148106649726719665728169819714333172605016313499067227953767878741853545763313707499816244740855778447731454065384788859848319503"),
           e_float("0.44727928217193967651655712666040617006236300257644793444619887007723922383970962870988815495150987337761018019128790177957898245520422485269324604484642139354461290347689315448558082058132330317789105861674569680430563377440355102600184370927625450804550114009478901349833826102470780452480255838220723171955252412104006070322080932915859579006653276371401264439817338080069936810866666557553662506811"),
           e_float("0.46407403288360522126660904671571257203469668709200603873826642103612288853249598361813813213381052968904786566929537791978751985511297321991996818974870946807510786919602279514706154473236597480481149516597293844121405001964448599792635426082163120478756812832932606227610137817312140031064078333902425335570730565173883252754294319888872518149175050583958244086010074110878967984441526026195572046031"),
           e_float("0.48070357880154616464768530714893198018226307768872832018696934136162055774617690112915494983829868655926209174893609677823844628976682666861087174925649829592164380174433963170047900751735818142724368678683601091750819984658303806035572915499999180599872513173096429390456178642478189724903758698238722978406369084171804020040246631229610021517925007543961283845124822740019511921386188934760298241688"),
           e_float("0.49716200000672278683141570737786924159326600032981923078600441023882683095816876734389429898823686013764499093454507915253215528870989821318738227798745591597923864925733083640574132559603114206682739488541451077277291582357627881380008066440685837422009543184722898767087492264154499861112499590934108906196324393034778681622285346845867860458748417916763883649390228287689107774312170267691257606116"),
           e_float("0.51344343749844216224309565441486087365890516381683759696704839526386373494321578458551193514743669178342420835082611868891019193801223760604220552152028015878259509179672236586872004169442377393342941368136686044214656339879518691219516228434732537186028321245942076903928921929607502848888640267094590400556200402256089794954485061564115688273804254406706725374971267431122825004095102239220991848356"),
           e_float("0.52954209528009218542956877037980380998240467111773187487177084701668417706002935457309027480414979338624119758863233287969233845786459113619958146654397106933375312089626001011352424174223416515118670901639015699899005014886945323983797633471828049323917701068414699189471811508040323789047713536270617216249222074877291822920747392986535291960399633972613345908694327479738445245500914715996152461985"),
           e_float("0.54545224242244689926647810432697721723945987179773365856990386707254353534614807468692870318816991084937065603191754270239773531928848863926268254420020634174904439920465735399587679402503040251639815041072160696029528969373711375024524059535996077596844557011786411865071706766713049961515353664484996577751962474564968659755104983468313555304855249829815310291744255989014492588353749587481644931913"),
           e_float("0.56116821510380861353700162760755101727268623115746212675907859515911800480855365905235006799852352328451502804871577600277181740574994973635138803211912076695967558806493981733454148905054449991651227073996616835900542604367257843601995979944175684600136575098939764120745952964355353589317556067474680987527548079297833539998258342242865222215681747969549869015697939554127499557081626950060916329896"),
           e_float("0.57668441862626054773920164705882295031880435874490231795930393597704964539534854834250638055542815083463738683146430082379073149079998953871974990605030531115748567904948229002538680465351816034414085890696196467615521969543006224204433997063527288514443404935419253943724579872472854300703798475966107579038880496698051818375532546368197809806544115496171522444187250876233927302975709248591908972346"),
           e_float("0.59199532940731223634617420193837196766186356068263223313261061480558639436412180991021350240470913092271149633483820904350945127229180169976070379470147429711011056203078210298313829635000565303787641997857930629432231274870246836108452732993007541125359738273485061324228778750531830069944570036169084871305329515261365955383178502917713214334808810726412625844210978481512366368025275438632291862785"),
           e_float("0.60709549694622869462483067245797028399468956070763942538530335526853282815406226053099893555611232739741099281199863420254333016184720313024881100010161759837083928797224725640021095785125988238992410296927225409984765886863313873892022531648958451940083661715815760806237878803609330649695132473889046508160482887768573723088361332267243452286610176948724186843039692112797106039213976473403724518188"),
           e_float("0.62197954576434335539696684219824327976988998993669475584026026679831221725774460365328908947620452777457191790806959938899059379387140391128845696987642418506611453321626607869801717870254836897328796165084605948086983949944714226464644755644542238083403302661596239269476252222614109836597348873471190787660391585694078779921390758232910639208518119325492789999941075221166054973249356136808607130253"),
           e_float("0.6366421773186640485920116318191204083389644098160828009666722635549477083039305904975813615643101060893999315509501318081025137289051787335454356108133761354485193083183997634369795655283340428506642872565827559825155045924936470784378552800563136355526499002558162019410271880717338646318471375684163442601830537613691628498474632262547856029932241457937391840960919415488213025664314613747543749464"),
           e_float("0.65107817188809080279752785471799265973958362274943758073000075578938519480042543196041314945170036193559782763524413154927612489597355144799562963417455961310886431794132437757357185377007718709790504976900339191552944965308823754898079933186431693664015814010551367365293786806527034958873669211570906132849013497458819941168651227792824572805777219160376304646562062564773441718051418178414899683019"),
           e_float("0.6652823904315739978766556052897347198651017349760138699519597733553278561013395851136458951983261597283585391502588949649092379467069209284755289821255744166256794329589771465045421874634188329764638118238723545310838064785644468083837991172367935880462068347034222894524074808990476036821633127927532229213401486467496527893691588255513769781016943243185567913995336109327864083859254466073492381187"),
           e_float("0.67924977641755138662041086036801948989088186294785002709809874961811116536667286127777672928127306388394020078452402417993836722984523906631302047812425809759286220237826357465064765092612104224837992075711035615650942777454297235908308024053950635657488001916036801234116581671119069849133344664024677517075723660642709275823456343659009540444032487248071553674961012055521740306092600444870718199652"),
           e_float("0.69297535762401272778114932738244728669670875114228232862389083194872888693112134130021641463393969624412179768291914405554577080353247136859984307940401373940521815913274464950964347624918449081645304540343160683388727015489772202472645406318288749244334156857814927405528763108558137488794292057315715995191324964500528600378291562277858608403425720078390497455476055579003286296442406491998525563297"),
           e_float("0.70645424790855122905182233963742667718470686911515869065744744473731249895412640632516625097411541437953942564566468313798077366853928608154168668667806938130662439220702019172328936889436324187304262248463334787504456805683070026006307765178787997020889111556678907849442591478755800698808480163225125777511828352357189284217101098738405458071150544253514248561787426067001460586251699075230390564367"),
           e_float("0.71968164894777168289159927814596788937422432901416956306230349431557362414856173295064125294878325237342190029914430775648665560145040598898117000971783978541799092281781000633902779626437866517288284324732827083065703448279654800632624171861777710582293639879819116932680545313562525074940809403693475624332169458744562386580074420532959714281903926902622613852892104465683714186704831143197300465955"),
           e_float("0.73265285194543608674851404628602868786755398311878599262050209465658337331457767882450516660833910207846986678480603058221329185506983962144302950162737505562091432645466997334653618075359372680522922578429510783107155224742867979206003853893418268095936450823867623873015528453108944563276576646508412198497923383466470895808777876544429706485835161864475122029711660543090876323595451165397047981956"),
           e_float("0.74536323930873866831066285008063416514858255428941319323031554151661731879818806472410911187787504167842137286019020264008471692607030872105020489874402631524823767448432915438225335869622093354538021006314536198469136634364850042715775621307965524560308901397550829610851125072518884822515926626213581949190024268711827023522012804341871590177804438418738255381261594827085100659777173578154500251787"),
           e_float("0.75780828629211358196731753685850074775187628883294491833833279769413437275246840580617185041212744084038976069700142887035937511309419495512390089087847775651833369173386038513330257480188204696687136231267595399438343156895032682495327740328291738325217778497473260463740600852973600297913238958828132336080624048815574113414592522918778477418427876829087439774857073733879539765547872800792711360592"),
           e_float("0.76998356260799010064124325420889481428942836988785464918451704687709959533402569414853910266075223008145347866420469852220997470992987183595134711278161994827010482478666523199914707457365681979989417199177427808129308850228595726632468139527316915481709465938257650120793934685421343443942356060396291075752713480402305699120964704579260218579751719693291565685728074939857101460901984240449471777639"),
           e_float("0.78188473400392189344901888012886357289691591193533323711550248487573232160560048524966536928562079994581390209192526509899176077393862245482807165569409036943146775931090958041945317489351020506180957959482939768275851398130892970557450783138983566392455270904228057175489097967314871299150832712632639718878702471658606369540854496281803565819545728647765960328269135853132407415684491934581417388002"),
           e_float("0.79350756380552895006859336306152006552993066088382163294295016384877329185292344719536879395060919553184640006473875955257330264813115929942877156894433233876161573894628944452740080653935089289153173836334040374431360850336851424574668632837338016740333716530963434291489645017931035529052587483629111178971917421121398732580060101294617212337648611654041575132820234403350225337355214099696493406567"),
           e_float("0.80484791442470288298134387731514331459831415420391927496917008531718727007136925375073869996549995938671025493755987802316807560672754205522916341547950527416285009447065632296220924964603370109747266700136618832767813938243784759073035555035361911772169687111972294262096081393656654067512785827139608367560009298721819281091010743363153063005841441400130721362346287552727162527118465104052539630019"),
           e_float("0.81590174883253870457705586780548750833668862852238889952372206236774966573191832400412494946116015154305873210759963247859431688393192829248700535837612167242633896627292821666890819736549652534738107012873094812825219601489880060491958385552979476621004236099490018887651186347086675381603801017940808290855340870383683075409122477045713172106217670870448929077822708030574128623585863036730829850118"),
        }};
        static const std::vector<e_float> v(a.begin(), a.end());
        return v;
      }
    };

    bool test_case_00111_sin_small_x(const bool b_write_output)
    {
      return TestCase_case_00111_sin_small_x().execute(b_write_output);
    }
  }
}
