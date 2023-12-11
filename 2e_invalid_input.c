#include "minishell.h"

int is_valid_sequence(t_token *lexer_head)
{
    t_token *head;
    int i;

    i = 0;
    head = lexer_head;
    while (head)
    {
        if (head->next && (head->type > STRING && head->type <= SMALLER) && (head->next->type > STRING && head->next->type <= SMALLER))
            return (1);
        if (i == 0 && head->type == PIPE)
            return (1);
        if (head->next == NULL && (head->type > STRING && head->type <= SMALLER))
            return (1); // return other numbers to reflect which error?
        //add check for missing redirect arguments:
        if ((head->type > STRING && head->type <= SMALLER) && (head->next->type != 6)) //i.e. 6 is the type I gave to a string different than the enum number
            return (1);
        head = head->next;
        i++;
    }
    return (0);
}