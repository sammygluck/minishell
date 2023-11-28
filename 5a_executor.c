
/* Executor

	When the parser returns the t_simple_cmds list back to minishell_loop, 
	a simple check is done to determine how many commands there are,
	as they are handled by different functions. 
	However, with the exception of a few builtins, 
	the commands are ultimately executed by the same function handle_cmd,
	which finds, and if successful, executes the command.
	
*/