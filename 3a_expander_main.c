#include <minishell.h>

/*
    outline:
    for each lexer string, unless heredoc -> replace old one with expanded one
    make sure to free all necesarry parts

*/

t_token *expander(t_token **token_head, t_env_var *var_head)
{

    //when reassigning, make sure to free all old ones
    //for each token->name ; two passes
    
}