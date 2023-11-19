#include <minishell.h>

typedef struct s_begin_end 
{
    int begin;
    int end;
} t_begin_end;

char *expanded(char *string, t_env_var env_list)
{
    t_begin_end values;
    int we_done;
    char *to_replace;
    char *replace_with;
    char *tmp;

    init_begin_end(&values);
    we_done = stuff_to_replace(string, values);
    while(!we_done)
    {
        to_replace = extract(values.begin, values.end, string);
        replace_with = make_replace_string(env_list, to_replace);
        tmp = replace(string, replace_with, values);
        free(to_replace);
        free(replace_with);
        free(string);
        string = tmp;
        we_done = stuff_to_replace(string, values);
    }
    return (string);
}

void init_begin_end(t_begin_end *values)
{
    values->begin = 0;
    values-> end = 0; //need to find appropriate begin and end places
}

int stuff_to_replace(char *string, t_begin_end *values)
{
    //check if changed if yes return there is work to be done WERK AAN DE WINKEL!! :)
    values->begin = 0;
    values->end = 0;
    values->begin = find_begin(string, values->end);
    if (values->begin == -1)
        return (0);
    values->end = find_end(string, values->begin);
    return (1);
}

int find_begin(char *string, int end)
{
    //I think for further iteration purposes begin end with -1 and end++; chatGPT, what do you think?
    if (string[end] == '\0')
        return (-1); //don't return end as is this is beginning
    while(string[end])
    {
        if (string[end] == '$' && !is_in_single_quote(string, end))
            return (end);
        end++;
    }
    return (-1);
}

int find_end(char *string, int begin)
{
    while(string[begin])
    {
        if (is_space(string[begin]) || string[begin + 1] == '\0')
            return (begin);
        begin++;
    }
    return (0);
}

char *extract(char *string, int begin, int end)
{
    char *extracted;
    int n;

    n = end - begin;
    //if n = 0;
    //return (NULL);
    extracted = ft_strndup(&string[begin], n);
    return (extracted);
}

char *make_replace_string(t_env_var env_list, char *to_replace)
{
    //if can't use return and a function on the same line, create var and at each stage set it to what needs to be
    if(to_replace[0] == '$' && (to_replace[1] == '\0' || is_space(to_replace[1]));
        return (ft_strdup("$"));
    else if (to_replace[0] == '$' && to_replace[1] == '?')
        printf("exit code: \n");//to handle
    else
        return(var_extractor(to_replace, env_list));  
}

char *var_extractor(char *string, t_env_var *env_head)
{
    t_env_var *head;

    head = env_head;
    while(head)
    {
        if(!ft_strcmp(head->name, &string[1]))
            return(ft_strdup(head->value));
        head = head->next;
    }
    return (ft_strdup(""));    
}

char *replace(char *old_string, char *to_replace, t_begin_end v)
{
    char *new_string;
    int i;
    int j;

    new_string = ft_malloc(ft_strlen(old_string) - (v.end - v.begin + 1) + ft_strlen(to_replace) + 1);
    i = 0;
    j = 0;
    while (i < v.begin)
        new_string[j++] = old_string[i++];
    i = 0;
    while(to_replace[i])
        new_string[j++] = to_replace[i++];
    i = v.end + 1;
    while (old_string[i])
        new_string[j++] = old_string[i++];
    new_string[j] = '\0';
    return (new_string);
}




