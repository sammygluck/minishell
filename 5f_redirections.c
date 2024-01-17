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

static void	heredoc_redirect(char *temp_file, int fd_temp, t_process *p)
{
	if (fd_temp != ERROR)
		close(fd_temp);
	if (p->fd_in != ERROR)
		close(p->fd_in);
	p->fd_in = open_file(temp_file, 0);
	dup2(p->fd_in, STDIN_FILENO);
	close(p->fd_in);
}

int	input_redirect(t_cmd *command, t_process *p)
{
	t_redir	*redirection;

	redirection = command->redir;
	while (redirection)
	{
		if (redirection->type == SMALLER)
		{	
			p->input_redir = 1;
			redirect_input_from(redirection, p);
		}
		if (redirection->type == D_SMALLER && redirection->next->type != D_SMALLER)
			heredoc_redirect(p->heredoc->file, p->heredoc->fd, p);
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

// printf("the address of the head of the heredoc struct: %p\n", p->heredoc);
//printf("OK - redirect in\n");
//printf("OK - redirect out\n");
//printf("the file to redirect: %i\n", command->redir->type);
//printf("ok\n");
// printf("the heredoc file: %s\n", p->heredoc->file);
// printf("the heredoc delimiter: %s\n", p->heredoc->delimiter);
// printf("the heredoc fd file: %i\n", p->heredoc->fd);
// printf("the heredoc quotes: %i\n", p->heredoc->quotes);