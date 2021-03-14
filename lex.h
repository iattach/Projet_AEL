#ifndef LEX_H
#define LEX_H
#include <stdio.h>

enum  Gra {
    TERMINAL,
    NTERMINAL,
    COLON,
    NL,
};
struct Token {
    enum Gra key;
    char value[256];
};
#endif


struct Token* getTokens(void);

int getTokensLen(void);

void lexRun(char *file);