#include <minishell.h>

char *third_clean(char *string)
{
    t_quote q_struct;
    char *output;
    int i;
    int j;
    
    init_quote(&q_struct);
    output = ft_malloc(ft_strlen(string) + 1);
    j = 0;
    i = 0;
    while (string[i])
    {
        is_in_quote(string[i], &q_struct);
        if (is_quote(string[i]) && !q_struct.in_quote)
        {
            i++;
            continue;
        }
        output[j++] = string[i++];        
    }
    output[j] = '\0';
    return (output);
}