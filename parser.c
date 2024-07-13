#include "header.h"

// Token tokens[MAX_SIZE];
// int TokenCount = 0;
// int TokenIndex = 0;
/**
 * create_expression_node - Creates a new expression node
 * @token: The token to be stored in the expression node
 * @child: Pointer to the child expression node
 * @next: Pointer to the next expression node
 *
 * Description:
 * This function allocates memory for a new expression node, initializes it with
 * the provided token, child node, and next node, and returns a pointer to the new node.
 * If memory allocation fails, it logs an error message and exits the program.
 *
 * Return: Pointer to the newly created expression node
 */
ExpressionNode *create_expression_node(Token token, ExpressionNode *child, ExpressionNode *next)
{
    ExpressionNode *node = (ExpressionNode *)malloc(sizeof(ExpressionNode));
    if (node == NULL)
    {
        perror("Failed to allocate memory for ExpressionNode");
        exit(EXIT_FAILURE);
    }

    node->token = token;
    node->child = child;
    node->next = next;

    return (node);
}
/**
 * create_token_node - Creates a new token node
 * @token: The token to be stored in the token node
 * @next: Pointer to the next token node
 *
 * Description:
 * This function allocates memory for a new token node, initializes it with
 * the provided token and next node, and returns a pointer to the new node.
 * If memory allocation fails, it logs an error message and exits the program.
 *
 * Return: Pointer to the newly created token node
 */
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
/**
 * create_root_node - Creates a new root node
 * @child: Pointer to the child expression node
 *
 * Description:
 * This function allocates memory for a new root node, initializes it with
 * the provided child node, and returns a pointer to the new node.
 * If memory allocation fails, it logs an error message and exits the program.
 *
 * Return: Pointer to the newly created root node
 */
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
/**
 * free_expression_node - Frees an expression node and its children
 * @node: Pointer to the expression node to be freed
 *
 * Description:
 * This function recursively frees the memory allocated for the expression node
 * and its child and next nodes.
 *
 * Return: This function does not return a value.
 */
void free_expression_node(ExpressionNode *node)
{
    if (node == NULL)
    {
        return;
    }

    free_expression_node(node->child);
    free_expression_node(node->next);
    free(node);
}
/**
 * free_token_node - Frees a token node and its next nodes
 * @node: Pointer to the token node to be freed
 *
 * Description:
 * This function recursively frees the memory allocated for the token node
 * and its next nodes.
 *
 * Return: This function does not return a value.
 */
void free_token_node(TokenNode *node)
{
    if (node == NULL)
    {
        return;
    }

    free_token_node(node->next);
    free(node);
}
/**
 * free_root_node - Frees the root node and its child nodes
 * @root: Pointer to the root node to be freed
 *
 * Description:
 * This function frees the memory allocated for the root node and recursively
 * frees its child nodes.
 *
 * Return: This function does not return a value.
 */
void free_root_node(ROOT *root)
{
    if (root == NULL)
    {
        return;
    }

    free_expression_node(root->child);

    free(root);
}
/**
 * parse_return - Parses a return statement from the token list
 * @current: Double pointer to the current expression node in the AST
 *
 * Description:
 * This function parses a return statement from the token list. It checks the syntax
 * and structure of the return statement, including parentheses and semicolon. If the
 * syntax is correct, it creates corresponding expression nodes and links them in the AST.
 * If any syntax error is encountered, it logs an appropriate error message.
 *
 * Return: This function does not return a value.
 */
