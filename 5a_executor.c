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

static t_process	*init_process_struct(char ***env)
{
	t_process	*p;

	p = ft_malloc(sizeof(t_process));
	if (!p)
		exit (1); // Q: correct way to handle the error?
	p->fd_in = -1; // Q: ok to set ERROR at init?
	p->fd_out = -1; // Q: ok to set ERROR at init?
	p->status = -1; // Q : ok to set ERROR at init?
	p->quotes = 0; // to use for heredoc?
	p->input_redir = 0; 
	p->pipe_count = 0;
	p->cmds_count = 0;
	p->paths = NULL;
	p->envp = *env;
	p->env = env;
	return (p);
}

void	executor(t_cmd **command, char ***env, t_env_var **envs)
{
	t_cmd		*current_cmd;
	t_process	*p;
	pid_t		child;
	static fds	pipes[2];
	int			std_fds[2]; // to keep track of the stdin and stdout

	if (!command || !*command)
		return ;
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
		if (!p->pipe_count && current_cmd->argv && is_builtin(current_cmd->argv)) // there is only 1 command and it's a builtin
			execute_builtin(current_cmd, p, envs);
		else
			child = execute_cmd_in_child(current_cmd, pipes, p, envs);
		close_pipe_ends(current_cmd, pipes, p);
		swap((int **)pipes);
		if (p->input_redir)
			p->input_redir = 0;
		reset_stdin_out(std_fds);
		current_cmd = current_cmd->next;
	}
	//parent_wait(child, p);
}
