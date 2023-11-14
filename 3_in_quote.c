#include <minishell.h>
        // if (is_quote(string[i]) && in_quote == 0)
        //     in_quote = is_quote(string[i]);
        // else if (is_quote(string[i]) && in_quote > 0 && is_quote(string[i]) == in_quote)
        //     in_quote = 0;

typedef struct s_quote
{
    int in_quote;
    char    quote_type;
} t_quote;

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