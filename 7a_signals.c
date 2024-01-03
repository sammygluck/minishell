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


//sub 2 - head 1
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

//sub 1 - head 1
void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//head 1
void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

//sub 1 - head 2
void	signal_print_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1); //added this line
	rl_on_new_line();
}

//head 2
void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_print_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
