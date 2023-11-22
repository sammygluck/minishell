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

typedef struct s_begin_end 
{
    int begin;
    int end;
} t_begin_end;

typedef struct s_quote
{
    int in_quote;
    char    quote_type;
} t_quote;

typedef struct s_env_var {
    char *name;
    char *value;
    struct s_env_var *next;
} t_env_var;


//1 main
void free_token_list(t_token **head);

//2 lexer
t_token *tokenizer(char *string);

//2b lexer tokens
void add_token(char *string, int *i, int type, t_token **head);
char *token_string(int type, int *i);
char *word_string(char *string, int *i);
int find_word_end(char *string, int start_index, t_quote *q_struct);
int check_quote_error(t_quote *q_struct);

//2c lexer token utils
t_token *create_token(char *string, int type);
void add_token_to_list(t_token **token_list, t_token *token);

//2d helper functions
int is_quote(char character);
int is_space(char c);
int is_token(char *string, int position);
void print_list(t_token *head);

//3a expander main
void expander(t_token **token_head, t_env_var *env_head);

//3b first clean
char *initial_clean(char *string);

//3c second clean

char *expanded(char *string, t_env_var *env_list);
void init_begin_end(t_begin_end *values);
int stuff_to_replace(char *string, t_begin_end *values);
int find_begin(char *string, int end);
int find_end(char *string, int begin);
char *extract(char *string, int begin, int end);
char *make_replace_string(t_env_var *env_list, char *to_replace);
char *var_extractor(char *string, t_env_var *env_head);
char *replace(char *old_string, char *to_replace, t_begin_end *v);

//3d third clean
char *third_clean(char *string);

//3e env handler

t_env_var *environment_var_handler(char **env);
t_env_var *create_env_var(char *current_env);
char *extract_var_name(char *current_env);
char *extract_var_value(char *current_env);
void add_env_var(t_env_var **env_head, t_env_var *env_var);

//3f quote handler

void init_quote(t_quote *q_struct);
int is_in_quote(char current_chr, t_quote *q_struct);
int is_in_any_quote(const char *str, int index);
int is_in_single_quote(const char *str, int index);
int is_in_double_quote(const char *str, int index);

#endif