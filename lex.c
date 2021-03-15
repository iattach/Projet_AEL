#include "lex.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

FILE *fp;  
static struct Token tokens[1024];            // note all the signs 
int len = 0;                          // length of the list of token
void nextToken(char a);

int getTokenLen(){
    return len;
}
struct Token * getTokens(){
    return tokens;
}

struct Token* addToken(enum Gra key, char *value){
    int i = len;
    tokens[len].key = key;
    strcpy(tokens[len].value, value);
    len++;
    return &tokens[i];
}

void keyTerminal(int *i, struct Token* token){

    char c = fgetc(fp);
    
    if (!isalpha(c)){
        nextToken(c);
        return;
    }
    (*i)++;
    token->value[*i] = (char)c;
    return keyTerminal(i, token);
    
    
}

void singleOrMultChar(char a){
    
    int i = 0;
    
    if (isalpha(a)){
        struct Token *token = addToken(0, &a);
        if(a>='a' && a<='z'){
            token->key = TERMINAL;
        }else{
            if(a>='A' && a<='Z'){
                token->key = NTERMINAL;
            }
        }
        keyTerminal(&i, token);
        token->value[i + 1] = '\0';
    }
}
void nextToken(char a){
    if(a==' '){
        return;
    }
    switch(a){
        case ':' :
            //addToken(COLON,":");
            break;
        case '\n' :
            addToken(NL,"\\n");
            break;
        default:
            singleOrMultChar(a);
            break;
    }
}

void lexRun(){

    fp = fopen("grammaire.txt","r");
    addToken(NL,"\\n");
    while(!feof(fp)){
        char a = fgetc(fp);
        nextToken(a);
    }
    addToken(NL,"\\n");
    fclose(fp);
}