#include "minishell.h"

int	g_last_exit_code;

static void	parent_wait(t_process *p)
{
	int	i;

	i = 0;
	while (i < p->cmds_count)
	{
		waitpid(p->pid[i], &p->status, 0);
		//printf("waitpid[%i] in execute child\n", i);
		i++;
	}
	waitpid(p->pid[i], &p->status, 0);
	if (WIFEXITED(p->status))
		g_last_exit_code = WEXITSTATUS(p->status);
}

static void	save_stdin_out(int *save_fd)
{
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
}

static void	reset_stdin_out(int *save_fd, t_process *p)
{
	if (p->input_redir)
		p->input_redir = 0;
	if (p->heredoc->fd != ERROR)
		close(p->heredoc->fd);
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
	p->pid = ft_malloc(sizeof(pid_t) * p->cmds_count);
}

static t_process	*init_process_struct(char ***env)
{
	t_process	*p;

	p = ft_malloc(sizeof(t_process)); // Q: correct way to handle the error?
	p->fd_in = -1; // Q: ok to set ERROR at init?
	p->fd_out = -1; // Q: ok to set ERROR at init?
	p->status = -1; // Q : ok to set ERROR at init?
	p->input_redir = 0; 
	p->pipe_count = 0;
	p->cmds_count = 0;
	p->pid = NULL;
	p->paths = NULL;
	p->envp = *env;
	p->env = env;
	p->heredoc = NULL;
	return (p);
}

void	executor(t_cmd **command, char ***env, t_env_var **envs)
{
	t_cmd		*current_cmd;
	t_process	*p;
	static fds	pipes[2];
	int			std_fds[2];

	if (!command || !*command)
		return ;
	p = init_process_struct(env); 
	command_pipe_count(*command, p);
	current_cmd = *command;
	while (current_cmd)
	{
		save_stdin_out(std_fds);
		if (p->pipe_count && pipe(pipes[CURRENT]) == ERROR)
			exit_error("pipe", 1);
		heredoc_check(current_cmd, p);
		if (!p->pipe_count && current_cmd->argv && is_builtin(current_cmd->argv))
			g_last_exit_code = execute_builtin(current_cmd, p, envs);
		else
			execute_cmd_in_child(current_cmd, pipes, p, envs);
		close_pipe_ends(current_cmd, pipes, p);
		swap((int **)pipes);
		reset_stdin_out(std_fds, p);
		current_cmd = current_cmd->next;
	}
	parent_wait(p);
}

//printf("the input redirect in main: %i\n", p->input_redir);
// printf("the command to execute: %s\n", current_cmd->argv[0]);
//printf("Exit status of the child was %d\n", g_last_exit_code);