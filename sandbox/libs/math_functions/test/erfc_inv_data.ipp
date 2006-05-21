#define SC_(x) static_cast<T>(BOOST_JOIN(x, L))
   static const boost::array<boost::array<T, 2>, 100> erfc_inv_data = {
      SC_(0.00956696830689907073974609375), SC_(1.832184391051582711731256541599359331735), 
      SC_(0.063665688037872314453125), SC_(1.311339282092737086640055105484822812599), 
      SC_(0.068892158567905426025390625), SC_(1.286316565305373898738127895195338854718), 
      SC_(0.071423359215259552001953125), SC_(1.274755321776344058215704428086211324587), 
      SC_(0.0728825032711029052734375), SC_(1.268242522387371561738393687518023984868), 
      SC_(0.09234277904033660888671875), SC_(1.190178756246535875259766567441510867604), 
      SC_(0.102432854473590850830078125), SC_(1.154826903977823078146497880706118113588), 
      SC_(0.1942635476589202880859375), SC_(0.9178735528443878579995511780412810469667), 
      SC_(0.19508080184459686279296875), SC_(0.9161942752629032646404767631869277618212), 
      SC_(0.21972350776195526123046875), SC_(0.8678064594007161661713535461829067693456), 
      SC_(0.224929034709930419921875), SC_(0.8580919924152284867224297625328485999768), 
      SC_(0.2503655254840850830078125), SC_(0.8127923779477598070926819995714374417663), 
      SC_(0.25179326534271240234375), SC_(0.8103475955423936417307157186107256388648), 
      SC_(0.2539736330509185791015625), SC_(0.8066326381314558738773191719462921998277), 
      SC_(0.27095401287078857421875), SC_(0.7784313874823551106598826200232666844639), 
      SC_(0.2837726771831512451171875), SC_(0.7579355956263440770864088550908621329508), 
      SC_(0.298227965831756591796875), SC_(0.7355614373173595299453301005770428516518), 
      SC_(0.3152261674404144287109375), SC_(0.7101588837290742217667270852502075077668), 
      SC_(0.342373371124267578125), SC_(0.6713881533266128640126408255047881638389), 
      SC_(0.347730338573455810546875), SC_(0.6639738263692763456669198307149427734317), 
      SC_(0.3737452030181884765625), SC_(0.6289572925573171740836428308746584439674), 
      SC_(0.37676393985748291015625), SC_(0.6249936843093662471116097431474787933967), 
      SC_(0.42041814327239990234375), SC_(0.5697131213589784467617578394703976041604), 
      SC_(0.4238486588001251220703125), SC_(0.5655171880456876504494070613171955224472), 
      SC_(0.4420680999755859375), SC_(0.5435569422159360687847790186563654276103), 
      SC_(0.553845942020416259765625), SC_(0.4186121208546731033057205459902879301199), 
      SC_(0.55699646472930908203125), SC_(0.4152898953738801984047941692529271391195), 
      SC_(0.59405887126922607421875), SC_(0.3768620801611051992528860948080812212023), 
      SC_(0.603826224803924560546875), SC_(0.3669220210390825311547962776125822899061), 
      SC_(0.61633408069610595703125), SC_(0.3542977152760563782151668726041057557165), 
      SC_(0.63310086727142333984375), SC_(0.3375493847053488720470432821496358279516), 
      SC_(0.634198963642120361328125), SC_(0.3364591774366710656954166264654945559873), 
      SC_(0.722588002681732177734375), SC_(0.2510244067029671790889794981353227476998), 
      SC_(0.763116896152496337890625), SC_(0.213115119330839975829499967157244997714), 
      SC_(0.784454047679901123046875), SC_(0.1934073617841803428235669261097060281642), 
      SC_(0.797477066516876220703125), SC_(0.1814532246720147926398927046057793150106), 
      SC_(0.81746232509613037109375), SC_(0.1632073953550647568421821286058243218715), 
      SC_(0.843522548675537109375), SC_(0.1395756320903277910768376053314442757507), 
      SC_(0.8441753387451171875), SC_(0.1389857795955756484965030151195660030168), 
      SC_(0.87748873233795166015625), SC_(0.109002961098867662134935094105847496074), 
      SC_(0.8911724090576171875), SC_(0.09674694516640724629590870677194632943569), 
      SC_(0.91597831249237060546875), SC_(0.07460044047654119877070700345343119035515), 
      SC_(0.94951736927032470703125), SC_(0.04476895818328636312384562686715995170129), 
      SC_(0.970751285552978515625), SC_(0.0259268064334840921104659134138093242797), 
      SC_(0.97513782978057861328125), SC_(0.02203709146986755832638577823832075055744), 
      SC_(0.97952878475189208984375), SC_(0.01814413302702029459097557481591610553903), 
      SC_(0.981178104877471923828125), SC_(0.01668201759439857888105181293763417899072), 
      SC_(1.0073254108428955078125), SC_(-0.006492067534753215749601670217642082465642), 
      SC_(1.09376299381256103515625), SC_(-0.08328747254794857150987333986733043734817), 
      SC_(1.0944411754608154296875), SC_(-0.08389270963798942778622198997355058545872), 
      SC_(1.264718532562255859375), SC_(-0.2390787735821979528028028789569770109829), 
      SC_(1.27952671051025390625), SC_(-0.2530214201700340392837551955289041822603), 
      SC_(1.29262602329254150390625), SC_(-0.2654374523135675523971788948011709467352), 
      SC_(1.3109557628631591796875), SC_(-0.282950508503826367238408926581528085458), 
      SC_(1.31148135662078857421875), SC_(-0.2834552014554130441860525970673030809536), 
      SC_(1.32721102237701416015625), SC_(-0.2986277427848421570858990348074985028421), 
      SC_(1.3574702739715576171875), SC_(-0.3282140305634627092431945088114761850208), 
      SC_(1.362719058990478515625), SC_(-0.3334035993712283467959295804559099468454), 
      SC_(1.3896572589874267578125), SC_(-0.3603304982893212173104266596348905175268), 
      SC_(1.4120922088623046875), SC_(-0.3831602323665075533579267768785894144888), 
      SC_(1.41872966289520263671875), SC_(-0.3899906753567599452444107492361433402154), 
      SC_(1.45167791843414306640625), SC_(-0.4244594733907945411184647153213164209335), 
      SC_(1.48129451274871826171875), SC_(-0.4563258063707025027210352963461819167707), 
      SC_(1.4862649440765380859375), SC_(-0.4617640058971775089811390737537561779898), 
      SC_(1.50937330722808837890625), SC_(-0.4874174763856674076219106695373814892182), 
      SC_(1.5154802799224853515625), SC_(-0.4943041993872143888987628020569772222018), 
      SC_(1.52750003337860107421875), SC_(-0.5079978091910991117615000459548117088362), 
      SC_(1.53103363513946533203125), SC_(-0.5120597685873370942783226077302881881069), 
      SC_(1.58441460132598876953125), SC_(-0.5756584292527058478710392476034273328569), 
      SC_(1.5879499912261962890625), SC_(-0.5800336103175463592377907341030447077804), 
      SC_(1.59039986133575439453125), SC_(-0.5830784871670823806198622501806646778319), 
      SC_(1.59455978870391845703125), SC_(-0.588273673825686998734497652983815773459), 
      SC_(1.59585726261138916015625), SC_(-0.5899005483108011364541949539839185473259), 
      SC_(1.5962116718292236328125), SC_(-0.5903454775096607218832535637355431851718), 
      SC_(1.6005609035491943359375), SC_(-0.5958247243549040349587326482492767206448), 
      SC_(1.6150619983673095703125), SC_(-0.6143583249050861028039832921829036722514), 
      SC_(1.62944734096527099609375), SC_(-0.6331707263097125575937994856370309207836), 
      SC_(1.64380657672882080078125), SC_(-0.6524069265890823819975498133014027247554), 
      SC_(1.6469156742095947265625), SC_(-0.656635855345815020063728463464436343698), 
      SC_(1.67001712322235107421875), SC_(-0.6888269167957872563013714303376548038671), 
      SC_(1.6982586383819580078125), SC_(-0.7302336318927408409119676651737758401138), 
      SC_(1.74485766887664794921875), SC_(-0.8046505193013635090578266413458426260098), 
      SC_(1.75686132907867431640625), SC_(-0.8253191678260588578995203396384711816647), 
      SC_(1.81158387660980224609375), SC_(-0.9300427626888758122211127950646282789481), 
      SC_(1.826751708984375), SC_(-0.9629665092443368464606966822833571908852), 
      SC_(1.83147108554840087890625), SC_(-0.9736479209913771931387473923084901789046), 
      SC_(1.84174954891204833984375), SC_(-0.997713670556719074960678197806799852186), 
      SC_(1.8679864406585693359375), SC_(-1.065050516333636716777334376076374184102), 
      SC_(1.90044414997100830078125), SC_(-1.164612422633086435501625591693259387477), 
      SC_(1.91433393955230712890625), SC_(-1.215315881176612875682446995412738776976), 
      SC_(1.91501367092132568359375), SC_(-1.217962731073139868794942852653058932976), 
      SC_(1.918984889984130859375), SC_(-1.233778505900771488542027767896521427575), 
      SC_(1.92977702617645263671875), SC_(-1.28019542575660930623179572273596558907), 
      SC_(1.93538987636566162109375), SC_(-1.306695301483797253764522033930388453334), 
      SC_(1.93773555755615234375), SC_(-1.318335478463913327121670503572736587296), 
      SC_(1.94118559360504150390625), SC_(-1.33613349872692113073358883961598631154), 
      SC_(1.96221935749053955078125), SC_(-1.468821071545234761861756248744372345584), 
      SC_(1.98576259613037109375), SC_(-1.733272259459038694476413373595347034928), 
      SC_(1.9881370067596435546875), SC_(-1.77921769652839903464038407684397479173), 
      SC_(1.99292266368865966796875), SC_(-1.904368122482929779094714951471938518496), 
   };
#undef SC_

