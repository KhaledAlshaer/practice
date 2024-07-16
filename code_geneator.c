#include "header.h"
/**
 * generate - Generates assembly code from the AST
 *
 * Description:
 * This function opens a file named "as.s" for writing and traverses the AST
 * to generate corresponding assembly code. It iterates through the child nodes
 * of the root and calls specific functions to handle the generation of code for
 * different types of nodes.
 *
 * Return: This function does not return a value.
 */
void generate(ExpressionNode *root, char *file_name)
{
	file_name[strlen(file_name) - 2] = '\0';

	FILE *file = fopen("as.s", "w");
	ExpressionNode *cur = root->child;
	while (cur != NULL)
	{
		if (cur->token.type == TOKEN_INT && cur->next != NULL && cur->next->token.type == TOKEN_MAIN)
		{
			generate_main(cur, file);
		}
		else if (cur->token.type == TOKEN_RETURN)
		{
			generate_return(cur, file);
		}
		cur = cur->child;
	}
	fclose(file);
	system("as -o as.o as.s");
	char *command[256];
	sprintf(command, "gcc -o %s as.o", file_name);

	system(command);
	system("rm as.s as.o");
}
/**
 * generate_main - Generates assembly code for the main function
 * @cur: Pointer to the current expression node
 * @f: Pointer to the file where the assembly code will be written
 *
 * Description:
 * This function writes the assembly code for the main function to the specified file.
 *
 * Return: This function does not return a value.
 */
void generate_main(ExpressionNode *cur, FILE *f)
{

    fprintf(f, "\
.section .text\n\
.global main\n\
.intel_syntax noprefix\n\
\nmain:\n\
");
}
/**
 * generate_return - Generates assembly code for a return statement
 * @cur: Pointer to the current expression node
 * @f: Pointer to the file where the assembly code will be written
 *
 * Description:
 * This function writes the assembly code for a return statement to the specified file.
 * It generates the code to move the return value into the appropriate register and perform
 * a system call to exit the program.
 *
 * Return: This function does not return a value.
 */
void generate_return(ExpressionNode *cur, FILE *f)
{
    fprintf(f, "\
\tmov rax, 60\n\
\tmov rdi, %s\n\
\tsyscall\n\
",
            cur->next->next->token.value);
}
