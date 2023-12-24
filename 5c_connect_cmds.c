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

int	connect_commands(t_cmd *command, fds pipes[2], t_process *p)
{
	if (!p->pipe_count) // no pipe
		return (1);
	if (p->input_redir && command->cmd_nr != p->cmds_count) // there is an input redir (heredoc or regular file)
	{
		dup2(pipes[CURRENT][WRITE], STDOUT_FILENO);
		close(pipes[CURRENT][WRITE]);
		close(pipes[CURRENT][READ]);
		return (1);
	}
	if (p->input_redir && command->cmd_nr == p->cmds_count)
		return (1);
	if (command->cmd_nr == 1 || command->cmd_nr != p->cmds_count)
	{
		dup2(pipes[CURRENT][WRITE], STDOUT_FILENO);
		close(pipes[CURRENT][WRITE]);
		if (command->cmd_nr == 1)
			close(pipes[CURRENT][READ]);
	}
	if (command->cmd_nr == p->cmds_count || command->cmd_nr != 1)
	{
		dup2(pipes[PREVIOUS][READ], STDIN_FILENO);
		close(pipes[PREVIOUS][READ]);
		if (command->cmd_nr == p->cmds_count)
			close(pipes[PREVIOUS][WRITE]);
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

void	close_pipe_ends(t_cmd *command, fds pipes[2], t_process *p)
{
	if (p->pipe_count)
	{
		if (command->cmd_nr == 1 || command->cmd_nr != p->cmds_count)
			close(pipes[CURRENT][WRITE]); 
		if (command->cmd_nr == p->cmds_count || command->cmd_nr != 1)
			close(pipes[PREVIOUS][READ]);
		if (command->cmd_nr == p->cmds_count) //only when last cmd, close current pipe
		{
			close(pipes[CURRENT][READ]);
			close(pipes[CURRENT][WRITE]);
		}
	}
}
/*
	This function is used to swap the pipes array to maintain the correct references 
	to the current and previous pipes during command execution.
*/

void	swap(int **pipes) // TO DO: add protection
{
	int	*current_pipe;

	current_pipe = NULL;
	current_pipe = pipes[CURRENT];
	pipes[CURRENT] = pipes[PREVIOUS];
	pipes[PREVIOUS] = current_pipe;
}

// printf("command nr: %i\n", command->cmd_nr);
// printf("command heredoc active: %i\n", p->hd);
// printf("the current pipes inconnect commands: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
// printf("the previous pipes in connect commands: %i\t %i\n", pipes[PREVIOUS][WRITE], pipes[PREVIOUS][READ]);
// if (p->hd)