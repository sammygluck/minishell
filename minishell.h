/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:27:00 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/24 15:11:34 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> //remove maybe
# include <stddef.h>
# include <limits.h>
# include <fcntl.h>
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

typedef int	t_fds[2];

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
}	t_symbol;

typedef enum e_signal
{
	PROMPT,
	HEREDOC_CHILD,
	HEREDOC_PARENT,
	FORK,
	PARENT
}	t_signal;

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*previous;
	char			*string;
	int				type;
}	t_token;

typedef struct s_begin_end
{
	int	begin;
	int	end;
}	t_begin_end;

typedef struct s_quote
{
	char	quote_type;
	int		in_quote;
}	t_quote;

typedef struct s_env_var
{
	struct s_env_var	*next;
	char				*name;
	char				*value;
}	t_env_var;

typedef struct s_redir
{
	struct s_redir	*next;
	char			*file;
	int				type;
}	t_redir;

typedef struct s_cmd
{
	struct s_cmd	*next;
	t_redir			*redir;
	char			**argv;
	int				argc;
	int				cmd_nr;
}	t_cmd;

typedef struct s_hdoc
{
	char	*file;
	char	*delimiter;
	int		quotes;
	int		fd;
}	t_hdoc;

typedef struct s_process
{
	int		fd_in;
	int		fd_out;
	int		input_redir;
	int		output_redir;
	int		pipe_count;
	int		cmds_count;
	int		builtin;
	int		*pid;
	char	**paths;
	char	**envp;
	char	***env;
	t_hdoc	*heredoc;
}	t_process;

typedef struct s_export
{
	char	*key;
	char	*value;
}	t_export;

/******************************************************************************
*								FUNCTIONS									  *
******************************************************************************/

t_env_var	*environment_var_handler(char **env);
t_env_var	*create_env_var(char *current_env);
t_token		*tokenizer(char *string);
t_token		*create_token(char *string, int type);
t_token		*find_last_node(t_token *head);
t_token		*mini_tokenizer(char *string);
t_redir		*create_redirection_node(t_token **current);
t_cmd		*parser(t_token *lexer_head);
t_cmd		*parse_command(t_token **current, int cmd_nr);
t_cmd		*init_cmd(int cmd_nr);
void		init_env_vars(char ***env, t_env_var **envs);
void		check_arg_count(int argc);
void		process_commands(char ***env, t_env_var **envs);
void		add_token_to_list(t_token **token_list, t_token *token);
void		print_list(t_token *head);
void		expander(t_token **token_head, t_env_var *env_head);
void		init_begin_end(t_begin_end *values);
void		add_env_var(t_env_var **env_head, t_env_var *env_var);
void		init_quote(t_quote *q_struct);
void		add_argument_to_command(t_cmd *command, char *arg);
void		append_command(t_cmd **commands, t_cmd *new_cmd);
void		parse_redirection(t_token **current, t_cmd *command);
void		append_redirection(t_cmd *command, t_redir *new_redir);
void		exec_error_message(char *command, char *message, t_process *p);
void		executor(t_cmd **command, char ***env, t_env_var **envs);
void		free_array(char **array);
void		error_message(char *msg);
void		exit_error(char *source, int type);
void		save_stdin_out(int *save_fd);
void		free_process(t_process *p);
void		reset_std_redirection(int *save_fd, t_process *p);
void		close_pipe_ends(t_cmd *command, t_fds pipes[2], t_process *p);
void		swap(int **pipes);
void		execute_command(t_cmd *command, t_process *p, t_env_var **envs);
void		free_old_env(char **env);
void		update(t_export *key_value, char ***env,
				t_env_var **env_list, int append);
void		modified_ft_env(t_env_var *env);
void		extract_key_value(char *string, t_export *key_value, int *append);
void		free_key_value(t_export *key_value);
void		print_export_error(int i);
void		pwd_export(char *pwd, char ***env, t_env_var **env_l);
void		oldpwd_export(char *oldpwd, char ***env, t_env_var **env_l);
void		final_exit(int exit_number);
void		process_sign_and_whitespace(char **str, int *sign);
void		prompt_signal(int signal);
void		p_parent_signal(int signal);
void		p_fork_signal(int signal);
void		heredoc_signal_handler(int i);
void		h_parent_signal(int signal);
void		h_child_signal(int signal);
void		shlvl_export(char ***env, t_env_var **env_l);
void		free_token_list(t_token **head);
void		free_char_env(char **env);
void		free_env_list(t_env_var **head);
void		free_redirection_list(t_redir **head);
void		free_cmd_list(t_cmd **head);
void		print_env(char **env);
void		connect_redirections(t_process *p);
void		remove_prev_file_ref(t_hdoc *hd);
void		parent_wait(t_process *p);
void		print_arguments(char **argv, int start_index, int flag_n);
void		replace_node(t_token **head, t_token *node_to_replace,
				t_token *new_nodes);
void		insert_new_nodes(t_token **head, t_token *node_to_replace,
				t_token *new_nodes, t_token *last_new_node);
