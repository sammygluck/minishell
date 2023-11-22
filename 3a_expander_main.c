#include <minishell.h>

void expander(t_token **token_head, t_env_var *env_head);

/*
    outline:
    for each lexer string, unless heredoc -> replace old one with expanded one
    make sure to free all necesarry parts

*/
void expander(t_token **token_head, t_env_var *env_head)
{
    t_token *head;
    char *tmp;
    char *new_string;

    head = *token_head;
    //for each string in the token list
    while(head)
    {
        if (head->type == 6) //why isn't it 0?
        {
        //pass it to the first clean
            tmp = head->string;
            new_string = initial_clean(head->string);
        //free old
            free(tmp);
            head->string = new_string;
        //pass it to the second clean
            //tmp = head->string;
   //         new_string = expanded(head->string, env_head);
            //free(tmp);
   //         if (new_string)
   //             head->string = new_string;
        //free old
        // //pass it to the third clean
        //     tmp = head->string;
        //     new_string = third_clean(tmp);
        // //free old
        //     free(tmp);
        //     head->string = new_string;
        }
        //heredocs
        //if head->next && head->next->
        //skip tokens
        head = head->next;
        //freeing: parent/child?    
    }
}