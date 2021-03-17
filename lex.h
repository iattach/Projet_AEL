#include <stdio.h>
#include <string.h>

enum  Gra {
    TERMINAL,
    NTERMINAL,
    COLON,
    NL,
};
struct Token {
    char tokens[1024][1024][1024];
    char list_NT[1024][1024];
    char list_T[1024][1024];
};

struct Token * getTokens();

int * getTokenLen();

int getposLT();

void lexRun();

