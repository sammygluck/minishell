#include "minishell.h"

static int	fork_pipe_redirect(t_cmd *command, fds pipes[2], int pipe_count, t_process *p)
{
	pid_t	child;
	
	child = fork();
	if (child == ERROR)
		exit_error("fork", 1);
	if (child == 0)
	{
		if (input_redirect(command, p) && 
			connect_commands(command, pipes, pipe_count, p) && 
			output_redirect(command, p))
			return (1);
	}
	else // parent
		waitpid(child, &p->status, 0);
	return (0);
}

static void	command_pipe_count(t_cmd *command, t_process *p)
{
	t_cmd	*current_cmd;
	
	current_cmd = command;
	while (current_cmd)
	{
		p->cmds_count = current_cmd->cmd_nr;
		if (current_cmd->next)
			p->pipe_count++;
		current_cmd = current_cmd->next;
	}
}

static t_process	*init_process_struct(char **env)
{
	t_process	*p;

	p = ft_malloc(sizeof(t_process));
	if (!p)
		exit (1);
	p->fd_in = -1; // TO DO: remove?
	p->fd_out = -1; // TO DO: remove?
	p->status = -1; // TO DO: remove?
	p->pipe_count = 0;
	p->cmds_count = 0;
	p->paths = NULL;
	p->envp = env;
	return (p);
}

void	executor(t_cmd **command, char **env)
{
	t_cmd		*current_cmd;
	t_process	*p;
	static fds	pipes[2];
	int			child_process;

	if (*command == 0)
		exit(1);
	p = init_process_struct(env);
	command_pipe_count(*command, p);
	current_cmd = *command;
	while (current_cmd)
	{	
		if (p->pipe_count && pipe(pipes[CURRENT]) == ERROR)
			exit_error("pipe", 1);
		child_process = fork_pipe_redirect(current_cmd, pipes, p->pipe_count, p);
		if (child_process)
			execute_cmd(current_cmd->argv, p);
		close_pipe(current_cmd, pipes, p->pipe_count, p);
		swap((int **)pipes);
		if (current_cmd->next)
			current_cmd = current_cmd->next;
		else
			break ;
	}
}
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the command to check: %s\n", current_cmd->argv[0]);
//printf("OK - after child process\n");
//printf("OK - after execute cmd\n");
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("OK - fork_pipe\n");