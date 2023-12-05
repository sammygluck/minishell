#include "minishell.h"

static void	redirect_input_from(t_redir *redirection, t_process *p)
{
	if (p->fd_in)
		close(p->fd_in);
	p->fd_in = open_file(redirection->file, 0);
	if (p->fd_in == ERROR)
	{
		perror(redirection->file);
		exit(1);
	}
	dup2(p->fd_in, STDIN_FILENO);
	close(p->fd_in);
}

int	redirect_in(t_cmd *command, t_process *p)
{
	t_redir	*redirection;

	redirection = command->redir;
	while (redirection)
	{
		if (redirection->type == SMALLER)
			redirect_input_from(redirection, p);
		redirection = redirection->next;
	}
	return (1);
}

/* 
	> and >> are used to redirect output from a program into a file.
 	> (GREATER) truncates --> type 1 in open_file 
	>> (D_GREATER) appends --> type 2  in open_file
*/

static void	redirect_output_to(t_redir *redirection, t_process *p)
{
	//static int	fd_out;

	if (p->fd_out)
		close(p->fd_out);
	if (redirection && redirection->type == GREATER)
		p->fd_out = open_file(redirection->file, 1);
	else
		p->fd_out = open_file(redirection->file, 2);
	dup2(p->fd_out, STDOUT_FILENO);
	close(p->fd_out);
}

int	redirect_out(t_cmd *command, t_process *p)
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
