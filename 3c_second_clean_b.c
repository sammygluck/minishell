#include "minishell.h"

void init_begin_end(t_begin_end *values)
{
    values->begin = 0;
    values-> end = 0; 
}

int stuff_to_replace(char *string, t_begin_end *values)
{
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
    begin++;
    if (is_space(string[begin]) || string[begin] == '"')
        return (begin);
    while(string[begin])
    {
        if (is_space(string[begin]) || string[begin] == '$')
            return (begin);
        if (is_in_double_quote(string, begin) && string[begin + 1] == '"')
            return (begin + 1);
        begin++;
    }
    return (begin);
}