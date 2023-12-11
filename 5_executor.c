#include "minishell.h"

static void	save_stdin_out(int *save_fd)
{
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	printf("the stdin/stdout fds: %i\t %i\n", save_fd[0], save_fd[1]);
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
	int			std_fds[2]; // to keep track of the stdin and stdout due to redirects

	if (*command == 0)
		exit(1);
	p = init_process_struct(env); 
	command_pipe_count(*command, p);
	current_cmd = *command;
	while (current_cmd)
	{
		printf("command nr: %i\n", current_cmd->cmd_nr);
		printf("command nr: %i\n", current_cmd->cmd_nr);
		save_stdin_out(std_fds);
		if (p->pipe_count && pipe(pipes[CURRENT]) == ERROR)
			exit_error("pipe", 1);
		printf("the pipe fds after: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
		connect_commands(current_cmd, pipes, p->pipe_count, p);
		redirections_check(current_cmd, p);
		if (is_builtin(current_cmd->argv[0]))
			execute_builtin(current_cmd->argv);
		else
			execute_cmd_fork(current_cmd, pipes, p->pipe_count, p);
		close_pipe_ends(current_cmd, pipes, p->pipe_count, p);
		swap((int **)pipes);
		reset_stdin_out(std_fds);
		current_cmd = current_cmd->next;
	}
}
//printf("-----the exit status of the child: %i\n", WEXITSTATUS(p->status));
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the command to check: %s\n", current_cmd->argv[0]);
//printf("OK - after child process\n");
//printf("OK - after execute cmd\n");
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("OK - fork_pipe\n");