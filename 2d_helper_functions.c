
#include "minishell.h"

int is_quote(char character);
int is_space(char c);
int is_token(char *string, int position);
void print_list(t_token *head);



int is_quote(char character)
{
    if (!character)
        return (0);
    if (character == '\'')
        return (S_QUOTE_STRING);
    else if (character == '\"')
        return (D_QUOTE_STRING);
    return (0);
}

int is_space(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int is_token(char *string, int position)
{
    if(string[position] == '>' && string[position + 1] == '>')
        return (D_GREATER);
    if (string[position] == '<' && string[position + 1] == '<')
        return (D_SMALLER);
    if (string[position] == '|')
        return (PIPE);
    if (string[position] == '>')
        return (GREATER);
    if (string[position] == '<')
        return (SMALLER);
    return (STRING);
}

void print_list(t_token *head)
{
    if (!head)
        return;
    while(head)
    {
        printf("%s\n", head->string);
        printf("%i\n", head->type);
        head = head->next;
    }
}