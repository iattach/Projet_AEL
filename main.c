#include "lex.h"
#include "analy.h"

int main(int argc , char ** argv){

    lexRun();

    int len = getTokenLen();
    if (!len) {
        return 0;
    }

    struct Token* p = getTokens();
    for (int i = 0; i < len; i++){
        printf("%d: key->%u, value->%s.\n", i, p->key, p->value);
        p++;
    }

    char *c = argv[1];

    int i=0;
    while(c[i]!='\0'){
        printf("%c\n",c[i]);
        i++;
    }

    
    analy(c);
    
    return 0;
}

