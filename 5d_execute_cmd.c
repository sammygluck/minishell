#include "minishell.h"

int	execute_builtin(t_cmd *command, t_process *p, t_env_var **envs)
{
	//create return value
	if (p->pipe_count == 0)
	{
		input_redirect(command, p);
		output_redirect(command, p);
	}
	if (ft_strncmp(command->argv[0], "echo", ft_strlen("echo")) == 0)
		ft_echo(command->argv);
	else if (ft_strncmp(command->argv[0], "cd", ft_strlen("cd")) == 0)
		ft_cd(command->argv, p->env, envs);
	else if (ft_strncmp(command->argv[0], "pwd", ft_strlen("pwd")) == 0)
	 	ft_pwd(command->argv);
	else if (ft_strncmp(command->argv[0], "export", ft_strlen("export")) == 0)
		ft_export(command->argv, p->env, envs);
	else if (ft_strncmp(command->argv[0], "unset", ft_strlen("unset")) == 0)
		ft_unset(command->argv, p->env, envs);
	else if (ft_strncmp(command->argv[0], "env", ft_strlen("env")) == 0)
		ft_env(envs);
	else if (ft_strncmp(command->argv[0], "exit", ft_strlen("exit")) == 0)
	 	ft_exit(command->argv);
	return (1);
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

void	execute_cmd(t_cmd *command, t_process *p, t_env_var **envs)
{
	if (!command)
		exit (EXIT_FAILURE);
	if (command->argv && ft_strchr(command->argv[0], '/'))
		execute_local_binary(command, p);
	// else if (command->argv && is_builtin(command->argv))
	// 	execute_builtin(command, p, envs);
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
			execute_cmd(command, p, envs);
	}
	else
		waitpid(child,&p->status, 0);
	return (child);
}