/////////////////////////////////////////////////////////////////////////////
// test_data.cpp
//
//  Copyright 2009 Erwann Rogard. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <libs/adaptive_rejection_sampling/src/example/test_data.h>

namespace libs{namespace adaptive_rejection_sampling{
	const double limitingNc=2.50663;//sqrt(2*pi)
	const double initAr[rowsCount][2]={{-0.5,1.5},{-0.001,0.001}};
	//TODO {-40,40} or above will generate overflow.

	const double unifsAr[]={
	//SeedRandom[0]; Table[Random[], {i, 1, 500}]
0.0318536, 0.640208, 0.724303, 0.580884, 0.931151, 0.636734, 0.928425,
0.0489398, 0.702304, 0.425234, 0.693611, 0.0187156, 0.741754, 0.803531,
0.312868, 0.97356, 0.965564, 0.969633, 0.795063, 0.934604, 0.677499,
0.551747, 0.0255607, 0.806945, 0.645645, 0.911538, 0.301258, 0.226061,
0.714494, 0.274804, 0.372834, 0.177121, 0.0121903, 0.84957, 0.679223,
0.158405, 0.270436, 0.0460394, 0.366355, 0.184846, 0.304872, 0.0764065,
0.571292, 0.250241, 0.627373, 0.52466, 0.545731, 0.443296, 0.981728,
0.613122, 0.244473, 0.217235, 0.267234, 0.338317, 0.871639, 0.0401144,
0.255043, 0.488747, 0.192417, 0.881709, 0.984607, 0.442708, 0.826062,
0.696863, 0.679735, 0.366301, 0.25477, 0.446622, 0.0523622, 0.841641,
0.709039, 0.00332598, 0.0706346, 0.22852, 0.464566, 0.786091, 0.803401,
0.890202, 0.592926, 0.745976, 0.548357, 0.401455, 0.40051, 0.864267, 0.56375,
0.958748, 0.574448, 0.167404, 0.884015, 0.592447, 0.319678, 0.720782,
0.831653, 0.750805, 0.61064, 0.717456, 0.761018, 0.522286, 0.146074,
0.931365, 0.957617, 0.632083, 0.553148, 0.185389, 0.40926, 0.230628,
0.152638, 0.321122, 0.84551, 0.27188, 0.57819, 0.153718, 0.961495, 0.679433,
0.258512, 0.432936, 0.129842, 0.928628, 0.647872, 0.715481, 0.368824,
0.406342, 0.501798, 0.784116, 0.411207, 0.774259, 0.94865, 0.598727,
0.00194757, 0.543631, 0.796012, 0.277605, 0.156438, 0.271751, 0.217822,
0.123887, 0.194943, 0.592318, 0.959311, 0.690951, 0.0651006, 0.66369,
0.311439, 0.97547, 0.696276, 0.257348, 0.809641, 0.191355, 0.285069,
0.483089, 0.86099, 0.592628, 0.283121, 0.939458, 0.0649782, 0.315023,
0.126683, 0.667706, 0.847156, 0.191135, 0.93174, 0.0753886, 0.887845,
0.500184, 0.86664, 0.411698, 0.576406, 0.524714, 0.170364, 0.154351,
0.766766, 0.333359, 0.885295, 0.671262, 0.905775, 0.740731, 0.602173,
0.731804, 0.840797, 0.425709, 0.47549, 0.0640975, 0.993641, 0.234573,
0.543749, 0.988709, 0.105796, 0.734389, 0.67711, 0.57701, 0.52939, 0.209675,
0.506746, 0.42266, 0.762624, 0.876316, 0.621451, 0.751398, 0.856849,
0.135585, 0.019278, 0.0195941, 0.016052, 0.709877, 0.543788, 0.955497,
0.0224109, 0.475303, 0.0000388042, 0.966788, 0.916615, 0.740914, 0.322929,
0.389777, 0.387225, 0.531239, 0.816183, 0.967117, 0.624601, 0.654923,
0.194732, 0.215719, 0.767752, 0.519338, 0.175454, 0.196125, 0.7517, 0.809461,
0.631666, 0.240629, 0.72929, 0.334158, 0.631627, 0.273841, 0.812675,
0.593243, 0.308698, 0.884064, 0.425449, 0.0620045, 0.492515, 0.916946,
0.800848, 0.407082, 0.297782, 0.701227, 0.0330955, 0.887744, 0.122328,
0.505102, 0.281395, 0.0782829, 0.490662, 0.264473, 0.552106, 0.744125,
0.859035, 0.990632, 0.739431, 0.150882, 0.550337, 0.106569, 0.313982,
0.0888772, 0.0578224, 0.189623, 0.513134, 0.681795, 0.76004, 0.488396,
0.480038, 0.794051, 0.637712, 0.983294, 0.198643, 0.715769, 0.14705,
0.718821, 0.646538, 0.971643, 0.288015, 0.728189, 0.907107, 0.820762,
0.737678, 0.62162, 0.593125, 0.731885, 0.679855, 0.431998, 0.079991,
0.0500892, 0.919815, 0.943602, 0.599953, 0.256038, 0.282103, 0.960308,
0.40131, 0.540269, 0.135054, 0.241487, 0.754772, 0.568626, 0.847039,
0.513298, 0.847666, 0.747864, 0.109361, 0.891678, 0.254541, 0.0159792,
0.429506, 0.45968, 0.17455, 0.96589, 0.509691, 0.516078, 0.574597, 0.709852,
0.227587, 0.555771, 0.173287, 0.169583, 0.0925333, 0.314284, 0.418515,
0.600957, 0.245494, 0.800986, 0.57085, 0.853094, 0.136133, 0.909308,
0.316309, 0.837114, 0.706627, 0.449628, 0.141759, 0.871224, 0.196936,
0.93355, 0.567162, 0.161372, 0.969349, 0.377779, 0.393875, 0.991789,
0.876816, 0.0634953, 0.97536, 0.390831, 0.631322, 0.262509, 0.40451,
0.537738, 0.495189, 0.353201, 0.0882012, 0.700624, 0.788562, 0.903573,
0.946442, 0.829399, 0.591625, 0.970023, 0.37928, 0.668027, 0.622276,
0.592244, 0.985405, 0.676238, 0.74546, 0.528749, 0.0100459, 0.285407,
0.114139, 0.266239, 0.605536, 0.747669, 0.61895, 0.913038, 0.517335,
0.0470457, 0.830388, 0.00946538, 0.570893, 0.217646, 0.238763, 0.0394421,
0.191613, 0.549619, 0.616487, 0.447198, 0.206207, 0.873381, 0.871027,
0.918449, 0.196161, 0.587974, 0.756888, 0.65221, 0.590625, 0.840305,
0.137938, 0.739172, 0.0732904, 0.793259, 0.307549, 0.729706, 0.502398,
0.575612, 0.0687861, 0.690264, 0.310785, 0.0259931, 0.452299, 0.243066,
0.104578, 0.152612, 0.581272, 0.324617, 0.908417, 0.564639, 0.824385,
0.672407, 0.317792, 0.724334, 0.686447, 0.933235, 0.244501, 0.931075,
0.378898, 0.203529, 0.742103, 0.355463, 0.310111, 0.513265, 0.431318,
0.32947, 0.857812, 0.270199, 0.32674, 0.176857, 0.27654, 0.945583, 0.418323,
0.612219, 0.452155, 0.273176, 0.100532, 0.887885, 0.765708, 0.339941,
0.85603, 0.95681, 0.386811, 0.136412, 0.113927, 0.601347, 0.0766993,
0.623147, 0.682609, 0.271877, 0.218887, 0.352948, 0.355869, 0.0950198,
0.942347, 0.407365, 0.937545, 0.482801, 0.490192, 0.134189, 0.837014,
0.594916, 0.724483, 0.794248, 0.980983, 0.638107, 0.337673, 0.657837,
0.867056, 0.0367598, 0.260973, 0.0346899, 0.184448, 0.764883, 0.0420863,
0.681742, 0.828579, 0.669863, 0.0997392, 0.274377, 0.891033, 0.187062,
0.609547, 0.140188, 0.0540195, 0.592145
	};

