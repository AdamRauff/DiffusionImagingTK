/*=========================================================================
 *
 *  Copyright Section of Biomedical Image Analysis
 *            University of Pennsylvania
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include <stdio.h>
#include <iostream>

#include <itkReplaceSpecialFunctions.h>
#include <vnl/vnl_math.h>
#include <cmath>
#include <cstdlib>

static double percision  = 1e-10; //This is a percent error. since there is such a dynamic range!
static bool passed = true;

bool
areEqual(double x, double y)
{
  //Compare binanry significant and eponent
  // x = xSig * 2^xExp
  double xSig,ySig;
  int xExp,yExp;

  xSig = frexp(x , &xExp);
  ySig = frexp(y , &yExp);

  if (xExp != yExp)
  {
    std::cerr << xExp << " : " << yExp << std::endl;
    return false;
  }

  if ( vcl_abs(xSig - ySig) > percision )
  {
    std::cerr << vcl_abs(xSig - ySig) << std::endl;
    return false;
  }
  return true;
}


int testLegendre()
{
  passed = true;
  const double exp1[231] = {1, 0.117496875, 0.11876657713241551, -0.4099625, \
-0.712599462794493, 2.819925, 0.0023009192724609373, \
0.0046515672225017615, -0.0113546042578125, -0.07659924621265846, \
0.165669377734375, 1.5319849242531693, -4.0876575328125, \
-23.443898801408874, 92.77306506562499, 0.00001802338827609558, \
0.00005465446124963865, -0.0000781679799836792, \
-0.0013604235149584914, 0.00028235248564050354, 0.04926065019936351, \
0.01360238744475678, -2.0689473083732675, 0.4743521758760459, \
82.27841418468955, -141.82798288238754, -2181.6311988095763, \
8633.231821671025, 7.563184997688813e-8, 3.057965905543399e-7, \
-1.282557183575731e-7, -9.562822766772713e-6, \
-0.00001877866269040974, 0.0004593036041558838, 0.001823120200970439, \
-0.028471216556953546, -0.14200785607336755, 2.0499275921006554, \
9.188525812891012, -152.7827508864132, -374.7920614402738, \
9924.649379234539, -5590.557181520847, -399882.36328970117, \
1.5824293059071682e6, 1.974779116167373e-10, 9.980595493274848e-10, \
5.902435625279642e-10, -3.553977531565993e-8, -1.5760654853735383e-7, \
1.9387756624128256e-6, 0.000017507840338264303, \
-0.00013909574028626382, -0.0019266666213059575, \
0.012518470302250746, 0.2144068691933633, -1.3770317332475819, \
-22.888799461114775, 171.85556903848467, 2119.8661156837666, \
-21127.393658662277, -137398.69583416366, 2.1068418795227977e6, \
1.8894799323521291e6, -1.2140905409193549e8, 4.804444077428892e8, \
3.5156117418928534e-13, 2.1321614201797787e-12, \
3.4161434642518086e-12, -8.08141292834831e-11, \
-5.930588947228966e-10, 4.390516279367885e-9, 7.483875420768244e-8, \
-2.735764114441897e-7, -0.000010121014905407126, \
0.000016745621447894318, 0.0014828160149345548, \
-0.0010130035024180644, -0.22886564144226182, 0.15802854637721803, \
35.62317194278774, -60.344521449631976, -5251.980861090017, \
19307.081383793044, 665480.1001509816, -4.45070661375265e6, \
-6.0118923997431405e7, 6.881450009799143e8, 1.919873870005875e9, \
-5.51206727244924e10, 2.1812556863720306e11, 4.539268059183701e-16, \
3.2118244085472545e-15, 8.392508914997485e-15, \
-1.2253931462039473e-13, -1.335864982117987e-12, \
5.502428009832392e-12, 1.8533229697725374e-10, \
-9.994879276967799e-12, -2.857653383749574e-8, -8.497687841441163e-8, \
4.929038188471468e-6, 0.000026110212241641528, \
-0.0009363610122243557, -0.006272962872876183, 0.19159271546294465, \
1.3173222033039984, -40.90024901395985, -232.66079042584, \
8696.413275021743, 28486.05849633546, -1.724303238094521e6, \
101319.00776840851, 2.893244953932346e8, -1.1854071751224713e9, \
-3.453480387860448e10, 3.167888412737937e11, 1.6923135914236997e12, \
-3.4973136682338195e13, 1.383969924313346e14, 4.444581764511666e-19, \
3.594088867171675e-18, 1.3024294878812834e-17, \
-1.306782379224017e-16, -2.0307740177329397e-15, \
2.842361023878983e-15, 3.001102822680852e-13, 1.0563042786614507e-12, \
-4.981533596054113e-11, -4.1267547006087713e-10, \
9.300140243449174e-9, 1.2311727812845028e-7, -1.9395146493766653e-6, \
-0.000034946501197892935, 0.0004512875954170109, \
0.009751933646499277, -0.11691899295949307, -2.652525951847803, \
33.142561007425286, 682.6812987608864, -9851.009026601376, \
-157582.2144359999, 2.880666997925124e6, 2.9399507164189324e7, \
-7.665636304196954e8, -3.250904273013291e9, 1.6809988088196405e11, \
-2.5791748433313074e11, -2.5798305356128137e13, \
1.9257097957852756e14, 1.7273657318211892e15, -2.9553612863529788e16, \
1.169506519516187e17, 3.4132318170725925e-22, 3.10510448797766e-21, \
1.4390967500019938e-20, -1.0098547352174163e-19, \
-2.2334543033072076e-18, -2.4730446804124903e-18, \
3.411041896935647e-16, 2.5287278182145675e-15, \
-5.757358329730441e-14, -8.776435467258612e-13, \
1.051646881923382e-11, 2.794842078043019e-10, -2.0189447255014926e-9, \
-8.996754826082751e-8, 4.025613512354506e-7, 0.000029783373610123974, \
-0.00008768741504032061, -0.010095848521310277, 0.024711247655910804, \
3.4527801942881147, -10.19629262088848, -1163.6387896174324, \
5190.274385233461, 373508.07686323364, -2.615129110477199e6, \
-1.0860435333109097e8, 1.1687615950179663e9, 2.633527889192031e10, \
-4.3535502244245435e11, -4.436192364206722e12, 1.2566508584741411e14, \
1.694620615967076e14, -2.4487112503432708e16, 1.4614815691256672e17, \
2.1243428079594307e18, -3.2085504125362844e19, 1.2696994587379733e20, \
2.110758274508428e-25, 2.1335676835429832e-24, \
1.2044890883944524e-23, -5.684281903304104e-23, \
-1.8615027193915427e-21, -6.64021164186497e-21, \
2.8473073312637514e-19, 3.4090977029720014e-18, \
-4.536732197344439e-17, -1.1751472327011922e-15, \
6.532634723192027e-15, 3.9731178259769564e-13, \
-3.485458867006611e-13, -1.3967374980487192e-10, \
-3.672701510169351e-10, 5.16829605196638e-8, 2.7383900935518397e-7, \
-0.000020119587836448062, -0.00014223182390787277, \
0.00818574054588611, 0.06359000129901157, -3.438011029272166, \
-24.970219005266145, 1462.328663994664, 8120.47420999449, \
-613046.5472897362, -1.6990114602270254e6, 2.4424026771769354e8, \
-2.2185224103089952e8, -8.800645891046568e10, 4.7751323920720526e11, \
2.662876457618381e13, -2.960699752061699e14, -5.873467886600775e15, \
1.167525712687476e17, 5.717857451959219e17, -2.885277455895449e19, \
1.3039508769667305e20, 3.1498751786101344e21, -4.352026202116336e22, \
1.7221999354133882e23};

  const double exp2[231] = {1, 0.076483875, 0.24366210177159273, 0.08219350000000003, \
-1.4619726106295563, 1.8356130000000002, 0.0009749638558359376, \
0.006212073911378592, 0.021885899073187498, -0.017245002506308157, \
-0.42141572219562495, 0.3449000501261632, 7.878923666347499, \
-31.308852513348107, 39.31054266730501, 4.971267578618259e-6, \
0.00004751234845286413, 0.0003187565354583276, 0.0009857155815635372, \
-0.004852261406390102, -0.0509440809106113, 0.11294170544047111, \
2.1396513982456744, -8.151799162735372, -59.61607837296274, \
578.3518579355896, -1896.5409107232872, 2381.245124186272, \
1.3579350288378274e-8, 1.730442152393002e-7, 1.7122235094074738e-6, \
0.000011173063252611097, 0.000017074391903403802, \
-0.00047220819512660834, -0.003281002712139478, 0.020713132184586466, \
0.26266410734132073, -1.4913455172902255, -16.53625366918297, \
157.07533402691502, 340.7775433648944, -11595.816212287491, \
74634.35985130534, -226285.48479910786, 284117.89289929083, \
2.3080029556389727e-11, 3.676414479954371e-10, 4.8089390569501765e-9, \
4.731084002486075e-8, 2.6784685855747674e-7, -6.572199427152259e-7, \
-0.000026662172037500893, -0.00011073074210418914, \
0.002083744355787802, 0.018154383757522267, -0.19612629950247928, \
-1.996982213327449, 24.754882946759086, 136.81004648456778, \
-3228.281385985765, 7161.91394355941, 233504.31432328917, \
-2.8046451682506693e6, 1.5394312485333106e7, -4.4721780855853334e7, \
5.615145025651678e7, 2.67462135695033e-14, 5.11248046423673e-13, \
8.31611966602391e-12, 1.0894993650505858e-10, 1.013051830359909e-9, \
3.757715380708783e-9, -5.9405568295886506e-8, -9.961418024204116e-7, \
-4.4866238223527844e-7, 0.00013261659056012403, \
0.0006983416934242184, -0.01766771369160489, -0.13568749568479177, \
2.756163335890363, 16.776960842823424, -477.89714574246295, \
-232.8191655297191, 70300.61819877577, -528245.3450436286, \
-3.809230539951102e6, 1.0269399301956849e8, -9.277258175985606e8, \
4.673662278448275e9, -1.3216793053867037e10, 1.6594645461614202e10, \
2.2479714894210926e-17, 5.013106625213128e-16, 9.751549109479838e-15, \
1.5932796133371133e-13, 2.031105172001022e-12, \
1.6420647983373817e-11, -8.32478859236771e-12, -2.372133768777194e-9, \
-2.5167961055415428e-8, 1.5797842645578168e-7, 5.78845099425305e-6, \
6.865758937978479e-6, -0.0011133039252183802, -0.004947375161121768, \
0.22368654989963943, 1.0389487838355713, -48.629115453538844, \
-61.17885548382359, 10212.694676615087, -52957.73133995493, \
-1.518630530591063e6, 2.4046537540506903e7, -1.2995928383911155e7, \
-3.5375572210793157e9, 5.250816490500626e10, -4.118949123371524e11, \
1.9663582443049873e12, -5.458706358297308e12, 6.853803061439258e12, \
1.4327797533370558e-20, 3.6516363855664075e-19, \
8.266539741107334e-18, 1.6170847866363693e-16, 2.604618964504881e-15, \
3.1028540633966033e-14, 1.7903182414908986e-13, \
-2.1748283149961094e-12, -6.37623191292454e-11, \
-3.775695644778346e-10, 9.562650942755223e-9, 1.782349947296073e-7, \
-8.946102362876164e-7, -0.000050615311938326246, \
-9.276504187712894e-6, 0.013434119916111759, 0.02390384579126703, \
-3.654080617182398, -0.6812664675456349, 988.7721433276809, \
-4543.82415507489, -228129.3542745236, 2.961978234992311e6, \
2.689851934792353e7, -9.811812746662964e8, 6.693297381366717e9, \
1.0028056381839998e11, -2.8155477350021436e12, 3.308824851800706e13, \
-2.3829798011893547e14, 1.0963616535399251e15, -3.002681682223801e15, \
3.770085356372305e15, 7.162388729200145e-24, 2.053612506317007e-22, \
5.303187734578376e-21, 1.2078375030491694e-19, \
2.3450186979771385e-18, 3.635182017298453e-17, \
3.7755889300484777e-16, 4.555174463631531e-16, \
-7.130584382998141e-14, -1.2415097748164379e-12, \
1.7068095856958252e-13, 3.3738265876358004e-10, 3.713099598052564e-9, \
-6.572725262111344e-8, -1.6819712899687987e-6, \
0.00001044733706578271, 0.0006049751687733204, \
-0.0015829771585692447, -0.20821307934761535, 0.5413781882306817, \
70.34651262496169, -408.1782949470958, -21685.868442738774, \
272872.3878619364, 4.809559531926505e6, -1.3110302642144044e8, \
1.896885283510157e7, 3.725374189647949e10, -5.391944614698517e11, \
-7.991223898291847e11, 1.3909524460702908e14, -2.49095960056785e15, \
2.5710280525995196e16, -1.748006111814768e17, 7.828374793560356e17, \
-2.1220281893394737e18, 2.664360811137655e18, 2.8831960224502775e-27, \
9.185277323484602e-26, 2.664602934177712e-24, 6.923544069765893e-23, \
1.5710807865829139e-21, 2.979431079942548e-20, 4.290951596976082e-19, \
3.312265327766537e-18, -3.3535315236555e-17, -1.5154582924929378e-15, \
-1.6895513107047818e-14, 2.0066369334016264e-13, \
8.45225141700197e-12, 3.7877664541538356e-11, -2.654272586669425e-9, \
-3.968567836214102e-8, 7.190900182117716e-7, 0.000020456021032606475, \
-0.00019563563087112023, -0.009092048119163093, 0.06729298375967119, \
3.8186602100484985, -34.345791355733866, -1486.7812477285388, \
21324.03254490015, 470738.6700014028, -1.2278807659242207e7, \
-6.623471440460764e7, 5.379925542569677e9, -4.444796720424705e10, \
-1.235004180345787e12, 3.4340192422578816e13, -2.188535606406241e14, \
-5.706637277534702e15, 1.7594856257204278e17, -2.5655751837246684e18, \
2.4351315352361366e19, -1.5882325182080356e20, 6.968238005714062e20, \
-1.8736020372753573e21, 2.3524436993167304e21};

  const double x1 = 0.245;
  const double x2 = 0.623;

  unsigned int counter = 0;
  for( int l=0;l<=20;l=l+2 )
  {
    for (int m=-l;m<=l;m++)
    {
      double val = LegendreP( l, m, x1 );
      if ( !areEqual(val, exp1[counter]) )
      {
        printf("Failed Legnedre test- (%d,%d) : (%f,%f,%f)\n",l,m,val,exp1[counter],val/exp1[counter]-1);
        passed = false;
      }
      ++counter;
    }
  }

  if (!passed)
  {
    std::cout << "[FAILED] 1st Legendre" << std::endl;
    return EXIT_FAILURE;
  }

  counter = 0;
  for( int l=0;l<=20;l=l+2 )
  {
    for (int m=-l;m<=l;m++)
    {
      double val = LegendreP( l, m, x2 );
      if ( !areEqual(val, exp2[counter]) )
      {
        printf("Failed Legnedre test- (%d,%d) : (%f,%f,%f)\n",l,m,val,exp2[counter],val/exp2[counter]-1);
        passed = false;
      }
      ++counter;
    }
  }

  if (!passed)
  {
    std::cout << "[FAILED] 2nd Legendre" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Passed Legendre" << std::endl;
  return EXIT_SUCCESS;

}

int testBinomialCoeff()
{
  int n,k;
  passed = true;

  //Test cases
  //if (n<0 or k<0 or k > n)
  n = -1;
  if (binomialCoeff(n,k) != 0 )
  {
    std::cerr << "binomail coeff failed n=-1" <<std::endl;
    return EXIT_FAILURE;
  }

  n = 1; k = -1;
  if (binomialCoeff(n,k) != 0 )
  {
    std::cerr << "binomail coeff failed n=1, k=-1" <<std::endl;
    return EXIT_FAILURE;
  }

  n = 3; k = 4;
  if (binomialCoeff(n,k) != 0 )
  {
    std::cerr << "binomail coeff failed n=1, k=-1" <<std::endl;
    return EXIT_FAILURE;
  }

  //Test n=0;
  n=0;  k=1;
  if (binomialCoeff(n,k) != 0 )
  {
    std::cerr << "binomail coeff failed n=0" <<std::endl;
    return EXIT_FAILURE;
  }

  //test k > n
  n=20; k=21;
  if (binomialCoeff(n,k) != 0 )
  {
    std::cerr << "binomail coeff failed k>n" <<std::endl;
    return EXIT_FAILURE;
  }

  //test k=0
  k=0;
  if (binomialCoeff(n,k) != 1 )
  {
    std::cerr << "binomail coeff failed k=0" <<std::endl;
    return EXIT_FAILURE;
  }

  //test k< n-k
  k = 12;
  if (binomialCoeff(n,k) != 125970 )
  {
    std::cerr << "binomail coeff failed k<n-k" <<std::endl;
    return EXIT_FAILURE;
  }

  //test k= n-k
  k = 10;
  if (binomialCoeff(n,k) != 184756 )
  {
    std::cerr << "binomail coeff failed k=n-k" <<std::endl;
    return EXIT_FAILURE;
  }

  //test k= n-k
  k = 3;
  if (binomialCoeff(n,k) != 1140 )
  {
    std::cerr << "binomail coeff failed k=n-k" <<std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Passed BinomailCoeff test" << std::endl;
  return EXIT_SUCCESS;
}



int LegendreP_derivatives()
{
  passed = true;

  const double expFirst1[231] = {0, -0.06125, 0.45380559751174027, 0.735, \
      -2.7228335850704415, -1.47, -0.00239889453125, 0.01534876223859227, \
      0.07308809375, -0.19084241650913505, -1.5801428124999999, \
      3.8168483301827014, 26.311713749999996, -77.35776168250504, \
      -96.72342749999999, -0.00002818626108764648, 0.00015185231057743628, \
      0.0013216919323193357, -0.0013549919249257263, -0.050661969221240236, \
      -0.0011904244829291592, 2.133984588889453, 0.04999782828302468, \
      -85.1121082916836, 81.94991161950794, 2398.0778420002034, \
      -6061.458310857409, -13501.264159000406, -1.577046474158363e-7, \
      6.902183906113261e-7, 9.662854292154235e-6, 6.9064485490578645e-6, \
      -0.000493320071028028, -0.0015212840351141348, 0.03031658334229148, \
      0.13905098088111117, -2.1143669885539875, -10.011670623440004, \
      152.79558004514908, 506.03992144036584, -9845.879305605793, \
      -7167.766461518858, 421195.56265229586, -902580.8977246429, \
      -3.2996212022426655e6, -5.147167567871554e-10, 1.7324572998029672e-9, \
      3.788772016328272e-8, 9.771799407871114e-8, -2.2461973726419493e-6, \
      -0.000015531535496683608, 0.00016172154991189082, \
      0.001878467390170579, -0.013916340872513476, -0.21788386146029295, \
      1.4203186737861144, 23.967224760632224, -165.32612956546012, \
      -2320.8840299035537, 19581.40051601966, 169251.59053912753, \
      -1.9581964864485478e6, -5.792843665426153e6, 1.2128567167169093e8, \
      -2.1074494218854588e8, -1.2522554312296376e9, \
      -1.0995929169568328e-12, 2.589584934572334e-12, \
      9.225853337301628e-11, 4.2212732290936645e-10, -5.765155768625103e-9, \
      -6.918073774440502e-8, 3.992144613949823e-7, 0.000010082636693477144, \
      -0.000027823996454232198, -0.0015163342813159142, \
      0.0018178250715681385, 0.23579598970833096, -0.16299616776549875, \
      -36.78417439449964, 43.671429519352955, 5464.262216150029, \
      -14438.383721635842, -711560.9353034212, 3.549889125807778e6, \
      7.012914824396019e7, -5.84419126955798e8, -3.5944804406434937e9, \
      5.18493293274825e10, -6.694599307532834e10, -6.822406678830576e11, \
      -1.6563939937764402e-15, 2.226580132991243e-15, \
      1.5264094233815626e-13, 1.0265256812124784e-12, \
      -9.157264980698973e-12, -1.782505762106865e-10, 3.96756901196924e-10, \
      2.945660027638963e-8, 4.295809998325045e-8, -5.194726407871514e-6, \
      -0.00002179206460974835, 0.000986211992106498, 0.005982037161270231, \
      -0.19925044308938733, -1.358732177023359, 41.84259304877135, \
      261.29538320428367, -8787.858922303212, -38448.23121995661, \
      1.7413828689427401e6, 2.5920845167833064e6, -2.98604258193687e8, \
      6.193820079112931e8, 3.8401140665954666e10, -2.36733767563435e11, \
      -2.65377590936003e12, 3.0779394331648496e13, -2.424494038903678e13, \
      -5.050152227872844e14, -1.8535344575000116e-18, \
      6.180186908574931e-19, 1.8231218806357093e-16, \
      1.6518227504937802e-15, -9.283449264703312e-15, \
      -3.0139491139052366e-13, -3.072860285253917e-13, \
      5.3859165209710776e-11, 3.21774870317459e-10, -1.034542305028566e-8, \
      -1.1244324196495917e-7, 2.1609328754730805e-6, \
      0.000034022942176555335, -0.0004927997204580629, \
      -0.009823233394307577, 0.12313613207588393, 2.735908004985941, \
      -33.49302792464042, -721.4182604779485, 9626.862251137078, \
      172806.27944754084, -2.7658553936623414e6, -3.4828672233875595e7, \
      7.370206400651217e8, 4.951505555713984e9, -1.657581000647398e11, \
      -1.721192103163848e11, 2.734874869293183e13, -1.1793397827509272e14, \
      -2.4341706026184135e15, 2.4179414631240096e16, -5.08186798018744e15, \
      -4.8772207308741766e17, -1.6013566651549387e-21, \
      -1.0847255753449954e-21, 1.6417494059521124e-19, \
      1.90884212551803e-18, -5.599164199256157e-18, -3.602064219081145e-16, \
      -1.5413321222783502e-15, 6.663351599389838e-14, \
      7.551694399156739e-13, -1.2905836055736721e-11, \
      -2.6634124385621326e-10, 2.5923337559407e-9, 8.963830487015062e-8, \
      -5.324639136227578e-7, -0.000030299910051142408, \
      0.00011373254840885285, 0.01036750052545331, -0.02811947955202714, \
      -3.561318209320131, 9.616862006793282, 1205.5329610997107, \
      -4443.539764937754, -390660.57019800955, 2.2105701024521613e6, \
      1.1610805264692603e8, -1.0073511251105632e9, -2.9600184466779602e10, \
      3.8726290773649493e11, 5.710376002907861e12, -1.1689636690954311e14, \
      -5.678371574371196e14, 2.4682660746243044e16, -6.138803174497696e16, \
      -2.762513743340173e18, 2.4234913622042477e19, 1.1208629872963158e19, \
      -5.956939932481676e20, -1.1003181515562962e-24, \
      -1.857541024703186e-24, 1.1513965127288373e-22, \
      1.6681502232651338e-21, -9.141224247731156e-22, \
      -3.1964232532319793e-19, -2.4772706568994926e-18, \
      5.834478773685164e-17, 1.0701906287851964e-15, \
      -1.0107249576357804e-14, -3.9277426268682775e-13, \
      1.2915192018367041e-12, 1.4333761427373772e-10, \
      1.2397819791824816e-10, -5.3881975709815166e-8, -2.15092542634619e-7, \
      0.000021037545646604806, 0.0001309706521288457, \
      -0.008517203083746762, -0.06345537636201579, 3.5460847761595753, \
      26.65125807204663, -1495.2801733825816, -9519.187982724421, \
      623851.3908851247, 2.5513581126946895e6, -2.492609159148055e8, \
      -2.1679426730515063e8, 9.123553645021698e10, -2.860776763915145e11, \
      -2.8710454265406152e13, 2.2902965857555772e14, 6.984130848979279e15, \
      -1.0052109589707211e17, -1.015793819465439e18, 2.7524262032369517e19, \
      -1.416864341185844e19, -3.826667965349233e21, 3.0110320891467655e22, \
      3.78899027828823e22, -8.977663962898589e23 };

  const double expFirst2[231] = { 0, -0.15575, 0.14301697410730754, 1.869, \
      -0.8581018446438451, -3.738, -0.00397078784375, \
      -0.009003959993474673, 0.06661411925000002, 0.5211832938332439, \
      -0.44092357750000044, -10.423665876664879, 23.98108293000001, \
      45.37995836711235, -160.10216586000004, -0.000030370124109289457, \
      -0.0001656188262343133, 0.000038068538676208066, \
      0.009214110892299792, 0.055246375081641305, -0.1962564503731894, \
      -2.73535115107191, 8.242770915673956, 92.8139101371574, \
      -557.2694267662916, 69.07155657411158, 6610.97356302984, \
      -14547.338040548226, -1.1061070362425627e-7, -9.555818035659776e-7, \
      -3.8235552394679595e-6, 0.00003505335251454198, \
      0.0006732153440407975, 0.0027520749426253673, -0.03316122786762944, \
      -0.31470247621598396, 1.9065506094639773, 22.658578287550842, \
      -167.13258845285236, -915.4502089149023, 13436.30112250385, \
      -36379.659202964205, -166665.50604281167, 1.24958983105044e6, \
      -2.314284511294154e6, -2.349982008238796e-10, -2.778839881659328e-9, \
      -2.131138731118204e-8, -5.2185640384875445e-9, 2.476507870505234e-6, \
      0.00003073931111161475, 0.00003297079224592581, -0.00300211334052289, \
      -0.01896545173516406, 0.26921435249585157, 2.552961477918359, \
      -29.613578774543676, -225.30956661374904, 3709.1710744828415, \
      3992.1351770972524, -334975.07692196826, 2.1589772429399723e6, \
      309362.93686731486, -6.82217328768486e7, 3.380322564245158e8, \
      -5.717275947023139e8, -3.267922366734273e-13, -4.905392685075204e-12, \
      -5.4608886180147674e-11, -2.9671118301127537e-10, \
      3.4479217023984337e-9, 1.0272709353629204e-7, 9.105609758596466e-7, \
      -4.497726158566888e-6, -0.00017136563025196887, \
      -0.0004876807587048619, 0.024008663891080403, 0.15547515130622966, \
      -3.5235060064230197, -24.254123603771824, 576.7841413193156, \
      1757.4063820688402, -88924.77866534327, 317417.5892104679, \
      8.09687729070254e6, -1.0413539673274769e8, 3.4951898474170697e8, \
      2.5265423154880943e9, -3.0690213904805275e10, 1.268142938053681e11, \
      -2.027577209428585e11, -3.2044021257308757e-16, \
      -5.830901592072993e-15, -8.45394359681731e-14, \
      -8.120997674399638e-13, -3.1183727418203314e-13, \
      1.6111632134225164e-10, 2.964749243585138e-9, 1.5268011276887174e-8, \
      -3.557155236047337e-7, -6.595752966335269e-6, 0.00001479768336596936, \
      0.0014442304723649812, 0.004057666058416195, -0.29100042063459625, \
      -1.3282022268203946, 61.1100883332652, 177.23885343161942, \
      -12869.133354712085, 26107.886598316487, 2.211036794151525e6, \
      -2.14638147747411e7, -1.5477323040167663e8, 4.628305982594175e9, \
      -3.470984863539549e10, -8.061622431962219e9, 2.0994416781502546e12, \
      -1.7047016327211828e13, 6.349192621431934e13, -9.769848595843438e13, \
      -2.334143729848901e-19, -4.990943658981964e-18, \
      -8.889315457207661e-17, -1.1893239892197657e-15, \
      -7.843271915612626e-15, 1.186459022540476e-13, 4.603203062403043e-12, \
      6.158490261111092e-11, -3.6687865202303776e-11, \
      -1.4916044793404793e-8, -1.6943786437229416e-7, \
      2.0510625110633583e-6, 0.00006106357958154693, \
      -0.00014274860857855525, -0.017193199978264684, \
      -0.016880442811785246, 4.671412189160492, 4.591480444805587, \
      -1262.6686064037585, 2788.5997785264217, 310148.66211386264, \
      -2.6252283786099884e6, -5.248244126640825e7, 1.0626373447890733e9, \
      -5.645567293594704e8, -1.8953499204345728e11, 2.578378456804152e12, \
      -1.0765997837261834e13, -9.963842461211169e13, 1.7526199410210348e15, \
      -1.1789581733985236e16, 4.103972443990109e16, -6.141851931586744e16, \
      -1.3126790975426263e-22, -3.2250069680207054e-21, \
      -6.801680669451925e-20, -1.153185367037324e-18, \
      -1.3045126206795801e-17, -1.505903582243265e-18, \
      4.03077542666389e-15, 9.625991280113866e-14, 8.611302837370773e-13, \
      -1.1595018688743375e-11, -4.2992298821296617e-10, \
      -2.3422286859068054e-9, 1.0671017009792818e-7, 1.8156347953329044e-6, \
      -0.00002020623240965664, -0.0007414940632910572, \
      0.0032556508788421736, 0.2645698559688238, -0.692103139583196, \
      -90.48289074133776, 378.5670841917679, 28970.23237230667, \
      -260521.50852547964, -7.537765269813814e6, 1.382211551818233e8, \
      9.101631673033803e8, -4.778005679241722e10, 3.479294664266082e11, \
      6.51162169403802e12, -1.6887048383448525e14, 1.4849648738656968e15, \
      1.031900182127895e14, -1.4302395736249328e17, 1.6689124692252078e18, \
      -1.0040396111079301e19, 3.33244741931843e19, -4.883078645024467e19, \
      -5.871273918804856e-26, -1.6295090327608892e-24, \
      -3.967603662090687e-23, -8.100745814690682e-22, \
      -1.2494835025032717e-20, -9.351606632864998e-20, \
      1.8821642444111932e-18, 8.67145080081037e-17, 1.5276333582306691e-15, \
      4.626144394126621e-15, -4.285585837345602e-13, \
      -8.966619253599356e-12, 2.0424705172451403e-11, \
      3.6632140922541383e-9, 3.451925854343718e-8, -1.1213291724307843e-6, \
      -0.000023222499505052476, 0.0003125867471875719, \
      0.011224974827308744, -0.09528542332300695, -4.881812340863689, \
      40.01987779566292, 1970.6565806823232, -22719.37994520756, \
      -688644.4293179318, 1.3300843655664898e7, 1.5968794551217175e8, \
      -6.40567316227498e9, 1.3000487992547462e10, 1.9861490231884683e12, \
      -3.1326165656044543e13, -1.0482814964680581e14, 9.96943065672284e15, \
      -1.4939873317328794e17, 7.717730807358029e17, 8.052627921736006e18, \
      -1.9366646869387077e20, 1.858277754136462e21, -1.0375732262083714e22, \
      3.3238533100502723e22, -4.7904621224876585e22};

  const double expSecond1[231] = {0, -0.25, -0.38712086719251637, 3, 2.3227252031550982, \
-6, -0.008540885416666666, -0.04358944070690092, 0.22828958333333338, \
1.4436356424973222, -4.3486875000000005, -28.872712849946442, \
82.18424999999999, 219.69078116278064, -344.3685, \
-0.00008565950561523437, -0.0008164738245911643, \
0.002766169324544271, 0.04622267999812714, -0.03774742670898437, \
-2.1459339616092374, 0.5046433957031251, 90.12922638758799, \
-63.41567687109375, -2795.54768628673, 5018.937622453125, \
32591.022361440584, -41031.040244906246, -3.970626539150783e-7, \
-6.104697441281216e-6, 9.635531324384416e-6, 0.0004655126380778913, \
0.0008411836122758381, -0.03129613448957091, -0.11558963163486376, \
2.2210944322061046, 9.775287441571328, -159.91879911883956, \
-582.5717434397134, 10410.346176610863, 16788.67900724609, \
-483126.1466623169, 420004.5778319532, 7.982956368358633e6, \
-8.307658480236843e6, -1.027616982222451e-9, -2.4396771462764208e-8, \
-6.568200670546862e-9, 2.238998398984141e-6, 0.000010851275421741603, \
-0.0001801231110934823, -0.0016474961130495333, 0.01583997160161822, \
0.20949016930842648, -1.5643787862083154, -24.35043427869333, \
172.0816664829147, 2488.7432113841073, -19570.60171323134, \
-199480.41096430604, 1.9628531288446938e6, 9.459956486079922e6, \
-1.327305970076218e8, -2.1026037633527122e7, 2.9677477142392793e9, \
-2.50009141968542e9, -1.622097868270097e-12, -6.051427842766742e-11, \
-1.3221895893735788e-10, 6.223453421635506e-9, 5.246172439406761e-8, \
-5.212326668793563e-7, -9.162998256050652e-6, \
0.000042918428958940354, 0.0014819196159542142, \
-0.0033990117411398144, -0.23843032085135873, 0.28989163474755775, \
37.89799935401233, -45.223095020619006, -5728.050028133042, \
12248.678710371434, 768995.3560395752, -3.0288780980806313e6, \
-8.147908208356974e7, 5.283783341575214e8, 5.318093109614021e9, \
-5.299368314551782e10, -7.430710303579398e10, 1.564416138853604e12, \
-1.0064280298230763e12, -1.5800174910550256e-15, \
-1.0205773227770373e-13, -4.2760464503249726e-13, \
1.11302496312806e-11, 1.4247986459722503e-10, -8.177820276988574e-10, \
-2.7773788370848884e-8, 1.7034107568975675e-8, 5.242343703103561e-6, \
0.000013872331771037589, -0.0010232988935639758, \
-0.0050532223217909684, 0.2080719060150971, 1.2904768147493229, \
-43.51206044199034, -271.00013109735784, 9088.58085473944, \
45027.849207229214, -1.8054293235379613e6, -4.650300901654812e6, \
3.1632213598295677e8, -1.726763104669076e8, -4.335799769718806e10, \
1.761776222402513e11, 3.683391844521526e12, -2.877393997758344e13, \
-8.622465103983972e13, 1.1112933231776632e15, -4.817289173053201e14, \
-8.018379573857049e-19, -1.2444930267281007e-16, \
-7.845942373284064e-16, 1.3680119208009676e-14, \
2.5183230646110647e-13, -5.903535592894824e-13, \
-5.3036614827761476e-11, -1.8074883645202964e-10, \
1.0974407205112814e-8, 9.113656427684139e-8, -2.370861222886251e-6, \
-0.0000310163140080779, 0.0005438499246887928, 0.009499586056415892, \
-0.1336665193170889, -2.7466842987443063, 35.25898136378663, \
747.0981292584512, -9816.469178647008, -185574.7935955267, \
2.7622738085260643e6, 3.969889132811973e7, -7.34361149686909e8, \
-6.492680735255098e9, 1.6887533259875974e11, 5.562764220823635e11, \
-2.9707241509856836e13, 5.3569023639108195e13, 3.1991972931948575e15, \
-2.015939301386807e16, -1.040579326217624e17, 1.0233265365034705e18, \
-2.109882928121038e17, 1.4202596524023749e-22, \
-1.1468112990005366e-19, -9.807906735884031e-19, \
1.2021241908253736e-17, 3.142492225230104e-16, 2.389919368568718e-16, \
-6.931805312966074e-14, -5.390136764061787e-13, \
1.482506058887656e-11, 2.321354192996291e-10, -3.2033890304325076e-9, \
-8.483641629604447e-8, 6.990382953550288e-7, 0.00002991055784000132, \
-0.00015497289576816835, -0.010473701195884925, 0.036911644821165254, \
3.647183275374699, -10.8474083043576, -1247.3366801781472, \
4292.086059805096, 409208.3436193196, -1.9980851337130195e6, \
-1.2417627414205864e8, 9.054608441879021e8, 3.2966457042934643e10, \
-3.560128534612176e11, -6.965642293793504e12, 1.121028814908466e14, \
9.456013170940596e14, -2.553723865174433e16, -1.6376601136862792e16, \
3.445360872010093e18, -1.739737694365658e19, -1.4478078791772157e20, \
1.1850170842096049e21, 5.283271130026281e19, 6.71173700732903e-25, \
-8.256182236105272e-23, -9.05005007903092e-22, 7.67549083902652e-21, \
2.919304194538247e-19, 1.109401331270084e-18, -6.535259407186957e-17, \
-8.407708091894549e-16, 1.3435034094667206e-14, \
3.5887795944587496e-13, -2.384304208294308e-12, \
-1.4043006768627925e-10, 2.0521108378243577e-10, \
5.472769478817357e-8, 1.2105136399841696e-7, -0.0000217427648434795, \
-0.0001064313126125251, 0.00885317485660303, 0.058468234398918136, \
-3.6813699273471325, -26.564769281381558, 1546.1753694857955, \
10264.683231074068, -643465.0384196443, -3.1561344427917604e6, \
2.5790563817946088e8, 5.599901166483312e8, -9.569949145998723e10, \
1.3061849403092287e11, 3.11059312181046e13, -1.7428447693791534e14, \
-8.132152659457775e15, 8.76778711697046e16, 1.4485476152415716e18, \
-2.6797540656023736e19, -9.55300675843296e19, 4.524840330158314e21, \
-1.7607260127055128e22, -2.3666904402692857e23, 1.684086316929524e24, \
5.476208801420263e23 };

  const double expSecond2[231] = { 0, -0.25, -1.447280280022289, 3, 8.683681680133734, -6, \
0.0017123645833333327, -0.07205297230150476, -0.3458924166666666, \
1.5789445566409102, 12.876772500000001, -31.57889113281821, \
-124.52127, 363.146980399584, 69.04253999999997, \
0.00007494184854101564, -0.00042591754667640396, \
-0.00817995942408073, -0.025202042167100307, 0.39372866066726564, \
2.9611737588631044, -13.322741497366877, -124.36929787225039, \
661.4641499210065, 1524.2195102662265, -14841.718379052078, \
17001.265527172684, 35897.26535810415, 4.981899907667527e-7, \
3.3982632659370626e-7, -0.000044623749243005, -0.0004972810752610822, \
0.00009144663522821045, 0.04981830029357009, 0.2834981917281731, \
-3.0228801167716095, -27.0257189328845, 217.64736840755586, \
1428.8308863099924, -16571.559409653157, 1825.1285245387094, \
516096.5998495207, -1.9451111029712348e6, -444382.1768581858, \
1.0423524501117427e7, 1.5369755019314825e-9, 7.78871978571887e-9, \
-8.586069996721077e-8, -2.323915840122147e-6, \
-0.00001735399507150501, 0.00013686299121170377, \
0.0037209204614733495, 0.011131450633890646, -0.39096593320312983, \
-2.667017803328603, 40.45768298670623, 293.3719583661464, \
-4644.675286453183, -13753.129887184572, 450532.62155883625, \
-1.491435212794619e6, -1.5128916358270278e7, 1.377646080474336e8, \
-2.748561439127356e8, -9.474596003900285e8, 3.739310785167403e9, \
2.802814762656528e-12, 2.4898358757072184e-11, \
-1.017824705492054e-11, -4.809849745359656e-9, -7.808439882397453e-8, \
-2.5704662835677725e-7, 0.000011287748081998778, \
0.0001782946213072787, -0.00025375030376342984, -0.03161644073079776, \
-0.12169431445739967, 4.773899195779032, 27.419114229672687, \
-744.728274541529, -2923.5842105245697, 113933.00581750281, \
-131675.7016284329, -1.2582768907963537e7, 1.0037275210704252e8, \
2.605705243017658e8, -7.915487112754719e9, 4.095662586579693e10, \
-5.720178548615662e9, -6.436727873585934e11, 1.7390019398445715e12, \
3.400872113039268e-15, 4.236590729071886e-14, 2.317554451988417e-13, \
-4.842508161012463e-12, -1.5521365690885456e-10, \
-1.7549546962097454e-9, 7.471400825054187e-9, 5.347634530181625e-7, \
5.49342893610451e-6, -0.000057101987351333926, \
-0.0017091394068912056, 0.0007496516774824769, 0.3784648167125985, \
1.0921854591161078, -79.4760912897309, -229.35894641438264, \
16531.343194006302, -6679.936195576654, -3.0154732137631737e6, \
1.9141801655910686e7, 3.3147257664742863e8, -5.42094616144734e9, \
1.1663694395665438e10, 3.7807598485332623e11, -4.0125860565112603e12, \
1.2518860203668133e13, 4.673249605914394e13, -4.613168336371649e14, \
1.0368862687806839e15, 2.9525756256470433e-18, 4.6964827978908e-17, \
4.719170923974002e-16, -1.3113827296655625e-15, \
-1.7201068096081766e-13, -3.523469940779713e-12, \
-2.2392516760090427e-11, 6.216710389973627e-10, \
1.7370127011847328e-8, 8.805273237893514e-8, -3.6764827282321907e-6, \
-0.00006315370131776754, 0.00048380421780143325, \
0.020992987622298568, -0.030987187761589513, -5.970470646023141, \
-1.1134151929727523, 1623.9680157182947, -2275.6990692111344, \
-410098.8529211075, 2.457295034199125e6, 8.083268453271483e7, \
-1.1387701890968878e9, -6.272984764563465e9, 2.6729334182549716e11, \
-1.9132678697904565e12, -1.2542653892331758e13, 3.197217016468631e14, \
-2.1851688239032235e15, 1.9324889964006005e15, 6.258867917633222e16, \
-3.861842028917815e17, 7.769136954865303e17, 1.9277846593561172e-21, \
3.717235347550753e-20, 5.23566954858336e-19, 2.729727343054045e-18, \
-1.0961987970235925e-16, -3.912185836057183e-15, \
-5.760475518730867e-14, 8.863523216015463e-14, 2.256329982404366e-11, \
4.0171349297056645e-10, -9.417085936946715e-10, \
-1.4918982487859427e-7, -1.5010607112644104e-6, \
0.0000360459941710721, 0.0008270940102927372, -0.007098262833840815, \
-0.3250522528769366, 1.4193271448736324, 114.96951583740884, \
-485.4098835467822, -37797.0759645302, 277329.69677918736, \
1.0663827619387163e7, -1.496480700177372e8, -1.9443165100253587e9, \
5.797345253175712e10, -1.0465802323264026e11, -1.2054138507021736e13, \
1.7061724038517975e14, -1.5549437044046638e14, \
-2.1221980628076064e16, 2.6807727429215312e17, -1.201848778777191e18, \
-3.9505149220822907e18, 7.72870687837343e19, -3.841074287212276e20, \
7.171230287684186e20, 9.818094611540193e-25, 2.220078944185414e-23, \
3.9616189995584758e-22, 4.270783522679689e-21, \
-2.9581107160873246e-20, -2.735922188302259e-18, \
-6.60648812213589e-17, -6.018438851164106e-16, \
1.3231445151985154e-14, 5.598705697286867e-13, 6.21183994278497e-12, \
-1.125844001615806e-10, -4.315312359753723e-9, -1.358280772062267e-8, \
1.6370098983418552e-6, 0.000022307512509886935, \
-0.0005101554730794562, -0.012913111563841872, 0.15505613073298186, \
6.022634105367325, -56.1324059413746, -2529.5063242542765, \
27221.65431148229, 938548.7085853049, -1.5128247695550023e7, \
-2.646044921827892e8, 7.57289578280932e9, 2.3751553879504417e10, \
-2.7467307872202954e12, 2.4937982765067473e13, 4.54064238734378e14, \
-1.2686632942299552e16, 8.634923702093542e16, 1.0369050816280803e18, \
-2.708961083500108e19, 2.3558907330205178e20, -4.584989359542433e20, \
-9.797001652040186e21, 1.0360081692772459e23, -4.528490851444339e23, \
8.010733445929475e23};

  const double x1 = 0.245;
  const double x2 = 0.623;

  unsigned int counter = 1;
  double first, second;
  for( int l=2;l<=2;l=l+2 )
  {
    for (int m=-l;m<=l;m++)
    {
      LegendreP_derivatives( l, m, x1, first, second );
      if ( !areEqual(first, expFirst1[counter]) )
      {
        printf("Failed Legnedre First Dirivative test- (%d,%d) : (%f,%f)\n",l,m,first,expFirst1[counter]);
        passed = false;
      }

      if ( !areEqual(second, expSecond1[counter]) )
      {
        printf("Failed Legnedre Second Dirivative test- (%d,%d) : (%f,%f)\n",l,m,second,expSecond1[counter]);
        passed = false;
      }

      ++counter;
    }
  }

  if (!passed)
  {
    std::cout << "[FAILED] 1st Legendre" << std::endl;
    return EXIT_FAILURE;
  }

  counter = 1;
  for( int l=2;l<=20;l=l+2 )
  {
    for (int m=-l;m<=l;m++)
    {
      LegendreP_derivatives( l, m, x2, first, second );
      if ( !areEqual(first, expFirst2[counter]) )
      {
        printf("Failed Legnedre First Dirivative test- (%d,%d) : (%f,%f)\n",l,m,first,expFirst2[counter]);
        passed = false;
      }

      if ( !areEqual(second, expSecond2[counter]) )
      {
        printf("Failed Legnedre Second Dirivative test- (%d,%d) : (%f,%f)\n",l,m,second,expSecond2[counter]);
        passed = false;
      }
      ++counter;
    }
  }

  if (!passed)
  {
    std::cout << "[FAILED] 2nd Legendre" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Passed Legendre Dirivative Test" << std::endl;
  return EXIT_SUCCESS;
}

int itkReplaceSpecialFunctionsTest( int , char **  )
{
  if ( testLegendre() )
    return EXIT_FAILURE;

  if ( testBinomialCoeff() )
    return EXIT_FAILURE;

  if ( LegendreP_derivatives() )
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}