#include "lex.h"
#include "analy.h"

int main(int argc , char ** argv){

    lexRun();
    char *c = argv[1];
    int len = getTokenLen();
    if (!len) {
        return 0;
    }
    analy(c);
    
    return 0;
}

