#include "header.h"

//Token tokens[MAX_SIZE];
//int TokenCount = 0;
//int TokenIndex = 0;

typedef struct ExpressionNode 
{
    Token token;
    struct ExpressionNode *child;
} ExpressionNode;

typedef struct TokenNode 
{
    Token token;
    struct TokenNode *next;
} TokenNode;

ExpressionNode *create_expression_node(Token token, ExpressionNode *child)
{
    ExpressionNode *node = (ExpressionNode *)malloc(sizeof(ExpressionNode));
    if (node == NULL)
    {
        perror("Failed to allocate memory for ExpressionNode");
        exit(EXIT_FAILURE);
    }

    node->token = token;
    node->child = child;

    return(node);
}

TokenNode *create_token_node(Token token, TokenNode *next)
{
    TokenNode *node = (TokenNode *)malloc(sizeof(TokenNode));
    if (node == NULL)
    {
        perror("Failed to allocate memory for TokenNode");
        exit(EXIT_FAILURE);
    }

    node->token = token;
    node->next = next;

    return(node);
}

/**
 * parser - 
 */
void parser()
{
}
void parse_return ()
{
    TokenNode openParen = {TOKEN_OPEN_PAREN, "("};
    TokenNode val = {TOKEN_LITERAL_INT, tokens[TokenIndex].value};
    TokenNode closeParen = {TOKEN_CLOSE_PAREN, ")"};
    TokenNode scolon = {TOKEN_SEMICOLON, ";"};
    ExpressionNode ret = {TOKEN_RETURN, "return"};

    if (TokenIndex >= TokenCount)
    {
        fprintf(stderr, "Error: Reached end of tokens :'\)\n");
        return;
    }

    if (strcmp(tokens[TokenIndex].value, "return") == 0)
    {
        TokenIndex++;

        if (TokenIndex >= TokenCount)
        {
            fprintf(stderr, "Error: Unexpected end of tokens :'\)\n");
            return;
        }

        if (strcmp(tokens[TokenIndex].value, "(") == 0)
        {
            TokenIndex++;

            if (TokenIndex >= TokenCount)
            {
                fprintf(stderr, "Error: Unexpected end of tokens :'\)\n");
                return;
            }

            if (tokens[TokenIndex].type == TOKEN_LITERAL_INT)
            {
                TokenIndex++;

                if (TokenIndex >= TokenCount)
                {
                    fprintf(stderr, "Error: Unexpected end of tokens :'\)\n");
                    return;
                }

                if (strcmp(tokens[TokenIndex].value, ")") == 0)
                {
                    TokenIndex++;

                    if (TokenIndex >= TokenCount)
                    {
                        fprintf(stderr, "Error: Unexpected end of tokens :'\)\n");
                        return;
                    }

                    if (strcmp(tokens[TokenIndex].value, ";") == 0)
                    {
                        printf("Correct Return Statment horaaaaay!!\n");
                        return;
                    }
                }
            }
        }
    }

    fprintf(stderr, "Syntax Error: Invalid Return Statment :'\)\n");
}


void parse_main()
{
    if (TokenIndex >= TokenCount)
    {
        fprintf(stderr, "Error: Reached end of tokens :'\)\n");
        return;
    }

    if (strcmp(tokens[TokenIndex].value, "int") == 0)
    {
        TokenIndex++;

        if (TokenIndex >= TokenCount)
        {
            fprintf(stderr, "Error: Reached end of tokens :'\)\n");
            return;
        }

        if (strcmp(tokens[TokenIndex].value, "main") == 0)
        {
            TokenIndex++;

            if (TokenIndex >= TokenCount)
            {
                fprintf(stderr, "Error: Reached end of tokens :'\)\n");
                return;
            }

            if (strcmp(tokens[TokenIndex].value, "(") == 0)
            {
                TokenIndex++;

                if (TokenIndex >= TokenCount)
                {
                    fprintf(stderr, "Error: Reached end of tokens :'\)\n");
                    return;
                }

                if (strcmp(tokens[TokenIndex].value, ")") == 0)
                {
                    printf("Correct main Statment horaaaaay!!\n");
                    return;
                }
            }
        }
    }
}
