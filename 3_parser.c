#include <minishell.h>

typedef struct s_cmd {
    char    **arguments;
    char    *redirects;
    //pid

} t_cmd;
/*
The goal of the parser is to take the tokens of the lexer and convert them to a list of actual commands that can be executed
How would such a command table look like? It would be a list of commands and their corresponding properties:
command id;
arguments = argument_vector;
arg_number;
redirects = redirect_vector;
redirect_number;
input = STDIN;
ouput = pipe;
pid;

also we would have to init (i.e. malloc + give default values to each of the vars), each time we create a command
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
    command = NULL;
    init_command(command);
    while (head && head->type != PIPE)
    {
        if (head->type == STRING)// && head->string)
        {
            //add string to argument vector
            //argv can't be linked list, as execve takes an array for argv
            //which means we need to expand argv to hold an extra argument each time we find a new argument
            //we can also count and allocate beforehand, but expansion might be the better option, albeit maybe new code
            add_string_to_array(array, current_array_size, head->string);
        }
        else if (head->type != D_SMALLER)
            //a word on redirections_vector
            //this can and probably should use a linked list
            //reason: redirections = redirect token + filename -> need to hold both in struct
            //add token to redirections_vector
            //also add next token to redirections (i.e. the filename)
        // else if (head->type == D_SMALLER)
            //add token to heredoc
        token_head = &head->next;
    }
}

void add_command_to_cmd_list(t_cmd *command)
{

}

void init_command(t_cmd *command)
{

}

void add_string_to_array(void **array, int array_size, char *string)
{
    //1. expand array, increment array_size
    //2. save the new string in the latests edition to the array
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