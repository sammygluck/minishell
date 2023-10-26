#include <minishell.h>

int ft_strlen(char *string)
{
    int i;

    i = 0;
    if (!string)
        return (i);    
    while(string[i])
        i++;
    return (i);
}

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
        return (NULL);
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

/*as of now returns nothing but in future returns int for success or failure*/
void add_token(char *string, int *i, int type, t_token **head)
{
    char *string_to_add;

    //if it's a token stringtoadd = tokentype
    //if it's a word; stringtoadd = begin of word until end of word
    //by quotes, well have to do begin of word until end of word - adjusted
    
    if (type > 0 && type < 6)
        string_to_add = token_string(type, i);
    if (type > 5)
        string_to_add = word_string(string, i);        
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
        return (strdup(">>"));
    if (type == 2) 
        return (strdup("<<"));
    if (type == 3)
        return (strdup("|"));
    if (type == 4)
        return (strdup(">"));
    if (type == 5)
        return (strdup("<"));
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
    int n;

    j = *i;
    while(string[j])
    {
        if (is_token(string[j], j) || is_space(string[j]));
            break ;
        j++;
    }
    n = j - *i;
    *i = j;
    return (strndup(&string[*i], n));//this might be a mind bender and very likely also incorrect
}