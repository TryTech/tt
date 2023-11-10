#include "../include/lex.h"
#include "../include/token.h"

const char *reservedWords[] = {
    "function",
    "ret",
    "i64"};

int isReservedWords(char* word) 
{
    if (!word)
        return 0;

    int numReservedWords = sizeof(reservedWords) / sizeof(char*);

    for (int i = 0; i < numReservedWords; i++) {
        if (strcmp(word, reservedWords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void lex(char* buffer)
{
    struct TokenList *head = NULL;
    struct TokenList *tail = NULL;

    int64_t current = 0;
    int64_t start = 0;  
    int64_t line = 1;
    int64_t column = 1;
    int64_t length = strlen(buffer);

    while(current < length) {
        char c = buffer[current];
        switch (c) {
            case '\n':
                line++;
                column = 1;
                break;
            case ' ':
            case '\r':
            case '\t':
                break;
            case '(':
                printf("Left Parenthesis\n");
                break;
            case ')':
                printf("Right Parenthesis\n");
                break;
            case '{':
                printf("Left Brace\n");
                break;
            case '}':
                printf("Right Brace\n");
                break;
            case '[':
                printf("Left Bracket\n");
                break;
            case ']':
                printf("Right Bracket\n");
                break;
            case ';':
                printf("Semicolon\n");
                break;
            case ',':
                printf("Comma\n");
                break;
            case '.':
                printf("Dot\n");
                break;
            case '-':
                printf("Minus\n");
                break;
            case '+':
                printf("Plus\n");
                break;
            case '/':
                printf("Slash\n");
                break;
            case '*':
                printf("Star\n");
                break;
            case '!':
                printf("Bang\n");
                break;
            case '=':
                printf("Equal\n");
                break;
            case '<':
                printf("Less\n");
                break;
            case '>':
                printf("Greater\n");
                break;
            case '"':
                printf("String\n");
                break;
            default:
                if(isalpha(c)) {
                    start = current;
                    while(isalpha(buffer[current]) || isdigit(buffer[current])) {
                        current++;
                    }
                    char* identifier = strndup(buffer + start, current - start);
                    struct Token *token = malloc(sizeof(struct Token));
                    token->value = identifier;
                    token->type = isReservedWords(identifier) ? "reserved" : "identifier";
                    token->line = line;
                    token->column = column;

                    struct TokenList *node = malloc(sizeof(struct TokenList));
                    node->token = token;
                    node->next = NULL;
                    if (head == NULL) {
                        head = node;
                        tail = node;
                    } else {
                        tail->next = node;
                        tail = node;
                    }
                    current--; // decrement current to avoid skipping characters
                } else {
                    printf("Unknown character: %c\n", c);
                }
                break;
        }
        current++;
        column++;
    }
}