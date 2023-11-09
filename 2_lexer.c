#include <minishell.h>

t_token *tokenizer(char *string);

t_token *tokenizer(char *string)
{
    int i;
    int token_nr;
    t_token *token_head;

    i = 0;
    token_nr = 0;
    token_head = NULL;
    while (string[i])
    {
        //if is quote, handle quote behaviour
        if (is_space(string[i]))
        {
            i++;
            continue ;
        }
        token_nr = is_token(string, i);
        if (token_nr)
        {
            add_token(string, &i, token_nr, &token_head);
            continue ;
        }
        else //add a string ; are there other options around??? what about quotes???
        {
            add_token(string, &i, 6, &token_head);
            continue ;
        }
    }
    return (token_head);
}


