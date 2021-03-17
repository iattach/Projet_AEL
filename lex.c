#include "lex.h"
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
//read rule
FILE *fp; 
static struct Token GrToken; 
//char GrToken.tokens[1024][1024][1024];            // note all the signs 
//char GrToken.list_NT[1024][1024];
//char GrToken.list_T[1024][1024];

int len = 0;                          // length of the list of token
int posT =0;
int posLNT=0;
int posLT=0;
char * lineChar;


void findfirst(char, int, int); 


 //List_first = {}
    //List_first_v2 = []
    //List_follow = {}
    //
struct Token * getTokens(){
    struct Token * getT=malloc(sizeof(GrToken));
    *getT = GrToken;
    return getT;
}

int getposLNT(){
    return posLNT;
}

int getposLT(){
    return posLT;
}
int * getTokenLen(){
    return &len;
}
int isSign(char a){
    //isalpha(a)
    return a!='\0'&& a!='\n' && a!=' ';

}
void keyToken(int *i, char * token){
    char c = *lineChar;
    
    if(!isSign(c)){
        return;
    }
    token[*i]= c;
    (*i)++;
    lineChar++;
    return keyToken(i, token);
}

void singleOrMultChar(){
    char a=*lineChar;
    int i = 0;
    
    if(isSign(a)){
        char token[1024]; 
        keyToken(&i, token);
        token[i]='\0';
        strcpy(GrToken.tokens[len][posT],token);
        posT++;
    }
}
void nextToken(){
    char a=*lineChar;
    switch(a){
        case ' ':
            break;
        case '\0' :
            return ;
        case '\n' :
            return ;
            break;
        default:
            singleOrMultChar();
            break;
    }
    lineChar++;
    nextToken();
}
void showTokens(){
    printf("Rules : \n");
    for(int j =0 ; j<len; j++){
        for(int t=0;t<1024 && GrToken.tokens[j][t][0]!='\0';t++){
            printf("%s ",GrToken.tokens[j][t]);
        }
        
        printf("\n");
    }

    printf("-----------------------------------------------\n\n"); 

    printf("NT : ");
    for(int m=0; m<posLNT;m++){
        printf("%s ",GrToken.list_NT[m]);
    }
    printf("\n");

    printf("T : ");
    for(int n=0; n<posLT;n++){
        printf("%s ",GrToken.list_T[n]);
    }
    printf("\n");
    printf("-----------------------------------------------\n\n"); 
}

int findToken(int type, char * s){
    int find = 0;
    int i=0;
    char ** list;
    if(type){
        while(i<=posLNT) {
            if(strcmp(GrToken.list_NT[i], s) == 0) {
                find = 1;
                break;
            }
            i++;
        }
    }else{
        while(i<=posLT) {
            if(strcmp(GrToken.list_T[i], s) == 0) {
                find = 1;
                break;
            }
            i++;
        }
    }
    
    return find;
}
int isUpper(char * c){
    if(*c>='A'&&*c<='Z'){
        return 1;
    }else{
        if(*c>='a'&&*c<='c'){
            return 0;
        }else{
            if(*c!='\0'&&*c!=':'){
                return -1;
            }else{
                return -2;
            }
        }
    }
}

void lexRun(){
    
    char filename[]="./grammaire.txt"; 

    char line[1024]; //read by line 

    if((fp = fopen(filename,"r"))==NULL){ //make sure file exists and can be read
        printf("Error : File can not be read\n");
        exit(1);
    }
    //identify the GrToken.tokens 
    len = 0;

    while(!feof(fp)){
        if(fgets(line, 1024, fp)!=NULL && strcmp(line, "\n") != 0){

                lineChar=line;

                nextToken();

                GrToken.tokens[len][posT][0]='\0';
                posT=0;
                len++;
        } 
    }
    fclose(fp); 
    //identify the NT and T
    for(int j =0 ; j<len; j++){
        for(int t=0;t<1024 && GrToken.tokens[j][t][0]!='\0';t++){
            //printf("%s ",GrToken.tokens[j][t]);
            if(isUpper(GrToken.tokens[j][t])==1&&findToken(1,GrToken.tokens[j][t])==0){
                strcpy(GrToken.list_NT[posLNT],GrToken.tokens[j][t]);
                posLNT++;
            }else{
                if(isUpper(GrToken.tokens[j][t])==0&&findToken(0,GrToken.tokens[j][t])==0){
                    strcpy(GrToken.list_T[posLT],GrToken.tokens[j][t]);
                    posLT++;
                }else{
                    if(isUpper(GrToken.tokens[j][t])==-1&&findToken(0,GrToken.tokens[j][t])==0){
                        strcpy(GrToken.list_T[posLT],GrToken.tokens[j][t]);
                        posLT++;
                }
                }
            }
        }
    }

    //show results
    showTokens();
    /*
    //First
    
    /*
    strcpy(production[0], "E=TR"); 
    strcpy(production[1], "R=+TR"); 
    strcpy(production[2], "R=#"); 
    strcpy(production[3], "T=FY"); 
    strcpy(production[4], "Y=*FY"); 
    strcpy(production[5], "Y=#"); 
    strcpy(production[6], "F=(E)"); 
    strcpy(production[7], "F=i"); 
    */
    
}