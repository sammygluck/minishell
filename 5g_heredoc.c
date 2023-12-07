#include "minishell.h"

/*
	Heredoc general structure:
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
	int		chars_read;
	char	*temp_file;
	char	*buffer;
	int		buffer_size = 1024; // Q: what should the actual buffer size be?
	
	temp_file = "temp_file_heredoc"; // TO DO: change location of temp file
	fd_temp = open_file(temp_file, 3);
	buffer = malloc(sizeof(char) * (buffer_size + 1));
	if (!buffer)
		exit_error("malloc error", 0);
	chars_read = read(0, buffer, buffer_size);
	while (ft_strncmp(buffer, delimiter, ft_strlen(delimiter) != 0))
	{
		buffer[chars_read] = '\0';
		write(fd_temp, buffer, buffer_size);
		chars_read = read(0, buffer, buffer_size);
		if (chars_read == ERROR)
		{
			free(buffer);
			exit_error("read error", 1);
		}
	}
	free(buffer);
	heredoc_redirect(temp_file, fd_temp, p);
}
