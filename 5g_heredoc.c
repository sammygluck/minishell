#include "minishell.h"

void	heredoc_handler(char *delimiter, t_hdoc *hd)
{
	char	*line;

	hd->file = HEREDOC_TEMP_FILE;
	if (!hd->file)
		error_message("heredoc file creation error\n"); // TO DO: add the proper error handling?
	if (!delimiter)
		error_message("delimiter missing\n"); // TO DO: change to correct error handler
	hd->fd = open_file(hd->file, 3);
	while (1)
	{
		line = readline("> ");
		if (!line) 
			error_message("heredoc input error\n"); // TO DO: change to correct error handler
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (!hd->quotes && ft_strchr(line, '$'))
			line = heredoc_var_expansion(line);
		ft_putendl_fd(line, hd->fd);
		free(line);
	}
	free(line);
}

char	*heredoc_delimiter_qoutes(char *delimiter, t_hdoc *hd)
{
	int		len;
	char	*new_delimiter; // delimiter w/o quotes

	len = ft_strlen(delimiter); // Q: heredoc delimiter len check needed?
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

	hd = ft_malloc(sizeof(t_hdoc)); // Q: correct way to handle the error?
	hd->file = NULL;
	hd->delimiter = NULL;
	hd->quotes = 0;
	hd->fd = -1;
	p->heredoc = hd;
	return (hd);
}

int	heredoc_check(t_cmd *command, t_process *p)
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
				hd->quotes = 0; // reset the hd quotes
				free(hd->delimiter);
			}
			if (hd->fd != ERROR)
				close(hd->fd);
			if (hd->file)
				unlink(hd->file);
			p->input_redir = 1;
			hd->delimiter = heredoc_delimiter_qoutes(redirection->file, hd); // ft_malloc if quoted
			heredoc_handler(hd->delimiter, hd);
		}
		redirection = redirection->next;
	}
	return (1);
}
