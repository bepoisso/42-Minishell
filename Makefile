#_________________COLORS_________________

PURPLE	= \033[0;35m
YELLOW	= \033[0;93m
RESET	= \033[0m

#_________________VARIABLE_________________

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -g -I$(INC_DIR) #-Werror#
LIBS= -lreadline -lhistory -L./libft -lft
VALARGS = --suppressions=./valgrind.sup --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes --track-fds=yes --show-reachable=yes --child-silent-after-fork=yes -s
MAKEFLAGS += --no-print-directory

#_________________FILES_________________

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./includes

SRC_FILES = e_check.c\
			e_exec.c\
			e_file_redir.c\
			e_free.c\
			e_free2.c\
			e_start_exec.c\
			e_tolkien.c\
			sighand.c\
			p_parser.c\
			p_utils.c\
			p_error.c\
			p_token.c\
			p_quote.c\
			p_init.c\
			p_cmd.c\
			p_main.c\
			p_header.c\
			d_print_struct.c\
			b_pwd.c\
			b_builtin.c\
			b_echo.c\
			b_env.c\
			b_export.c\
			b_unset.c\
			b_cd.c\
			p_dolars.c\

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

val:  re
		valgrind $(VALARGS) ./$(NAME)

exec: re
		./$(NAME)

debug: re
		gdb -tui -q ./$(NAME)
	
.PHONY: all clean fclean re val exec debug
