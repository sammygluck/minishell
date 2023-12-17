#include "minishell.h"

void add_token(char *string, int *i, int type, t_token **head);
char *token_string(int type, int *i);
char *word_string(char *string, int *i);
int find_word_end(char *string, int start_index, t_quote *q_struct);
int check_quote_error(t_quote *q_struct);

/*
ADD TOKEN:
This function takes our string at the index we left off with from the previous addition to our list.
Based on our assesment in the parent function, we're either adding a token or a string.
If it's a token we'll not just add the token, but we'll also idenitfy the token-type and create and add this token to the list.
If it's a string, we'll have to add the string until the string ends. This will vary on whether this string has quotes or not.

Return value: since failure over here would be a malloc failure and malloc failures are going to exit the program, I've left it at void.
*/
void add_token(char *string, int *i, int type, t_token **head)
{
    char *string_to_add;
    t_token *token;

    //edit: quotes need to be dealt within word   
    if (type > STRING && type <= SMALLER)
        string_to_add = token_string(type, i);
    if (type > 5)
        string_to_add = word_string(string, i); 
    if (!string_to_add)
    {
        printf("Error: creating string_to_add in lexer failed\n");//to be remove after
        exit(EXIT_FAILURE);//perhaps do signal something or get back to prompt
    }
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
We've also implemented quote support, so that:
a. it doesn't consider space, token etc. to be valid seperator within a quote
b. it checks for the appearance of the closing quote
return value: pointer to extracted string
*/

char *word_string(char *string, int *i)
{
    int j;
    int chars_to_copy;
    t_quote q_struct;
    char *result;

    if (!string || !i)
        return (NULL);
    init_quote(&q_struct);
    j = find_word_end(string, *i, &q_struct);
    if (check_quote_error(&q_struct))
        return (NULL);
    chars_to_copy = j - *i;
    result = strndup(&string[*i], chars_to_copy);
    *i = j;
    return (result);
}

int find_word_end(char *string, int start_index, t_quote *q_struct)
{
    int j = start_index;
    while (string[j])
    {
        is_in_quote(string[j], q_struct);
        if (!q_struct->in_quote && (is_token(string, j) || is_space(string[j])))
            break;
        j++;
    }
    return (j);
}

int check_quote_error(t_quote *q_struct)
{
    if (q_struct->in_quote)
    {
        printf("Syntax error: missing closing quote for '%c'\n", q_struct->quote_type);
        return (1); // Error found
    }
    return (0); // No error
}



