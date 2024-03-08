NAME	:= minishell

# Compiler
CC	:=	cc
CFLAGS	:=	-Wextra -Wall -Werror
INC		= -I ./includes/
# Source
SRCS	:=	src/main.c

OBJS	:=	$(SRCS:.c=.o)

all: $(NAME)

%.o: %c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)

# Compiling Minishell
$(NAME): $(OBJS)
	@echo "Compiling Minishell..."
	@$(CC) $(OBJS) $(INC) -o $(NAME) -l readline

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS)

fclean: clean
	@echo "Cleaning Minishell..."
	@rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re