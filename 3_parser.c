#include <minishell.h>

/*
The goal of the parser is to take the tokens of the lexer and convert them to a list of actual commands that can be executed
How would such a command table look like? It would be a list of commands and their corresponding properties:
command = command;
arguments = arguments;
input = STDIN;
ouput = pipe;
*/
