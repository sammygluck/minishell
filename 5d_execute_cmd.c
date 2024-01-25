/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5d_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:43:31 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/25 10:56:58 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* execute_builtin:
*	Executes the given command if it is a builtin command.
*	Returns 0 or 1 if the builtin command succeeded or failed.
*/

int	execute_builtin(t_cmd *command, t_process *p, t_env_var **envs)
{
	int	ret;

	ret = 1;
	if (ft_strncmp(command->argv[0], "echo", ft_strlen("echo")) == 0)
		ret = ft_echo(command->argv);
	else if (ft_strncmp(command->argv[0], "cd", ft_strlen("cd")) == 0)
		ret = ft_cd(command->argv, p->env, envs);
	else if (ft_strncmp(command->argv[0], "pwd", ft_strlen("pwd")) == 0)
		ret = ft_pwd(envs);
	else if (ft_strncmp(command->argv[0], "export", ft_strlen("export")) == 0)
		ret = ft_export(command->argv, p->env, envs);
	else if (ft_strncmp(command->argv[0], "unset", ft_strlen("unset")) == 0)
		ret = ft_unset(command->argv, p->env, envs);
	else if (ft_strncmp(command->argv[0], "env", ft_strlen("env")) == 0)
		ret = ft_env(envs);
	else if (ft_strncmp(command->argv[0], "exit", ft_strlen("exit")) == 0)
		ret = ft_exit(command->argv);
	return (ret);
}

static void	execute_local_binary(t_cmd *command, t_process *p)
{
	char	*cmd;

	if (!command)
		return ;
	cmd = command->argv[0];
	if (access(cmd, F_OK) == ERROR)
	{
		exec_error_message(command->argv[0], " ", p);
		perror(" ");
		exit (127);
	}
	if (access(cmd, F_OK | X_OK) == ERROR)
	{
		exec_error_message(command->argv[0], "", p);
		perror(" ");
		exit (126);
	}
	else if (execve(cmd, command->argv, p->envp) == ERROR)
	{
		exec_error_message(command->argv[0], ": is a directory\n", p);
		exit (126);
	}
	exit (127);
}

static void	execute_env_binary(t_cmd *command, t_process *p)
{
	int		i;
	char	*tmp;

	i = 0;
	while (p->paths[i])
	{
		tmp = ft_strjoin(p->paths[i], command->argv[0]);
		if (!tmp)
			exit (1);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			execve(tmp, command->argv, p->envp);
			exit (EXIT_SUCCESS);
		}
		free(tmp);
		i++;
	}
	exec_error_message(command->argv[0], ": command not found\n", p);
	exit (127);
}

void	execute_command(t_cmd *command, t_process *p, t_env_var **envs)
{
	if (!command)
	{
		free_process(p);
		exit (EXIT_FAILURE);
	}
	if (command->argv && ft_strchr(command->argv[0], '/'))
		execute_local_binary(command, p);
	if (command->argv && is_builtin(command->argv))
	{
		g_last_exit_code = execute_builtin(command, p, envs);
		free_process(p);
		exit(g_last_exit_code);
	}
	else
	{
		if (!retrieve_path_var_env(p))
		{
			free_process(p);
			exit(EXIT_FAILURE);
		}
		execute_env_binary(command, p);
	}
}

int	execute_cmd_in_child(t_cmd *command, t_fds pipes[2], \
		t_process *p, t_env_var **envs)
{
	static int			i;

	if (command->cmd_nr == 1 && i != 0)
		i = 0;
	p->pid[i] = fork();
	if (p->pid[i] == ERROR)
		exit_error("fork", 1);
	if (p->pid[i] == 0)
	{
		signal_handler(FORK);
		connect_commands(command, pipes, p);
		redirection_check(command, p);
		connect_redirections(p);
		execute_command(command, p, envs);
	}
	i++;
	return (EXIT_SUCCESS);
}
