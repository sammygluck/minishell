#include <minishell.h>

void add_token(char *string, int *i, int type, t_token **head);
char *token_string(int type, int *i);
char *word_string(char *string, int *i);
int handle_quotes(char *string, int j, int *is_quoted, char *quote_type);

/*as of now returns nothing but in future returns int for success or failure*/
void add_token(char *string, int *i, int type, t_token **head)
{
    char *string_to_add;
    t_token *token;

    //edit: quotes need to be dealt within word   
    if (type > STRING && type <= SMALLER)
        string_to_add = token_string(type, i);
    if (type > 5)
        string_to_add = word_string(string, i); 
    token = create_token(string_to_add, type);
    add_token_to_list(head, token);
    free(string_to_add);
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
    int is_quoted;
    char quote_type;
    char *result;

    is_quoted = 0;
    quote_type = '\0';
    if (!string || !i)
        return (NULL);
    j = *i;
    while(string[j])
    {
        if (handle_quotes(string, j, &is_quoted, &quote_type))
            return (NULL); //error note
        if (!is_quoted && (is_token(string, j) || is_space(string[j])))
            break ;
        j++;
    }
    chars_to_copy = j - *i;
    result = strndup(&string[*i], chars_to_copy);
    *i = j;
    return (result);
}

int handle_quotes(char *string, int j, int *is_quoted, char *quote_type)
{
    char current_char;
    char next_char;

    current_char = string[j];
    next_char = string[j+1];
    if (is_quote(current_char))
    {
        if (!(*is_quoted))
        {
            *is_quoted = 1;
            *quote_type = current_char;
        }
        else if (current_char == *quote_type)
            *is_quoted = 0;
    }
    if (next_char == '\0' && (*is_quoted))
    {
        printf("Syntax error: missing closing quote\n");//error note, location
        return (-1);
    }
    return (0);
}




