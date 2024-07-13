#include "header.h"
ExpressionNode *create_expression_node(Token token, ExpressionNode *child, TokenNode *next)
{
    ExpressionNode *node = (ExpressionNode *)malloc(sizeof(ExpressionNode));
    if (node == NULL)
    {
        perror("Failed to allocate memory for ExpressionNode");
        exit(EXIT_FAILURE);
    }

    node->token = token;
    node->child = child;
    node->next = (ExpressionNode *)next;

    return (node);
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

    return (node);
}

ROOT *create_root_node(ExpressionNode *child)
{
    ROOT *node = (ROOT *)malloc(sizeof(ROOT));

    if (node == NULL)
    {
        perror("Failed to allocate memory for RootNode");
        exit(EXIT_FAILURE);
    }

    node->child = child;

    return (node);
}

void free_expression_node(ExpressionNode *node)
{
    if (node == NULL)
    {
        return;
    }

    free_expression_node(node->child);
    free_token_node((TokenNode *)node->next);
    free(node);
}

void free_token_node(TokenNode *node)
{
    if (node == NULL)
    {
        return;
    }

    free_token_node(node->next);
    free(node);
}

void free_root_node(ROOT *root)
{
    if (root == NULL)
    {
        return;
    }

    free_expression_node(root->child);

    free(root);
}

ExpressionNode *parse_return(ExpressionNode **current)
{

    if (TokenIndex >= TokenCount)
    {
        fprintf(stderr, "Error: Reached end of tokens :')\n");
        return NULL;
    }

    if (strcmp(tokens[TokenIndex].value, "return") == 0)
    {
        Token retToken = {TOKEN_RETURN, "return"};

        ExpressionNode *ret = create_expression_node(retToken, NULL, NULL);
        TokenIndex++;

        if (TokenIndex >= TokenCount)
        {
            fprintf(stderr, "Error: Unexpected end of tokens :')\n");
            return NULL;
        }

        if (strcmp(tokens[TokenIndex].value, "(") == 0)
        {
            Token openParenToken = {TOKEN_OPEN_PAREN, "("};

            TokenNode *openParen = create_token_node(openParenToken, NULL);
            TokenIndex++;

            if (TokenIndex >= TokenCount)
            {
                fprintf(stderr, "Error: Unexpected end of tokens :') \n");
                return NULL;
            }

            if (tokens[TokenIndex].type == TOKEN_LITERAL_INT)
            {
                Token valToken = {TOKEN_LITERAL_INT, tokens[TokenIndex].value};

                TokenNode *val = create_token_node(valToken, NULL);
                TokenIndex++;

                if (TokenIndex >= TokenCount)
                {
                    fprintf(stderr, "Error: Unexpected end of tokens :') \n");
                    return NULL;
                }

                if (strcmp(tokens[TokenIndex].value, ")") == 0)
                {
                    Token closeParenToken = {TOKEN_CLOSE_PAREN, ")"};

                    TokenNode *closeParen = create_token_node(closeParenToken, NULL);
                    TokenIndex++;

                    if (TokenIndex >= TokenCount)
                    {
                        fprintf(stderr, "Error: Unexpected end of tokens :') \n");
                        return NULL;
                    }

                    if (strcmp(tokens[TokenIndex].value, ";") == 0)
                    {
                        Token scolonToken = {TOKEN_SEMICOLON, ";"};

                        TokenNode *scolon = create_token_node(scolonToken, NULL);

                        openParen->next = val;
                        val->next = closeParen;
                        closeParen->next = scolon;
                        ret->next = (ExpressionNode *)openParen;

                        // *current = ret;
                        // *current = (*current)->child;
                        return ret;

                        // printf("Correct Return Statment horaaaaay!!\n");

                        return NULL;
                    }
                    else
                    {
                        fprintf(stderr, "Syntax Error: Expected ;\n");
                    }
                }
                else
                {
                    fprintf(stderr, "Syntax Error: Expected ) \n");
                }
            }
            else
            {
                printf("toke value: %s", tokens[TokenIndex].value);
                fprintf(stderr, "Syntax Error: Expected an Integer\n");
            }
        }
        else
        {
            fprintf(stderr, "Syntax Error: Expected ( \n");
        }
    }

    fprintf(stderr, "Syntax Error: Invalid Return Statment :') \n");
}

