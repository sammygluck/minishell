#include "minishell.h"

static int fork_pipe_redirect(t_cmd	**command, io pipes[2], int pipe_count, t_process *p)
{
	pid_t	child;
	
	child = fork();
	if (child == 0)
	{
		if (redirect_in(*command, p) && 
			connect_commands(*command, pipes, pipe_count, p) && 
			redirect_out(*command, p))
			return (1);
	}
	else // parent
		waitpid(child, &p->status, 0);
	return (0);
}

static t_process	*init_process_struct(char **env)
{
	t_process	*p;

	p = ft_malloc(sizeof(t_process));
	p->fd_in = -1; // TO DO: remove?
	p->fd_out = -1; // TO DO: remove?
	p->status = -1; // TO DO: remove?
	p->total_cmds = 0;
	p->paths = NULL;
	p->envp = env;
	return (p);
}

int	executor(t_cmd **command, char **env)
{
	t_cmd		*current_cmd;
	t_process	*p;
	int			pipe_count;
	static io 	pipes[2];
	int			is_child_process;

	// check if the command exists
	if (*command == 0)
		return (0); // TO DO: needs to be adjusted to where the function needs to exit

	// init the process struct
	p = init_process_struct(env);

	// retrieve the env path to locate the binaries
	if (!retrieve_path_var_env(p))
		return (0);
	
	// count the number of pipes and commands
	pipe_count = 0;
	current_cmd = *command;
	while (current_cmd)
	{
		p->total_cmds = current_cmd->cmd_nr;
		if (current_cmd->next)
			pipe_count++;
		current_cmd = current_cmd->next;
	}

	// loop through the nodes with the different commands
	current_cmd = *command;
	while (current_cmd)
	{
		if (pipe_count && pipe(pipes[CURRENT]) == ERROR)
		{
			perror("pipe() error");
			exit (1);
		}
		is_child_process = fork_pipe_redirect(&current_cmd, pipes, pipe_count, p);
		if (is_child_process)
			execute_cmd(current_cmd->argv, p);
		close_pipe(current_cmd, pipes, pipe_count, p);
		alternate_pipes((int **)pipes);
		if (current_cmd->next)
			current_cmd = current_cmd->next;
		else
			break ;
	}
	return (1);
}

