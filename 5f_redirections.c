#include "minishell.h"

static void	redirect_input_from(t_redir *redirection, t_process *p)
{
	if (p->fd_in)
		close(p->fd_in);
	p->fd_in = open_file(redirection->file, 0);
	if (p->fd_in == ERROR)
		exit_error(redirection->file, 1);
	dup2(p->fd_in, STDIN_FILENO);
	close(p->fd_in);
}

int	input_redirect(t_cmd *command, t_process *p)
{
	t_redir	*redirection;
	char	*delimiter;

	redirection = command->redir;
	while (redirection)
	{
		if (redirection->type == SMALLER)
		{	
			p->input_redir = 1;
			redirect_input_from(redirection, p);
		}
		if (redirection->type == D_SMALLER)
		{
			p->input_redir = 1;
			delimiter = heredoc_delimiter_qoutes(redirection->file, p); // ft_malloc if quoted
			//printf("the redirection delimiter after clean: %s\n", delimiter);
			heredoc_handler(command->redir->file, p);
		}
		if (p->quotes && delimiter)
			free(delimiter);
		redirection = redirection->next;
	}
	return (1);
}


static void	redirect_output_to(t_redir *redirection, t_process *p)
{
	if (p->fd_out)
		close(p->fd_out);
	if (redirection && redirection->type == GREATER)
		p->fd_out = open_file(redirection->file, 1);
	else
		p->fd_out = open_file(redirection->file, 2);
	if (p->fd_out == ERROR)
		exit_error(redirection->file, 1);
	dup2(p->fd_out, STDOUT_FILENO);
	close(p->fd_out);
}

int	output_redirect(t_cmd *command, t_process *p)
{
	t_redir	*redirection;

	redirection = command->redir;
	while (redirection)
	{
		if (redirection->type == GREATER || redirection->type == D_GREATER)
			redirect_output_to(redirection, p);
		redirection = redirection->next;
	}
	return (1);
}

//printf("OK - redirect in\n");
//printf("OK - redirect out\n");
//printf("the file to redirect: %i\n", command->redir->type);