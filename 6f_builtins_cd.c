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

ft_cd(char **argv, char **env, t_env_var **env_head)
{
    char *home;
    int ret_value;

    ret_value = 0;
    if (!argv || !argv[0])
    {
        printf("error:ft_cd"); //find appropriate error
        return (1);
    }
    if (!argv[1]) //i.e. no cd argument is provided
    {
        home = get_env_value(*env_head, "HOME");
        if (!home)
        {
            printf("minishell: cd: HOME not set\n");
            return (1);
        }
        else
        {
            ret_value = ft_chdir(HOME_VAR);
            return (ret_value);
        }
    }
    if (argv[3] != NULL)
    {
        printf("minishell: cd: too many arguments\n");
        return (1);
    }
    else
    {
        //must format path first (relative vs absolute)
        ret_value = ft_chdir(path);
        return (ret_value);
    }

}

// a few changes necessary here, complete the function
// 1. export must be complete
// 2. path formatting must be done
ft_chdir(path)
{
    char buf[PATH_MAX];
    char *OLD_PWD;
    char *PWD;

    OLD_PWD = getcwd(buf, PATH_MAX);
    PWD = path;
    if (chdir(path))
    {
        export old_pwd;
        export pwd;
        return (success);
    }
    else
    {
        print error;
        return (failure);
    }

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