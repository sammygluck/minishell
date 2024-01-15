#include "minishell.h"

/* execute_builtin:
*	Executes the given command if it is a builtin command.
*	Returns 0 or 1 if the builtin command succeeded or failed.
*/

int	execute_builtin(t_cmd *command, t_process *p, t_env_var **envs)
{
	int	ret;

	ret = 1;
	if (p->pipe_count == 0)
	{
		input_redirect(command, p);
		output_redirect(command, p);
	}
	if (ft_strncmp(command->argv[0], "echo", ft_strlen("echo")) == 0)
		ret = ft_echo(command->argv);
	else if (ft_strncmp(command->argv[0], "cd", ft_strlen("cd")) == 0)
		ret = ft_cd(command->argv, p->env, envs);
	else if (ft_strncmp(command->argv[0], "pwd", ft_strlen("pwd")) == 0)
	 	ret = ft_pwd(command->argv);
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
	if (access(cmd, F_OK | X_OK) == 0) //  X_OK for execute/search permission), or the existence test (F_OK).
		execve(cmd, command->argv, p->envp);
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
		if (access(tmp, X_OK) == 0)
		{
			execve(tmp, command->argv, p->envp);
			perror("execve error");
			exit (1); // TO DO: check if the function ever comes here
		}
		free(tmp);
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command->argv[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit (127);
}

void	execute_command(t_cmd *command, t_process *p, t_env_var **envs)
{
	if (!command)
		exit (EXIT_FAILURE);
	if (command->argv && ft_strchr(command->argv[0], '/'))
		execute_local_binary(command, p);
	if (command->argv && is_builtin(command->argv))
	{
		g_last_exit_code = execute_builtin(command, p, envs);
		if (g_last_exit_code == 1)
			exit(EXIT_FAILURE);
		else
			exit (EXIT_SUCCESS);
	}
	else
	{
		if (!retrieve_path_var_env(p))
			exit(EXIT_FAILURE);
		execute_env_binary(command, p);
	}
}

pid_t	execute_cmd_in_child(t_cmd *command, fds pipes[2], t_process *p,  t_env_var **envs)
{
	pid_t	child;
	
	child = fork();
	if (child == ERROR)
		exit_error("fork", 1);
	if (child == 0)
	{
		if (input_redirect(command, p) && connect_commands(command, pipes, p) &&
			output_redirect(command, p))
			execute_command(command, p, envs);
	}
	return (child);
}
//printf("the exit code as builtin: %i\n", g_last_exit_code);