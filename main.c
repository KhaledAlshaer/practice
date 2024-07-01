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

	file = fopen("test.c", "r");

	lexer(file);

	for (int i = 0; i < TokenCount; i++)
	{
		printf("%s\n", tokens[i].value);
	}
    
	fclose(file);

	parser();

	return(0);
}
