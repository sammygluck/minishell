#include "minishell.h"

void	execute_builtin(char **cmds, char **env, t_env_var *envs)
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
	exit (0);
}

void	execute_cmd(char **cmds, t_process *p, t_env_var *envs)
{
	int		i;
	char	*tmp; // path to binaries to check by the access system call

	if (!retrieve_path_var_env(p))
		exit(1);
	// if (cmds && is_builtin(cmds))
	// 	execute_builtin(cmds, p->envp, envs);
	// else
	{
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
}
