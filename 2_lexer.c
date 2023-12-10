#include "minishell.h"

t_token *tokenizer(char *string);

/*
This is the 'main' from the lexer.
It returns the head of a tokenlist. 
The procedure is: 
    while we're iterating over the string
    create tokens/strings
    and add each new token to a linked list
*/

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
        token_nr = is_token(string, i);
        if (is_space(string[i]))
            i++;
        else if (token_nr)
            add_token(string, &i, token_nr, &token_head);
        else
            add_token(string, &i, 6, &token_head);
    }
    return (token_head);
}


