#include "minishell.h"

t_process	*init_process_struct(char **env)
{
	t_process	*p;

	p = ft_malloc(sizeof(t_process));
	p->fd_in = -1; // TO DO: remove?
	p->fd_out = -1; // TO DO: remove?
	p->status = -1; // TO DO: remove?
	p->paths = NULL;
	p->envp = env;
	return (p);
}

int	executor(t_cmd *command, char **env)
{
	t_cmd		*current_cmd;
	t_process	*p;

	// check if the command exists
	if (command == 0)
		return (0); // TO DO: needs to be adjusted to where the function needs to exit

	// init the process struct
	p = init_process_struct(env);

	// retrieve the env path to locate the binaries
	if (!retrieve_path_var_env(p))
		return (0);

	// loop through the nodes with the different commands
	current_cmd = command;
	//printf("current_cmd: %s\n", command->argv[0]);
	while (current_cmd)
	{
		// check if there is a redirection and handle the different cases from there
		if (command->redir)
			check_redirection_type(command, p); 
		// check if there is a pipe
		if (current_cmd->next)
			run_pipe(command, p);
		else
			break ;
		current_cmd = current_cmd->next;
	}
	execute_cmd(current_cmd->argv, p);
	return (1);
}