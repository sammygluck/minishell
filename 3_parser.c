#include <minishell.h>

typedef struct s_cmd {
    char    **arguments;
    char    *redirects;
    //pid

} t_cmd;
/*
The goal of the parser is to take the tokens of the lexer and convert them to a list of actual commands that can be executed
How would such a command table look like? It would be a list of commands and their corresponding properties:
command = command;
arguments = arguments;
input = STDIN;
ouput = pipe;
*/

//until each pipe, create a new command

void create_command_table(t_token **lexer)
{
    t_token *head;
    t_cmd   *command;

    head = *lexer;
    while(head)
    {
        command = add_tokens_to_command(&head);
        add_command_to_cmd_list(command);
    }

}

t_cmd *add_tokens_to_command(t_token **token_head)
{
    t_cmd   *command;
    t_token *head;

    head = *token_head;
    command = init_command(command);
    while (head && head->type != PIPE)
    {
        if (head->type == STRING)// && head->string)
        {
            //add string to argument vector
        }
        else if (head->type != D_SMALLER)
            //add token to redirections
            //also add next token to redirections
        // else if (head->type == D_SMALLER)
            //add token to heredoc
        token_head = &head->next;
    }
}

void add_command_to_cmd_list(t_cmd *command)
{

}


// void create_command_table(t_token **lexer)
{
    t_token *head;

    head = *lexer;
    while(head)
    {
        if (head->type == STRING)
            //add to argument vector
        else if (head->type < STRING && head->type != PIPE)
            //add to redirect
        if (head->type == PIPE)
            //next command
        //as long as it's not a pipe;
    }
}