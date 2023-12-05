#include "minishell.h"

void	execute_cmd(char **cmds, t_process *p)
{
	int		i;
	char	*tmp; // path to binaries to check by the access system call

	if (!retrieve_path_var_env(p))
		exit(1);
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
