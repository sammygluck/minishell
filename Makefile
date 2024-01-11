# current project
NAME = minishell
CC = gcc
CFLAGS = -I. -I$(LIBFTDIR) -Wextra -Wall -g #-fsanitize=address

### _ ONLY TO ACTIVATE WHEN USING MAC AT 19 
LDFLAGS = -L$(HOME)/42/42-useful-programs/homebrew/opt/readline/lib
CPPFLAGS = -I$(HOME)/42/42-useful-programs/homebrew/opt/readline/include

LIBS = -lreadline
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
HEADERS = $(wildcard *.h)
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
