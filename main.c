#include "monty.h"

/**
 * main - Monty 0.98 interpreter.
 * @argc: count of the input arguments from terminal.
 * @argv: array of strings holding the input arguments.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE if failed.
 */
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK | R_OK) != 0)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	read_monty(argv[1]);

	return (EXIT_SUCCESS);
}
