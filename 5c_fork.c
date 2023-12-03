#include "minishell.h"

void	fork_handler(t_cmd *command, t_process *p)
{
	pid_t		child; // to store the process id of the child processes

	child = fork(); // init fork
	if (child == -1) // child/fork error
	{
		perror("fork error");
		exit(1);
	}
	if (child == 0)
	{	
		// if output redirection present
		if (command->redir && command->redir->type == GREATER)
		{
			dup2(p->fd_out, STDOUT_FILENO);
			close(p->fd_out);
		}
		else // No output redirection, restore STDOUT to the terminal
			dup2(STDOUT_FILENO, STDOUT_FILENO);
		if (command->next)
		{
			close(p->pfd[0]); // close READ END of the pipe
			dup2(p->pfd[1], STDOUT_FILENO); 
		}
		execute_cmd(command->argv, p);
	}
	else // parent
	{
		if (command->next)
		{
			close(p->pfd[1]); // close WRITE END of the pipe
			dup2(p->pfd[0], STDIN_FILENO);
		}
		waitpid(child, &p->status, 0);
	}
}
