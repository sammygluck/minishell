#include <minishell.h>

void init_quote(t_quote *q_struct)
{
    q_struct->in_quote = 0;
    q_struct->quote_type = '\0';
}

int is_in_quote(char current_chr, t_quote *q_struct)
{
    if (is_quote(current_chr) && q_struct->in_quote == 0)
    {
        q_struct->in_quote = 1;
        q_struct->quote_type = current_chr;
    }
    else if (is_quote(current_chr) && q_struct->in_quote == 1 && q_struct->quote_type == current_chr)
        q_struct->in_quote = 0;
    return (q_struct->in_quote);
}

//what follows is chatGPT generated functions:
int is_in_any_quote(const char *str, int index)
{
    t_quote q_struct;
    init_quote(&q_struct);

    for (int i = 0; i <= index; i++)
    {
        if (str[i] == '\0')
            break;
        is_in_quote(str[i], &q_struct);
    }
    return q_struct.in_quote;
}
//this also chatGPT
int is_in_single_quote(const char *str, int index)
{
    t_quote q_struct;
    init_quote(&q_struct);

    for (int i = 0; i <= index; i++)
    {
        if (str[i] == '\0')
            break;
        if (str[i] == '\'' && q_struct.in_quote == 0)
        {
            q_struct.in_quote = 1;
            q_struct.quote_type = '\'';
        }
        else if (str[i] == '\'' && q_struct.in_quote == 1 && q_struct.quote_type == '\'')
            q_struct.in_quote = 0;
    }
    return (q_struct.in_quote && q_struct.quote_type == '\'');
}

int is_in_double_quote(const char *str, int index)
{
    t_quote q_struct;
    init_quote(&q_struct);

    for (int i = 0; i <= index; i++)
    {
        if (str[i] == '\0')
            break;
        if (str[i] == '"' && q_struct.in_quote == 0)
        {
            q_struct.in_quote = 1;
            q_struct.quote_type = '"';
        }
        else if (str[i] == '"' && q_struct.in_quote == 1 && q_struct.quote_type == '"')
            q_struct.in_quote = 0;
    }
    return (q_struct.in_quote && q_struct.quote_type == '"');
}
