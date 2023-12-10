#include "minishell.h"

char **realloc_array(char **argv, int argc) 
{
    char **new_argv;
    int i;
  
    new_argv = ft_malloc((argc + 2) * sizeof(char *)); //ft_malloc exits program upon failure
    i = 0;
    while (i < argc)
    {
        new_argv[i] = argv[i];
        i++;
    }
    new_argv[argc] = NULL;
    new_argv[argc + 1] = NULL; 
    if (argv)
        free(argv);
    return (new_argv);
}