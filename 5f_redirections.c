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
}

void	check_redirection_type(t_cmd *command, t_process *p)
{
	t_cmd	*current_cmd;

	current_cmd = command;
	while (current_cmd->redir)
	{
		if (command->redir->type == GREATER || command->redir->type == D_GREATER)
			redirect_output(command, p);
		else
			printf("Other redirection type");
		current_cmd->redir = current_cmd->redir->next;
	}
}