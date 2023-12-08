#include "minishell.h"

static int	is_builtin(char **cmds)
{
	if (ft_strncmp(cmds[0], "echo", ft_strlen("echo")) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "cd", ft_strlen("cd")) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "pwd", ft_strlen("pwd")) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "export", ft_strlen("export")) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "unset", ft_strlen("unset")) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "env", ft_strlen("env")) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}
void	execute_cmd(char **cmds, t_process *p)
{
	int		i;
	char	*tmp; // path to binaries to check by the access system call

	if (!retrieve_path_var_env(p))
		exit(1);
	if (is_builtin(cmds))
	{
		printf("this is a builtin function - TBC\n");
		exit (1);
	}
	i = 0;
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

