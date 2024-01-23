/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5c_connect_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:19:37 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/23 11:45:38 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_redirections(t_process *p)
{
	if (p->input_redir)
	{
		if (dup2(p->fd_in, STDIN_FILENO) == ERROR)
			perror("dup2 input_redirect");
		close(p->fd_in);
	}
	if (p->output_redir)
	{
		if (dup2(p->fd_out, STDOUT_FILENO) == ERROR)
			perror("dup2 output_redirect");
		close(p->fd_out);
	}
}

/*
	This function is to connect the commands via pipes using dup2.
	If there are pipes, 
	it checks if the current command is the last in the pipeline 
	or not and performs the following redirections:
		If it's the last command or not the first command, 
			it redirects the stdin to the previous pipe's read end.
		If it's the first command or not the last command, 
			it redirects the stdout to the current pipe's write end.
	It returns 1 to indicate success.
*/

int	connect_commands(t_cmd *command, t_fds pipes[2], t_process *p)
{
	if (!p->pipe_count)
		return (1);
	if (p->input_redir && command->cmd_nr == p->cmds_count)
	{
		close(pipes[CURRENT][WRITE]);
		close(pipes[CURRENT][READ]);
		return (1);
	}
	if (command->cmd_nr == 1 || command->cmd_nr != p->cmds_count)
	{
		dup2(pipes[CURRENT][WRITE], STDOUT_FILENO);
		close(pipes[CURRENT][WRITE]);
		close(pipes[CURRENT][READ]);
	}
	if (command->cmd_nr == p->cmds_count || command->cmd_nr != 1)
	{
		dup2(pipes[PREVIOUS][READ], STDIN_FILENO);
		close(pipes[PREVIOUS][READ]);
		close(pipes[CURRENT][WRITE]);
		close(pipes[CURRENT][READ]);
	}
	return (1);
}
/*
	This function closes the pipes created following 
	the same principles as the connect_commands function
	If there are pipes, 
	it checks if the current command is the last in the pipeline or not 
	and performs the following redirections:
		If it's the last command or not the first command, 
			it closes the read end of the previous pipe.
		If it's the first command or not the last command, 
			it closes the write end of the current pipe.
*/

void	close_pipe_ends(t_cmd *command, t_fds pipes[2], t_process *p)
{
	if (p->pipe_count)
	{
		if (command->cmd_nr == 1 || command->cmd_nr != p->cmds_count)
			close(pipes[CURRENT][WRITE]);
		if (command->cmd_nr == p->cmds_count || command->cmd_nr != 1)
			close(pipes[PREVIOUS][READ]);
		if (command->cmd_nr == p->cmds_count)
		{
			close(pipes[CURRENT][READ]);
			close(pipes[CURRENT][WRITE]);
		}
	}
}
/*
	swaps the pipes array to maintain the correct references 
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
