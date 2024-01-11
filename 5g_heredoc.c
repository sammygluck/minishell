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

static void	heredoc_redirect(char *temp_file, int fd_temp, t_process *p)
{
	if (fd_temp)
		close(fd_temp);
	if (p->fd_in)
		close(p->fd_in);
	p->fd_in = open_file(temp_file, 0); // Q: is this the rigth file permission?
	if (p->fd_in == ERROR)
		exit_error(temp_file, 1);
	dup2(p->fd_in, STDIN_FILENO);
	close(p->fd_in);
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

char	*heredoc_delimiter_qoutes(char *delimiter, t_process *p)
{
	int		len;
	char	*new_delimiter; // delimiter w/o quotes

	len = ft_strlen(delimiter); // Q: heredoc delimiter len check needed?
	if (len && ((delimiter[0] == '\'' && delimiter[len - 1] == '\'') || 
			(delimiter[0] == '\"' && delimiter[len - 1] == '\"')))
	{
		p->quotes = 1;
		new_delimiter = third_clean(delimiter);
		return (new_delimiter);
	}
	return (delimiter);
}

void	heredoc_handler(char *delimiter, t_process *p)
{
	int		fd_temp;
	char	*temp_file;
	char	*line;

	temp_file = create_heredoc_file_name();
	if (!temp_file)
		error_message("heredoc file creation error\n"); // TO DO: add the proper error handling?
	if (!delimiter || *delimiter == '\0')
		error_message("delimiter missing\n"); // TO DO: change to correct error handler
	fd_temp = open_file(temp_file, 3);
	while (1)
	{
		line = readline("> ");
		if (!line) // Q: what if *line == NULL?
			error_message("heredoc input error\n"); // TO DO: change to correct error handler
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (!p->quotes && ft_strchr(line, '$'))
			line = heredoc_var_expansion(line);
		ft_putendl_fd(line, fd_temp);
		free(line);
	}
	free(line);
	heredoc_redirect(temp_file, fd_temp, p);
	// free(heredoc_file) ??
}
