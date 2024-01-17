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
# include <signal.h>

# define CURRENT 0
# define PREVIOUS 1
# define ERROR -1
# define CHILD 0
# define READ 0
# define WRITE 1
# define HEREDOC_TEMP_FILE "./temp/.minishell_heredoc"

/******************************************************************************
*							GLOBAL VARIABLE									  *
******************************************************************************/
extern int	g_last_exit_code;

/******************************************************************************
*								STRUCTS									      *
******************************************************************************/

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

typedef enum e_signal 
{
    PROMPT,
    HEREDOC_CHILD,
    HEREDOC_PARENT,
    FORK,
    PARENT
} t_signal;

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
	struct s_redir *next; 
} t_redir;

typedef struct s_cmd
{
	int argc;
	char **argv;
	t_redir *redir;
	int cmd_nr;
	struct s_cmd *next;
} t_cmd;

typedef	struct s_hdoc
{
	char	*file; // a pointer to the last opened file
	char	*delimiter; // a pointer to the heredoc delimiter
	int		quotes; // flag for quotes
	int		fd; // fd of opened file
} t_hdoc;

typedef	struct	s_process
{
	int		fd_in; // the fd of the input file; if any
	int		fd_out; // the fd of the output file; if any
	int		status; // to keep track of the status of the last child
	int		input_redir; // flag for heredoc
	int		pipe_count;
	int		cmds_count;
	int		*pid;
	char	**paths;
	char	**envp;
	char	***env;
	t_hdoc	*heredoc;
}	t_process;

typedef struct s_export
{
    char *key;
    char *value;
} t_export;


/******************************************************************************
*								FUNCTIONS									  *
******************************************************************************/

//1 main
char *ft_readline(void);
void    init_env_vars(char ***env, t_env_var **envs);
void    check_arg_count(int argc);
void process_commands(char ***env, t_env_var **envs);

//2 lexer
t_token *tokenizer(char *string);

//2b lexer tokens
int		add_token(char *string, int *i, int type, t_token **head);
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
int error_unexpected_token(t_token *lexer_head);
char	*unexpected_token(t_token *lexer_head);


//3a expander main
void	expander(t_token **token_head, t_env_var *env_head);
char *process_token_string(char *str, t_env_var *env_head);

//3b first clean
char *initial_clean(char *string);

//3c second clean

char *expanded(char *string, t_env_var *env_list);
void init_begin_end(t_begin_end *values);
int stuff_to_replace(char *string, t_begin_end *values);
int find_begin(char *string, int end);
int find_end(char *string, int begin);
int is_valid_env_char(char chr);
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
int		execute_cmd_in_child(t_cmd *command, fds pipes[2], t_process *p,  t_env_var **envs);
void	execute_command(t_cmd *command, t_process *p, t_env_var **envs);
int		execute_builtin(t_cmd *command, t_process *p, t_env_var **envs);

// 5e retrieve path from env and create 2d array of different directories for paths
int		retrieve_path_var_env(t_process *p);
char	**create_paths_array(char *path);

// 5f redirection functions
int	input_redirect(t_cmd *command, t_process *p);
int	output_redirect(t_cmd *command, t_process *p);

// 5g heredoc functions
int		heredoc_check(t_cmd *command, t_process *p);
void	heredoc_handler(char *delimiter, t_hdoc *hd);
char	*heredoc_delimiter_qoutes(char *delimiter, t_hdoc *hd);
char	*heredoc_var_expansion(char *word);
char	*replace_or_delete_heredoc_var(char *old_word, char *var_value, int *index);
char	*replace_var_value(char *old_word, char *var_value, int *index, int len_var);
char	*delete_var_name(char *old_word, int *index, int len_newstr, int len_var);
char	*retrieve_env_var_value(char *word);
int		env_var_name_length(char *s);
int		valid_env_var_name(char c);

// 5g heredoc utils
int	ft_strcmp(const char *s1, const char *s2);

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
int ft_export_init(char **argv, t_env_var **list, t_export *key_value);
int ft_export_process_args(char **argv, char ***env, t_env_var **list, t_export *key_value);

t_env_var *create_env_var_key_value(t_export *key_value);
void	update(t_export *key_value, char ***env, t_env_var **env_list, int append);
void modified_ft_env(t_env_var *env);
int is_right_format(char *string);
int valid_identifiers(char *string);
int has_equal_sign(char *string);
int has_plus_equal_sign(char *string);
int is_alpha_under(char c);
int	arg_exists_and_updated(t_export *key_value, t_env_var **env_list, int append);
int update_env_value(t_export *key_value, t_env_var *env_var, int append);
int compare_key_length(t_export *key_value, t_env_var *env_var);
void	extract_key_value(char *string, t_export *key_value, int *append);
void free_key_value(t_export *key_value);
int	is_valid_sep(char *s, int i);
void print_export_error(int i);


//6f builtins cd
int ft_cd(char **argv, char ***env, t_env_var **env_head);
int cd_too_many_args(void);
int cd_oldpwd(char ***env, t_env_var **env_head);
int cd_home(char ***env, t_env_var **env_head);
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
int	signal_handler(int i);
void	prompt_signal(int signal);
void	p_parent_signal(int signal);
void	p_fork_signal(int signal);

void	heredoc_signal_handler(int i);
void	h_parent_signal(int signal);
void	h_child_signal(int signal);

//8 shlvl export
void shlvl_export(char ***env, t_env_var **env_l);
char *return_env_value(char *string, t_env_var *env_l);

//9 free
void free_token_list(t_token **head);
void	free_char_env(char **env);
void	free_env_list(t_env_var **head);
void    free_redirection_list(t_redir **);
void    free_cmd_list(t_cmd **head);

//test
void print_env(char **env);

#endif