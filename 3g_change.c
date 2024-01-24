#include "minishell.h"

void replace_node(t_token **head, t_token *node_to_replace, t_token *new_nodes);
void process_token_list(t_token **head);

void process_token_list(t_token **head) 
{
    t_token *current;
    t_token *next_token;
    t_token *new_tokens;
    t_token *last_new_token;

    current = *head;
    while (current != NULL) 
    {
        next_token = current->next;
        if (current->type == 6) {
            new_tokens = mini_tokenizer(current->string);
            last_new_token = new_tokens;
            while (last_new_token != NULL && last_new_token->next != NULL)
                last_new_token = last_new_token->next;
            replace_node(head, current, new_tokens);
            if (last_new_token != NULL)
                next_token = last_new_token->next;
            else
                next_token = NULL;
        }
        current = next_token;
    }
}

void replace_node(t_token **head, t_token *node_to_replace, t_token *new_nodes) 
{
    t_token *last_new_node;

    if (new_nodes == NULL)
        return;
    last_new_node = new_nodes;
    while (last_new_node->next != NULL)
        last_new_node = last_new_node->next;
    // Handling the case where the head is the node to be replaced
    if (*head == node_to_replace) 
    {
         // Link the last new node to the next of the node to be replaced
        last_new_node->next = node_to_replace->next;
        // Update the previous pointer of the next node, if it exists
        if (node_to_replace->next != NULL)
            node_to_replace->next->previous = last_new_node;
        // Change the head to the new nodes
        *head = new_nodes;
        new_nodes->previous = NULL;
    } 
    else 
    {
        // Link the previous node of node_to_replace to new_nodes
        if (node_to_replace->previous != NULL) 
        {
            node_to_replace->previous->next = new_nodes;
            new_nodes->previous = node_to_replace->previous;
        }
        // Link the last new node to the next of the node to be replaced
        last_new_node->next = node_to_replace->next;
        // Update the previous pointer of the next node, if it exists
        if (node_to_replace->next != NULL)
            node_to_replace->next->previous = last_new_node;
    }
    free(node_to_replace->string);
    free(node_to_replace);
}

