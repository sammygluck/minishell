/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5b_executor_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:35:26 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/19 11:42:55 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	error_message(char *msg)
{
	ft_putstr_fd(msg, 2);
	return ;
}

void	exit_error(char *source, int type)
{
	if (type)
		perror(source);
	else
		ft_putstr_fd(source, 2);
	exit(EXIT_FAILURE);
}

int	open_file(char *file, int file_type)
{
	int	fd;

	if (file_type == 0)
		fd = open(file, O_RDONLY);
	if (file_type == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_type == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_type == 3)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == ERROR)
		perror(file);
	return (fd);
}

int	is_builtin(char **commands)
{
	char	*cmd;

	cmd = *commands;
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", ft_strlen("env") + 1) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	return (0);
}
