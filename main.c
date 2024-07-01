#include "header.h"

Token tokens[MAX_SIZE];
int TokenCount = 0;
int TokenIndex = 0;

/**
 * 
 * 
 */
int main()
{
    FILE *file;

    file = fopen("test", "r");

    lexer(file);
    
    fclose(file);

    parser();

    return(0);
}
