#include <minishell.h>

void handle_quotes();
int find_second_quote();
char *extract_string();

int is_quote(char character)
{
    if (character == '\'')
        return (S_QUOTE_STRING);
    else if (character == '\"')
        return (D_QUOTE_STRING);
    return (0);
}

void handle_quotes(char *string, int *i, t_token **head)
{
    //check if there is a matching quote, return index of matching quote
    //if not report as error
    //extract the string
    //create a new node
    //add node to the list
    //free string to add
    //increment the i
}

int find_second_quote()
{
    //args: current str pos., quote type, str pos?
    //check string from current position
    //continue until you find matching quote
    //if found, return index of second quote
    //if not found return -1
}

char *extract_string()
{
    //either use ft_strdup, ftstrndup
    //or malloc strlen of string to extract
    //extract string
    //make sure the quotes are/aren't there anymore
    //return the string
    //make sure to free all necessary things
    //check for errors
}
