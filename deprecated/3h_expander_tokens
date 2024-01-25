#include "minishell.h"

t_token *get_last(t_token *head);
t_token *expanded_tokens(char *string);
void clean(t_token *head);
void set_all_tokens_to_string(t_token *head);
t_token *insert_head_into_existing_list(t_token *curr);

t_token *insert_head_into_existing_list(t_token *curr)
{
    t_token *previous;
    t_token *next;
    t_token *current;
    t_token *first;
    t_token *last;
    
    current = curr;
    first = expanded_tokens(curr->string);
    // printf("%s\n", first->string);
    // //exit(1);
    last = get_last(first);
    previous = current->previous; //1st = NULL, middle-last = value
    next = current->next; //first- middle = value; last = NULL
    if (previous)
        previous->next = first;
    if (next)
        next->previous = last;
    first->previous = previous;
    last->next = next;
    if (current->string)
        free(current->string);
    return (next);
}

t_token *expanded_tokens(char *string)
{
    t_token *head;

    head = tokenizer(string);
    clean(head);
    set_all_tokens_to_string(head);
    // insert_head_into_existing_list(head, current_list_pos);
    return (head);
}

void clean(t_token *head)
{
    char *tmp;

    while (head)
	{
        tmp = head->string;
		head->string = third_clean(tmp);
        free(tmp);
		head = head->next;
	}
}

void set_all_tokens_to_string(t_token *head)
{
    while (head)
    {
        head->type = 6;
        head = head->next;
    }
}


t_token *get_last(t_token *head)
{
    if (!head)
        return (NULL);
    while(head->next)
        head = head->next;
    return (head);
}