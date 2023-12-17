/*
OVERVIEW:
Our program might receive signals when running. We will have to handle them appropriately.
The signals we will need to handle are:
ctrl-c -> SIGINT -> 2 
    has to display a new prompt on a new line
ctrl-d -> EOF

ctrl-\ -> SIGQUIT ->
    should do nothing

*/


#include "minishell.h"

int	handle_signal(int i)
{
	struct sigaction	act;

    ft_bzero(&act, sizeof(act));
	if (i == 0)
		act.sa_handler = &handle_prompt;
	else if (i == 1)
		act.sa_handler = &handle_heredoc_child;
	else if (i == 2)
		act.sa_handler = &handle_heredoc_parent;
	else if (i == 3)
		act.sa_handler = &handle_fork;
	else if (i == 4)
		act.sa_handler = &handle_parent;
    // sigaction(SIGINT, &act, NULL);
    // sigaction(SIGQUIT, &act, NULL);
	return (0);
}