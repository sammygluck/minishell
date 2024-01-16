#include "minishell.h"

/*
	heredoc general structure:
		command << DELIMITER
		text
		more text
		DELIMITER
*/

static int	ft_strcmp(const char *s1, const char *s2) // TODO: move to another file
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

static char	*create_heredoc_file_name()
{
	static int	i;
	char		*number;
	char		*name;

	number = ft_itoa(i); // malloc
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_TEMP_FILE, number); // malloc
	if (!name)
		return (NULL);
	free(number);
	i++;
	return (name);
}

char	*heredoc_delimiter_qoutes(char *delimiter, t_process *p, t_hdoc *hd)
{
	int		len;
	char	*new_delimiter; // delimiter w/o quotes

	len = ft_strlen(delimiter); // Q: heredoc delimiter len check needed?
	if (len && ((delimiter[0] == '\'' && delimiter[len - 1] == '\'') || 
			(delimiter[0] == '\"' && delimiter[len - 1] == '\"')))
	{
		//p->quotes = 1;
		hd->quotes = 1;
		new_delimiter = third_clean(delimiter);
		return (new_delimiter);
	}
	return (delimiter);
}

void	heredoc_handler(char *delimiter, t_process *p, t_hdoc *hd)
{
	char	*line;

	//hd->file = create_heredoc_file_name();
	hd->file = HEREDOC_TEMP_FILE;
	if (!hd->file)
		error_message("heredoc file creation error\n"); // TO DO: add the proper error handling?
	if (!delimiter)
		error_message("delimiter missing\n"); // TO DO: change to correct error handler
	hd->fd = open_file(hd->file, 3);
	while (1)
	{
		line = readline("> ");
		if (!line) // Q: what if *line == NULL?
			error_message("heredoc input error\n"); // TO DO: change to correct error handler
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (!hd->quotes && ft_strchr(line, '$'))
			line = heredoc_var_expansion(line);
		ft_putendl_fd(line, hd->fd);
		free(line);
	}
	free(line);
	//heredoc_redirect(temp_file, fd_temp, p);
	// free(heredoc_file) ??
}