	const double dbarsAr[rowsCount][colsCount]={
//http://library.wolfram.com/infocenter/MathSource/7071/
//Needs/@{"DerivativeBasedAdaptiveRejectionSampling`"}
//(updf[x_]=-x^2/2);
//derpdf[x_]=D[updf[x],x];fun[x_]:=Through[{updf,derpdf}[x]];
//obj=Make[DerivativeBasedAdaptiveRejectionSampling,-Infinity,{-0.5,1.5},
//Infinity,fun];
//SeedRandom[0];
//Table[Random[obj],{i,1,200}]
	{
0.141745, 1.46004, 0.435265, 0.405936, 0.569917, 0.69644, 0.28452, 1.31983,
-0.948686, -0.355268, -2.28089, -1.0315, -1.69986, -0.921566, -1.47095,
-0.690358, 0.0578929, -0.148842, -0.711542, -0.639049, 1.14158, -0.677548,
-0.894439, 2.22401, 0.523814, -0.351621, -0.139481, 1.01296, -2.71976,
-0.764845, 0.808851, 1.23049, 0.674951, -0.257876, 1.10572, 1.75395,
-0.995511, 0.237257, 0.595794, 0.69054, 0.585606, 0.0547851, 1.49416,
0.342468, -0.922238, -0.757723, -0.477841, -0.625136, -1.05489, -0.659164,
-1.15407, 0.388236, -0.33907, 0.00665978, -0.226911, 1.64774, -2.89875,
0.846041, -1.0304, -0.792532, -0.87503, 1.76212, -1.54685, -0.499185,
0.525101, 0.894835, -0.577293, 1.09351, -0.583184, -1.54777, -1.16989,
1.03661, 1.49894, 1.2201, 1.11822, 0.198862, -0.971502, 0.745697, 1.20699,
1.32035, 0.266477, 1.01176, -0.0603491, 2.60336, 2.29275, 0.637665, 0.19831,
-0.822231, -0.198492, 1.15692, 0.691748, -1.12689, -2.06152, 0.562544,
1.70426, -0.0625452, 1.83791, -0.467944, -0.292193, 0.912702, 0.393499,
-0.805756, 0.0410027, -0.876347, 0.874439, -0.722345, -0.441612, -0.618086,
0.230796, 1.19514, -1.57416, 1.38229, -0.246109, 0.523543, 1.21369,
0.00502308, -1.45678, -0.646947, 0.65328, 2.36906, -1.06022, -1.28207,
-1.38752, -0.900858, 0.467792, -0.037129, 0.818464, 2.13572, 0.566456,
0.575598, 1.90916, 0.603957, 0.917385, 0.305047, 0.615273, -0.181381,
0.254675, -0.57974, -0.251611, -1.10844, 0.691832, 1.02829, 1.03096,
-1.23667, -0.663676, -0.178793, -0.939778, 0.0241847, 0.189163, -0.749454,
-0.944755, -1.33115, -0.207084, -0.692012, 0.179532, -1.10342, -0.480246,
0.544648, -1.07765, -0.855219, 0.170068, 1.87704, -0.270944, -1.5292,
0.337762, -0.241472, -0.0106132, -1.35404, 0.804609, 1.61488, 0.23439,
-0.307646, 0.314074, 2.19449, 0.663366, -2.33366, -1.20824, 0.270442,
0.305383, 0.0449081, 0.960354, 0.180996, -0.711864, -0.872776, 0.298954,
-0.820307, 1.13637, -0.856141, 0.699548, 0.231805, -1.09235, -1.45408,
-0.504153, 0.00741735, -1.48758, -0.494894, -0.118789, -1.25911, 0.207677,
1.33258
	},
	{
-1.0069, -0.0888453, -0.831128, -1.5793, -0.714572, -1.31585, -0.473706,
0.449351, 2.24188, -0.762645, -0.40621, -0.646156, -0.861084, 2.15386,
1.04294, -0.34856, -0.137735, 1.02059, -2.72294, -0.757315, 0.80602, 1.25789,
0.674914, -0.254455, 1.1239, 1.74859, -0.984392, 0.237422, 0.596959,
0.690173, 0.586869, 0.0568957, 1.51853, 0.127728, -0.240463, -1.05212,
1.01533, 0.191764, 1.77757, -0.666622, -1.15893, 0.571003, -0.242494,
0.785751, 0.75323, -2.89553, 0.827233, -1.02354, -0.789845, -0.87066,
1.75448, -1.5403, -0.503064, -0.662954, -0.884808, -0.0474979, 0.230706,
1.55874, -0.490513, 0.430597, -0.885626, -1.46475, 1.11678, 0.193279,
-0.95459, 0.730364, 1.2089, 1.3218, 0.258749, 1.00223, -0.0621141, 2.52404,
0.110627, 0.62817, 0.194668, -0.809695, -0.196692, 1.16396, 0.681194,
-1.10443, -2.06919, 0.554977, 1.71459, -0.063567, 1.84927, -0.462767,
-0.288571, 0.902549, 0.316573, -0.863094, 0.732137, -0.935636, 0.680162,
0.335252, 0.610841, 0.335149, 0.889437, -0.503159, -0.190535, -0.0210858,
0.846184, -0.534706, -1.84765, 0.0119911, -1.41872, -0.63189, 0.657138,
2.3761, -1.03278, -1.2465, -1.3493, -0.878755, 0.473413, -0.0301713,
0.822694, 2.14143, 0.571419, 0.58044, 1.91519, 0.608363, 0.920617, 0.309752,
0.619516, -0.172522, -1.64758, 1.59082, -0.657837, 1.76081, 0.100862,
-0.703407, 0.173077, 0.0326771, 0.668846, 1.23965, -2.15419, -0.102648,
1.83136, 0.0396945, 0.554039, 0.140268, -0.95544, -0.485216, 0.256125,
0.847413, 1.05309, 1.33953, 0.985332, -0.12802, 1.13626, 1.50674, -0.988656,
-0.311724, 2.42764, -1.52918, -0.277536, -0.6379, 0.0944436, -0.377421,
0.527194, 1.30549, 0.954255, 1.89024, 0.434891, 0.233669, 0.661652, -2.33993,
-1.20633, 0.267835, 0.303034, 0.0423017, 0.958475, 0.178246, -0.712382,
-0.871756, 0.296549, -0.819792, 1.13558, -0.855267, 0.697873, 0.229045,
-1.09034, -1.45428, -0.504806, 0.00461931, -1.4878, -0.495555, -0.121771,
-1.2577, 0.204893, 1.33436, 0.934877, -0.475671, 0.486964, -0.694213,
-0.309207, 0.651196, -0.497478, -0.174707, 1.07433, -0.450561
	}/*,
	{
0.529408, -0.572962, 0.513134, 1.09102, -0.446931, -2.31367, -1.07024,
-1.65772, -0.991474, -1.41893, 0.316418, 0.101749, 2.20439, -0.789688,
-0.455837, -0.671601, -0.133474, 0.533734, -0.33293, -0.123377, 1.01884,
-2.84025, -0.739753, 0.817716, 1.23135, 0.68474, -0.240307, 1.1094, 1.74923,
-0.964486, 0.247936, 0.605768, 0.700262, 0.595585, 0.0704208, 1.49061,
0.351399, -0.893621, -0.732741, -0.457881, -0.602697, -1.02153, 0.482917,
-0.158708, 1.4697, 0.589565, -0.22761, 0.810946, 0.777513, -0.588444,
-0.606062, -1.15607, 0.238942, -1.51718, -0.491623, 0.5219, 0.891154,
-0.568383, 1.09968, -0.574161, -1.51816, -1.14434, 1.04009, 1.49898, 1.2251,
1.12483, 0.197319, -0.955108, 0.7397, 1.21228, 1.32328, 0.264442, 1.0136,
-0.05877, 2.59868, 0.113766, 0.636344, 0.19926, -0.808387, -0.194002,
1.16929, 0.68976, -1.10335, -2.06418, 0.562148, 1.71744, -0.0596623, 1.85829,
0.656597, -0.278601, 0.0820534, 1.86301, 0.405698, -0.787386, 0.0518405,
-0.856926, 0.890728, -0.704709, -0.427899, -0.602186, 0.241426, 1.20638,
-1.54251, 1.39324, -0.233995, 0.536647, 1.22478, 0.0158325, -1.41932,
-0.630541, 0.666663, 2.42852, 0.129343, -0.485568, -1.57847, 0.034831,
0.715261, -0.0488615, 0.357443, 0.577802, 0.586948, 1.91679, 0.615296,
0.930781, 0.31408, 0.626599, -0.171493, -1.64925, 1.59048, -0.657399,
1.76157, 0.10329, -0.702949, 0.175781, 0.0348913, 0.676323, 1.24054, -2.1487,
-0.100895, 1.83245, 0.0419179, 0.5602, 0.142844, -0.959328, -0.484952,
0.259603, 0.856629, 1.06205, 1.33933, 0.995501, -0.126491, 1.14199, 1.50614,
-0.99265, -0.311227, 2.43815, -1.53094, 0.34045, -0.241218, -0.0102394,
-1.35164, 0.812487, 1.61671, 0.235734, -0.306519, 0.316296, 2.20262,
0.669109, -2.33199, -1.20476, 0.272096, 0.307466, 0.0456673, 0.968802,
0.182121, -0.71053, -0.873064, 0.300945, -0.82023, 1.14137, 0.221495,
0.391493, 0.998431, 0.642341, 0.820357, 0.613393, 0.189654, 0.497326,
-1.94589, -0.699194, -1.02964, -0.457675, 0.161575, 0.447034, 0.597158,
1.50555, 1.48887, -0.832003, -0.372902, 0.0313541
		}
*/
};

const double dbarsAr_1[rowsCount][colsCount]={
		{
0.141745, 1.33381, 0.426831, 1.26225, -1.89854, -0.897882, 0.838643,
-1.54007, -2.30111, -0.044346, 0.142936, -0.135894, 2.24405, 1.12291,
-1.65728, 0.998875, 0.74184, -0.933235, -0.0388802, 1.04855, 0.489241,
-0.754671, 1.70117, 1.012, 0.710938, 0.389866, -0.711446, -1.19651,
-0.0203415, 1.74711, -0.598965, 0.20724, -0.725755, -0.701951, 0.0494646,
-0.143604, -1.24613, 0.0279407, 2.15801, 0.681699, 0.328013, 1.44541,
-1.23486, 0.828028, 1.36543, 1.03439, 0.918938, -0.0265206, -0.387218,
-0.076768, 0.800854, -0.411455, 2.16942, 0.457931, -0.196697, -0.284127,
0.534544, 0.503739, -3.41858, 1.84569, -1.18528, 0.0780855, 0.150777,
0.408558, 0.443995, 0.156452, 0.692409, 1.01228, 0.759334, -1.34742, 1.03379,
-0.290627, 2.86162, -0.119085, -1.24148, 0.700215, -2.29297, 0.964773,
0.124512, 0.303614, 1.61431, -1.4556, -0.156011, 1.0084, 0.830255, 1.05757,
0.154845, -1.88508, -0.129886, 1.03547, 1.176, 0.785608, 1.53973, 1.8992,
2.77731, 2.04471, -1.59957, -0.330269, 1.26241, 0.0256007, 0.268512,
-0.220542, -1.43231, 0.0720815, 1.204, 0.14314, -1.7892, -0.121695,
-0.534143, 0.941237, 0.0132183, 0.022217, 0.470914, 0.626662, 0.445137,
-1.29242, -0.00970714, 1.16948, 0.735443, -1.88325, -0.433613, -0.606454,
-1.54183, -1.49544, 0.094033, 0.723201, 0.867906, -0.520399, -1.00751,
1.47801, 1.42468, -0.350553, 0.785197, 0.629861, -2.46001, -2.30542,
0.309157, -1.10753, -0.577067, 1.62911, 0.45703, -0.935387, -0.549376,
-0.0946363, 0.371496, -2.41213, -0.220742, 0.175092, 1.09752, -0.62542,
1.12166, -2.09823, -0.601381, -2.86214, 0.10954, 0.590989, -0.973066,
1.46301, 0.792074, -1.34962, -0.879902, 1.65352, 0.437317, 0.173572,
0.925062, 0.048294, -1.28388, -1.72524, 0.645622, -1.18075, -2.22984,
-0.723657, 0.189837, 2.37712, -0.75926, 0.538907, -0.43072, 0.944666,
-0.837109, 0.976338, 1.34111, 0.0991566, -0.258803, -1.06002, 1.21002,
-1.44289, 0.638089, 1.00737, 1.71371, -0.597833, 0.0714153, 0.480828,
-0.404158, 0.644062, 0.307913, -0.186949, -1.86538, 1.14846, -1.48996,
-1.52847
		}
		,{
-1.0069, 0.156742, -0.417404, 0.437548, -0.281333, 1.04091, 0.227179,
-1.42126, -0.117095, 0.170918, 0.32806, -0.869292, -1.08031, -0.781675,
-0.633754, -0.303382, -0.10267, 2.09981, -0.580473, 1.42548, 0.46753,
0.435109, -1.56679, 0.35183, 0.568393, 0.915227, 1.0314, -0.693608, 0.401515,
-0.26384, 0.059707, -0.22768, 1.12433, 0.851969, -0.331733, -0.72248,
-1.14998, 1.58311, -0.667841, -0.369045, -0.37373, 0.270167, 0.31521,
1.35972, 0.306363, -0.345251, -0.015306, -0.130807, -0.189045, -1.49638,
0.627692, 0.73079, 1.67192, -0.106333, 0.963331, 0.164454, 1.96056, -0.56965,
1.9271, -0.504757, 2.23061, 0.5194, -1.19926, 0.0095152, -0.317078, 0.563346,
-1.5221, 0.739839, -0.571485, -0.440377, 0.0709085, -0.747549, -0.0910522,
1.40917, -0.260453, 0.0130628, -1.45343, 0.826262, 1.2158, 0.0783399,
0.0412418, 0.963945, 1.15625, -1.91127, 0.189972, -0.382944, 0.0918011,
0.454509, -0.703767, -0.174849, 0.159959, 1.05823, -0.4264, -0.590481,
-1.2988, -0.848062, 0.241531, -0.510632, -0.0275028, 0.473148, 1.13515,
0.242954, -0.14626, -1.01411, -0.2157, -0.737154, -0.633909, -0.654967,
1.53957, 1.48028, 0.152267, -1.56139, -0.206021, 0.122424, 0.70234,
-0.578689, 1.11168, 2.44343, 1.59295, -0.839182, 0.2639, -0.173227, -0.27531,
-0.630458, -0.334442, 1.23416, -1.51948, 1.13123, -1.66876, -0.429953,
-0.434543, 0.450697, -0.434158, 0.602726, 1.61313, -1.4758, -0.375996,
-1.02527, -0.666235, -1.46841, -0.356521, 0.677749, 1.56872, 2.22185,
1.00662, 0.108562, -0.118864, -1.16429, 0.513448, 0.161982, -0.189252,
1.27415, -0.342396, -0.0141248, 1.49332, -1.12614, -0.0865247, -0.316942,
0.951224, -0.10252, 0.577158, -0.0862558, -1.50196, -2.05539, 0.6763,
1.44124, 2.1768, -1.88302, -1.30918, -0.805962, -1.45817, -0.136336,
-0.0609584, 0.402924, 0.5517, 1.46616, 0.704505, 0.20012, -0.823511,
-0.862812, -0.292884, 0.465785, 0.425288, 1.16758, 3.24276, -0.0773998,
0.0257699, -1.71858, 0.108825, -0.67329, -1.22934, 0.29387, 0.347636,
-0.442009, -0.824865, -0.540887, -0.618095, -1.14491, -0.0768351, -0.283569
		}

	};
}//adaptive_rejection_sampling
}//libs


