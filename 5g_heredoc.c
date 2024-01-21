/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5g_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:33:04 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/21 16:48:46 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_handler_loop(char *delimiter, t_fds pipes[2], t_process *p, t_env_var **envs)
{
	char	*line;

	while (1)
	{
		heredoc_signal_handler(HEREDOC_CHILD);
		line = readline("> ");
		if (!line)
		{
			g_last_exit_code = 130;
			//error_message("heredoc input error\n");
			break ;
		}
		// if (g_last_exit_code == -1)
		// {
		// 	g_last_exit_code = 130;
		// 	break ;
		// }
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (!p->heredoc->quotes && ft_strchr(line, '$'))
			line = heredoc_var_expansion(line, envs);
		if (!p->pipe_count)
			ft_putendl_fd(line, p->heredoc->fd);
		else
			ft_putendl_fd(line, pipes[CURRENT][WRITE]);
		free(line);
	}
	free(line);
}

static void	heredoc_handler(char *delimiter, t_fds pipes[2], t_process *p, t_env_var **envs)
{
	int		child;
	int		status; //status of child
	t_hdoc	*hd;

	heredoc_signal_handler(HEREDOC_PARENT);
	hd = p->heredoc;
	hd->file = HEREDOC_TEMP_FILE;
	if (!hd->file)
		error_message("heredoc file creation error\n");
	if (!delimiter)
		error_message("delimiter missing\n");
	hd->fd = open_file(hd->file, 3);
	if (hd->fd == ERROR)
		exit_error(hd->file, 1);
	child = fork();
	if (child == ERROR)
		exit_error("fork in heredoc", 1);
	if (child == 0)
	{
		heredoc_handler_loop(delimiter, pipes, p, envs);
		exit(EXIT_SUCCESS);
	}
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_last_exit_code = WEXITSTATUS(status);
}

char	*heredoc_delimiter_qoutes(char *delimiter, t_hdoc *hd)
{
	int		len;
	char	*new_delimiter;

	len = ft_strlen(delimiter);
	if (len && ((delimiter[0] == '\'' && delimiter[len - 1] == '\'') || 
			(delimiter[0] == '\"' && delimiter[len - 1] == '\"')))
	{
		hd->quotes = 1;
		new_delimiter = third_clean(delimiter);
		return (new_delimiter);
	}
	return (delimiter);
}

static t_hdoc	*init_heredoc_struct(t_process *p)
{
	t_hdoc	*hd;

	hd = ft_malloc(sizeof(t_hdoc));
	hd->file = NULL;
	hd->delimiter = NULL;
	hd->quotes = 0;
	hd->fd = -1;
	p->heredoc = hd;
	return (hd);
}

int	heredoc_check(t_cmd *command, t_fds pipes[2], t_process *p, t_env_var **envs)
{
	t_redir	*redirection;
	t_hdoc	*hd;

	redirection = command->redir;
	hd = init_heredoc_struct(p);
	while (redirection)
	{
		if (redirection->type == D_SMALLER)
		{
			if (hd->quotes && hd->delimiter)
			{
				hd->quotes = 0;
				free(hd->delimiter);
			}
			if (hd->fd != ERROR)
				close(hd->fd);
			if (hd->file)
				unlink(hd->file);
			p->input_redir = 1;
			hd->delimiter = heredoc_delimiter_qoutes(redirection->file, hd);
			heredoc_handler(hd->delimiter, pipes, p, envs);
		}
		redirection = redirection->next;
	}
	return (1);
}
