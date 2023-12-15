#include "shell.h"

/**
 * main - main function.
 * @ac: arg count.
 * @av: arg vector.
 * Return: Always 0.
 */

int main(int ac, char **av)
{
	infa_t infa[] = { INFO_INT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infa->readfd = fd;
	}
	populate_env_list(infa);
	read_history(infa);
	hsh(infa, av);
	return (EXIT_SUCCESS);
}
