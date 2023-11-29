#include <minishell.h>

char **realloc_array(char **argv) 
{
    int count;
    int i;
  
    count = 0;
    if (argv && argv[0]) 
    {
        while (argv[count]) 
            count++; 
    }
    char **new_argv = ft_malloc((count + 2) * sizeof(char *)); //ft_malloc exits program upon failure
    i = 0;
    while (i < count)
    {
        new_argv[i] = argv[i];
        i++;
    }
    new_argv[count] = NULL;
    new_argv[count + 1] = NULL; 
    if (argv)
        free(argv);
    return (new_argv);
}