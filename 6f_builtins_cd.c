/*
1. Check if a path argument is provided with the cd command
   - If not, proceed to check for the HOME environment variable
       - If HOME is set, use that as the path
       - If HOME is not set, display an error message and exit the function

2. Store the current working directory in a variable (old_path)
   - Use getcwd() or similar function to get the current directory
   - This will be used to update OLDPWD later

3. Attempt to change the directory to the specified path
   - Use chdir() to change the directory
   - If chdir() is successful:
       - Update the PWD environment variable with the new directory
           - Use setenv() or a similar function to update PWD
       - Update the OLDPWD environment variable with old_path
           - Use setenv() or a similar function to update OLDPWD
   - If chdir() fails:
       - Display an error message (using perror() or a custom error handler)
       - Do not change OLDPWD or PWD
       - Exit the function with an error status

4. Optional: If implementing a return status like in bash,
   - Set the return status to 0 on successful directory change
   - Set the return status to a non-zero value on failure

5. End of cd command implementation
*/
#include "minishell.h"

int ft_cd(char **argv, t_env_var **env_head) 
{
    char *home;
    int ret_value;

    ret_value = 0;
    if (!argv || !argv[0]) 
    {
        printf("error:ft_cd\n"); // Provide more specific error message
        return (1);
    }
    if (!argv[1]) 
    {
        home = get_env_value(*env_head, "HOME");
        if (!home) 
        {
            printf("minishell: cd: HOME not set\n");
            return (1);
        }
        ret_value = ft_chdir(home, env_head);
        free(home); // Free memory allocated by get_env_value
        return (ret_value);
    }
    if (argv[2] != NULL) // Corrected argument check
    { 
        printf("minishell: cd: too many arguments\n");
        return (1);
    }
    // Path formatting can be done here if needed
    ret_value = ft_chdir(argv[1], env_head);
    return (ret_value);
}

int ft_chdir(const char *path, t_env_var **env_head) 
{
    char buf[PATH_MAX];
    char *old_pwd;
    char *pwd;

    old_pwd = getcwd(buf, PATH_MAX);
    if (chdir(path) != 0) 
    {
        perror("minishell: cd"); // Improved error handling
        return (1); // Failure
    }
    pwd = getcwd(buf, PATH_MAX);
    // Update OLD_PWD and PWD in environment
    // Implement update_env_variable function to update environment variables
    update_env_variable(env_head, "OLDPWD", old_pwd);
    update_env_variable(env_head, "PWD", pwd);
    return (0); // Success
}


char *get_env_value(t_env_var *env, char *string)
{
    t_env_var *head;

    if (!env)
        return (NULL);
    head = env;
    while (head)
    {
        if (!strncmp(head->name, string, ft_strlen(string) + 1))
            return (ft_strdup(head->value));
        head = head->next;
    }
    return (NULL);
}



