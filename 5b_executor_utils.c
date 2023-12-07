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

void exit_error(char *source, int type)
{
	if (type) // system call with ERRNO set
		perror(source);
	else
		ft_putstr_fd(source, 2);
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
	if (file_type == 3)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777); // TO DO: check if right file permissions
	if (fd == ERROR)
	{
		perror(file);
		exit(1); // Q: exit failure ok?
	}
	return (fd);
}