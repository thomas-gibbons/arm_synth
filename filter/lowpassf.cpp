#include "lowpassf.h"
#include <stdio.h>
  
#define Fs 44100.0
#define Pi 3.141592653589793
#define TwoPiOverFs (2 * Pi / Fs)

////
//  Constructor
LowpassF::LowpassF(){
    y_of_n_minus1 = 0;
    set_cutoff(6927.0);
}
  
  
////
//  Change the cutoff frequency
//  void Lowpass::set_cutoff(float fc){
void LowpassF::set_cutoff(float fc){
    a0 = fc * TwoPiOverFs;
    b1 = 1 - a0;
    printf("a0: %f\n", a0);
    printf("b1: %f\n", b1);
}
  
  
////
//  Get the value of the filtered sample
short LowpassF::value(short x){
    float y;
    y = (a0 * x) + (b1 * y_of_n_minus1);
    y_of_n_minus1 = y;
    return y;
}


int32_t fixed_point_coeff[128][2] = {{23,8168},{24,8167},{25,8166},{26,8165},{28,8163},{29,8162},{30,8161},{32,8159},{33,8158},{35,8156},{36,8155},{38,8153},{40,8151},{42,8149},{44,8147},{46,8145},{48,8143},{51,8140},{53,8138},{55,8136},{58,8133},{61,8130},{64,8127},{67,8124},{70,8121},{73,8118},{77,8114},{80,8111},{84,8107},{88,8103},{92,8099},{97,8094},{101,8090},{106,8085},{111,8080},{116,8075},{122,8069},{128,8063},{134,8057},{140,8051},{147,8044},{154,8037},{161,8030},{169,8022},{177,8014},{185,8006},{194,7997},{203,7988},{212,7979},{222,7969},{233,7958},{244,7947},{255,7936},{267,7924},{280,7911},{293,7898},{307,7884},{322,7869},{337,7854},{353,7838},{369,7822},{387,7804},{405,7786},{424,7767},{444,7747},{465,7726},{487,7704},{510,7681},{534,7657},{559,7632},{585,7606},{613,7578},{642,7549},{672,7519},{704,7487},{737,7454},{772,7419},{808,7383},{846,7345},{886,7305},{928,7263},{972,7219},{1018,7173},{1066,7125},{1116,7075},{1169,7022},{1224,6967},{1281,6910},{1342,6849},{1405,6786},{1471,6720},{1541,6650},{1613,6578},{1689,6502},{1769,6422},{1852,6339},{1939,6252},{2031,6160},{2127,6064},{2227,5964},{2332,5859},{2442,5749},{2557,5634},{2677,5514},{2803,5388},{2936,5255},{3074,5117},{3219,4972},{3370,4821},{3529,4662},{3696,4495},{3870,4321},{4052,4139},{4243,3948},{4443,3748},{4652,3539},{4872,3319},{5101,3090},{5342,2849},{5593,2598},{5857,2334},{6133,2058},{6422,1769},{6724,1467},{7041,1150},{7373,818},{7721,470},{8084,107}};
////
//  Constructor
//  Alls this is scaled by 2^13
Lowpass::Lowpass(){
   set_cutoff(80);
}


////
//  Change the cutoff frequency in fixed point 
void Lowpass::set_cutoff(int fc){
    a0 = fixed_point_coeff[fc][0];
    b1 = fixed_point_coeff[fc][1];
}


////
//  Get the value of the filtered sample
int16_t Lowpass::value(int16_t x){
    int32_t y, feedforward, feedback;
    feedforward = (a0 * x) >> 13;
    feedback    = (b1 * y_of_n_minus1) >> 13;
    y = feedforward + feedback;
    y_of_n_minus1 = y;
    return (int16_t)y;
}