ExpressionNode *parse_main(ExpressionNode **current)
{
    if (TokenIndex >= TokenCount)
    {
        fprintf(stderr, "Error: Reached end of tokens :') \n");
        return NULL;
    }

    if (strcmp(tokens[TokenIndex].value, "int") == 0)
    {
        Token INT_Token = {TOKEN_INT, "int"};

        ExpressionNode *INT = create_expression_node(INT_Token, NULL, NULL);
        TokenIndex++;

        if (TokenIndex >= TokenCount)
        {
            fprintf(stderr, "Error: Reached end of tokens :') \n");
            return NULL;
        }

        if (strcmp(tokens[TokenIndex].value, "main") == 0)
        {
            Token MAINToken = {TOKEN_MAIN, "main"};

            TokenNode *MAIN = create_token_node(MAINToken, NULL);
            TokenIndex++;

            if (TokenIndex >= TokenCount)
            {
                fprintf(stderr, "Error: Reached end of tokens :') \n");
                return NULL;
            }

            if (strcmp(tokens[TokenIndex].value, "(") == 0)
            {
                Token openParenToken = {TOKEN_OPEN_PAREN, "("};

                TokenNode *openParen = create_token_node(openParenToken, NULL);
                TokenIndex++;

                if (TokenIndex >= TokenCount)
                {
                    fprintf(stderr, "Error: Reached end of tokens :') \n");
                    return NULL;
                }

                if (strcmp(tokens[TokenIndex].value, ")") == 0)
                {
                    Token closeParenToken = {TOKEN_CLOSE_PAREN, ")"};

                    TokenNode *closeParen = create_token_node(closeParenToken, NULL);
                    TokenIndex++;

                    if (TokenIndex >= TokenCount)
                    {
                        fprintf(stderr, "Error: Reached end of tokens :') \n");
                        return NULL;
                    }

                    if (strcmp(tokens[TokenIndex].value, "{") == 0)
                    {
                        Token openCurlyToken = {TOKEN_OPEN_CURLY_PAREN, "{"};

                        TokenNode *openCurly = create_token_node(openCurlyToken, NULL);

                        MAIN->next = openParen;
                        openParen->next = closeParen;
                        closeParen->next = openCurly;
                        INT->next = (ExpressionNode *)MAIN;

                        // *current = INT;
                        // *current = (*current)->child;
                        return INT;

                        // printf("Correct main Statment horaaaaay!!\n");
                    }
                    else
                    {
                        fprintf(stderr, "Syntax Error: Expected { \n");
                    }
                }
                else
                {
                    fprintf(stderr, "Syntax Error: Expected ) \n");
                }
            }
            else
            {
                fprintf(stderr, "Syntax Error: Expected ( \n");
            }
        }
        else
        {
            fprintf(stderr, "Syntax Error: Expected main\n");
        }
    }
}

// void print_expression_tree(ExpressionNode *node, int depth)
// {
//     if (node == NULL)
//     {
//         return NULL;
//     }

//     for (int i = 0; i < depth; ++i)
//     {
//         printf("  ");
//     }
//     printf("- Token: %s\n", node->token.value);

//     print_expression_tree(node->child, depth + 1);

//     // print_expression_tree(node->next, depth);
// }

// void print_parse_tree(ROOT *root)
// {
//     if (root == NULL)
//     {
//         printf("Parse tree is empty.\n");
//         return NULL;
//     }

//     printf("Parse Tree:\n");
//     print_expression_tree(root->child, 0);
// }

/**
 * parser - The Main Parser Function
 */
ExpressionNode *parser()
{

    ExpressionNode *root = create_expression_node((Token){0}, NULL, NULL);
    ExpressionNode *current = root;

    while (TokenIndex < TokenCount)
    {
        if (strcmp(tokens[TokenIndex].value, "int") == 0 && strcmp(tokens[TokenIndex + 1].value, "main") == 0)
        {
            current->child = parse_main(&current);
        }
        else if (strcmp(tokens[TokenIndex].value, "return") == 0)
        {
            current->child = parse_return(&current);
        }
        current = current->child;
        TokenIndex++;
    }

    // print_parse_tree(root);

    // free_root_node(root);
    return root;
}
