#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> //remove maybe
# include <stddef.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft/libft.h>


typedef enum e_symbol 
{
    STRING,
    D_GREATER, 
    D_SMALLER,
    PIPE,
    GREATER,
    SMALLER,
    S_QUOTE_STRING,
    D_QUOTE_STRING,
} t_symbol;

typedef struct s_token 
{
    char    *string;
    int     type;
    struct s_token *next;
    struct s_token *previous;
}   t_token;

//tokenizer
t_token *tokenizer(char *string);
void add_token(char *string, int *i, int type, t_token **head);
char *word_string(char *string, int *i);
char *token_string(int type, int *i);
void add_token_to_list(t_token **token_list, t_token *token);
t_token *create_token(char *string, int type);
int is_quote(char character);
int is_space(char c);
int is_token(char *string, int position);
void print_list(t_token *head);

#endif