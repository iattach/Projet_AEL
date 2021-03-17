#include "lex.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Token * tokens;

void analy( char * cr){
    
    tokens=getTokens();

    free(tokens);

}