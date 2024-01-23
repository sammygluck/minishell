#include "minishell.h"

/*
PROTOTYPE FOR NEW FIXING THE EVAL ISSUE
*/

t_token *expander_tokens(char *str)
{
    char *token_str;
    int token_idx;
    int in_quote;
    t_token *head;

    token_str = malloc(sizeof(char) * (strlen(str) + 1));
    token_idx = 0;
    in_quote = 0;
    head = NULL;

    head = tokenize_string(str, token_str, &token_idx, &in_quote);

    if (token_idx != 0)  // Add the last token if there is one
        head = add_new_token(head, &token_str, &token_idx);

    free(token_str);
    return head;
}

t_token *tokenize_string(char *str, char *token_str, int *token_idx)
{
    int i;
    t_token *head;
    t_token *current;


    i = 0;
    head = NULL;
    current = NULL;
    while (str[i] != '\0')
    {
        if (ft_isspace(str[i]) && !is_in_any_quote(str, i))
        {
            if (*token_idx != 0)
            {
                 if (head == NULL)
                {
                    head = add_new_token(NULL, &token_str, token_idx);
                    current = head;
                }
                else
                    current = add_new_token(current, &token_str, token_idx);
            }
        }
        else
        {
            token_str[*token_idx] = str[i];
            (*token_idx)++;
        }
        i++;
    }
    return head;
}


t_token *add_new_token(t_token *head, char **token_str, int *token_idx)
{
    t_token *new_token;

    (*token_str)[*token_idx] = '\0';
    new_token = create_new_token(*token_str);
    *token_idx = 0;

    if (!head)
        return new_token;
    else
        head->next = new_token;

    return new_token;
}

t_token *create_new_token(char *str)
{
    t_token *new_token;

    new_token = ft_malloc(sizeof(t_token));
    new_token->string = ft_strdup(str);
    new_token->next = NULL;
    new_token->previous = NULL;
    return (new_token);
}