void parse_return(ExpressionNode **current)
{

    if (TokenIndex >= TokenCount)
    {
        fprintf(stderr, "Error: Reached end of tokens :')\n");
        return;
    }

    if (strcmp(tokens[TokenIndex].value, "return") == 0)
    {
        Token retToken = {TOKEN_RETURN, "return"};

        ExpressionNode *ret = create_expression_node(retToken, NULL, NULL);
        TokenIndex++;

        if (TokenIndex >= TokenCount)
        {
            fprintf(stderr, "Error: Unexpected end of tokens :')\n");
            return;
        }

        if (strcmp(tokens[TokenIndex].value, "(") == 0)
        {
            Token openParenToken = {TOKEN_OPEN_PAREN, "("};

            TokenNode *openParen = create_token_node(openParenToken, NULL);
            TokenIndex++;

            if (TokenIndex >= TokenCount)
            {
                fprintf(stderr, "Error: Unexpected end of tokens :') \n");
                return;
            }

            if (tokens[TokenIndex].type == TOKEN_LITERAL_INT)
            {
                Token valToken = {TOKEN_LITERAL_INT, tokens[TokenIndex].value};

                TokenNode *val = create_token_node(valToken, NULL);
                TokenIndex++;

                if (TokenIndex >= TokenCount)
                {
                    fprintf(stderr, "Error: Unexpected end of tokens :') \n");
                    return;
                }

                if (strcmp(tokens[TokenIndex].value, ")") == 0)
                {
                    Token closeParenToken = {TOKEN_CLOSE_PAREN, ")"};

                    TokenNode *closeParen = create_token_node(closeParenToken, NULL);
                    TokenIndex++;

                    if (TokenIndex >= TokenCount)
                    {
                        fprintf(stderr, "Error: Unexpected end of tokens :') \n");
                        return;
                    }

                    if (strcmp(tokens[TokenIndex].value, ";") == 0)
                    {
                        Token scolonToken = {TOKEN_SEMICOLON, ";"};

                        TokenNode *scolon = create_token_node(scolonToken, NULL);

                        openParen->next = val;
                        val->next = closeParen;
                        closeParen->next = scolon;
                        ret->next = (ExpressionNode *)openParen;

                        (*current)->child = ret;
                        *current = (*current)->child;

                        printf("Correct Return Statment horaaaaay!!\n");

                        return;
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
/**
 * parse_main - Parses the main function from the token list
 * @current: Double pointer to the current expression node in the AST
 *
 * Description:
 * This function parses the main function from the token list. It checks the syntax and structure
 * of the main function declaration, including parentheses and curly braces. If the syntax is correct,
 * it creates corresponding expression nodes and links them in the AST. If any syntax error is encountered,
 * it logs an appropriate error message.
 *
 * Return: This function does not return a value.
 */
void parse_main(ExpressionNode **current)
{
    if (TokenIndex >= TokenCount)
    {
        fprintf(stderr, "Error: Reached end of tokens :') \n");
        return;
    }

    if (strcmp(tokens[TokenIndex].value, "int") == 0)
    {
        Token INT_Token = {TOKEN_INT, "int"};

        ExpressionNode *INT = create_expression_node(INT_Token, NULL, NULL);
        TokenIndex++;

        if (TokenIndex >= TokenCount)
        {
            fprintf(stderr, "Error: Reached end of tokens :') \n");
            return;
        }

        if (strcmp(tokens[TokenIndex].value, "main") == 0)
        {
            Token MAINToken = {TOKEN_MAIN, "main"};

            TokenNode *MAIN = create_token_node(MAINToken, NULL);
            TokenIndex++;

            if (TokenIndex >= TokenCount)
            {
                fprintf(stderr, "Error: Reached end of tokens :') \n");
                return;
            }

            if (strcmp(tokens[TokenIndex].value, "(") == 0)
            {
                Token openParenToken = {TOKEN_OPEN_PAREN, "("};

                TokenNode *openParen = create_token_node(openParenToken, NULL);
                TokenIndex++;

                if (TokenIndex >= TokenCount)
                {
                    fprintf(stderr, "Error: Reached end of tokens :') \n");
                    return;
                }

                if (strcmp(tokens[TokenIndex].value, ")") == 0)
                {
                    Token closeParenToken = {TOKEN_CLOSE_PAREN, ")"};

                    TokenNode *closeParen = create_token_node(closeParenToken, NULL);
                    TokenIndex++;

                    if (TokenIndex >= TokenCount)
                    {
                        fprintf(stderr, "Error: Reached end of tokens :') \n");
                        return;
                    }

                    if (strcmp(tokens[TokenIndex].value, "{") == 0)
                    {
                        Token openCurlyToken = {TOKEN_OPEN_CURLY_PAREN, "{"};

                        TokenNode *openCurly = create_token_node(openCurlyToken, NULL);

                        MAIN->next = openParen;
                        openParen->next = closeParen;
                        closeParen->next = openCurly;
                        INT->next = (ExpressionNode *)MAIN;

                        (*current)->child = INT;
                        *current = (*current)->child;

                        printf("Correct main Statment horaaaaay!!\n");

                        return;
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

void print_expression_tree(ExpressionNode *node, int depth)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < depth; ++i)
    {
        printf("  ");
    }
    printf("- Token: %s\n", node->token.value);

    print_expression_tree(node->child, depth + 1);

    print_expression_tree(node->next, depth);
}

void print_parse_tree(ROOT *root)
{
    if (root == NULL)
    {
        printf("Parse tree is empty.\n");
        return;
    }

    printf("Parse Tree:\n");
    print_expression_tree(root->child, 0);
}

/**
 * parser - Parses the tokens to construct an abstract syntax tree (AST)
 *
 * Description:
 * This function parses the list of tokens and constructs an abstract syntax tree (AST).
 * It initializes the root of the AST and iterates through the tokens, identifying and
 * parsing specific constructs such as the main function and return statements.
 * The corresponding parsing functions are called to handle these constructs.
 *
 * Return: This function does not return a value.
 */
void parser()
{
    root = create_root_node(NULL);
    ExpressionNode *current = (ExpressionNode *)root;

    while (TokenIndex < TokenCount)
    {
        if (strcmp(tokens[TokenIndex].value, "int") == 0 && strcmp(tokens[TokenIndex + 1].value, "main") == 0)
        {
            parse_main(&current);
        }
        else if (strcmp(tokens[TokenIndex].value, "return") == 0)
        {
            parse_return(&current);
        }

        TokenIndex++;
    }
}
