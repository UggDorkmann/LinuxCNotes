#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
//30度对应60个点
int main(){
    srand(time(0));
    int arr[60] = {0};
    int i=0;
//    arr[0] = 1000;
    FILE *p_file = fopen("polarMapData.txt","w");
    int outLoop = 0;
    for(outLoop=0;outLoop<20;outLoop++){
        arr[0] = 1000000+rand()%62000 - 31000;
    for(i=1;i<60;i++){
        //arr[i] = arr[i-1] + rand()%62 -31;
        arr[i] = arr[i-1] + rand()%38000 -19000;
    }
    for(i=0;i<60;i++){
        //float angle =((float)(i-30))/2;//right
        float angle =((float)(i-210))/2;//down
        fprintf(p_file,"%d<%f\n",arr[i],angle);
    }
        fprintf(p_file,"\npl\n");
    }
    fprintf(p_file,"\n");
    fclose(p_file);
    p_file = NULL;
    return 0;
}
