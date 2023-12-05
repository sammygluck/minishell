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

int main(void)
{
    int i;

    i = 1;
    if (!arguments)
        printf("error ft_export\n");
    if (!argv[i]) // or not argv[i]
        modified_ft_env();//make sure to set the right parameter
    while (argv[i])
    {
        if(is_right_format(argv[i])) //i.e. key=value -> valid identifier issue
            update //i.e. seperate the key from value and update t_env list & char **env
        if(!right_format) //is this necessary?
            error for this argument or skip this 
        i++;
    }
}

update(key=value string)
{
    if key exist
        update the key value pair
    if it does not exist
        create new env node
        add to env list
        mirror the char **env list
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