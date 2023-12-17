/*
1. Start the pwd command implementation.

2. Allocate a buffer to store the current working directory path.
   - You can use dynamic allocation (with malloc) or a fixed-size array.
   - Ensure the buffer is sufficiently large to store the longest possible path (e.g., PATH_MAX from <limits.h>).

3. Use getcwd() or a similar function to obtain the current working directory.
   - Pass the allocated buffer and its size to getcwd().
   - If getcwd() returns NULL, handle the error:
       - Print an error message to standard error (using perror or a custom message).
       - Free any dynamically allocated memory (if applicable).
       - Exit the function with a failure status.

4. If getcwd() successfully retrieves the current directory:
   - Print the directory path to standard output.
   - End the line with a newline character unless specific project requirements dictate otherwise.

5. Free any dynamically allocated memory (if applicable).

6. End of pwd command implementation.

*/

#include "minishell.h"

int ft_pwd(char **argv, char **env, t_env_var **env_l) // do I need to add other parameters??
{
   char buffer[PATH_MAX];

   (void) argv;
   (void) env_l;
   (void) env;
   if (!getcwd(buffer, PATH_MAX))
   {
      perror("pwd error");
      return (1);
   }
   printf("%s\n", buffer);
   return (0);
}