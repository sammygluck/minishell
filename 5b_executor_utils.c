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
int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen("echo")) == 0)
		return (1);
	else if (ft_strncmp(command, "cd", ft_strlen("cd")) == 0)
		return (1);
	else if (ft_strncmp(command, "pwd", ft_strlen("pwd")) == 0)
		return (1);
	else if (ft_strncmp(command, "export", ft_strlen("export")) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", ft_strlen("unset")) == 0)
		return (1);
	else if (ft_strncmp(command, "env", ft_strlen("env")) == 0)
		return (1);
	else if (ft_strncmp(command, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}