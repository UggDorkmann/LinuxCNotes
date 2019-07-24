#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>

int main(){
    srand(time(0));
    int vow[5]={97,101,105,111,117};
    int con[21]={98,99,100,102,103,104,106,107,108,109,110,112,113,114,115,116,118,119,120,121,122};
    FILE * p_file = fopen("words.txt","w");
    int amount = 0;
    int al=0;
    for(amount=0;amount<20;amount++){
        al = rand()%26+1;//[1,26]
        al = al + 96;
        fprintf(p_file,"%c",al);

        
        al = rand()%5;
        al = vow[al];
        fprintf(p_file,"%c",al);

        al = rand()%10;
        
        if(al>5){
            al = rand()%26+1;//[1,26]
            al = al + 96;
            fprintf(p_file,"%c",al);
        }
        fprintf(p_file,"\n");
    }
    for(amount=0;amount<4000;amount++){
        al = rand()%26+1;//[1,26]
        al = al + 96;
        fprintf(p_file,"%c",al);
        al = rand()%5;
        al = vow[al];
        fprintf(p_file,"%c",al);
        al = rand()%21;
        al = con[al];
        fprintf(p_file,"%c",al);
        al = rand()%5;
        al = vow[al];
        fprintf(p_file,"%c",al);

        al = rand()%44;
        if(al>25){
            al = rand()%21;
            al = con[al];
            fprintf(p_file,"%c",al);
            al = rand()%5;
            al = vow[al];
            fprintf(p_file,"%c",al);
            al = rand()%21;
            al = con[al];
            fprintf(p_file,"%c",al);
        }
        else{
            al = rand()%21;
            al = con[al];
            fprintf(p_file,"%c",al);
        }
        fprintf(p_file,"\n");
        printf("%d entered\n",amount);
    }
    fclose(p_file);
    p_file =NULL;

return 0;
}
