#include "header.h"

Token tokens[MAX_SIZE];
int TokenCount = 0;
int TokenIndex = 0;
ROOT *root;

/**
 * 
 * 
 */
int main()
{
    FILE *file;

    file = fopen("test.c", "r");

    lexer(file);

    for (int i = 0; i < TokenCount; i++)
    {
        printf("%s\n", tokens[i].value);
    }
    
    fclose(file);

    parser();

    free(root);

    /**for (int i < 0; i < TokenCount; i++)
    {
        free(tokens[i].value);
    }*/

    return(0);
}
