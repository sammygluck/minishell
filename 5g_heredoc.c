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

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_TEMP_FILE, number);
	if (!name)
		return (NULL);
	free(number);
	i++;
	return (name);
}

void	heredoc_handler(char *delimiter, t_process *p)
{
	int		fd_temp;
	char	*temp_file;
	char	*line;

	temp_file = create_heredoc_file_name();
	if (!temp_file)
		error_message("heredoc file creation error"); // TO DO: add the proper error handling?
	if (!delimiter || *delimiter == '\0')
		error_message("missing delimiter - syntax error near unexpected token"); // TO DO: change to correct error handler
	fd_temp = open_file(temp_file, 3);
	while (1)
	{
		line = readline("> ");
		if (!line) // Q: what if *line == NULL?
			error_message("heredoc input error"); // TO DO: change to correct error handler
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (ft_strchr(line, '$'))
			line = init_retrieve_replace_heredoc_var(line);
		ft_putendl_fd(line, fd_temp);
		free(line);
	}
	free(line);
	heredoc_redirect(temp_file, fd_temp, p);
	// free(heredoc_file) ??
}


// heredoc quotes check pseudo code

// if p->quotes == 6 || p->quotes == 7
// 		no expension 
// 	else
// 		activate expansion
// */