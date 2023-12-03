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

int ft_exit()
{
    if no argument provided
        final_exit(last_exit_status);
    else if more than 1 argument
        error: too many arguments
        do not exit shell
    else if 1 argument 
        if valid number //what is a valid number for exit code??
            final_exit(valid_number)
        if not valid number
            error but do not exit
}

void final_exit(exit_number)
{
    cleanup;
    printf("exit\n");
    exit(exit_status);
}