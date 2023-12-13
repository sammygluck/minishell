// static int	fork_connect_redirect(t_cmd *command, fds pipes[2], t_process *p)
// {
// 	pid_t	child;
	
// 	child = fork();
// 	if (child == ERROR)
// 		exit_error("fork", 1);
// 	if (child == 0)
// 	{
// 		if (input_redirect(command, p) && 
// 			connect_commands(command, pipes, p) &&
// 			output_redirect(command, p))
// 			return (1);
// 	}
// 	else // parent
// 		waitpid(child, &p->status, 0); //Q: to move to main executor function bc else no status?
// 	return (0);
// }


// static void	execute_cmd_in_child(t_cmd *command, t_process *p, t_env_var *envs)
// {
// 	static int	i;
	
// 	if (command->cmd_nr == 1 && i != 0) // new set of command(s) -> reset i
// 		i = 0;
// 	p->pid[i] = fork();
// 	if (p->pid[i] == ERROR)
// 		exit_error("fork", 1);
// 	if (p->pid[i] == 0)
// 		execute_cmd(command->argv, p, envs);
// 	else  // parent
// 	{
// 		i++;
// 		waitpid(p->pid[i], &p->status, 0); //Q: to move to main executor function bc else no status?
// 	}
//}


// printf("command nr: %i\n", current_cmd->cmd_nr);
// void	executor(t_cmd **command, char **env, t_env_var *envs)
// {
// 	t_cmd		*current_cmd;
// 	t_process	*p;
// 	static fds	pipes[2];
// 	int			child_process;

// 	if (*command == 0)
// 		exit(1);
// 	p = init_process_struct(env); 
// 	command_pipe_count(*command, p);
// 	current_cmd = *command;
// 	while (current_cmd)
// 	{
// 		if (p->pipe_count && pipe(pipes[CURRENT]) == ERROR)
// 			exit_error("pipe", 1);
// 		child_process = fork_connect_redirect(current_cmd, pipes, p);
// 		if (child_process)
// 			execute_cmd(current_cmd->argv, p, envs);
// 		close_pipe_ends(current_cmd, pipes, p);
// 		swap((int **)pipes);
// 		current_cmd = current_cmd->next;
// 	}
// }
// printf("command nr: %i\n", current_cmd->cmd_nr);
//printf("-----the exit status of the child: %i\n", WEXITSTATUS(p->status));
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the command to check: %s\n", current_cmd->argv[0]);
//printf("OK - after child process\n");
//printf("OK - after execute cmd\n");
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("the pipe fds: %i\t %i\n", pipes[CURRENT][READ], pipes[CURRENT][WRITE]);
//printf("OK - fork_pipe\n");