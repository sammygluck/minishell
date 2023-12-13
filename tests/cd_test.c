#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

// ft_cd(char **argv, char **env, t_env_var **env_head)
// {
//     char *home;
//     int ret_value;

//     ret_value = 0;
//     if (!argv || !argv[0])
//     {
//         printf("error:ft_cd"); //find appropriate error
//         return (1);
//     }
//     if (!argv[1]) //i.e. no cd argument is provided
//     {
//         home = get_env_value(*env_head, "HOME");
//         if (!home)
//         {
//             printf("minishell: cd: HOME not set\n");
//             return (1);
//         }
//         else
//         {
//             ret_value = ft_chdir(HOME_VAR);
//             return (ret_value);
//         }
//     }
//     if (argv[3] != NULL)
//     {
//         printf("minishell: cd: too many arguments\n");
//         return (1);
//     }
//     else
//     {
//         //must format path first (relative vs absolute)
//         ret_value = ft_chdir(path);
//         return (ret_value);
//     }

// }

// // a few changes necessary here, complete the function
// // 1. export must be complete
// // 2. path formatting must be done
// ft_chdir(path)
// {
//     char buf[PATH_MAX];
//     char *OLD_PWD;
//     char *PWD;

//     OLD_PWD = getcwd(buf, PATH_MAX);
//     PWD = path;
//     if (chdir(path))
//     {
//         export old_pwd;
//         export pwd;
//         return (success);
//     }
//     else
//     {
//         print error;
//         return (failure);
//     }

// }

// char *get_env_value(t_env_var *env, char *string)
// {
//     t_env_var *head;

//     if (!env)
//         return (NULL);
//     head = env;
//     while (head)
//     {
//         if (!strncmp(head->name, string, ft_strlen(string) + 1))
//             return (ft_strdup(head->value));
//         head = head->next;
//     }
//     return (NULL);
// }

int main(void)
{
    char buffer[PATH_MAX];
    printf("%s\n", getcwd(buffer, PATH_MAX));
    chdir("tests");
    printf("%s\n", getcwd(buffer, PATH_MAX));
}