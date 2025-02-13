#_________________COLORS_________________

PURPLE	= \033[0;35m
YELLOW	= \033[0;93m
RESET	= \033[0m

#_________________VARIABLE_________________

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I./libft/includes
LIBS= -lreadline -lhistory -L./libft -lft
VALARGS = --supressions=./valgrind.sup --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes --track-fds=yes
MAKEFLAGS += --no-print-directory

#_________________FILES_________________

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./includes

SRC_FILES = e_exec.c\


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

clean:
		@rm -rf $(OBJ_DIR)
		@echo "Clean Program Objs	✅"

fclean: clean
		@rm -f $(NAME)
		@echo "Clean Program		✅"

re: fclean all

val: re
		valgrind $(VALARGS) ./$(NAME)

exec: re
		./$(NAME)

debug: re
		gdb -tui -q ./$(NAME)

.PHONY: all clean fclean re