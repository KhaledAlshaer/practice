#include "header.h"

/**
 * 
 * 
 * comments section
 * 
 * 
 */
int lexer(FILE *file) {

    char word[256];
    int ch;
    int i =  0;
    Token token;
    token.value = NULL;

    if (file == NULL){
        perror("File Doesn't Exist");
        token.type = UNKNOWN;
        return(token);
    }

    while ((ch = fgetc(file)) != EOF) {
        switch (ch) {
            case ';':
                token.type = TOKEN_SEMICOLON;
                return (token);
            case '(':
                token.type = TOKEN_OPEN_PAREN;
                return (token);
            case ')':
                token.type = TOKEN_CLOSE_PAREN;
                return (token);
            case '{':
                token.type = TOKEN_OPEN_CURLY_PAREN;
                return (token);
            case '}':
                token.type = TOKEN_CLOSE_CURLY_PAREN;
                return (token);
            default:
                if (isalpha(ch)){
                    word[i++] = ch;

                    while (isalpha(ch = fgetc(file))) {
                        word[i++] = ch;
                    }

                    ungetc(ch, file);
                    word[i] = '\0';
                    if (strcmp(word) == "return") {
                        token.type = TOKEN_RETURN;
                    } else if (strcmp(word) == "int") {
                        token.type = TOKEN_INT;
                    } else {
                        token.type = TOKEN_UNKNOWN;
                    }

                    token.value = strdup(word);

                    return(token);


                } else if (isdigit(ch)) {
                    word[i++] = ch;

                    while (isdigit(ch)) {
                        word[i++] = ch;
                    }

                    ungetc(ch, file);
                    word[i] = '\0';
                    token.type = TOKEN_LITERAL_INT;
                    token.value = strdup(word);

                    return(token);
                } else if (isspace(ch)) {
                    continue;
                } else {
                    token.type = TOKEN_UNKNOWN;

                    return(token);
                }
        }
    }

    token.type = TOKEN_UNKNOWN;

    return(token);
}
