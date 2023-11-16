#include <minishell.h>

t_token *create_token(char *string, int type);
void add_token_to_list(t_token **token_list, t_token *token);

/*
returns a pointer to a new token node;
arguments: a string and a type of token;
in case of error returns NULL;
*/
t_token *create_token(char *string, int type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->string = ft_strdup(string);
    if (!token->string)
    {
        free(token);
        return (NULL);
    }
    //either type gets verified here or earlier not sure yet
    token->type = type;
    token->next = NULL;
    token->previous = NULL;
    return (token);    
}

/*
adds a given pointer to a token to the end of the list of tokens;
as of now, returns nothing;
*/
void add_token_to_list(t_token **token_list, t_token *token) //not sure if it's **token_list or *token_list
{
    t_token *head;

    //first check if there is a valid pointer to token_list or token
    if (!token_list || !token)
        return ;
    //check if there are already any nodes in our list, otherwise set token to head and return
    if (!*token_list)
    {
        *token_list = token;
        return ;
    }
    //loop until end of list;
    head = *token_list;
    while (head->next)
        head = head->next;
    head->next = token;
    head->next->previous = head;
}