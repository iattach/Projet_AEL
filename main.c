#include "lex.h"
#include "analysis.h"

void strTrim(char*pStr) { 
 
    char *pTmp = pStr; 
     
    while (*pStr != '\0'){ 
    
        if (*pStr != ' '){ 
            *pTmp++ = *pStr; 
        }
    ++pStr; 
    
    } 
    *pTmp = '\0'; 
 
} 
int main(int argc , char ** argv){
    
    if(argc==2){
        lexRun();
        char *c=strtok ( argv[1], " ");
        //char *c = argv[1];
        //strTrim(c);
       // printf("chaine : %s\n",c);
        /*int len = getTokenLen();
        if (!len) {
            return 0;
        }*/
        //printf("test\n");
        calculFF();
        table();
       // analy(c);
        
        return 0;
    }else{
        printf("Usage ./parser [word] Ex : ./parser \"a b cd\" \n");
        return 1;
    }
    
}

