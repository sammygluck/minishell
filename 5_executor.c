#include "minishell.h"

static int	fork_connect_redirect(t_cmd *command, fds pipes[2], t_process *p)
{
	pid_t	child;
	
	child = fork();
	if (child == ERROR)
		exit_error("fork", 1);
	if (child == 0)
	{
		if (input_redirect(command, p) && 
			connect_commands(command, pipes, p) &&
			output_redirect(command, p))
			return (1);
	}
	else // parent
		waitpid(child, &p->status, 0); //Q: to move to main executor function bc else no status?
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

void	executor(t_cmd **command, char **env, t_env_var *envs)
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
		child_process = fork_connect_redirect(current_cmd, pipes, p);
		if (child_process)
			execute_cmd(current_cmd->argv, p, envs);
		close_pipe_ends(current_cmd, pipes, p);
		swap((int **)pipes);
		current_cmd = current_cmd->next;
	}
}


// void	executor(t_cmd **command, char **env)
// {
// 	t_cmd		*current_cmd;
// 	t_process	*p;
// 	static fds	pipes[2];
// 	int			std_fds[2]; // to keep track of the stdin and stdout due to redirects

// 	if (*command == 0)
// 		exit(1);
// 	p = init_process_struct(env); 
// 	command_pipe_count(*command, p);
// 	current_cmd = *command;
// 	while (current_cmd)
// 	{
// 		save_stdin_out(std_fds);
// 		if (p->pipe_count && pipe(pipes[CURRENT]) == ERROR)
// 			exit_error("pipe", 1);
// 		printf("the pipe fds start: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
// 		input_redirect(current_cmd, p);
// 		connect_commands(current_cmd, pipes, p, std_fds);
// 		output_redirect(current_cmd, p);
// 		printf("the pipe fds end: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
// 		// if (current_cmd->argv && is_builtin(current_cmd->argv))
// 		// 	execute_builtin(current_cmd->argv);
// 		//else
// 		execute_cmd_fork(current_cmd, pipes, p);
// 		close_pipe_ends(current_cmd, pipes, p);
// 		swap((int **)pipes);
// 		if (p->hd)
// 			p->hd = 0;
// 		reset_stdin_out(std_fds);
// 		current_cmd = current_cmd->next;
// 	}
// }

// printf("command nr: %i\n", current_cmd->cmd_nr);
// printf("command nr: %i\n", current_cmd->cmd_nr);
//printf("-----the exit status of the child: %i\n", WEXITSTATUS(p->status));
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the command to check: %s\n", current_cmd->argv[0]);
//printf("OK - after child process\n");
//printf("OK - after execute cmd\n");
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("OK - fork_pipe\n");