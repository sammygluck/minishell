#include <minishell.h>

//create a system for the $ sign to be translated to the actual text
//remove quotes and where necessary interpret the $ sign
//handle heredoc quotes
    //remove but flag a quoted heredoc
//also some hardcode stuff for the $ sign

//a lot of string manipulation ahead!!!


//1st manipulation
//extract the strings from $"string"
//if $-sign is followed by a quote
//find second quote and remove dollar sign


char *initial_clean(char *string)
{
    int i;
    int j;
    int in_quote;
    char *new_string;

    i = 0;
    j = 0;
    in_quote = 0;
    new_string = ft_malloc(ft_strlen(string) + 1);
    while (string[i])
    {
        if (is_quote(string[i]) && in_quote == 0)
            in_quote = is_quote(string[i]);
        else if (is_quote(string[i]) && in_quote > 0 && is_quote(string[i]) == in_quote)
            in_quote = 0;
        if (string[i] == '$' && is_quote(string[i + 1]) && !in_quote)
            i++;
        new_string[j++] = string[i];
            i++;
    }
    new_string[j] = '\0';
    return (new_string);
}

