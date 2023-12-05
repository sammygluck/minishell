/*
1. Start the unset command implementation.

2. Check if any arguments are provided to the unset command.
   - If no arguments are provided, simply return from the function as there's nothing to unset.

3. Loop through each argument provided to the unset command:
   - For each argument (which represents an environment variable name to unset):
       - Remove the variable from the 't_env' list:
           - Search for a node in the list that matches the variable name.
           - If found, remove the node from the list and free its memory.
       - Remove the variable from the 'char **env' array:
           - Search for an entry in the array that starts with the variable name followed by '='.
           - If found, remove this entry from the array.
               - This might involve shifting subsequent elements and possibly resizing the array.

4. For resizing the 'char **env' array (if required):
   - If an entry is removed:
       - Allocate a new array with a size one less than the current array.
       - Copy all entries except the removed one to the new array.
       - Free the old array and update the pointer to point to the new array.

5. Repeat steps 3 and 4 for each argument provided to the unset command.

6. End of unset command implementation.

*/

#include <minishell.h>

int ft_unset(void) //double check everything!!
{
    int i;

    i = 1;
    //make sure to do some other error checking perhaps
    if (!argv[i])
        return (0);
    while (argv[i])
    {
        arg_in_env(argv[i], envlist);
        i++;
    }
    free_old_env(env);
    env = mirror_list_to_array(list);
    return (0);
}

int arg_in_env(char *string, t_env_var **env_list)
{
    t_env_var *head;

    head = *env_list;
    while (head)
    {
        if (!strncmp(string, head->name, ft_strlen(string) + 1))
        {
            free(head->value);
            head->value = NULL;
            return (1);
        }
        head = head->next;
    }
    return (0); //if it returns index it should return -1 upon not found
}

void free_old_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}

char **mirror_list_to_array(t_env_var *list)
{
    t_env_var *head;
    char **env;
    int arr_size;
    
    env = NULL;
    head = list;
    arr_size = 0;
    while (list)
    {
        if (list->name && list->value)
        {
            env = realloc_array(env, arr_size);
            env[arr_size] = ft_env_join(list->name, list->value);
            env[arr_size + 1] = NULL;
            arr_size++;
        }
        list = list->next;
    }
    return (env);    
}

char **realloc_array(char **argv, int argc) //remove this from here afterwards
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

char	*ft_env_join(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joined[j++] = s1[i++];
    joined[j++] = '=';
	i = 0;
	while (s2[i])
		joined[j++] = s2[i++];
	joined[j] = '\0';
	return (joined);
}

// //dispose for this function, perhaps useful for 
// char *arg_in_env(char *string, t_env *env_list)
// {
//     int i;
//     int len;

//     if (!string)
//         return (NULL);
//     len = ft_strlen(string);

//     i = 0;
//     while(string[i])
//         i++;
//     if (!string[i])
//         return (NULL);
//     i++;

// }