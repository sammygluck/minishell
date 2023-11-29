#include "minishell.h"

void	execute_cmd(char **cmds, t_process *p)
{
	int		i;
	char	*tmp; // path to binary to check by the access system call

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

void	run_pipe(char **cmdargs, t_process *p)
{
	pid_t		child; // to store the process id of the child processes
	
	if (pipe(p->pfd) == -1) // create the pipe and check for errors
	{
		perror("Pipe error");
		exit(1);
	}
	child = fork(); // init fork
	if (child == -1) // child/fork error
	{
		perror("fork error");
		exit(1);
	}
	if (child == 0)
	{
		close(p->pfd[0]); // close READ END of the pipe
		dup2(p->pfd[1], STDOUT_FILENO); 
		execute_cmd(cmdargs, p);
	}
	else // parent
	{
		close(p->pfd[1]); // close WRITE END of the pipe
		dup2(p->pfd[0], STDIN_FILENO);
	}
}
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

int	retrieve_path_var_env(t_env_var *head, t_process *p)
{
	t_env_var	*current;

	current = head;
	while (current) // Q: is this right condition in the while loop?
	{
		if (ft_strncmp(current->name, "PATH", ft_strlen("PATH")) == 0)
		{
			p->paths = create_paths_array(current->value);
			if (!p->paths)
			{
				printf("Error in the find_path function");
				return (0);
			}
			break ;
		}
		current = current->next;
	}
	return (1);
}

int	executor(t_cmd *ptr, t_env_var *envs, char **env)
{
	t_cmd		*current;
	t_process	p;

	p.envp = env;
	if (!p.envp)
	{
		printf("env error");
		return (0);
	}
	// retrieve the env path to locate the binaries
	if (!retrieve_path_var_env(envs, &p))
		return (0);

	// loop through the nodes with the different commands
	current = ptr;
	while (current->next != NULL)
	{
		// check if there is another command after the current one
		if (current->next)
			run_pipe(current->argv, &p);
		current = current->next;
	}
	return (1);
}