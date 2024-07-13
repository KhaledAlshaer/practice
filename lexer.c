#include "header.h"

/**
 * add_token - Adds a token to the token list
 * @type: The type of the token to be added
 * @val: The value of the token to be added
 *
 * Description:
 * This function adds a new token to the global token list. It first checks if
 * the current number of tokens has reached the maximum allowed size. If so,
 * it logs an error message and exits the program. Otherwise, it assigns the
 * type and value to the next available token in the list and increments the token count.
 *
 * Return: This function does not return a value.
 */
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
 * lexer - Tokenizes the input from a given file
 * @file: Pointer to the file to be tokenized
 *
 * Description:
 * This function reads the content of the provided file character by character,
 * and identifies different types of tokens such as semicolons, parentheses,
 * curly braces, keywords (like "return" and "int"), identifiers, and integer literals.
 * It calls the add_token function to add the identified tokens to the token list.
 * If the file pointer is NULL, it logs an error and adds a TOKEN_UNKNOWN type token.
 *
 * Return: This function does not return a value.
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
