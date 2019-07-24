#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#define jingdu 30
int absV(int num){
    if(num>0)
        return num;
    else
        return (0-num);

}
int main(){
    srand(time(0));
    FILE *p_file = fopen("3dmapdata.txt","w");
    float arr[jingdu+1][jingdu+1] = {0};
    int i=0;
    int j=0;

    for(i=0;i<jingdu+1;i++){
        if(i==0)
            arr[i][0] = rand()%28 -14;
        else
            arr[i][0] = arr[i-1][0] + rand()%28 - 14;
        for(j=1;j<jingdu+1;j++){
            
            arr[i][j] = arr[i][j-1] + rand()%28 - 14;
            if(i>0 && absV(arr[i][j]-arr[i-1][j])>28){
                arr[i][j] = (arr[i][j]+arr[i-1][j])/2;
            
            }
        }
        
    }
    for(i=0;i<jingdu;i++){
        for(j=0;j<jingdu;j++){
            int x1=100*i,y1=100*j;
            int x2=100*(i),y2=100*(j+1);
            int x3=100*(i+1),y3=100*(j+1);
            int x4=100*(i+1),y4=100*(j);
            float z1=arr[i][j];
            float z2=arr[i][j+1];
            float z3=arr[i+1][j+1];
            float z4=arr[i+1][j];
            fprintf(p_file,"%d,%d,%f\n",x1,y1,z1);
            fprintf(p_file,"%d,%d,%f\n",x2,y2,z2);
            fprintf(p_file,"%d,%d,%f\n",x3,y3,z3);
            fprintf(p_file,"%d,%d,%f\n",x4,y4,z4);
            fprintf(p_file,"%d,%d,%f\n",x1,y1,z1);
            
            fprintf(p_file,"\n3dpoly\n");
        }
    }

    fclose(p_file);
    p_file = NULL;
    return 0;
}

