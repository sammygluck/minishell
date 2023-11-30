#include "minishell.h"

void	run_pipe(char **cmdargs, t_process *p)
{
	pid_t		child; // to store the process id of the child processes
	
	if (pipe(p->pfd) == -1) // create the pipe and check for errors
	{
		perror("Pipe error");
		exit(1);
	}
	child = fork(); // init fork
	if (child == -1) // child/fork error
	{
		perror("fork error");
		exit(1);
	}
	if (child == 0)
	{
		close(p->pfd[0]); // close READ END of the pipe
		dup2(p->pfd[1], STDOUT_FILENO); 
		execute_cmd(cmdargs, p);
	}
	else // parent
	{
		close(p->pfd[1]); // close WRITE END of the pipe
		dup2(p->pfd[0], STDIN_FILENO);
	}
}