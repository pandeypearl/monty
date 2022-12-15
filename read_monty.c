#include "monty.h"

/**
 * read_monty - function that reads and interpretates a monty file.
 * @file: name of the monty file to be interpretated.
 * 
 * Return: 0 on success, 1 on failure
 */

int read_monty(char *file)
{
	int error = EXIT_SUCCESS;

	if (file == NULL)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	error = proc_monty();
	close(fd);
	return (error);
}

/**
 * proc_monty - processes the opened monty file.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */

int proc_monty(void)
{
	int stay1 = 1, i = 0, stk = 1, error = EXIT_SUCCESS;
	char buf[1024];
	ssize_t ra = 0, bsize = sizeof(buf) / sizeof(buf[0]);
	stack_t *stack = NULL;

	while (stay1)
	{
		ra = read(fd, &buf[i], bsize - i);
		if (ra <= 0)
			return (1);
		if (ra < bsize)
		{
			bsize = ra;
			stay1 = 0;
		}
		error = proc_lines(&stack, &buf, bsize, &i, &stk);
	}
	free_stack(stack);
	return (error);
}

/**
 * proc_lines - processes the lines acquired on the buf.
 * @stck: head of the stack.
 * @b: buffer holding several lines to be read.
 * @bsize: size of the buffer.
 * @i: index from which new characters must be stored in buf in a new read.
 * @md: mode selection for stack or queue, 1 is default for stack mode.
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */

int proc_lines(stack_t **stck, char (*b)[1024], ssize_t bsize, int *i, int *md)
{
	int start = 0, end = 0, error = EXIT_SUCCESS, count = 0, n_bytes = 0;
	char line[1024], *token = NULL;
	void (*f)(stack_t **stack, unsigned int line_number) = NULL;

	while (1)
	{
		if (end + 1 < bsize && count != 0)
		{
			start = end + 1;
			end = start;
		}
		else if (end + 1 >= bsize)
		{
			*i = 0;
			break;
		}
		while (end < bsize && (*b)[end] != '\n')
			end++;
		if ((*b)[end] != '\n')
		{
			n_bytes = end - start;
			for (*i = 0; *i < n_bytes; (*i)++)
				(*b)[*i] = (*b)[start + *i];
			break;
		}
		n_bytes = end - start + 1;
		++count;
		_strncpy(line, &((*b)[start]), n_bytes);
		line[n_bytes] = '\0';
		if (line[0] == '#')
			continue;
		token = strtok(line, " \n\t\r");
		if (token == NULL)
			continue;
		f = check_f(token, md, *stck, count);
		f(stck, count);
	}
	return (error);
}
