#include "header.h"

Token tokens[MAX_SIZE];
int TokenCount = 0;
int TokenIndex = 0;

/**
 *
 *
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Enter one file\n");
	}

	if (strstr(argv[1], ".c") == NULL)
	{
		fprintf(stderr, "extension is not .c\n");
	}

	FILE *file;

	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		fprintf(stderr, "file not found\n");
	}

	lexer(file);

	fclose(file);

	ExpressionNode *root = parser();

	generate(root, argv[1]);

	return (0);
}
