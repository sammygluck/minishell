#include "minishell.h"

char	**create_paths_array(char *path)
{
	int		i;
	char	**paths; // 2D array with different paths to binaries

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
		{
			free_array(paths);
			return (NULL);
		}
		i++;
	}
	return (paths);
}

int	retrieve_path_var_env(t_process *p)
{
	char	*tmp;
	char	*path;
	int		i;

	tmp = getenv("PATH");
	if (!tmp)
		return (0);
	path = (char *)malloc(sizeof(char) * ((int)ft_strlen(tmp) + 1));
	if (!path)
		return (0);
	i = 0;
	while (tmp[i])
	{
		path[i] = tmp[i];
		i++;
	}
	path[i] = '\0';
	p->paths = create_paths_array(path);
	if (!p->paths)
		return (0);
	return (1);
}
t_process	*init_process_struct(char **env)
{
	t_process	*p;

	p = ft_malloc(sizeof(t_process));
	p->fd_in = -1;
	p->fd_out = -1;
	p->status = -1;
	p->paths = NULL;
	p->envp = env;
	return (p);
}

int	executor(t_cmd *command, char **env)
{
	t_cmd		*current_cmd;
	t_process	*p;


	// check if the command exists
	if (command == 0)
		return (0); // TO DO: needs to be adjusted to where the function needs to exit

	p = init_process_struct(env);

	// check if there is a redirection and handle the different cases from there
	if (command->redir)
	{
		check_redirection_type(); 
	}

	// retrieve the env path to locate the binaries
	if (!retrieve_path_var_env(p))
		return (0);

	// loop through the nodes with the different commands
	current_cmd = command;
	while (current_cmd)
	{
		// check if there is another command after the current one
		if (current_cmd->next)
			run_pipe(current_cmd->argv, p);
		else
			break ;
		current_cmd = current_cmd->next;
	}
	execute_cmd(current_cmd->argv, p);
	return (1);
}
