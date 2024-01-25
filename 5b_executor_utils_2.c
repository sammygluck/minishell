/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5b_executor_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:25:30 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/25 12:10:15 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_stdin_out(int *save_fd)
{
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
}

void	reset_std_redirection(int *save_fd, t_process *p)
{
	if (p->input_redir)
		p->input_redir = 0;
	if (p->output_redir)
		p->output_redir = 0;
	if (p->heredoc->fd != ERROR)
		close(p->heredoc->fd);
	dup2(save_fd[0], STDIN_FILENO);
	close(save_fd[0]);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[1]);
}

void	parent_wait(t_process *p)
{
	int	i;
	int	status;

	i = 0;
	while (i < p->cmds_count)
	{
		waitpid(p->pid[i], &status, 0);
		i++;
	}
	waitpid(p->pid[i], &status, 0);
	if (WIFEXITED(status))
		g_last_exit_code = WEXITSTATUS(status);
}

void	exec_error_message(char *command, char *message, t_process *p)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(message, 2);
	free_process(p);
}

void	free_process(t_process *p)
{
	if (!p)
		return ;
	if (p->fd_in != ERROR)
		close (p->fd_in);
	if (p->fd_out != ERROR)
		close(p->fd_out);
	if (p->paths)
		free_array(p->paths);
	if (p->pid)
		free(p->pid);
	if (p->heredoc)
	{
		if (p->heredoc->fd != ERROR)
			close(p->heredoc->fd);
		if (p->heredoc->quotes && p->heredoc->delimiter)
		{
			p->heredoc->quotes = 0;
			free(p->heredoc->delimiter);
		}
		free(p->heredoc);
	}
	free(p);
}
