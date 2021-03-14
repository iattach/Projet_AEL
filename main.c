#include "lex.h"

int main(int argc , char ** argv){

    lexRun(argv[1]);

    int len = getTokensLen();
    if (!len) {
        return 0;
    }

    struct Token* p = getTokens();
    for (int i = 0; i < len; i++){
        printf("%d: key->%u, value->%s.\n", i, p->key, p->value);
        p++;
    }

    return 0;
}

