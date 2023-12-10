/*
1. Start the echo command implementation.

2. Initialize a flag to track if the '-n' option is used.
   - Set the flag to false initially.

3. Check if the first argument after "echo" is '-n'.
   - If yes, set the '-n' flag to true.
   - Skip this argument for the rest of the processing.

4. Loop through each argument provided to the echo command (starting from the first argument or the second if '-n' was found):
   - Print the argument to standard output.
   - If there are more arguments:
       - Print a space after the current argument to separate from the next one.

5. After all arguments are processed:
   - If the '-n' flag is not set:
       - Print a newline character to end the output.

6. End of echo command implementation.

*/

//improvements: the -nnnnnn flag

#include "minishell.h"

int ft_echo(char **argv, char **env, t_env_var **env_l)//fix parameters
{
    int flag_n;
    int i;

    (void) env;
    (void) env_l;
    if (!argv)
        exit(EXIT_FAILURE);
    flag_n = 0;
    i = 1;
    if (argv[i] && ft_strncmp(argv[i], "-n", 3) == 0) 
    {
        flag_n = 1;
        i++;
    }
    while (argv[i]) 
    {
        printf("%s", argv[i]);
        if (argv[i + 1]) 
            printf(" "); 
        i++;
    }
    if (!flag_n) 
        printf("\n");
    return (0);
}
