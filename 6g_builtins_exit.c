/*
1. Start the exit command implementation.

2. Check if there are any arguments provided to the exit command:
   - If no arguments are provided:
       - Print a message "exit" to standard output.
       - Exit the shell with the status of the last executed command.

   - If one argument is provided:
       - Check if the argument is a valid number (integer).
           - If valid, convert it to an integer and use it as the exit status.
           - If invalid (non-integer or overflow), display an error message indicating an invalid exit argument and do not exit the shell.

   - If more than one argument is provided:
       - Display an error message indicating too many arguments and do not exit the shell.

3. If the shell is to be exited (in cases of no argument or one valid argument):
   - Perform any necessary cleanup operations (like freeing allocated memory, if any).
   - Exit the shell using the exit() function with the appropriate status.

4. End of exit command implementation.

*/

int ft_exit(char **argv, char **env, t_env_var *env)
{
    int exit_code;
    
    //VOID SOME STUFF
    if (!argv)
        exit(EXIT_FAILURE);
    if (!arg[1])
        final_exit(last_exit_status);
    else if (argv[1] && argv[2])
    {
        error: too many arguments
        do not exit shell
    }
    else if (argv[1]) //not sure if this condition is even necessary
    {
        exit_code = validate_and_process_exit_code(argv[1]);
        if (exit_code != -1) 
            final_exit(exit_code);
        else 
            error and exit;
    } 
}

void final_exit(exit_number)
{
    // is cleanup necessary?
    printf("exit\n");
    exit(exit_status);
}

