#include "header.h"
/**
 * generat - Generates assembly code from the AST
 *
 * Description:
 * This function opens a file named "as.s" for writing and traverses the AST
 * to generate corresponding assembly code. It iterates through the child nodes
 * of the root and calls specific functions to handle the generation of code for
 * different types of nodes.
 *
 * Return: This function does not return a value.
 */
void generat()
{
    FILE *file = fopen("as.s", "w");
    ExpressionNode *cur = root->child;
    while (cur != NULL)
    {
        if (cur->token.type == TOKEN_INT && cur->next != NULL && cur->next->token.type == TOKEN_MAIN)
        {
            generat_main(cur, file);
        }
        else if (cur->token.type == TOKEN_RETURN)
        {
            generat_return(cur, file);
        }
        cur = cur->child;
    }
}
/**
 * generat_main - Generates assembly code for the main function
 * @cur: Pointer to the current expression node
 * @f: Pointer to the file where the assembly code will be written
 *
 * Description:
 * This function writes the assembly code for the main function to the specified file.
 *
 * Return: This function does not return a value.
 */
void generat_main(ExpressionNode *cur, FILE *f)
{

    fprintf(f, "\
.global main\n\
.intel_syntax noprefix\n\
main:\n\
");
}
/**
 * generat_return - Generates assembly code for a return statement
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
void generat_return(ExpressionNode *cur, FILE *f)
{
    fprintf(f, "\
\tmov rax, 60\n\
\tmov rdi, %s\n\
\tsyscall\n\
",
            cur->next->next->token.value);
}

int main()
{
    generat();
}