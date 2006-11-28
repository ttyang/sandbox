#define SC_(x) static_cast<T>(BOOST_JOIN(x, L))
   static const boost::array<boost::array<T, 3>, 300> erf_large_data = { {
      { SC_(8.2311115264892578125), SC_(0.9999999999999999999999999999997436415644), SC_(0.2563584356432915693836191701249115171878e-30) }, 
      { SC_(8.3800067901611328125), SC_(0.9999999999999999999999999999999787664373), SC_(0.212335626810981756102114466368867764939e-31) }, 
      { SC_(8.39224529266357421875), SC_(0.9999999999999999999999999999999827316301), SC_(0.1726836993826464997300336080711750877816e-31) }, 
      { SC_(8.66370105743408203125), SC_(0.9999999999999999999999999999999998367494), SC_(0.1632506054605993373182936619108145081694e-33) }, 
      { SC_(8.9759693145751953125), SC_(0.9999999999999999999999999999999999993611), SC_(0.6389109854135105643535885036658544645608e-36) }, 
      { SC_(9.1102085113525390625), SC_(0.9999999999999999999999999999999999999445), SC_(0.5554662272164108694298027082501260363284e-37) }, 
      { SC_(9.45745944976806640625), SC_(0.9999999999999999999999999999999999999999), SC_(0.8480477594433168680596946662186145070498e-40) }, 
      { SC_(10.61029338836669921875), SC_(1), SC_(0.6786472703144874611591306359565011820753e-50) }, 
      { SC_(10.8140201568603515625), SC_(1), SC_(0.8470069870191149998048954134093763207838e-52) }, 
      { SC_(10.82457828521728515625), SC_(1), SC_(0.6733586817565831939437647508350297170672e-52) }, 
      { SC_(10.9283580780029296875), SC_(1), SC_(0.6977670213613499261034444110870077646237e-53) }, 
      { SC_(10.98818302154541015625), SC_(1), SC_(0.1870385270398381154229086866501074415355e-53) }, 
      { SC_(11.31863117218017578125), SC_(1), SC_(0.1142544869245536263179923727458113771164e-56) }, 
      { SC_(11.69488239288330078125), SC_(1), SC_(0.1919907987324948057617154107998359393185e-60) }, 
      { SC_(11.78605365753173828125), SC_(1), SC_(0.2239752724414047638235296360419194553396e-61) }, 
      { SC_(12.1997470855712890625), SC_(1), SC_(0.1061491854672859805410277580039105082623e-65) }, 
      { SC_(12.4239101409912109375), SC_(1), SC_(0.4177140558891845034847722323657671701092e-68) }, 
      { SC_(13.54282093048095703125), SC_(1), SC_(0.9235451601555197945993611934762413642509e-81) }, 
      { SC_(14.22005176544189453125), SC_(1), SC_(0.6009313847910459672567608314935750835662e-89) }, 
      { SC_(14.22926807403564453125), SC_(1), SC_(0.4620339167397254212949689945484104460402e-89) }, 
      { SC_(14.359676361083984375), SC_(1), SC_(0.1100471801774583728133644248988374419641e-90) }, 
      { SC_(14.41039371490478515625), SC_(1), SC_(0.2548929323782609375991749296565683531577e-91) }, 
      { SC_(14.87335300445556640625), SC_(1), SC_(0.3198000452629152167848001696581299429735e-97) }, 
      { SC_(14.92373943328857421875), SC_(1), SC_(0.7101988862786309879894988884459001902733e-98) }, 
      { SC_(15.8191242218017578125), SC_(1), SC_(0.7438591168260150840237290305856485663443e-110) }, 
      { SC_(15.96480560302734375), SC_(1), SC_(0.7187861904421355163894524608883700422307e-112) }, 
      { SC_(15.99831295013427734375), SC_(1), SC_(0.2457896620902286177098546091913977024151e-112) }, 
      { SC_(16.7455272674560546875), SC_(1), SC_(0.5559992295828943910250640094814395579468e-123) }, 
      { SC_(17.008663177490234375), SC_(1), SC_(0.760237064211963037211163791564153667507e-127) }, 
      { SC_(17.2220897674560546875), SC_(1), SC_(0.5043169273534506801418127595237229711103e-130) }, 
      { SC_(17.757808685302734375), SC_(1), SC_(0.35565429074608249855471197796329792194e-138) }, 
      { SC_(17.802867889404296875), SC_(1), SC_(0.7145708921803004436285314631231014067581e-139) }, 
      { SC_(18.112152099609375), SC_(1), SC_(0.1053094819294519519788245447399920974245e-143) }, 
      { SC_(18.2649860382080078125), SC_(1), SC_(0.4020674492293458832133643654712400773494e-146) }, 
      { SC_(18.32352447509765625), SC_(1), SC_(0.4706809140073901333884996503518029500936e-147) }, 
      { SC_(18.4129180908203125), SC_(1), SC_(0.1755474923764976123532737166943228663005e-148) }, 
      { SC_(18.652309417724609375), SC_(1), SC_(0.2428091775485678872414439322587700295772e-152) }, 
      { SC_(18.9056758880615234375), SC_(1), SC_(0.1764835785229242910502507612159515936326e-156) }, 
      { SC_(19.1091136932373046875), SC_(1), SC_(0.7645206854732087495539968665185944859194e-160) }, 
      { SC_(19.1576213836669921875), SC_(1), SC_(0.1191626992794708978523133508616313098621e-160) }, 
      { SC_(19.31610870361328125), SC_(1), SC_(0.2657165206820982194424196529775105931442e-163) }, 
      { SC_(19.3672046661376953125), SC_(1), SC_(0.3671679040400985756060408739652361271147e-164) }, 
      { SC_(19.6346797943115234375), SC_(1), SC_(0.1067452532475426004914816798590685683097e-168) }, 
      { SC_(19.8862934112548828125), SC_(1), SC_(0.5060597273643268882175716699743699135461e-173) }, 
      { SC_(19.93419647216796875), SC_(1), SC_(0.7494327004502860500754429706601818608063e-174) }, 
      { SC_(20.2273464202880859375), SC_(1), SC_(0.5692529890798582547111055729709760376723e-179) }, 
      { SC_(20.242107391357421875), SC_(1), SC_(0.3130080167182599318145495989493729041355e-179) }, 
      { SC_(20.4949970245361328125), SC_(1), SC_(0.1037715327566096248596862690543722677311e-183) }, 
      { SC_(20.6639499664306640625), SC_(1), SC_(0.9828104968491392552509099594974133192176e-187) }, 
      { SC_(20.9242725372314453125), SC_(1), SC_(0.1928501126858728847552898327055431396084e-191) }, 
      { SC_(20.9607219696044921875), SC_(1), SC_(0.4182492638018175069922633264256087874033e-192) }, 
      { SC_(21.2989482879638671875), SC_(1), SC_(0.2552602767811562690060253249228934667833e-198) }, 
      { SC_(21.3341617584228515625), SC_(1), SC_(0.5679087385569991824361542895704294427451e-199) }, 
      { SC_(21.5831966400146484375), SC_(1), SC_(0.1280987506428470296014925421711821162698e-203) }, 
      { SC_(22.0373077392578125), SC_(1), SC_(0.3131661581007378806102060325912155502701e-212) }, 
      { SC_(22.2569446563720703125), SC_(1), SC_(0.1846614406013614928732974356509343390705e-216) }, 
      { SC_(22.9114551544189453125), SC_(1), SC_(0.2598259766741800523533570657530873506244e-229) }, 
      { SC_(23.0804386138916015625), SC_(1), SC_(0.108696918487531328017390687052866837422e-232) }, 
      { SC_(23.3235530853271484375), SC_(1), SC_(0.1355781333962075845012366321672254343728e-237) }, 
      { SC_(23.4473209381103515625), SC_(1), SC_(0.4129348514781646974836324488402049303682e-240) }, 
      { SC_(24.12081146240234375), SC_(1), SC_(0.4900590012091086604540120205982908317771e-254) }, 
      { SC_(24.3631992340087890625), SC_(1), SC_(0.382044899410099463972224844951303224334e-259) }, 
      { SC_(25.061580657958984375), SC_(1), SC_(0.379460392354870154626118964688104627376e-274) }, 
      { SC_(25.23714447021484375), SC_(1), SC_(0.5508622514289808668363975738198678197993e-278) }, 
      { SC_(25.3777942657470703125), SC_(1), SC_(0.4435055276360357438046878641441812378362e-281) }, 
      { SC_(25.813503265380859375), SC_(1), SC_(0.8969991006618404791166973289604328222239e-291) }, 
      { SC_(26.1247920989990234375), SC_(1), SC_(0.8433396822097075603573541828301520902564e-298) }, 
      { SC_(26.3525791168212890625), SC_(1), SC_(0.5380559555748413036380180439113786214843e-303) }, 
      { SC_(26.776111602783203125), SC_(1), SC_(0.8944111506115654515313274252719979616663e-313) }, 
      { SC_(26.8727970123291015625), SC_(1), SC_(0.4980346568584009068204868294049186460128e-315) }, 
      { SC_(27.6731243133544921875), SC_(1), SC_(0.5315985423107748521341095763480509306686e-334) }, 
      { SC_(27.6761074066162109375), SC_(1), SC_(0.4506400985060962000709584088621043872847e-334) }, 
      { SC_(27.96904754638671875), SC_(1), SC_(0.3715003445893695695072259525562685194324e-341) }, 
      { SC_(28.58887481689453125), SC_(1), SC_(0.2166518476138800933879816106005670654441e-356) }, 
      { SC_(28.742389678955078125), SC_(1), SC_(0.3244339622815072602163752228132919409512e-360) }, 
      { SC_(28.851139068603515625), SC_(1), SC_(0.6157273676049535809152624774082572414474e-363) }, 
      { SC_(28.9178009033203125), SC_(1), SC_(0.1305949729571576658796058283659336601413e-364) }, 
      { SC_(29.1156768798828125), SC_(1), SC_(0.1335911177834992334477211342269950231736e-369) }, 
      { SC_(29.3093738555908203125), SC_(1), SC_(0.1614718326165092385338896025176950706834e-374) }, 
      { SC_(29.5636444091796875), SC_(1), SC_(0.504780346276441675830815513402480460203e-381) }, 
      { SC_(29.631839752197265625), SC_(1), SC_(0.8890342529017924395163297463196226030207e-383) }, 
      { SC_(30.6340579986572265625), SC_(1), SC_(0.5049904008337056546410563604215235735623e-409) }, 
      { SC_(30.707683563232421875), SC_(1), SC_(0.5505904741434267060539220169867548888751e-411) }, 
      { SC_(30.8368549346923828125), SC_(1), SC_(0.1934000588075928658952471412237852868705e-414) }, 
      { SC_(31.179210662841796875), SC_(1), SC_(0.1150586385665917046799828457578881631925e-423) }, 
      { SC_(31.4387989044189453125), SC_(1), SC_(0.9951971607786623315295164065875436156955e-431) }, 
      { SC_(32.356414794921875), SC_(1), SC_(0.3647911693171115642349382796707730440408e-456) }, 
      { SC_(32.586200714111328125), SC_(1), SC_(0.1196854549366123742924784427293234502016e-462) }, 
      { SC_(32.75687408447265625), SC_(1), SC_(0.1707585732299349124939643284536648783473e-467) }, 
      { SC_(33.2696990966796875), SC_(1), SC_(0.3314340732586949021659796359200734182646e-482) }, 
      { SC_(33.519634246826171875), SC_(1), SC_(0.1851275204503437416978123025595612676848e-489) }, 
      { SC_(33.957134246826171875), SC_(1), SC_(0.276057351872287608387770565675906984022e-502) }, 
      { SC_(34.00215911865234375), SC_(1), SC_(0.1292839762753917184628820650991754160974e-503) }, 
      { SC_(35.2607574462890625), SC_(1), SC_(0.1723862426577913396207111099832970757108e-541) }, 
      { SC_(35.6440582275390625), SC_(1), SC_(0.2682942190174394220973041800979694793591e-553) }, 
      { SC_(35.898014068603515625), SC_(1), SC_(0.3427988522143486471852246306766064547166e-561) }, 
      { SC_(35.91162872314453125), SC_(1), SC_(0.128908321457486470920213918176837870702e-561) }, 
      { SC_(36.391139984130859375), SC_(1), SC_(0.1115677489279136454855597068297808612163e-576) }, 
      { SC_(36.69866943359375), SC_(1), SC_(0.1914841862056771258044968899947647500071e-586) }, 
      { SC_(36.778095245361328125), SC_(1), SC_(0.5580499602695800066261393252867262445483e-589) }, 
      { SC_(36.836078643798828125), SC_(1), SC_(0.7802735251877915942902082027097296754913e-591) }, 
      { SC_(36.926517486572265625), SC_(1), SC_(0.9862852517813094777393024048350874991345e-594) }, 
      { SC_(37.220302581787109375), SC_(1), SC_(0.3390210353535371981540883592991293306856e-603) }, 
      { SC_(37.62610626220703125), SC_(1), SC_(0.2161308855123068080619903224122596349173e-616) }, 
      { SC_(37.78128814697265625), SC_(1), SC_(0.1781872758239509973907000853718925676836e-621) }, 
      { SC_(39.196559906005859375), SC_(1), SC_(0.8334676760927633157297582502293215474801e-669) }, 
      { SC_(39.287792205810546875), SC_(1), SC_(0.6459479389166880954444837324458596842583e-672) }, 
      { SC_(39.3513031005859375), SC_(1), SC_(0.4369573452597126768250060965811055881436e-674) }, 
      { SC_(39.75826263427734375), SC_(1), SC_(0.4509483787208385166749854593762529916563e-688) }, 
      { SC_(39.86272430419921875), SC_(1), SC_(0.1098531610189679641881639506181744668225e-691) }, 
      { SC_(40.162616729736328125), SC_(1), SC_(0.4120302102977277191187506721340552814976e-702) }, 
      { SC_(40.170276641845703125), SC_(1), SC_(0.2226415732825465240782514517928537101293e-702) }, 
      { SC_(40.382472991943359375), SC_(1), SC_(0.8354572576931370443665770929403858031245e-710) }, 
      { SC_(40.696559906005859375), SC_(1), SC_(0.7225661474676652832663905782266313267167e-721) }, 
      { SC_(40.782176971435546875), SC_(1), SC_(0.673503764299797652470711537205502876345e-724) }, 
      { SC_(40.9482574462890625), SC_(1), SC_(0.8541553669484881480206884088881859451573e-730) }, 
      { SC_(41.145099639892578125), SC_(1), SC_(0.8156452609298646477772692892407567909292e-737) }, 
      { SC_(41.515956878662109375), SC_(1), SC_(0.3927474520057692651749738005168570105415e-750) }, 
      { SC_(41.838653564453125), SC_(1), SC_(0.8109391651273807861676399802649936141133e-762) }, 
      { SC_(42.584423065185546875), SC_(1), SC_(0.3614692055111044536160065200200925139014e-789) }, 
      { SC_(42.6111907958984375), SC_(1), SC_(0.3693115729392217140417024607374602650062e-790) }, 
      { SC_(42.6995391845703125), SC_(1), SC_(0.1964210029215776788610761375896332961826e-793) }, 
      { SC_(43.375934600830078125), SC_(1), SC_(0.1002957731076485676078330474511548731955e-818) }, 
      { SC_(43.761638641357421875), SC_(1), SC_(0.2518258316895643034341457105016197161517e-833) }, 
      { SC_(43.97068023681640625), SC_(1), SC_(0.2717687606713113972202367030042368252574e-841) }, 
      { SC_(43.977039337158203125), SC_(1), SC_(0.1553279441110419250099473836953698361303e-841) }, 
      { SC_(44.299617767333984375), SC_(1), SC_(0.662284188550331482050024128495832271562e-854) }, 
      { SC_(44.5380706787109375), SC_(1), SC_(0.4157106895546200361762199057481171702463e-863) }, 
      { SC_(44.7019195556640625), SC_(1), SC_(0.1849263581704522121134821381775513596569e-869) }, 
      { SC_(44.944408416748046875), SC_(1), SC_(0.6665835026232982550759602414166037648457e-879) }, 
      { SC_(45.39469146728515625), SC_(1), SC_(0.1423064152931413223321009373154837793895e-896) }, 
      { SC_(45.555110931396484375), SC_(1), SC_(0.6535595984749616464428461737502955522054e-903) }, 
      { SC_(45.922885894775390625), SC_(1), SC_(0.1587405585152606350596738044081514147077e-917) }, 
      { SC_(46.490032196044921875), SC_(1), SC_(0.2711887374954078187100515917478258475121e-940) }, 
      { SC_(46.700458526611328125), SC_(1), SC_(0.8220768482426773312423439218857395793096e-949) }, 
      { SC_(46.80968475341796875), SC_(1), SC_(0.300689768353676045411682389398910728652e-953) }, 
      { SC_(46.93021392822265625), SC_(1), SC_(0.3716830576798476782128277462132351948199e-958) }, 
      { SC_(47.80080413818359375), SC_(1), SC_(0.5560372820563731575239827056999357124531e-994) }, 
      { SC_(47.98065185546875), SC_(1), SC_(0.1829295366299049625367873244831792588204e-1001) }, 
      { SC_(48.160678863525390625), SC_(1), SC_(0.5544641890677600654790600067979757964649e-1009) }, 
      { SC_(48.228302001953125), SC_(1), SC_(0.8174825675757120829683639765764518487113e-1012) }, 
      { SC_(48.86585235595703125), SC_(1), SC_(0.1054147185420251960062940386161051253868e-1038) }, 
      { SC_(48.88062286376953125), SC_(1), SC_(0.2487429897424450019093445470126394812466e-1039) }, 
      { SC_(49.2615814208984375), SC_(1), SC_(0.1428662569339560177970591891033928074615e-1055) }, 
      { SC_(49.300342559814453125), SC_(1), SC_(0.3129115225209756198596637394420488168835e-1057) }, 
      { SC_(49.3912200927734375), SC_(1), SC_(0.3976507934443091883911509821945069748171e-1061) }, 
      { SC_(49.450878143310546875), SC_(1), SC_(0.1091595819414626077382205537328240830492e-1063) }, 
      { SC_(49.4884796142578125), SC_(1), SC_(0.2642659241845869227101266198364933762561e-1065) }, 
      { SC_(50.086460113525390625), SC_(1), SC_(0.3607878684331161959098857667661007215536e-1091) }, 
      { SC_(51.2444610595703125), SC_(1), SC_(0.3860548279363456071149897668546024070402e-1142) }, 
      { SC_(51.339717864990234375), SC_(1), SC_(0.2197789266327651540257336225175053590062e-1146) }, 
      { SC_(51.447040557861328125), SC_(1), SC_(0.354996685112096717011426990868690176895e-1151) }, 
      { SC_(51.52539825439453125), SC_(1), SC_(0.1110143282538327027879325761520351634781e-1154) }, 
      { SC_(51.782512664794921875), SC_(1), SC_(0.3217426516835935075931472670615112969831e-1166) }, 
      { SC_(52.144077301025390625), SC_(1), SC_(0.1532358547576965427522636443372608038782e-1182) }, 
      { SC_(52.820537567138671875), SC_(1), SC_(0.2202669107160275614166035168539425499729e-1213) }, 
      { SC_(52.8442840576171875), SC_(1), SC_(0.1790754358721238111167473370381879109436e-1214) }, 
      { SC_(52.871673583984375), SC_(1), SC_(0.9892522319813664639479190973985140674034e-1216) }, 
      { SC_(52.872089385986328125), SC_(1), SC_(0.9466912463849392521290423205053783831664e-1216) }, 
      { SC_(53.07733917236328125), SC_(1), SC_(0.3390908799279318246606852431264844551837e-1225) }, 
      { SC_(53.088535308837890625), SC_(1), SC_(0.1032764828225424213243462240852153489629e-1225) }, 
      { SC_(53.778041839599609375), SC_(1), SC_(0.1017002820918486891770554932818686415531e-1257) }, 
      { SC_(54.0477142333984375), SC_(1), SC_(0.2381751287333891734284837295419122638673e-1270) }, 
      { SC_(54.561374664306640625), SC_(1), SC_(0.139407502357667351124920158334676469294e-1294) }, 
      { SC_(54.6435394287109375), SC_(1), SC_(0.1765212687763302697244562949068373410255e-1298) }, 
      { SC_(55.047882080078125), SC_(1), SC_(0.9580050759351008955877580245822791128101e-1318) }, 
      { SC_(55.53577423095703125), SC_(1), SC_(0.3516341067901357169932495766343569323525e-1341) }, 
      { SC_(55.63845062255859375), SC_(1), SC_(0.3871072763485538347396913418646976027199e-1346) }, 
      { SC_(55.9916534423828125), SC_(1), SC_(0.289528812850324808187999318666603687985e-1363) }, 
      { SC_(55.991954803466796875), SC_(1), SC_(0.2799194648396030874187262104833020570154e-1363) }, 
      { SC_(56.6115570068359375), SC_(1), SC_(0.138610665425682272373334040969461433112e-1393) }, 
      { SC_(56.749294281005859375), SC_(1), SC_(0.2289081242224445766088406090902886148302e-1400) }, 
      { SC_(57.362518310546875), SC_(1), SC_(0.9220583307012274413074526609845212209396e-1431) }, 
      { SC_(57.5469818115234375), SC_(1), SC_(0.5725247795522802723716771177781160453318e-1440) }, 
      { SC_(58.515666961669921875), SC_(1), SC_(0.8387169924209196731842556332538391198272e-1489) }, 
      { SC_(58.8695220947265625), SC_(1), SC_(0.7612989272837028720721864253441810819973e-1507) }, 
      { SC_(59.008518218994140625), SC_(1), SC_(0.5818271285898335632169611265925278206909e-1514) }, 
      { SC_(59.44551849365234375), SC_(1), SC_(0.1907993812890002855694347258421797523393e-1536) }, 
      { SC_(59.853458404541015625), SC_(1), SC_(0.1386369169907035409186787094207373016361e-1557) }, 
      { SC_(60.46059417724609375), SC_(1), SC_(0.2591809034926289626577001708586017024727e-1589) }, 
      { SC_(60.804798126220703125), SC_(1), SC_(0.1921652566797868246807189497430043640543e-1607) }, 
      { SC_(60.9976654052734375), SC_(1), SC_(0.1202209001001935503022907284085976927471e-1617) }, 
      { SC_(61.63448333740234375), SC_(1), SC_(0.1443858912194400214601650177255810967138e-1651) }, 
      { SC_(61.718036651611328125), SC_(1), SC_(0.4818094804505875544021186960960583940739e-1656) }, 
      { SC_(61.749187469482421875), SC_(1), SC_(0.1028760000725124920333886117069810603088e-1657) }, 
      { SC_(61.7707366943359375), SC_(1), SC_(0.7180844057437257539436486908675040497688e-1659) }, 
      { SC_(62.129795074462890625), SC_(1), SC_(0.3411714823101512343643373517899997588934e-1678) }, 
      { SC_(62.415653228759765625), SC_(1), SC_(0.1172420264374634693794507306774825437228e-1693) }, 
      { SC_(63.656280517578125), SC_(1), SC_(0.1359202639129155863922014558394013590937e-1761) }, 
      { SC_(63.720615386962890625), SC_(1), SC_(0.3748863560151785919817454048142060747672e-1765) }, 
      { SC_(63.735622406005859375), SC_(1), SC_(0.5534848650018337136859100029355185261672e-1766) }, 
      { SC_(63.745220184326171875), SC_(1), SC_(0.1628046476475599666226420695090084595775e-1766) }, 
      { SC_(63.783538818359375), SC_(1), SC_(0.1227798051543007555849422132322321585877e-1768) }, 
      { SC_(63.87148284912109375), SC_(1), SC_(0.1632762187944705003794943454328122376037e-1773) }, 
      { SC_(64.515594482421875), SC_(1), SC_(0.1969332977981314849672526645022956975392e-1809) }, 
      { SC_(64.97594451904296875), SC_(1), SC_(0.2525310788037616742275863982689138714012e-1835) }, 
      { SC_(65.00909423828125), SC_(1), SC_(0.3394161846767033496272256639147831568993e-1837) }, 
      { SC_(65.32428741455078125), SC_(1), SC_(0.4872272181442093260036099253187279262469e-1855) }, 
      { SC_(65.8734893798828125), SC_(1), SC_(0.2462682463022898342795255163765824211512e-1886) }, 
      { SC_(65.895782470703125), SC_(1), SC_(0.1304674583839710679197974600800374601509e-1887) }, 
      { SC_(66.16791534423828125), SC_(1), SC_(0.3203747642032728309060331250397804757235e-1903) }, 
      { SC_(66.27771759033203125), SC_(1), SC_(0.1545497931044982506797819622759819541777e-1909) }, 
      { SC_(66.7202606201171875), SC_(1), SC_(0.4214693722661996667087731543216442503726e-1935) }, 
      { SC_(67.0804595947265625), SC_(1), SC_(0.4916509034440560388255363947533037583151e-1956) }, 
      { SC_(67.51879119873046875), SC_(1), SC_(0.1163704950246886518963746466814171576513e-1981) }, 
      { SC_(67.61028289794921875), SC_(1), SC_(0.4965812608096806464498341746692252789426e-1987) }, 
      { SC_(68.0894927978515625), SC_(1), SC_(0.2827017688141873952389885023460208246821e-2015) }, 
      { SC_(68.7330780029296875), SC_(1), SC_(0.1601703792022999521045114304499339964142e-2053) }, 
      { SC_(68.936859130859375), SC_(1), SC_(0.1045603435996106684348791239772064284538e-2065) }, 
      { SC_(69.3484344482421875), SC_(1), SC_(0.1990640753018030347229172891391208563692e-2090) }, 
      { SC_(69.4951629638671875), SC_(1), SC_(0.2821572392833612189407917583240153887473e-2099) }, 
      { SC_(69.6038970947265625), SC_(1), SC_(0.7606563437817722315286512269995042517896e-2106) }, 
      { SC_(69.8057861328125), SC_(1), SC_(0.4535113025492646420574078398459972783487e-2118) }, 
      { SC_(69.884307861328125), SC_(1), SC_(0.7806399428418380776194369203828958230443e-2123) }, 
      { SC_(70.090423583984375), SC_(1), SC_(0.2297973354469257356841567122165370429556e-2135) }, 
      { SC_(70.1346893310546875), SC_(1), SC_(0.4627340318338513849654024935557448249929e-2138) }, 
      { SC_(70.4619598388671875), SC_(1), SC_(0.4786946947734960725308155565435423870322e-2158) }, 
      { SC_(70.51854705810546875), SC_(1), SC_(0.1640745397943748179034151831339364278733e-2161) }, 
      { SC_(70.62750244140625), SC_(1), SC_(0.3431785975089560474469843416846358607766e-2168) }, 
      { SC_(70.77237701416015625), SC_(1), SC_(0.4345108777332364055904822498668881910844e-2177) }, 
      { SC_(71.46120452880859375), SC_(1), SC_(0.1213533316440842841172645481517647701339e-2219) }, 
      { SC_(71.54265594482421875), SC_(1), SC_(0.1059138463142173993761026331012035279463e-2224) }, 
      { SC_(71.8696136474609375), SC_(1), SC_(0.4560525021368102193256510775118687007107e-2245) }, 
      { SC_(71.89171600341796875), SC_(1), SC_(0.1900755308625425801959286367021480241643e-2246) }, 
      { SC_(72.96099853515625), SC_(1), SC_(0.1012288958237199779078623773782261227323e-2313) }, 
      { SC_(73.07500457763671875), SC_(1), SC_(0.5943790030417452214269807905148252301626e-2321) }, 
      { SC_(73.10594940185546875), SC_(1), SC_(0.6446581210317819300626283182106697992806e-2323) }, 
      { SC_(73.1313323974609375), SC_(1), SC_(0.1574358163400440570765391931676616457296e-2324) }, 
      { SC_(73.20639801025390625), SC_(1), SC_(0.2666631324666853271144728061565555980879e-2329) }, 
      { SC_(73.376953125), SC_(1), SC_(0.3692800481745944696527608913821150780197e-2340) }, 
      { SC_(73.430145263671875), SC_(1), SC_(0.1498451636616422925337939153598716367853e-2343) }, 
      { SC_(73.44467926025390625), SC_(1), SC_(0.1772057595578452829782717746213217866987e-2344) }, 
      { SC_(73.60561370849609375), SC_(1), SC_(0.9327165682410597575108877219484860075423e-2355) }, 
      { SC_(73.62299346923828125), SC_(1), SC_(0.7217309662507557984084259593722358671817e-2356) }, 
      { SC_(73.77313995361328125), SC_(1), SC_(0.1762441226759232140980568288616069877708e-2365) }, 
      { SC_(74.2175445556640625), SC_(1), SC_(0.4796668342626380739003100430828430758387e-2394) }, 
      { SC_(74.27039337158203125), SC_(1), SC_(0.1873022555292045249630763229328993092174e-2397) }, 
      { SC_(74.39823150634765625), SC_(1), SC_(0.1041846943079459800746159253005438318555e-2405) }, 
      { SC_(74.77135467529296875), SC_(1), SC_(0.6972625788619583784396293640501867635862e-2430) }, 
      { SC_(74.807342529296875), SC_(1), SC_(0.320164469944205443450167902957404361688e-2432) }, 
      { SC_(75.01886749267578125), SC_(1), SC_(0.5501656655265385463409067358984172337294e-2446) }, 
      { SC_(75.3089447021484375), SC_(1), SC_(0.6319468915000774061299279774718180641493e-2465) }, 
      { SC_(75.34217071533203125), SC_(1), SC_(0.4232650489503930895532015931831887522867e-2467) }, 
      { SC_(75.3960723876953125), SC_(1), SC_(0.1252103871082113384792176510455204354046e-2470) }, 
      { SC_(75.45360565185546875), SC_(1), SC_(0.2128736422560450047027718674310538561411e-2474) }, 
      { SC_(75.5235443115234375), SC_(1), SC_(0.5520057148754538352100449496414500231534e-2479) }, 
      { SC_(75.7169952392578125), SC_(1), SC_(0.1082452065927623584648516750055819887681e-2491) }, 
      { SC_(76.1279449462890625), SC_(1), SC_(0.8546877316832444989935075245988734481682e-2519) }, 
      { SC_(76.470703125), SC_(1), SC_(0.1638058714171406332549731275799690588823e-2541) }, 
      { SC_(76.938812255859375), SC_(1), SC_(0.1056702363179452330608841676726809135679e-2572) }, 
      { SC_(77.5743560791015625), SC_(1), SC_(0.2358904373500824632540699420486265405702e-2615) }, 
      { SC_(77.62860107421875), SC_(1), SC_(0.5201021650937707207333604556951161883551e-2619) }, 
      { SC_(77.94854736328125), SC_(1), SC_(0.1249443652740786709208083871965551047597e-2640) }, 
      { SC_(78.06497955322265625), SC_(1), SC_(0.1611056496774920949293225513029265281761e-2648) }, 
      { SC_(78.1817626953125), SC_(1), SC_(0.1913800020341339537443259258588625217145e-2656) }, 
      { SC_(78.7396087646484375), SC_(1), SC_(0.1826214635685593066183737049160168091905e-2694) }, 
      { SC_(79.23296356201171875), SC_(1), SC_(0.2578910365673578199346966028090255709301e-2728) }, 
      { SC_(79.28195953369140625), SC_(1), SC_(0.1091891461191934352451814384442219402849e-2731) }, 
      { SC_(79.53916168212890625), SC_(1), SC_(0.1977970219864078402856631374181827871126e-2749) }, 
      { SC_(79.89411163330078125), SC_(1), SC_(0.5214347553208988003055180927464712623108e-2774) }, 
      { SC_(80.03131103515625), SC_(1), SC_(0.1539244869801023794218894091743149755693e-2783) }, 
      { SC_(81.0540618896484375), SC_(1), SC_(0.4282424762803665933789596667679893825473e-2855) }, 
      { SC_(82.27494049072265625), SC_(1), SC_(0.1058661602699748027888078315752637932386e-2941) }, 
      { SC_(82.40390777587890625), SC_(1), SC_(0.6316127985700229083559360532999075433841e-2951) }, 
      { SC_(82.67310333251953125), SC_(1), SC_(0.3161239679691280797883924212187842089968e-2970) }, 
      { SC_(82.83135223388671875), SC_(1), SC_(0.1331877990458538379342065811181569680933e-2981) }, 
      { SC_(82.8936614990234375), SC_(1), SC_(0.4360382415173864210795784221294622630074e-2986) }, 
      { SC_(82.896820068359375), SC_(1), SC_(0.2582766043573584963841163098015327607626e-2986) }, 
      { SC_(83.0903167724609375), SC_(1), SC_(0.290013476198442869046820654577037968453e-3000) }, 
      { SC_(83.20987701416015625), SC_(1), SC_(0.6710637821460133939254155513062400075894e-3009) }, 
      { SC_(83.5117340087890625), SC_(1), SC_(0.930787700439063954052855467933526662801e-3031) }, 
      { SC_(84.054412841796875), SC_(1), SC_(0.2976066148553277399257428533933691648135e-3070) }, 
      { SC_(84.19962310791015625), SC_(1), SC_(0.7279769443639285050812101610482378417998e-3081) }, 
      { SC_(84.58744049072265625), SC_(1), SC_(0.2702912324282395041651536403393819660776e-3109) }, 
      { SC_(84.58887481689453125), SC_(1), SC_(0.2120514736394887571017949592511629200089e-3109) }, 
      { SC_(85.08606719970703125), SC_(1), SC_(0.4856698297979953595767807992015152776328e-3146) }, 
      { SC_(85.918212890625), SC_(1), SC_(0.761735048565653930137023626638747177308e-3208) }, 
      { SC_(86.31143951416015625), SC_(1), SC_(0.2931592864000316245471343335876130048243e-3237) }, 
      { SC_(86.48769378662109375), SC_(1), SC_(0.1734166482219001810675374526329398742724e-3250) }, 
      { SC_(86.51556396484375), SC_(1), SC_(0.1396184688760208541263525791606580135888e-3252) }, 
      { SC_(86.661895751953125), SC_(1), SC_(0.137591974249259342744647335702120081949e-3263) }, 
      { SC_(86.67838287353515625), SC_(1), SC_(0.7894924978682044731133080698270675959047e-3265) }, 
      { SC_(86.699005126953125), SC_(1), SC_(0.2210314800408904240090566206375166498669e-3266) }, 
      { SC_(86.875640869140625), SC_(1), SC_(0.1067393543048809336522125654614257792709e-3279) }, 
      { SC_(87.12085723876953125), SC_(1), SC_(0.3141588749441732230579799060940491765735e-3298) }, 
      { SC_(87.1272430419921875), SC_(1), SC_(0.1032456874487975042510718930756313489085e-3298) }, 
      { SC_(87.350982666015625), SC_(1), SC_(0.1145259102841530225822158676931062199611e-3315) }, 
      { SC_(87.4471588134765625), SC_(1), SC_(0.5719031848650119145301950377270835213481e-3323) }, 
      { SC_(87.5886077880859375), SC_(1), SC_(0.100944910275613191627060617308017176992e-3333) }, 
      { SC_(88.114166259765625), SC_(1), SC_(0.790369642782630853434920273428079682513e-3374) }, 
      { SC_(88.35390472412109375), SC_(1), SC_(0.3336629458423611349557710086599109785783e-3392) }, 
      { SC_(88.45099639892578125), SC_(1), SC_(0.1168446033182320025804519666787072055362e-3399) }, 
      { SC_(88.55356597900390625), SC_(1), SC_(0.1521829146954713302263784465478849666514e-3407) }, 
      { SC_(88.97168731689453125), SC_(1), SC_(0.8788241912132849825702219058327694185942e-3440) }, 
      { SC_(89.04711151123046875), SC_(1), SC_(0.129507473240771950228590714535613326805e-3445) }, 
      { SC_(89.05876922607421875), SC_(1), SC_(0.1623712240263443145358629211111315306735e-3446) }, 
      { SC_(89.41626739501953125), SC_(1), SC_(0.3153753084460525420724595238130726065242e-3474) }, 
      { SC_(89.51361846923828125), SC_(1), SC_(0.8577730193641580987437405819558340102121e-3482) }, 
      { SC_(89.68304443359375), SC_(1), SC_(0.5586301300368715269248196410139332100555e-3495) }, 
      { SC_(89.70983123779296875), SC_(1), SC_(0.4571434971968977143179977283713339395878e-3497) }
   } };
#undef SC_

