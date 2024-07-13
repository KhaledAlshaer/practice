#include "header.h"

Token tokens[MAX_SIZE];
int TokenCount = 0;
int TokenIndex = 0;
ROOT *root;

void add_token(TokenType type, const char *val)
{
    if (TokenCount >= MAX_SIZE)
    {
        perror("ERROR: Too Many Tokens!");
        exit(1);
    }

    tokens[TokenCount].type = type;
    tokens[TokenCount].value = strdup(val);
    TokenCount++;
}

/**
 * lexer - A Funtion That Takes The Source File And Tokenize It's Contents.
 * @file: The Source FIle
 */
void lexer(FILE *file)
{
    char word[256];
    // int column = 0;
    // int line = 1;
    int ch;
    int i;
    Token token;

    if (file == NULL)
    {
        perror("File Doesn't Exist");
        token.type = TOKEN_UNKNOWN;
        add_token(TOKEN_UNKNOWN, "NULL");

        return;
    }

    while ((ch = fgetc(file)) != EOF)
    {
        i = 0;
        switch (ch)
        {
        case ';':
            add_token(TOKEN_SEMICOLON, ";");
            break;
        case '(':
            add_token(TOKEN_OPEN_PAREN, "(");
            break;
        case ')':
            add_token(TOKEN_CLOSE_PAREN, ")");
            break;
        case '{':
            add_token(TOKEN_OPEN_CURLY_PAREN, "{");
            break;
        case '}':
            add_token(TOKEN_CLOSE_CURLY_PAREN, "}");
            break;
        default:
            if (isalpha(ch))
            {
                word[i++] = ch;

                while (isalpha(ch = fgetc(file)))
                {
                    word[i++] = ch;
                }

                ungetc(ch, file);
                word[i] = '\0';
                if (strcmp(word, "return") == 0)
                {
                    add_token(TOKEN_RETURN, word);
                }
                else if (strcmp(word, "int") == 0)
                {
                    add_token(TOKEN_INT, word);
                }
                else
                {
                    add_token(TOKEN_IDENTIFIER, word);
                }
            }
            else if (isdigit(ch))
            {
                word[i++] = ch;

                while (isdigit(ch = fgetc(file)))
                {
                    word[i++] = ch;
                }

                ungetc(ch, file);
                word[i] = '\0';
                add_token(TOKEN_LITERAL_INT, word);
            }
            else if (isspace(ch))
            {
                continue;
            }
            else
            {
                add_token(TOKEN_UNKNOWN, "");
            }

            break;
        }
    }
}

// Token tokens[MAX_SIZE];
// int TokenCount = 0;
// int TokenIndex = 0;

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
    free_expression_node(node->next);
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
 * parser - The Main Parser Function
 */
void parser()
{

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

    // print_parse_tree(root);

    // free_root_node(root);
}

/**
 *
 *
 */
int main()
{
    root = create_root_node(NULL);
    FILE *file;

    file = fopen("test.c", "r");

    lexer(file);

    fclose(file);

    parser();

    ExpressionNode *tmp = root->child;
    // TokenNode *tmp_node;
    // while (tmp != NULL)
    // {
    //     printf("{%s | %d}\n", tmp->token.value, tmp->token.type);
    //     tmp = tmp->child;
    // }

    return (0);
}
