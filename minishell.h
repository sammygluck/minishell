#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> //remove maybe
# include <stddef.h>
# include <limits.h>
# include <fcntl.h> // open syscall
# include <readline/readline.h>
# include <readline/history.h>
# include <libft/libft.h>


typedef enum e_symbol 
{
	STRING,		// 0 
	D_GREATER,	// 1 - redirection '>>'
	D_SMALLER,	// 2 - redirection '<<'
	PIPE,		// 3
	GREATER,	// 4 - redirection '>'
	SMALLER,	// 5 - redirection '<'
	S_QUOTE_STRING, // 6
	D_QUOTE_STRING, // 7
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

typedef struct s_redir 
{
	int type; // see type in enum 
	char *file; // the string that is saved in the node after the redirection node
	struct s_redir *next; // the node after the node with the file name, this is the next next node
} t_redir;

typedef struct s_cmd
{
	int argc;
	char **argv;
	t_redir *redir;
	int cmd_nr;
	struct s_cmd *next;
} t_cmd;

typedef	struct	s_process
{
	int		fd_in; // the fd of the input file; if any
	int		fd_out; // the fd of the output file; if any
	int		status; // to keep track of the status of the last child
	int		pfd[2]; // to store the pipe fd's
	char	**paths;
	char	**envp;
}	t_process;

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

//4a parser
t_cmd *parser(t_token *lexer_head);
t_cmd *parse_command(t_token **current, int cmd_nr);
t_cmd *init_cmd(int cmd_nr);
void add_argument_to_command(t_cmd *command, char *arg);
void append_command(t_cmd **commands, t_cmd *new_cmd);
int is_redirection_token(t_token *token);
void parse_redirection(t_token **current, t_cmd *command);
t_redir *create_redirection_node(t_token **current);
void append_redirection(t_cmd *command, t_redir *new_redir);

//4b realloc array
char **realloc_array(char **argv, int argc);

// 5a executor functions
int		executor(t_cmd *ptr, char **env);
t_process	*init_process_struct(char **env);
void	check_redirection_type(t_cmd *command, t_process *p);
void	redirect_output(t_cmd *command, t_process *p);

// 5b executor utils functions
void	free_array(char **array);
int		open_file(char *file, int file_type);

// 5c main pipe function 
void	run_pipe(t_cmd *command, t_process *p);

// 5d execute command function
void	execute_cmd(char **cmds, t_process *p);

// 5e retrieve path from env and create 2d array of different directories for paths
int		retrieve_path_var_env(t_process *p);
char	**create_paths_array(char *path);

// 5f redirection functions
void	redirect_output(t_cmd *command, t_process *p);
void	check_redirection_type(t_cmd *command, t_process *p);

#endif