#include "lex.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Token * tokens;
char * c ;
int posT;
int pos ;
int verified=0;
int indexR[100];
int top=-1;
int find =0;
int currentC ;

void nTerminal();
void terminal();
int rule();

int push(int* indexR,int top_,int elem){
    indexR[++top_]=elem;
    return top_;
}

int pop(int * indexR,int top_){
    if (top_==-1) {
        return -1;
    }
    top_--;
    return top_;
}

void printing(int i){
    
    switch (i)
    {
    case 0:
        printf("\n");
        break;
    case 1:
        printf("%s",tokens[posT].value);
        break; 
    case 2:
        printf(" %s->",tokens[posT].value);
        break;
    default:
        break;
    }
}
void compareValue(){
    int i=0;
    int pass =1;
    
    while(tokens[posT].value[i]!= '\0'&& pass && c[pos]!='\0'){
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
    }
    
}
void terminal(){
    int ruleT;
    switch(tokens[posT].key){
        case TERMINAL:
            compareValue();
            break;
        case NTERMINAL:
            ruleT=posT; 
            if(rule()){
                
                posT=ruleT+1;
                terminal();
            }           
            break;
        case NL:
            if(c[pos]=='\0'){
                verified=1;
            }
            find = 1;
            
            break;
        default:
            
            break;
    }

}
void nTerminal(){

    switch(tokens[posT].key){
        case NTERMINAL:
            currentC=pos;
            posT++;
            terminal();
            break;
        default:
            break;
    }
}

int rule(){
    find = 0;

    char * ruleT=tokens[posT].value;

    struct Token* p = getTokens();
    for (int i = 0; i < getTokenLen()-1 && !find ; i++){
        find = 0;
        if(p[i].key==NL && p[i+1].key==NTERMINAL && strcmp(p[i+1].value, ruleT)==0){

                top=push(indexR,top,pos);
                posT=i+1;
                nTerminal();
                if(!find){
                    pos=indexR[top];
                    top=pop(indexR,top);
                }
                
        }
    }   

    if(!find){
        pos=currentC;
    }
    return find;
}

void analy( char * cr){
    pos=0;
    tokens=getTokens();
    c=malloc(sizeof(*cr));
    strcpy(c,cr);
    posT=1;
    
    rule();
    
    if(verified){
        printf("OK : verification passed\n");
    }else{
        printf("KO : verification failed\n");
    }
    free(c);

}