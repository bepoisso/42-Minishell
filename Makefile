#_________________COLORS_________________

PURPLE	= \033[0;35m
YELLOW	= \033[0;93m
RESET	= \033[0m

#_________________VARIABLE_________________

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -g -I$(INC_DIR) #-Werror#
LIBS= -lreadline -lhistory -L./libft -lft
VALARGS = --suppressions=./valgrind.sup --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes --track-fds=yes
MAKEFLAGS += --no-print-directory

#_________________FILES_________________

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./includes

SRC_FILES = e_exec.c \
			p_main.c\
			p_parser.c\
			p_utils.c\
			p_error.c\
			p_token.c\
			p_quote.c\
			e_free.c\
			p_init.c\
			p_cmd.c\

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

#_________________RULES_________________

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
		@echo "Create Program		✅"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
		@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)
		@make -C ./libft

clean:
		@rm -rf $(OBJ_DIR)
		@make clean -C ./libft
		@echo "Clean Program Objs	✅"

fclean: clean
		@rm -f $(NAME)
		@make fclean -C ./libft
		@echo "Clean Program		✅"

re: fclean all

val: 
		valgrind $(VALARGS) ./$(NAME)

exec: re
		./$(NAME)

debug: re
		gdb -tui -q ./$(NAME)
	
.PHONY: all clean fclean re val exec debug
