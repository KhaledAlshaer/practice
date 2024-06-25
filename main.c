#include "header.h"

/**
 * 
 * 
 */
int main()
{
    FILE *file;

    file = fopen("test.c", "r");

    lexer(file);
    
    fclose(file);

    parser();

    return(0);
}
