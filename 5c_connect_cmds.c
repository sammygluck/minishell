#include "minishell.h"

/*
	This function is to connect the commands via pipes using dup2.
	If there are pipes, it checks if the current command is the last in the pipeline 
	or not and performs the following redirections:
		If it's the last command or not the first command, 
			it redirects the stdin to the previous pipe's read end.
		If it's the first command or not the last command, 
			it redirects the stdout to the current pipe's write end.
	It returns 1 to indicate success.
*/

int	connect_commands(t_cmd *command, fds pipes[2], int pipe_count, t_process *p)
{
	if (pipe_count)
	{
		if (p->hd)
		{
			dup2(pipes[CURRENT][WRITE], STDOUT_FILENO);
			dup2(pipes[PREVIOUS][READ], p->fd_in);
			return (1);
		}
		if (command->cmd_nr == p->cmds_count || command->cmd_nr != 1)
			dup2(pipes[PREVIOUS][READ], STDIN_FILENO);
		if (command->cmd_nr == 1 || command->cmd_nr != p->cmds_count)
			dup2(pipes[CURRENT][WRITE], STDOUT_FILENO);
	}
	return (1);
}

/*
	This function closes the pipes created following the same principles as the connect_commands function
	If there are pipes, it checks if the current command is the last in the pipeline or not 
	and performs the following redirections:
		If it's the last command or not the first command, it closes the read end of the previous pipe.
		If it's the first command or not the last command, it closes the write end of the current pipe.
*/

void	close_pipe_end(t_cmd *command, fds pipes[2], int pipe_count, t_process *p)
{
	if (pipe_count)
	{
		if (command->cmd_nr == p->cmds_count || command->cmd_nr != 1)
			close(pipes[PREVIOUS][READ]);
		if (command->cmd_nr == 1 || command->cmd_nr != p->cmds_count)
			close(pipes[CURRENT][WRITE]);
	}
}
/*
	This function is used to swap the pipes array to maintain the correct references 
	to the current and previous pipes during command execution.
*/

void	swap(int **pipes)
{
	int	*current_pipe;

	current_pipe = NULL;
	current_pipe = pipes[CURRENT];
	pipes[CURRENT] = pipes[PREVIOUS];
	pipes[PREVIOUS] = current_pipe;
}