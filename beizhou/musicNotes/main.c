/*only for C Major*/
/*for further consideration:1.1 span = 3 unit
							2.1 unit = 6 or 8 symbols
							3.change rules in unit (I will think later)
							4.change rules between unit(only 2 types are important)
							*/
#include "all.h"
#define Note_  "<note default-x=\"0\" default-y=\"0\">\n"
#define Pitch_ "<pitch>\n"
#define _Pitch "</pitch>\n"
#define _Note  "<duration>1</duration>\n<voice>1</voice>\n<type>quarter</type>\n<stem>up</stem>\n</note>\n"
#define Alter "<alter>1</alter>\n"
#define HAND_1 30 // 30 halves
#define HAND_2 31
#define HAND_3 33
#define HAND_4 34
#define HAND_5 36
#define HAND_6 38
#define HAND_7 39
#define Delta  5

#if 0
typedef struct group{
	int len_span;//2 or 3
	int len_unit;//2  3  4  6  8
	int repeat; //1 or 0 ,usually 1
	int pos;// 0b 0000 0000 0000 0000
	int delta; //-7~7
}span;
#endif

typedef struct music_note{
	char step;
	char alter; // 1 0r 0
	char octave;
}Note;

int indexArr[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
/*[9] is a flag ,when it is 0, former 8 elements should not be changed */

/*when 1 unit includes 6 or 8 symbols ,this array should be longer*/
/*when 1 span includes 3 or more units,this array should also be longer*/

/**/
static int getRandDelta(){
	int tmp = rand()%(Delta*2) + 1;
	if(tmp>Delta)tmp-=Delta;
	else tmp-=(Delta+1);
	return tmp;
}
static int isInRange(int a,int hand){
	if(a>=0 && a<hand)return 1;
	else return 0;
}
static int istoofar(int a,int b){
	if(a-b>6 || b-a>6) return 1;
	else return 0;
}

//genNote_1_4  genNote_all this 2 rules are most important
/* these rules are of less importance
//genNote_1_3  genNote_1_2  genNote_1_1
//genNote_2_12 genNote_2_13 genNote_2_14 genNote_2_23 genNote_2_24 genNote_2_34
//genNote_3_123 genNote_3_124 genNote_3_234 genNote_3_134
*/
//first num : the num of changed notes, second num: the position of changed notes
//genNote_1_6 ...
/*when 1 unit includes 6 or 8 symbols ,more funcs will be listed later*/
static void genNote_1_4(){
	if(indexArr[8] == 0)return;
	int i = 0;
	for(i=0;i<4;i++){
		while(1){
			indexArr[i] = rand()%HAND_1;
			if(i==0){
				indexArr[i+4] = indexArr[i];
				break;
			}
			else if(!istoofar(indexArr[i],indexArr[i-1])){
				indexArr[i+4] = indexArr[i];
				break;
			}
			
		}
		
	}
	while(1){
		indexArr[7] = indexArr[3] + getRandDelta(); 
		if(isInRange(indexArr[7],HAND_1)) break;
		else indexArr[7] = indexArr[3];
	}
}
static int getsafeindex(){
	return rand()%18+6;
}
static void genNote_all(){
	if(indexArr[8] == 0)return;
	int i = 0;
	int tmp = getRandDelta();
	for(i=0;i<4;i++){
		while(1){
			indexArr[i] = getsafeindex();
			if(i==0){
				indexArr[i+4] = indexArr[i] + tmp;
				break;
			}
			else if(!istoofar(indexArr[i],indexArr[i-1])){
				indexArr[i+4] = indexArr[i] + tmp;
				break;
			}
		}
	}
	
}
Note Cnotes_halves[39] = {{'G','0','3'},{'G','1','3'},\
	{'A','0','3'},{'A','1','3'},{'B','0','3'},{'C','0','4'},\
	{'C','1','4'},{'D','0','4'},{'D','1','4'},{'E','0','4'},\
	{'F','0','4'},{'F','1','4'},{'G','0','4'},{'G','1','4'},\
	{'A','0','4'},{'A','1','4'},{'B','0','4'},{'C','0','5'},\
	{'C','1','5'},{'D','0','5'},{'D','1','5'},{'E','0','5'},\
	{'F','0','5'},{'F','1','5'},{'G','0','5'},{'G','1','5'},\
	{'A','0','5'},{'A','1','5'},{'B','0','5'},{'C','0','6'},\
	{'C','1','6'},{'D','0','6'},{'D','1','6'},{'E','0','6'},\
	{'F','0','6'},{'F','1','6'},{'G','0','6'},{'G','1','6'},\
	{'A','0','6'} };
//including all half notes is a bad idea 
Note Cnotes[39] = {{'G','0','3'},{'G','0','3'},\
	{'A','0','3'},{'A','0','3'},{'B','0','3'},{'C','0','4'},\
	{'C','0','4'},{'D','0','4'},{'D','0','4'},{'E','0','4'},\
	{'F','0','4'},{'F','0','4'},{'G','0','4'},{'G','0','4'},\
	{'A','0','4'},{'A','0','4'},{'B','0','4'},{'C','0','5'},\
	{'C','0','5'},{'D','0','5'},{'D','0','5'},{'E','0','5'},\
	{'F','0','5'},{'F','0','5'},{'G','0','5'},{'G','0','5'},\
	{'A','0','5'},{'A','0','5'},{'B','0','5'},{'C','0','6'},\
	{'C','0','6'},{'D','0','6'},{'D','0','6'},{'E','0','6'},\
	{'F','0','6'},{'F','0','6'},{'G','0','6'},{'G','0','6'},\
	{'A','0','6'} };

void mybuf0(char* buf,int size){
	int i=0;
	for(i=0;i<size;i++){
		buf[i] = 0x00;
	}
}
static void strize_note(char* buf,char step,char alter,char octave){
		char * tmp = buf;
		strncpy(tmp,Note_,strlen(Note_));
		tmp+=strlen(Note_);
		strncpy(tmp,Pitch_,strlen(Pitch_));
		tmp+=strlen(Pitch_);
		strncpy(tmp,"<step>",6);
		tmp+=6;tmp[0]=step;tmp++;
		strncpy(tmp,"</step>\n",8);
		tmp+=8;
		if('0'!=alter){
			strncpy(tmp,Alter,strlen(Alter));
			tmp+=strlen(Alter);
		}
		strncpy(tmp,"<octave>",8);
		tmp+=8;tmp[0]=octave;tmp++;
		strncpy(tmp,"</octave>\n",10);
		tmp+=10;
		strncpy(tmp,_Pitch,strlen(_Pitch));
		tmp+=strlen(_Pitch);
		strncpy(tmp,_Note,strlen(_Note));
}

int main(){
	system("rm work.musicxml");
	FILE* p_in;
	FILE* p_out;
	srand(time(0));
	char buf[1000];
	char outbuf[1000];
	mybuf0(buf,sizeof(buf));
	mybuf0(outbuf,sizeof(outbuf));
	p_in = fopen("test__1.musicxml","r");
	p_out = fopen("work.musicxml","a+");
	while(fgets(buf,sizeof(buf),p_in)){
		if(strstr(buf,"<note>")){
			fgets(buf,sizeof(buf),p_in);
			fgets(buf,sizeof(buf),p_in);
			fgets(buf,sizeof(buf),p_in);
			fgets(buf,sizeof(buf),p_in);
			
			int arr[4] = {0};
			//genNote_1_4();
			genNote_all();
			if(indexArr[8] == -1){
				arr[0] = indexArr[0];arr[1] =indexArr[1];arr[2]=indexArr[2];arr[3]=indexArr[3];
				indexArr[8] = 0;
			}
			else{
				arr[0] = indexArr[4];arr[1] =indexArr[5];arr[2]=indexArr[6];arr[3]=indexArr[7];
				indexArr[8] = -1;
			}
			
			mybuf0(outbuf,sizeof(outbuf));
			strize_note(outbuf,Cnotes[arr[0]].step,Cnotes[arr[0]].alter,Cnotes[arr[0]].octave);
			fprintf(p_out,"%s",outbuf);
			mybuf0(outbuf,sizeof(outbuf));
			strize_note(outbuf,Cnotes[arr[1]].step,Cnotes[arr[1]].alter,Cnotes[arr[1]].octave);
			fprintf(p_out,"%s",outbuf);
			mybuf0(outbuf,sizeof(outbuf));
			strize_note(outbuf,Cnotes[arr[2]].step,Cnotes[arr[2]].alter,Cnotes[arr[2]].octave);
			fprintf(p_out,"%s",outbuf);
			mybuf0(outbuf,sizeof(outbuf));
			strize_note(outbuf,Cnotes[arr[3]].step,Cnotes[arr[3]].alter,Cnotes[arr[3]].octave);
			fprintf(p_out,"%s",outbuf);
			
		}
		else{
			fprintf(p_out,"%s",buf);
		}
		mybuf0(buf,sizeof(buf));
	}
	fclose(p_in);
	fclose(p_out);
	return 0;
}
// sed -i '/sharp/d' tmp.xml
// sed -i '66,10384d' tmp.xml 
