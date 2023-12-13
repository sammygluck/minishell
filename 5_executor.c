#include "minishell.h"

static void	save_stdin_out(int *save_fd)
{
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
}

static void	reset_stdin_out(int *save_fd)
{
	dup2(save_fd[0], STDIN_FILENO);
	close(save_fd[0]);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[1]);
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
	p->fd_in = -1;
	p->fd_out = -1;
	p->status = -1; // TO DO: remove?
	p->quotes = 0; // to use for heredoc?
	p->hd = 0;
	p->pid = NULL; // to receive the status of the child
	p->pipe_count = 0;
	p->cmds_count = 0;
	p->paths = NULL;
	p->envp = env;
	return (p);
}

void	executor(t_cmd **command, char **env, t_env_var *envs)
{
	t_cmd		*current_cmd;
	t_process	*p;
	pid_t		child;
	static fds	pipes[2];
	int			std_fds[2]; // to keep track of the stdin and stdout due to redirects

	if (*command == 0)
		exit(1);
	p = init_process_struct(env); 
	command_pipe_count(*command, p);
	current_cmd = *command;
	while (current_cmd)
	{
		save_stdin_out(std_fds);
		if (p->pipe_count && pipe(pipes[CURRENT]) == ERROR)
			exit_error("pipe", 1);
		printf("the pipe fds start: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
		if (!p->pipe_count && current_cmd->argv && is_builtin(current_cmd->argv)) // there is only 1 command and it's a builtin
			execute_builtin(current_cmd, p, envs);
		else
			child = execute_cmd_in_child(current_cmd, pipes, p, envs);
		close_pipe_ends(current_cmd, pipes, p);
		swap((int **)pipes);
		if (p->hd)
			p->hd = 0;
		reset_stdin_out(std_fds);
		current_cmd = current_cmd->next;
	}
}
