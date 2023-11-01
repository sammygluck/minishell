#include <minishell.h>

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
}

//this isn't going to work; adjust we need the string to be persistent, perhaps by malloc/ft_strdup("our_string")
// but make sure to free it afterwards
//replace strdup with ft_strdup
char *token_string(int type, int *i)
{
    if (type == 1 || type == 2) 
        *i += 2; //check if this is possible
    else
        *i += 1; //check if this is possible
    if (type == 1) 
        return (ft_strdup(">>"));
    else if (type == 2) 
        return (ft_strdup("<<"));
    else if (type == 3)
        return (ft_strdup("|"));
    else if (type == 4)
        return (ft_strdup(">"));
    else if (type == 5)
        return (ft_strdup("<"));
    else 
        return (NULL);
}

/*
the idea of this function is to extract the string beginning from the i part until it reaches
a space, token or null byte;
return value: pointer to extracted string
the behaviour when quotes are active will differ
*/
char *word_string(char *string, int *i)
{
    int j;
    int chars_to_copy;
    char *result;

    if (!string || !i)
        return (NULL);
    j = *i;
    while(string[j])
    {
        if (is_token(string, j) || is_space(string[j]))
            break ;
        j++;
    }
    chars_to_copy = j - *i;
    result = strndup(&string[*i], chars_to_copy);
    *i = j;
    return (result);
}

/*as of now returns nothing but in future returns int for success or failure*/
void add_token(char *string, int *i, int type, t_token **head)
{
    char *string_to_add;
    t_token *token;

    //if it's a token stringtoadd = tokentype
    //if it's a word; stringtoadd = begin of word until end of word
    //by quotes, well have to do begin of word until end of word - adjusted
    
    if (type > 0 && type < 6)
        string_to_add = token_string(type, i);
    if (type > 5)
        string_to_add = word_string(string, i); 
    token = create_token(string_to_add, type);
    add_token_to_list(head, token);
    free(string_to_add);
}

void print_list(t_token *head)
{
    if (!head)
        return;
    while(head)
    {
        printf("%s\n", head->string);
        head = head->next;
    }
}