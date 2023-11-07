
#include <minishell.h>


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