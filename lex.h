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

struct Token* getTokens();

int getTokenLen();

void lexRun();