#ifndef TOKEN
#define TOKEN

#include <inttypes.h>

struct Token
{
    char* value;
    char* type;
    int64_t line;
    int64_t column;
};

struct TokenList
{
    struct Token* token;
    struct TokenList* next;
};

#endif // TOKEN