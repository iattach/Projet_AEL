#include "lex.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Token * tokens;
char * c ;
int posT;
int pos ;
int currentR;
int verified=0;

void nTerminal();
void terminal();
void nextrule();
void rule();

void printing(int i){
    
    switch (i)
    {
    case 0:
        printf("\n");
        break;
    case 1:
        printf("%s ",tokens[posT].value);
        break; 
    case 2:
        printf("%s -> ",tokens[posT].value);
        break;
    default:
        break;
    }
}
void compareValue(){
    printf("compareValue\n");
    int i=0;
    int pass =1;
    
    while(tokens[posT].value[i]!= '\0'&& pass){
        printf("while %c :%s : %d compare to %c : %s\n",tokens[posT].value[i],tokens[posT].value,i,c[pos],c);
        if(tokens[posT].value[i]==c[pos] ){
            pos++;
        }else{
            pass =0;
        }
        i++;
    }
    if(pass){
        posT++;
        terminal();
    }else{
        nextrule();
    }
    
}
void terminal(){
    printf("terminal\n");
    switch(tokens[posT].key){
        case TERMINAL:
            printing(1);
            compareValue();
            break;
        case NTERMINAL:
            rule();
            terminal();
            break;
        case NL:
            break;
        default:
            if(c[pos]=='\0' && tokens[posT+1].key==NL){
                verified=1;
            }
            break;
    }

}
void nTerminal(){
    printf("nTerminal\n");
    switch(tokens[posT].key){
        case TERMINAL:
            break;
        case NTERMINAL:
            printing(2);
            currentR=posT-1;
            posT++;
            terminal();
        case NL:
            nextrule();
        default:
            break;
    }
}

void rule(){
    printf("rule\n");
    int find =0;
    char * ruleT=tokens[posT].value;

    struct Token* p = getTokens();
    for (int i = 0; i < getTokenLen()-1 && !find ; i++){
        printf("while %s : %d compare to %s,%d,%d\n",p[i+1].value,i,ruleT,p->key,p[i+1].key==NTERMINAL);
        if(p->key==NL && p[i+1].key==NTERMINAL && strcmp(p[i+1].value, ruleT)==0){
                ///find=1;
                posT=i+1;
                nTerminal();
        }
        sleep(1);
        p++;
    }   
}
void nextrule(){
    printf("nextrule\n");
    char * ruleT=tokens[posT].value;

}
void analy( char * cr){
    pos=0;
    tokens=getTokens();
    c=malloc(sizeof(*cr));
    strcpy(c,cr);
    posT=1;

    struct Token* p =getTokens();
    for (int i = 0; i <  getTokenLen(); i++){
        printf("%d: key->%u, value->%s.\n", i, p->key, p->value);
        p++;
    }
    nTerminal();  
    
    if(verified){
        printf("verification passed\n");
    }else{
        printf("verification failed\n");
    }
    free(c);

}