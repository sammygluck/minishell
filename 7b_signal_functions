#include "minishell.h"

//handle prompt
void prompt_handler(int signal)
{
    if (signal == SIGINT)
    {
        printf('\n'); //is it better to use fd_put_char or the like??
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        //set global return value
    }
}

//handle process

void in_process(int signal)
{
    if (signal == SIGINT)
        //GLOBAL VALUE = 130
    else if (signal == SIGQUIT)
        //GLOBAL VALUE = 131
    exit(GLOBAL_VALUE);
}

//handle heredoc