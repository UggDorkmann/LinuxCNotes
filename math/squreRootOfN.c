#include"../all.h"
static float myAb(float a,float b){
	return a>b?(a-b):(b-a);
	
}
float miFunc(float x,int index){
	float tmp = x;
	int i = 0;
	for(i=0;i<index-1;i++){
		tmp *= x;
	}
	return tmp;
}

float kaigenhao(float y,int index, float precision){
	float left = 0.0;
	float right = 100.0;
	while(miFunc(left,index) < y){
		left += 1;
	}
	left -= 1;
	right = left + 1;
	float mid = (left+right)/2;
	//printf("left = %f,right = %f,mid = %f,precision = %f\n",left,right,mid,precision);
	while( myAb(miFunc(mid,index),y) > precision ){
		if(miFunc(mid,index) < y){
			left = mid;
		}
		else{
			right = mid;
		}
		mid = (left+right)/2;
	}
	return mid;
}
int main(){
	//printf("2.0开12次根号 = %f\n",kaigenhao(2.0,12,0.000001)); //这里的精度太高，会导致函数死循环，进程无法结束
	printf("2.0开12次根号 = %f\n",kaigenhao(2.0,12,0.00001));//1.059464
	float i   = 0;
	int j = 0;
	float tmp = 1.0;
	float arrChun[12] = {0};
	float arrPing[12] = {0};
	for(i = 0,j=0;i<12;i++,j++){
		printf("%f,%f\n",1.05946*tmp,1+(i+1)/12);
		arrChun[j] = tmp;
		arrPing[j] = 1+(i)/12;
		tmp *= 1.05946;
	}
	int k = 0;
	float lowKey = 27.5;
	int loopNum = 12;
	for(k=0;k<8;k++){
		if(k == 7)loopNum = 4;
		for(j=0;j<loopNum;j++){
			printf("%.1f\t",lowKey*arrChun[j]);
		}
		printf("\n");
		lowKey *= 2;
	}
	
	return 0;
}
#if 0
比中央C高的A是440赫兹，中央C是261.6赫兹
27.5    29.1    30.9    32.7    34.6    36.7    38.9    41.2    43.7    46.2    49.0    51.9
55.0    58.3    61.7    65.4    69.3    73.4    77.8    82.4    87.3    92.5    98.0    103.8
110.0   116.5   123.5   130.8   138.6   146.8   155.6   164.8   174.6   185.0   196.0   207.6
220.0   233.1   246.9   261.6   277.2   293.7   311.1   329.6   349.2   370.0   392.0   415.3
440.0   466.2   493.9   523.2   554.4   587.3   622.2   659.2   698.4   740.0   784.0   830.6
880.0   932.3   987.8   1046.5  1108.7  1174.6  1244.5  1318.5  1396.9  1479.9  1567.9  1661.2
1760.0  1864.6  1975.5  2093.0  2217.4  2349.3  2489.0  2637.0  2793.8  2959.9  3135.9  3322.3
3520.0  3729.3  3951.0  4186.0

#endif
