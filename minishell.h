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
# include <sys/wait.h>

# define CURRENT 0
# define PREVIOUS 1
# define ERROR -1
# define CHILD 0
# define READ 0
# define WRITE 1

typedef int fds[2];

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

typedef struct s_env_var 
{
	char *name;
	char *value;
	struct s_env_var *next;
} t_env_var;

typedef struct s_redir 
{
	int type;
	char *file;
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
	int		quotes; // heredoc flag to deal with the expander?
	int		input_redir; // flag for heredoc
	int		pipe_count;
	int		cmds_count;
	char	**paths;
	char	**envp;
	char	***env;
}	t_process;

typedef struct s_export
{
    char *key;
    char *value;
} t_export;

//1 main
void free_token_list(t_token **head);
char *ft_readline(void);;

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

//2e invalid input
int	is_valid_sequence(t_token *lexer_head);

//3a expander main
void	expander(t_token **token_head, t_env_var *env_head);

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
void	executor(t_cmd **command, char ***env, t_env_var **envs);

// 5b executor utils functions
void	free_array(char **array);
void	error_message(char *msg);
void	exit_error(char *source, int type);
int		open_file(char *file, int file_type);
int		is_builtin(char **commands);


// 5c connect commands with dup2
int		connect_commands(t_cmd *command, fds pipes[2], t_process *p);
void	close_pipe_ends(t_cmd *command, fds pipes[2], t_process *p);
void	swap(int **pipes);

// 5d execute command function
pid_t	execute_cmd_in_child(t_cmd *command, fds pipes[2], t_process *p,  t_env_var **envs);
void	execute_cmd(t_cmd *command, t_process *p, t_env_var **envs);
int		execute_builtin(t_cmd *command, t_process *p, t_env_var **envs);

// 5e retrieve path from env and create 2d array of different directories for paths
int		retrieve_path_var_env(t_process *p);
char	**create_paths_array(char *path);

// 5f redirection functions
//void	redirections_check(t_cmd *command, t_process *p);
int	input_redirect(t_cmd *command, t_process *p);
int	output_redirect(t_cmd *command, t_process *p);

// 5g heredoc functions
void	heredoc_handler(char *delimiter, t_process *p);

//6a builtins unset
int ft_unset(char **argv, char ***env, t_env_var **env_l);

//6a unset utils
int arg_in_env(char *string, t_env_var **env_list);
void free_old_env(char **env);
char **mirror_list_to_array(t_env_var *list);
char	*ft_env_join(char const *s1, char const *s2);

//6b builtins pwd
int ft_pwd(char **argv);

//6c builtins env
int ft_env(t_env_var **env_l);

//6d builtins echo
int ft_echo(char **argv);
int only_n(char *string);

//6e builtins export
int ft_export(char **argv, char ***env, t_env_var **list);
t_env_var *create_env_var_key_value(t_export *key_value);
void update(t_export *key_value, char ***env, t_env_var **env_list);
void modified_ft_env(t_env_var *env);
int is_right_format(char *string);
int valid_identifiers(char *string);
int has_equal_sign(char *string);
int is_alpha_under(char c);
int arg_exists_and_updated(t_export *key_value, t_env_var **env_list);
void extract_key_value(char *string, t_export *key_value);
void free_key_value(t_export *key_value);

//6f builtins cd
int ft_cd(char **argv, char ***env, t_env_var **env_head);
int ft_chdir(const char *path, char ***env, t_env_var **env_head);
char *get_env_value(t_env_var *env, char *string);
void pwd_export(char *pwd, char ***env, t_env_var **env_l);
void oldpwd_export(char *oldpwd, char ***env, t_env_var **env_l);

//6g builtins exit
int ft_exit(char **argv);
void final_exit(int exit_number);

//6g exit utils
void process_sign_and_whitespace(char **str, int *sign);
int convert_to_number(char *str, long long *number, int sign);
long long str_to_longlong_with_overflow_check(char *str, int *overflow);
long truncate_to_exit_code(long long number);
int validate_and_process_exit_code(char *input_str);

//7 signals
void	signal_reset_prompt(int signo);
void	set_signals_interactive(void);
void	signal_print_newline(int signal);
void	set_signals_noninteractive(void);
void	ignore_sigquit(void);

//8 shlvl export
void shlvl_export(char ***env, t_env_var **env_l);
char *return_env_value(char *string, t_env_var *env_l);


//test
void print_env(char **env);

#endif
