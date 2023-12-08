#include "minishell.h"

/*
	heredoc general structure:
		command << DELIMITER
		text
		more text
		DELIMITER
*/

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

void	heredoc_handler(char *delimiter, t_process *p)
{
	int		fd_temp;
	char	*temp_file;
	char	*line;

	temp_file = "./temp/temp_file_heredoc"; // TO DO: change location of temp file
	fd_temp = open_file(temp_file, 3);
	line = readline("> ");
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter) != 0))
	{
		write(fd_temp, line, ft_strlen(line));
		write(fd_temp, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	heredoc_redirect(temp_file, fd_temp, p);
}


// heredoc quotes check pseudo code

// if p->quotes == 6 || p->quotes == 7
// 		no expension 
// 	else
// 		activate expansion
// */