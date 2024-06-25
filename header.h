#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024

typedef enum {
    TOKEN_SEMICOLON,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_OPEN_CURLY_PAREN,
    TOKEN_CLOSE_CURLY_PAREN,
    TOKEN_RETURN,
    TOKEN_INT,
    TOKEN_LITERAL_INT,
    TOKEN_IDENTIFIER,
    TOKEN_UNKNOWN,
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;


extern Token tokens[MAX_SIZE];
extern int TokenCount;
extern int TokenIndex;

void lexer(FILE *file);
void parse_return ();
void parse_main();
void parser ();
void add_token(TokenType type, const char *val);

#endif
