#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> //remove maybe
# include <stddef.h>
# include <limits.h>


typedef struct s_token {
    char    *string;
    int     type;
    t_token *next;
}   t_token;

//tokenizer
void add_token(char *string, int *i, int type, t_token **head);
char *word_string(char *string, int *i);
char *token_string(int type, int *i);
void add_token_to_list(t_token **token_list, t_token *token);
t_token *create_token(char *string, int type);


//libft tmp
int ft_strlen(char *string);
char	*ft_strdup(const char *s);
char *ft_strndup(const char *s, size_t n);

#endif