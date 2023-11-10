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

struct TokenList* lex(char* buffer)
{
    struct TokenList* head = NULL;
    struct TokenList* tail = NULL;

    int64_t current = 0;
    int64_t start = 0;  
    int64_t line = 1;
    int64_t column = 1;
    int64_t length = strlen(buffer);

    while(current < length) {
        char c = buffer[current];
        char* type = NULL;
        switch (c) {
            case '+':
                type = "Plus";
                break;
            case '-':
                type = "Minus";
                break;
            case '*':
                type = "Asterisk";
                break;
            case '/':
                type = "Slash";
                break;
            case '%':
                type = "Percent";
                break;
            case '=':
                type = "Equal";
                break;
            case '!':
                type = "Exclamation";
                break;
            case '<':
                type = "Less Than";
                break;
            case '>':
                type = "Greater Than";
                break;
            case '&':
                type = "Ampersand";
                break;
            case '|':
                type = "Pipe";
                break;
            case '^':
                type = "Caret";
                break;
            case '~':
                type = "Tilde";
                break;
            case '?':
                type = "Question Mark";
                break;
            case ':':
                type = "Colon";
                break;
            case ',':
                type = "Comma";
                break;
            case '.':
                type = "Period";
                break;
            case '"':
                type = "Quote";
                break;
            case '\'':
                type = "Apostrophe";
                break;
            case '\\':
                type = "Backslash";
                break;
            case '\0':
                type = "EOF";
                break;
            case '\n':
                line++;
                column = 1;
                break;
            case ' ':
            case '\r':
            case '\t':
                break;
            case '(':
                type = "Left Parenthesis";
                break;
            case ')':
                type = "Right Parenthesis";
                break;
            case '{':
                type = "Left Brace";
                break;
            case '}':
                type = "Right Brace";
                break;
            case '[':
                type = "Left Bracket";
                break;
            case ']':
                type = "Right Bracket";
                break;
            case ';':
                type = "Semicolon";
                break;
            // Add more cases here for other characters
            default:
                if(isalpha(c)) {
                    start = current;
                    while(isalpha(buffer[current]) || isdigit(buffer[current])) {
                        current++;
                    }
                    char* identifier = strndup(buffer + start, current - start);
                    type = isReservedWords(identifier) ? "Reserved Word" : "Identifier";
                    current--;
                } else {
                    printf("Unknown character: %c\n", c);
                }
                break;
        }
        if (type != NULL) {
            struct Token* token = malloc(sizeof(struct Token));
            token->value = strndup(&c, 1);
            token->type = type;
            token->line = line;
            token->column = column;

            struct TokenList* node = malloc(sizeof(struct TokenList));
            node->token = token;
            node->next = NULL;

            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
        current++;
        column++;
    }

    free(buffer);
    return head;
}