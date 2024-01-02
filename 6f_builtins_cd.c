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

int ft_cd(char **argv, char ***env, t_env_var **env_head)
{
    char *home;
    char *old_pwd;
    int ret_value;

    ret_value = 0;
    if (!argv || !argv[0]) 
    {
        ft_putstr_fd("error:ft_cd\n", 2); // Provide more specific error message
        return (1);
    }
    if (!argv[1] || (!ft_strncmp(argv[1], "--", 2) && ft_strlen(argv[1]) == 2))
    {
        home = get_env_value(*env_head, "HOME");
        if (!home) 
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
        ret_value = ft_chdir(home, env, env_head);
        free(home); // Free memory allocated by get_env_value
        return (ret_value);
    }
    else if (!ft_strncmp(argv[1], "-", 1) && ft_strlen(argv[1]) == 1)
    {
        old_pwd = get_env_value(*env_head, "OLDPWD");
        if (!old_pwd)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            return (1);
        }
        ft_putendl_fd(old_pwd, 1);
        ret_value = ft_chdir(old_pwd, env, env_head);
        free(old_pwd);
        return (ret_value);
    }
    if (argv[2] != NULL) // Corrected argument check
    { 
        ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
        return (1);
    }
    // Path formatting can be done here if needed
    ret_value = ft_chdir(argv[1], env, env_head);
    return (ret_value);
}

int ft_chdir(const char *path, char ***env, t_env_var **env_head) //change in minishell.h
{
    char old_pwd[PATH_MAX];
    char new_pwd[PATH_MAX];

    if(!getcwd(old_pwd, PATH_MAX))
        old_pwd[0] = '\0'; //must I error out instead?
    if (chdir(path) != 0) 
    {
        perror("minishell: cd"); // Improved error handling
        return (1);
    }
    if (!getcwd(new_pwd, PATH_MAX))
        new_pwd[0] = '\0'; //perror("minishell: cd"); //exit here or return 1
    pwd_export(new_pwd, env, env_head);
    oldpwd_export(old_pwd, env, env_head);
    return (0); 
}


char *get_env_value(t_env_var *env, char *string)
{
    t_env_var *head;
    size_t string_len;

    if (!env || !string)
        return (NULL);
    string_len = ft_strlen(string);
    head = env;
    while (head)
    {
        if (ft_strlen(head->name) == string_len && !strncmp(head->name, string, string_len))
            return (ft_strdup(head->value));
        head = head->next;
    }
    return (NULL);
}

void pwd_export(char *pwd, char ***env, t_env_var **env_l)
{
    char *new_pwd;
    char *argv[3];

    new_pwd = ft_strjoin("PWD=", pwd);
    argv[0] = "export";
    argv[1] = new_pwd;
    argv[2] = NULL;
    ft_export(argv, env, env_l);
    free(new_pwd);
}

void oldpwd_export(char *oldpwd, char ***env, t_env_var **env_l)
{
    char *old_pwd;
    char *argv[3];

    old_pwd = ft_strjoin("OLDPWD=", oldpwd);
    argv[0] = "export";
    argv[1] = old_pwd;
    argv[2] = NULL;
    ft_export(argv, env, env_l);
    free(old_pwd);
}



