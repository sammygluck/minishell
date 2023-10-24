#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_token {
    char    *string;
    int     type;
    t_token *next;
}   t_token;


#endif