void		process_token_list(t_token **head);
void		free_node(t_token *node);
char		*ft_readline(void);
char		*token_string(int type, int *i);
char		*word_string(char *string, int *i);
char		*unexpected_token(t_token *lexer_head);
char		*process_token_string(char *str, t_env_var *env_head);
char		*initial_clean(char *string);
char		*expanded(char *string, t_env_var *env_list);
char		*extract(char *string, int begin, int end);
char		*make_replace_string(t_env_var *env_list, char *to_replace);
char		*var_extractor(char *string, t_env_var *env_head);
char		*replace(char *old_string, char *to_replace, t_begin_end *v);
char		*third_clean(char *string);
char		*extract_var_name(char *current_env);
char		*extract_var_value(char *current_env);
char		**realloc_array(char **argv, int argc);
char		**create_paths_array(char *path);
char		*heredoc_delimiter_qoutes(char *delimiter, t_hdoc *hd);
char		*heredoc_var_expansion(char *word, t_env_var **envs);
char		*replace_or_delete_heredoc_var(char *old_word,
				char *var_value, int *index);
char		*replace_var_value(char *old_word, char *var_value,
				int *index, int len_var);
char		*delete_var_name(char *old_word, int *index,
				int len_newstr, int len_var);
char		*retrieve_env_var_value(char *word, t_env_var **envs);
char		**mirror_list_to_array(t_env_var *list);
char		*ft_env_join(char const *s1, char const *s2);
char		*get_env_value(t_env_var *env, char *string);
char		*return_env_value(char *string, t_env_var *env_l);
char		*mini_word_string(char *string, int *i);
int			add_token(char *string, int *i, int type, t_token **head);
int			find_word_end(char *string, int start_index, t_quote *q_struct);
int			check_quote_error(t_quote *q_struct);
int			is_quote(char character);
int			is_space(char c);
int			is_token(char *string, int position);
int			error_unexpected_token(t_token *lexer_head);
int			stuff_to_replace(char *string, t_begin_end *values);
int			find_begin(char *string, int end);
int			find_end(char *string, int begin);
int			is_valid_env_char(char chr);
int			is_in_quote(char current_chr, t_quote *q_struct);
int			is_in_any_quote(const char *str, int index);
int			is_in_single_quote(const char *str, int index);
int			is_in_double_quote(const char *str, int index);
int			is_redirection_token(t_token *token);
int			open_file(char *file, int file_type);
int			is_builtin(char **commands);
int			connect_commands(t_cmd *command, t_fds pipes[2], t_process *p);
int			execute_cmd_in_child(t_cmd *command, t_fds pipes[2],
				t_process *p, t_env_var **envs);
int			execute_builtin(t_cmd *command, t_process *p, t_env_var **envs);
int			retrieve_path_var_env(t_process *p);
int			redirection_check(t_cmd *command, t_process *p);
int			heredoc_check(t_cmd *command, t_process *p, t_env_var **envs);
int			env_var_name_length(char *s);
int			valid_env_var_name(char c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_unset(char **argv, char ***env, t_env_var **env_l);
int			arg_in_env(char *string, t_env_var **env_list);
int			ft_pwd(t_env_var **envs);
int			ft_env(t_env_var **env_l);
int			check_path_var(t_env_var **env_l);
int			ft_echo(char **argv);
int			only_n(char *string);
int			ft_export(char **argv, char ***env, t_env_var **list);
int			ft_export_init(char **argv, t_env_var **list, t_export *key_value);
int			ft_export_process_args(char **argv, char ***env,
				t_env_var **list, t_export *key_value);
int			is_right_format(char *string);
int			valid_identifiers(char *string);
int			has_equal_sign(char *string);
int			has_plus_equal_sign(char *string);
int			is_alpha_under(char c);
int			arg_exists_and_updated(t_export *key_value,
				t_env_var **env_list, int append);
int			update_env_value(t_export *key_value,
				t_env_var *env_var, int append);
int			compare_key_length(t_export *key_value, t_env_var *env_var);
int			is_valid_sep(char *s, int i);
int			ft_cd(char **argv, char ***env, t_env_var **env_head);
int			cd_too_many_args(void);
int			cd_oldpwd(char ***env, t_env_var **env_head);
int			cd_home(char ***env, t_env_var **env_head);
int			ft_chdir(const char *path, char ***env, t_env_var **env_head);
int			ft_fallback_to_home(char ***env, t_env_var **env_head);
int			ft_exit(char **argv);
int			convert_to_number(char *str, long long *number, int sign);
int			validate_and_process_exit_code(char *input_str);
int			signal_handler(int i);
int			process_flags(char **argv, int *flag_n);
int			mini_add_token(char *string, int *i, int type, t_token **head);
int			mini_find_word_end(char *string, int start_index,
				t_quote *q_struct);
long long	str_to_longlong_with_overflow_check(char *str, int *overflow);
long		truncate_to_exit_code(long long number);

#endif
