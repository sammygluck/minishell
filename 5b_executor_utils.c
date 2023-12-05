#include "minishell.h"

void	free_array(char **array)
{
	int	i;
	
	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void exit_error(const char *source)
{
	perror(source);
	exit(EXIT_FAILURE);
}

int	open_file(char *file, int file_type)
{
	int fd;

	if (file_type == 0)
		fd = open(file, O_RDONLY); // TO DO: check if right file permissions
	if (file_type == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // TO DO: check if right file permissions
	if (file_type == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644); // TO DO: check if right file permissions
	if (fd == -1)
	{
		perror(file);
		exit(1); // Q: exit failure ok?
	}
	return (fd);
}