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
    values->begin = find_begin(string, values->end);
    if (values->begin == -1)
        return (0);
    values->end = find_end(string, values->begin);
    return (1);
}

int find_begin(char *string, int end)
{
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





