NAME	:= minishell

# Compiler
CC	:=	cc
CFLAGS	:=	-Wextra -Wall -Werror -g3
INC		= -I ./include/

# Libft
LIBFT_PATH	:=	./lib/libft/
LIBFT_NAME	:=	libft.a
LIBFT		:=	$(LIBFT_PATH)$(LIBFT_NAME)

# Source
SRCS	:=	src/parser_test.c \
			src/parser/parser.c \
			src/parser/lexer.c \
			src/parser/lexer_utils.c \
			src/parser/parser_utils_1.c \
			src/parser/parser_utils_2.c \
			src/parser/expander.c \


# Objects
OBJS	:=	$(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

# Making Libft
$(LIBFT):
	@echo "Making Libft..."
	@make -sC $(LIBFT_PATH)

%.o: %c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)

# Compiling Minishell
$(NAME): $(OBJS)
	@echo "Compiling Minishell..."
	@$(CC) $(OBJS) $(LIBFT) $(INC) -o $(NAME) -l readline

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS)
	@make clean -sC $(LIBFT_PATH)


fclean: clean
	@echo "Cleaning Minishell..."
	@rm -rf $(NAME)
	@make fclean -sC $(LIBFT_PATH)

re: fclean all

.PHONY: all, clean, fclean, re