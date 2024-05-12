NAME	:= minishell

# Compiler
CC	:=	cc
CFLAGS	:=	-Wextra -Wall -Werror -g
INC		= -I ./include/

# Libft
LIBFT_PATH	:=	./lib/libft/
LIBFT_NAME	:=	libft.a
LIBFT		:=	$(LIBFT_PATH)$(LIBFT_NAME)

# Source
SRCS	:=	src/main.c \
			src/parser/parser.c \
			src/parser/lexer.c \
			src/parser/lexer_utils.c \
			src/parser/parser_utils_1.c \
			src/parser/parser_utils_2.c \
			src/parser/expander.c \
			src/parser/expander_utils_1.c \
			src/parser/expander_utils_2.c \
			src/parser/handle_redirections.c \
			src/parser/handle_redirections_utils.c \
			src/parser/heredoc.c \
			src/utils/signal.c \
			src/execute/builtins/cd.c \
			src/execute/builtins/echo.c \
			src/execute/builtins/pwd.c \
			src/execute/builtins/env.c \
			src/execute/builtins/exit.c \
			src/execute/builtins/unset.c \
			src/execute/builtins/export.c \
			src/execute/handlers/builtinsutils.c \
			src/execute/error.c \
			src/execute/execute.c \
			src/execute/handlers/pipeutils.c \
			src/execute/handlers/singlehandler.c \
			src/execute/handlers/multihandler.c \
			src/execute/handlers/multihandlersutils.c \



# Objects
OBJS	:=	$(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

# Making Libft
$(LIBFT):
	@echo "Making Libft..."
	@make -sC $(LIBFT_PATH)
	@make bonus -sC $(LIBFT_PATH)

%.o: %c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC)

# Compiling Minishell
$(NAME): $(OBJS)
	@echo "Compiling Minishell..."
	@$(CC) $(OBJS) $(LIBFT) $(INC) -o $(NAME) -l readline

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS)
	@rm -rf lib/libft/.heredoc
	@make clean -sC $(LIBFT_PATH)


fclean: clean
	@echo "Cleaning Minishell..."
	@rm -rf $(NAME)
	@make fclean -sC $(LIBFT_PATH)

re: fclean all

.PHONY: all, clean, fclean, re