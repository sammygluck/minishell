#include <minishell.h>

//create a system for the $ sign to be translated to the actual text
//remove quotes and where necessary interpret the $ sign
//handle heredoc quotes
    //remove but flag a quoted heredoc
//also some hardcode stuff for the $ sign

//lexer_tokens -> expanded_lexer_tokens
/*
$ = $
$? = exit code
$VAR = the value in the var
$NO_EXIST = empty
$'string' = string
$'$hello' = echo the string '$hello'
$"$TRUE_VAR" = var

*/