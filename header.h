#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1024

typedef enum
{
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
    TOKEN_MAIN,
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;

typedef struct TokenNode
{
    Token token;
    struct TokenNode *next;
} TokenNode;

typedef struct ExpressionNode
{
    Token token;
    struct ExpressionNode *child;
    TokenNode *next;
} ExpressionNode;

typedef struct RootNode
{
    ExpressionNode *child;
} ROOT;

extern Token tokens[MAX_SIZE];
extern int TokenCount;
extern int TokenIndex;
// extern ROOT *root;

void lexer(FILE *file);
void generat(ExpressionNode *root, char *file_name);
ExpressionNode *parser();








void free_expression_node(ExpressionNode *node);

void free_token_node(TokenNode *node);

void free_root_node(ROOT *root);

#endif
