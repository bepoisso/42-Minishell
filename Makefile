#_________________COLORS_________________

PURPLE	= \033[0;35m
YELLOW	= \033[0;93m
RESET	= \033[0m

#_________________VARIABLE_________________

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I$(INC_DIR)
LIBS		= -lreadline -lhistory -L./libft -lft
VALARGS		= --suppressions=./valgrind.sup --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes --track-fds=yes --show-reachable=yes -s
SVALARGS	= --suppressions=./valgrind.sup --leak-check=full --track-origins=yes --show-leak-kinds=all --trace-children=yes --track-fds=yes --show-reachable=yes -s --log-file=test_valgrind.log
MAKEFLAGS	+= --no-print-directory

#_________________FILES_________________

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./includes

SRC_FILES = b_builtin.c\
			b_cd.c\
			b_cd_utils1.c\
			b_cd_utils2.c\
			b_echo.c\
			b_env.c\
			b_export.c\
			b_export_utils.c\
			b_pwd.c\
			b_unset.c\
			e_check.c\
			e_env_cpy.c\
			e_env_utils.c\
			e_exec.c\
			e_file_redir.c\
			e_free.c\
			e_free2.c\
			e_start_exec.c\
			e_start_exec_utils.c\
			e_start_exec_utils2.c\
			e_tolkien.c\
			e_utils.c\
			sighand.c\
			d_print.c\
			p_parser.c\
			p_utils.c\
			p_error.c\
			p_token.c\
			p_quote.c\
			p_init.c\
			p_cmd.c\
			p_main.c\
			p_header.c\
			p_dolars.c\
			p_readline.c\
			e_expans.c\
			p_lexer.c\

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

valsilent:
		valgrind $(SVALARGS) ./$(NAME)

exec: re
		./$(NAME)

debug: re
		gdb -tui -q ./$(NAME)
	
.PHONY: all clean fclean re val exec debug
