#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    TOKEN_MAIN,
} TokenType;

typedef struct {
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
    struct ExpressionNode *next;
} ExpressionNode;

typedef struct RootNode 
{
    struct ExpressionNode *child;
} ROOT;


extern Token tokens[MAX_SIZE];
extern int TokenCount;
extern int TokenIndex;
extern ROOT *root;

void lexer(FILE *file);
ExpressionNode *parse_return(ExpressionNode **current);
ExpressionNode *parse_main(ExpressionNode **current);
ExpressionNode *parser();
void generate(FILE *file);
void add_token(TokenType type, const char *val);
ExpressionNode *create_expression_node(Token token, ExpressionNode *child, ExpressionNode *next);
TokenNode *create_token_node(Token token, TokenNode *next);
ROOT *create_root_node(ExpressionNode *child);
void print_expression_tree(ExpressionNode *node, int depth);
void print_parse_tree(ROOT *root);
void free_expression_node(ExpressionNode *node);
void free_token_node(TokenNode *node);
void free_root_node(ROOT *root);
void generate_main(ExpressionNode *cur, FILE *f);
void generate_return(ExpressionNode *cur, FILE *f);

#endif
