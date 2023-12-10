#include "minishell.h"

t_cmd *parser(t_token *lexer_head)
{
    t_token *current;
    t_cmd *commands;
    t_cmd *new_cmd;
    int cmd_nr;

    current = lexer_head;
    commands = NULL;
    cmd_nr = 0;
    while (current)
    {   cmd_nr++;
        new_cmd = parse_command(&current, cmd_nr);
        append_command(&commands, new_cmd); 
    }
    return (commands);
}

t_cmd *parse_command(t_token **current, int cmd_nr)
{
    t_cmd *command;

    command = init_cmd(cmd_nr); 
    while (*current && (*current)->type != PIPE)
    {
        if (is_redirection_token(*current))
            parse_redirection(current, command); 
        else
        {
            add_argument_to_command(command, (*current)->string); //make sure string exists
            *current = (*current)->next;
        }
    }
    if (*current && (*current)->type == PIPE)
        *current = (*current)->next;
    return (command);
}

t_cmd *init_cmd(int cmd_nr)
{
    t_cmd *command;

    command = ft_malloc(sizeof(t_cmd));
    command->argc = 0;
    command->argv = NULL;
    command->redir = NULL;
    command->next = NULL;
    command->cmd_nr = cmd_nr;
    return (command);
}

void add_argument_to_command(t_cmd *command, char *arg)
{
  command->argv = realloc_array(command->argv, command->argc);
  command->argv[command->argc] = ft_strdup(arg);
  command->argv[command->argc + 1] = NULL;
  command->argc++;    
}

void append_command(t_cmd **commands, t_cmd *new_cmd)
{
    t_cmd *tmp;

    if (!*commands)
        *commands = new_cmd;
    else
    {
        tmp = *commands;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
    }
}

int is_redirection_token(t_token *token)
{
    if (token->type == GREATER)
        return (GREATER);
    else if (token->type == D_GREATER)
        return (D_GREATER);
    else if (token->type == SMALLER)
        return (SMALLER);
    else if (token->type == D_SMALLER)
        return (D_SMALLER);
    else
        return (0);
}

void parse_redirection(t_token **current, t_cmd *command)
{
    t_redir *new_redir;

    new_redir = create_redirection_node(current);
    append_redirection(command, new_redir);
}

t_redir *create_redirection_node(t_token **current)
{
    t_redir *new_redir;

    if (!(*current)->next)
    {
        printf("Syntax error: missing filename for redirection\n");
        exit(EXIT_FAILURE);
    }
    new_redir = ft_malloc(sizeof(t_redir));
    new_redir->type = (*current)->type;
    new_redir->file = ft_strdup((*current)->next->string);
    new_redir->next = NULL;
    *current = (*current)->next->next;
    return (new_redir);
}

void append_redirection(t_cmd *command, t_redir *new_redir)
{
    t_redir *last_redir;

    if (!command->redir)
        command->redir = new_redir;
    else
    {
        last_redir = command->redir;
        while (last_redir->next)
            last_redir = last_redir->next;
        last_redir->next = new_redir;
    }
}
