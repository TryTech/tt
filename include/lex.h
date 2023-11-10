#ifndef LEX
#define LEX

#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "./token.h"
#include <stdlib.h>

struct TokenList *lex(char *buffer);

#endif // LEX