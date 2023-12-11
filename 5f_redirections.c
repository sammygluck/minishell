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

void	input_redirect(t_cmd *command, t_process *p)
{
	t_redir	*redirection;
	char	*delimiter;

	redirection = command->redir;
	while (redirection)
	{
		if (redirection->type == SMALLER)
			redirect_input_from(redirection, p);
		if (redirection->type == D_SMALLER)
		{
			p->hd = 1; // flag to signal heredoc 
			delimiter = redirection->file;
			heredoc_handler(delimiter, p);
		}
		redirection = redirection->next;
	}
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

void	output_redirect(t_cmd *command, t_process *p)
{
	t_redir	*redirection;

	redirection = command->redir;
	while (redirection)
	{
		if (redirection->type == GREATER || redirection->type == D_GREATER)
			redirect_output_to(redirection, p);
		redirection = redirection->next;
	}
}

void	redirections_check(t_cmd *command, t_process *p)
{
	input_redirect(command, p);
	output_redirect(command, p);
}
