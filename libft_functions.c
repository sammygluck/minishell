
#include <minishell.h>


char *ft_strndup(const char *s, size_t n)
{
    size_t i;
    char *new_string;

    new_string = malloc(n + 1);
    if (!new_string)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        new_string[i] = s[i];
        i++;
    }
    new_string[i] = '\0';
    return(new_string);
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