#include "lex.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

FILE *fp;  
struct Token tokens[1024];            // note all the signs 
int len = 0;                          // length of the list of token
void nextToken(char a);

int getTokensLen(){
    return len;
}
struct Token* getTokens(){
    return tokens;
}

struct Token* addToken(enum Gra key, char *value){
    int i = len;
    tokens[len].key = key;
    strcpy(tokens[len].value, value);
    len++;
    return &tokens[i];
}

void keyWithIdentityOrWord(int *i, struct Token* token){

    char c = fgetc(fp);

        
    
    if (!isalpha(c)){
        nextToken(c);
        return;
    }
    (*i)++;
    token->value[*i] = (char)c;
    return keyWithIdentityOrWord(i, token);
    
    
}

void singleOrMultipleCharacter(char a){
    
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
        keyWithIdentityOrWord(&i, token);
        token->value[i + 1] = '\0';
    }
}
void nextToken(char a){
    if(a==' '){
        return;
    }
    switch(a){
        case ':' :
            addToken(COLON,":");
            break;
        case '\n' :
            addToken(NL,"\\n");
            break;
        default:
            singleOrMultipleCharacter(a);
            break;
    }
}

void lexRun(char *file){

    fp = fopen(file,"r");
    while(!feof(fp)){
        char a = fgetc(fp);
        nextToken(a);
    }
    fclose(fp);
}