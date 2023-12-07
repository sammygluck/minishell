/*
1. Start the export command implementation.

2. Check if any arguments are provided to the export command.
   - If no arguments are provided:
       - Display all environment variables in a sorted manner.
           - Use the 't_env' list or 'char **env' array as per your shell design.
           - If using 't_env', sort the list based on the variable names and then print.
           - If using 'char **env', convert it to a list, sort, and then print.
       - Each variable should be printed in the format "declare -x NAME='value'".
   - If arguments are provided:
       - Loop through each argument:
           - Check if the argument is in the format "KEY=VALUE".
               - If yes, add or update the variable in both 't_env' list and 'char **env' array.
               - If the format is incorrect, display an error message for that argument.

3. For adding or updating environment variables:
   - In 't_env' list:
       - Search for the variable by KEY.
       - If found, update its VALUE.
       - If not found, add a new node with KEY and VALUE.
   - In 'char **env' array:
       - Search for the variable by KEY.
       - If found, update its VALUE.
       - If not found, allocate new memory for the new "KEY=VALUE" string and add it to the array.

4. Optional: Implement functionality to handle variables without '='.
   - If a variable is provided without '=', treat it as a variable with an empty value.
   - Or, only add the variable name to the environment without changing its value if it already exists.

5. End of export command implementation.

*/
#include <minishell.h>

typedef struct s_export
{
    char *key;
    char *value;
} t_export;

int ft_export(char **argv, char **env, t_env_var **list)
{
    int i;
    t_export key_value;

    i = 1;
    if (!argv)
        printf("error ft_export\n");
    if (!argv[i]) // or not argv[i]
        modified_ft_env(*env);//make sure to set the right parameter
    while (argv[i])
    {
        if(is_right_format(argv[i])) //i.e. key=value -> valid identifier issue
        {
            extract_key_value(argv[i], &key_value);
            update(&key_value, ) //i.e. seperate the key from value and update t_env list & char **env
        }
        // if(!right_format) //is this necessary?
        //     error for this argument or skip this 
        i++;
    }
    free_key_value(&key_value);
}

t_env_var *create_env_var_key_value(t_export *key_value)
{
    t_env_var *env_var;

    //error check if current_env isn't NULL
    env_var = ft_malloc(sizeof(t_env_var));
    //extract strings
    env_var->name = ft_strdup(key_value->key); 
    env_var->value = ft_strdup(key_value->value);
    env_var->next = NULL;
    return (env_var);
}

void update(t_export *key_value, char **env, t_env_var **env_list) //return value?
{
    t_env_var *new_node;

    new_node = NULL;
    if (!arg_exists_and_updated(key_value, env))
    {
        new_node = create_env_var_key_value(key_value);
        add_env_var(env_list, new_node);
    }
    free_old_env(env);
    env = mirror_list_to_array(*env_list);
}

void modified_ft_env(t_env_var *env)//parameters + check again if works
{
    t_env_var *head;

    head = env;
    if (!env) 
        return ;
    while (head)
    {
        printf("declare -x %s=\"%s\"\n", env->value, env->string); 
        head = head->next;
    }
    return (0);   
}

int is_right_format(char *string)
{
    
    if (!valid_identifiers(string))
        return (0);
    if (!has_equal_sign(string))
        return (0);
    return (1);
}


int valid_identifiers(char *string)
{
    int i = 0;

    if (!string || string[0] == '\0')
    {
        printf("Error: Empty string or null pointer\n");
        return (0);
    }
    // Check first character
    if (!is_alpha_under(string[i]))
    {
        printf("Error: First character is not a valid identifier\n");
        return (0);
    }
    i++;
    while (string[i] && string[i] != '=')
    {
        if (!is_alpha_under(string[i]) && !is_digit(string[i]))
        {
            printf("Error: Invalid character in identifier\n");
            return (0);
        }
        i++;
    }
    return (1);
}

int has_equal_sign(char *string)
{
    int i;

    i = 0;
    while (string[i])
    {
        if (string[i] == '=')
            return (1);
        i++;
    }
    printf("Error: '=' not found in the string\n");
    return (0);
}

int is_alpha_under(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        return (1);
    else
        return (0);
}


int arg_exists_and_updated(t_export *key_value, t_env_var **env_list)
{
    t_env_var *head;

    head = *env_list;
    while (head)
    {
        if (!strncmp(key_value->key, head->name, ft_strlen(string) + 1))
        {
            free(head->value);
            head->value = ft_strdup(key_value->value);
            return (1);
        }
        head = head->next;
    }
    return (0); 
}

int extract_key_value(char *string, t_export *key_value)
{
    int i;
    int j;

	i = 0;
    free_key_value(key_value);
    while(string[i] && string[i] != '=')
        i++;
    key_value->key = ft_strndup(string, i);
    i++;
    key_value->value = ft_strdup(&string[i]);
}

void free_key_value(t_export *key_value)
{
    if (key_value->key)
    {
        free(key_value->key);
        key_value->key = NULL;
    }
    if (key_value->value)
    {
        free(key_value->value);
        key_value->value = NULL;
    }
}