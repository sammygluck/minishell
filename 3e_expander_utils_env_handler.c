#include <minishell.h>

//create a linked list with the env variables
//create a system for the $ sign to be translated to the actual text
//also some hardcode stuff for the $ sign

// add_env_var();
// remove_env_var();
// find_env_var();
// modify_env_var();

t_env_var *environment_var_handler(char **env)
{
    int i;
    char *current_env;
    t_env_var *new_env;
    t_env_var *var_head;

    var_head = NULL;
    i = 0;
    while (env[i])
    {
        current_env = env[i];
        new_env = create_env_var(current_env);
        add_env_var(&var_head, new_env);
        i++;
    }
    return (var_head);
}

t_env_var *create_env_var(char *current_env)
{
    t_env_var *env_var;

    //error check if current_env isn't NULL
    //malloc
    env_var = ft_malloc(sizeof(t_env_var));
    //extract strings
    env_var->name = extract_var_name(current_env); //consider using ft_malloc for strndup & strdup
    if (!env_var->name)
    {
        free(env_var);
        return (NULL); //or exit
    }
    env_var->value = extract_var_value(current_env);
    if (!env_var->value)
    {
        free(env_var->name);
        free(env_var);
        return(NULL);//or exit 
    }
    env_var->next = NULL;
    return (env_var);
}

char *extract_var_name(char *current_env)
{
    int len;
    char *extracted;

    len = 0;
    while (current_env[len] && current_env[len] != '=')
        len++;
    extracted = ft_strndup(current_env, len);
    return (extracted);    
}

char *extract_var_value(char *current_env)
{
    int len;
    char *extracted;

    len = 0;
    while (current_env[len] && current_env[len] != '=')
        len++
    if (current_env[len] == '=')
        len++;
    else 
        return (NULL);
    extracted = ft_strdup(&current_env[len]);
    return (extracted);
}

void add_env_var(t_env_var **env_head, t_env_var *env_var)
{
    t_env_var *head;

    if (!env_head || !env_var)
        return ; //or other error handling
    if (!*env_head)
    {
        *env_head = env_var;
        return ;
    }
    head = *env_head;
    while (head->next)
        head = head->next;
    head->next = env_var;
}
