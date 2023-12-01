#include "minishell.h"

// > and >> are used to redirect output from a program into a file.
// > (GREATER) truncates --> type 1 in open_file 
// >> (D_GREATER) appends --> type 2  in open_file

void	redirect_output(t_cmd *command, t_process *p)
{
	if (command->redir->type == GREATER)
		p->fd_out = open_file(command->redir->file, 1);
	else
		p->fd_out = open_file(command->redir->file, 2);
	if (dup2(p->fd_out, STDOUT_FILENO) < 0)
	{
		perror("dup2() in redirect output error");
		exit (1);
	}
}

void	check_redirection_type(t_cmd *command, t_process *p)
{
	if (command->redir->type == GREATER || command->redir->type == D_GREATER)
		redirect_output(command, p);
	else
		printf("Other redirection type");
}