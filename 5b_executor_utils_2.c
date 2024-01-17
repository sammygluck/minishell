/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5b_executor_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:25:30 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/17 18:42:05 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_stdin_out(int *save_fd)
{
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
}

void	reset_std(int *save_fd, t_process *p)
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

void	free_executor(t_process *p)
{
	if (!p)
		return ;
	if (p->paths)
		free_array(p->paths);
	if (p->pid)
		free(p->pid);
	if (p->heredoc)
		free (p->heredoc);
	free (p);
}
