/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5f_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:29:39 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/24 19:59:12 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input_from(t_redir *redirection, t_process *p)
{
	if (p->fd_in != ERROR)
		close(p->fd_in);
	p->fd_in = open_file(redirection->file, 0);
	if (p->fd_in == ERROR && p->builtin)
		return (0);
	else if (p->fd_in == ERROR && !p->builtin)
		exit(EXIT_FAILURE);
	return (1);
}

static int	heredoc_redirect(char *temp_file, int fd_temp, t_process *p)
{
	if (fd_temp != ERROR)
		close(fd_temp);
	if (p->fd_in != ERROR)
		close(p->fd_in);
	p->fd_in = open_file(temp_file, 0);
	if (p->fd_in == ERROR && p->builtin)
		return (0);
	else if (p->fd_in == ERROR && !p->builtin)
		exit(EXIT_FAILURE);
	return (1);
}

static int	redirect_output_to(t_redir *redirection, t_process *p)
{
	if (p->fd_out != ERROR)
		close(p->fd_out);
	if (redirection && redirection->type == GREATER)
		p->fd_out = open_file(redirection->file, 1);
	else
		p->fd_out = open_file(redirection->file, 2);
	if (p->fd_out == ERROR && p->builtin)
		return (0);
	else if ((p->fd_out == ERROR && !p->builtin))
		exit(EXIT_FAILURE);
	p->output_redir = 1;
	return (1);
}

int	redirection_check(t_cmd *command, t_process *p)
{
	t_redir	*redirection;

	redirection = command->redir;
	while (redirection)
	{
		if (redirection->type == SMALLER)
		{
			p->input_redir = 1;
			if (!redirect_input_from(redirection, p))
				return (0);
		}
		if (redirection->type == D_SMALLER)
		{
			if (!redirection->next
				|| (redirection->next && redirection->next->type != D_SMALLER))
				if (!heredoc_redirect(p->heredoc->file, p->heredoc->fd, p))
					return (0);
		}
		if (redirection->type == GREATER || redirection->type == D_GREATER)
			if (!redirect_output_to(redirection, p))
				return (0);
		redirection = redirection->next;
	}
	return (1);
}
