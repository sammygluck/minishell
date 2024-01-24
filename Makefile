# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 09:17:38 by jsteenpu          #+#    #+#              #
#    Updated: 2024/01/18 09:19:48 by jsteenpu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# current project
NAME = minishell
CC = gcc
CFLAGS = -I. -I$(LIBFTDIR) -Wextra -Wall -g #-fsanitize=address

### _ ONLY TO ACTIVATE WHEN USING MAC AT 19 
LDFLAGS = -L$(HOME)/.brew/opt/readline/lib
CPPFLAGS = -I$(HOME)/.brew/opt/readline/include

LIBS = -lreadline
SRC  = 1_main.c \
       1_main_utils_a.c \
       2_lexer.c \
       2b_lexer_tokens.c \
       2c_lexer_token_utils.c \
       2d_helper_functions.c \
       2e_unexpected_token.c \
       3a_expander_main.c \
       3b_first_clean.c \
       3c_second_clean_a.c \
       3c_second_clean_b.c \
       3d_third_clean.c \
       3e_expander_utils_env_handler.c \
       3f_expander_utils_in_quote_helper.c \
       3g_change.c \
       4a_parser_a.c \
       4a_parser_b.c \
       4b_realloc_array.c \
       5a_executor.c \
       5b_executor_utils_1.c \
       5b_executor_utils_2.c \
       5c_connect_cmds.c \
       5d_execute_cmd.c \
       5e_env_path.c \
       5f_redirections.c \
       5g_heredoc.c \
       5g_heredoc_utils.c \
       5g_heredoc_var_delete_or_replace.c \
       5g_heredoc_var_expansion.c \
       5g_heredoc_var_expansion_utils.c \
       6a_builtins_unset.c \
       6a_builtins_unset_utils.c \
       6b_builtins_pwd.c \
       6c_builtins_env.c \
       6d_builtins_echo.c \
       6e_builtins_export.c \
       6e_builtins_export_utils_a.c \
       6e_builtins_export_utils_b.c \
       6e_builtins_export_utils_c.c \
       6f_builtins_cd_a.c \
       6f_builtins_cd_b.c \
       6g_builtins_exit.c \
       6g_builtins_exit_utils.c \
       7a_signals_reg.c \
       7b_signals_heredoc.c \
       8_shlvl_export.c \
       9_free.c \
       10_mini_lexer.c \

OBJ = $(SRC:.c=.o)
HEADERS = minishell.h
RM = rm -f

# external projects
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

##_ PREVIOUS WITH NO FLAGS FOR READLINE FUNCTION 
# $(NAME): $(OBJ) $(LIBFT)
#	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)


### _ ONLY TO ACTIVATE WHEN USING MAC AT 19 
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) $(LDFLAGS) $(CPPFLAGS) $(RLINE) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

##_ PREVIOUS WITH NO FLAGS FOR READLINE FUNCTION 
#%.o: %.c $(HEADERS)
#	$(CC) $(CFLAGS) -c $< -o $@

### _ ONLY TO ACTIVATE WHEN USING MAC AT 19 
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
