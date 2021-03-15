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
void nextrule();
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
        printf(" %s ",tokens[posT].value);
        break; 
    case 2:
        printf(" %s ->",tokens[posT].value);
        break;
    default:
        break;
    }
}
void compareValue(){
    //printf("Fonction : compareValue\n");
    int i=0;
    int pass =1;
    
    while(tokens[posT].value[i]!= '\0'&& pass){
        printf("    posIndex %d -> %c == %c ? %s\n",pos, c[pos],tokens[posT].value[i],c);
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
        printf("    compareValue Not pass\n");
        nextrule();
    }
    
}
void terminal(){
    //printf("Fonction : terminal\n");
    int ruleT;
    switch(tokens[posT].key){
        case TERMINAL:
            printing(1);
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
    //printf("Fonction : nTerminal\n");
    switch(tokens[posT].key){
        case TERMINAL:
            break;
        case NTERMINAL:
            printing(2);
            //currentR=posT-1;
            currentC=pos;
            posT++;
            terminal();
            break;
        case NL:
            //printf("    nTerminal NL\n");
            nextrule();
            break;
        default:
            break;
    }
}

int rule(){
    find = 0;
    printf("{\n");
    //Fonction : rule\n");
    
    char * ruleT=tokens[posT].value;

    struct Token* p = getTokens();
    for (int i = 0; i < getTokenLen()-1 && !find ; i++){
        find = 0;
        printf("    rule-> index : %d -> value : %s ->> value(i+1) : %s compare to ruleT :%s \n",i,p[i].value,p[i+1].value,ruleT);
        if(p[i].key==NL && p[i+1].key==NTERMINAL && strcmp(p[i+1].value, ruleT)==0){
                ///find=1;
                //pos=posOfC-1;
                //pos=currentC;
                printf("    push pos : %d\n",pos);
                top=push(indexR,top,pos);
                posT=i+1;
                sleep(1);
                nTerminal();
                if(!find){
                    pos=indexR[top];
                    top=pop(indexR,top);
                    printf("    pop pos : %d\n",pos);
                }
                
        }
        //sleep(1);
        //p++;
    }   
    
    printf("}\n");//Fonction Fin: rule\n");
    if(!find){
        pos=currentC;
        printf("    current pos : %d \n",pos);
    }
    return find;
}
void nextrule(){
    printf("Fonction : nextrule\n");
  //  char * ruleT=tokens[posT].value;

}
void analy( char * cr){
    pos=0;
    tokens=getTokens();
    c=malloc(sizeof(*cr));
    strcpy(c,cr);
    posT=1;

    struct Token* p =getTokens();
    for (int i = 0; i <  getTokenLen(); i++){
        //printf("%d: key->%u, value->%s.\n", i, p->key, p->value);
        p++;
    }

    
    rule();
    
    
    
    if(verified){
        printf("verification passed\n");
    }else{
        printf("verification failed\n");
    }
    free(c);

}