# current project
NAME = minishell
CC = gcc
CFLAGS = -I. -I$(LIBFTDIR) -Wextra -Wall -g #-fsanitize=address
LIBS = -lreadline
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
HEADERS = $(wildcard *.h)
RM = rm -f

# external projects
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
