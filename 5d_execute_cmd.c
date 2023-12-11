#include "minishell.h"

void	ft_echo(char **cmd)
{
	int	n_flag;
	int		i;

	i = 1;
	n_flag = 0;
	if (cmd[1] && ft_strncmp(cmd[1], "-n", ft_strlen("-n")) == 0)
	{
		n_flag = 1;
		i = 2;
	}
	while (cmd && cmd[i])
	{
		printf("%s ", cmd[i]);
		i++;
	}
	if (n_flag == 0)
		printf("\n");
}

void	execute_builtin(char **cmds)
{
	if (ft_strncmp(cmds[0], "echo", ft_strlen("echo")) == 0)
		ft_echo(cmds);
	// else if (ft_strncmp(cmds, "cd", ft_strlen("cd")) == 0)
	// 	ft_cd(cmds);
	// else if (ft_strncmp(cmds, "pwd", ft_strlen("pwd")) == 0)
	// 	ft_pwd(cmds);
	// else if (ft_strncmp(cmds, "export", ft_strlen("export")) == 0)
	// 	ft_export(cmds);
	// else if (ft_strncmp(cmds, "unset", ft_strlen("unset")) == 0)
	// 	ft_unset(cmds);
	// else if (ft_strncmp(cmds, "env", ft_strlen("env")) == 0)
	// 	ft_env(cmds);
	// else if (ft_strncmp(cmds, "exit", ft_strlen("exit")) == 0)
	// 	ft_exit(cmds);
}

void	execute_cmd(char **cmds, t_process *p)
{
	int		i;
	char	*tmp; // path to binaries to check by the access system call

	if (!retrieve_path_var_env(p))
		exit(1);
	i = 0;
	printf("OK\n");
	while (p->paths[i])
	{
		tmp = ft_strjoin(p->paths[i], cmds[0]);
		if (!tmp)
			exit (1);
		if (access(tmp, X_OK) == 0)
		{
			execve(tmp, cmds, p->envp);
			perror("execve error");
			exit (1); // TO DO: check if the function ever comes here
		}
		free(tmp);
		i++;
	}
	ft_putstr_fd("executor: command not found: ", 2);
	ft_putendl_fd(cmds[0], 2);
	exit (127);
}

void	execute_cmd_fork(t_cmd *command, fds pipes[2], int pipe_count, t_process *p)
{
	pid_t	child;
	
	child = fork();
	if (child == ERROR)
		exit_error("fork", 1);
	if (child == 0)
	{
		//connect_commands(command, pipes, pipe_count, p);
		execute_cmd(command->argv, p);
	}
	else // parent
		waitpid(child, &p->status, 0);
}
