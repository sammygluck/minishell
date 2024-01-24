/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5g_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:33:04 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/24 19:56:02 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_handler_loop(t_process *p, t_env_var **envs)
{
	char	*line;
	char	*delimiter;

	delimiter = p->heredoc->delimiter;
	while (1)
	{
		heredoc_signal_handler(HEREDOC_CHILD);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (!p->heredoc->quotes && ft_strchr(line, '$'))
			line = heredoc_var_expansion(line, envs);
		ft_putendl_fd(line, p->heredoc->fd);
		free(line);
	}
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}

static int	heredoc_handler(t_process *p, t_env_var **envs)
{
	int		child;
	int		status;

	heredoc_signal_handler(HEREDOC_PARENT);
	p->heredoc->file = HEREDOC_TEMP_FILE;
	p->heredoc->fd = open_file(p->heredoc->file, 3);
	if (p->heredoc->fd == ERROR)
		exit_error(p->heredoc->file, 1);
	child = fork();
	if (child == ERROR)
		exit_error("fork in heredoc", 1);
	if (child == 0)
		heredoc_handler_loop(p, envs);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_last_exit_code = WEXITSTATUS(status);
	return (g_last_exit_code);
}

static t_hdoc	*init_heredoc_struct(t_process *p)
{
	t_hdoc	*hd;

	hd = malloc(sizeof(t_hdoc));
	if (!hd)
		return (NULL);
	hd->file = NULL;
	hd->delimiter = NULL;
	hd->quotes = 0;
	hd->fd = -1;
	p->heredoc = hd;
	return (hd);
}

int	heredoc_check(t_cmd *command, t_process *p, t_env_var **envs)
{
	t_redir	*redirection;
	t_hdoc	*hd;

	redirection = command->redir;
	hd = init_heredoc_struct(p);
	if (!hd)
		return (0);
	while (redirection)
	{
		if (redirection->type == D_SMALLER)
		{
			remove_prev_file_ref(hd);
			p->input_redir = 1;
			hd->delimiter = heredoc_delimiter_qoutes(redirection->file, hd);
			heredoc_handler(p, envs);
			if (g_last_exit_code == 130)
				return (0);
		}
		redirection = redirection->next;
	}
	return (1);
}
