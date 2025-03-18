#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

struct s_base;

/* 
	Struct for the cmd
*/
typedef struct s_cmd
{
	char			**cmd;
	char			*path_cmd;
	bool			builtin;
	int				input;
	int				output;
	int				hrdoc;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_var
{
	char			*name;
	char			*content;
	struct s_var	*next;
	struct s_var	*prev;
}	t_var;

typedef struct s_token
{
	int				id;
	char			*data;
	struct s_cmd	*cmd;
	bool			literal;
	t_var			expanse;
	struct s_base	*base;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;


/**
 * @struct s_base
 * @brief Represents the main structure for the Minishell project, containing
 *        all necessary data for environment management, command execution,
 *        and shell state tracking.
 * 
 * @var s_base::env
 * Array of environment variables as strings.
 * 
 * @var s_base::envir
 * Pointer to a linked list of environment variables (custom structure t_var).
 * 
 * @var s_base::input
 * Stores the current user input string.
 * 
 * @var s_base::tild
 * Stores the tilde (~) expansion value, typically the home directory.
 * 
 * @var s_base::exit_code
 * Stores the exit code of the last executed command.
 * 
 * @var s_base::count_forks
 * Tracks the number of forked processes.
 * 
 * @var s_base::stdin_back
 * Backup of the standard input file descriptor.
 * 
 * @var s_base::stdout_back
 * Backup of the standard output file descriptor.
 * 
 * @var s_base::path_list
 * Array of paths derived from the PATH environment variable.
 * 
 * @var s_base::lastpid
 * Process ID of the last executed child process.
 * 
 * @var s_base::cmds
 * Pointer to a linked list of parsed commands (custom structure t_cmd).
 * 
 * @var s_base::token
 * Pointer to a linked list of tokens (custom structure t_token) generated
 * during input parsing.
 * 
 * @var s_base::envir_nb
 * Number of environment variables stored in the envir linked list.
 */
typedef struct s_base
{
	char			**env;
	t_var			*envir;
	char			*input;
	char 			*tild;
	int				exit_code;
	int				count_forks;
	int				stdin_back;
	int				stdout_back;
	char			**path_list;
	pid_t			lastpid;
	t_cmd			*cmds;
	t_token			*token;
	int				envir_nb;
}	t_base;


void	ft_error(char *s, int code, t_base *base);
int		parser(char *str, t_base *base);
t_token	*tokenizer(char *s, t_base *base);
void	print_tokens(t_token *tokens);
int		open_quote(char *str);
int		skip_quote(char *s, int	i);
void	identify_token(t_token *tokens);
int		get_op_token(char *data, int id);
t_cmd	*parsing_cmd(t_base *base);
void	print_cmd(t_base *base);
void	header(void);
void	identify_builtin(t_cmd *cmd);
int		ft_strcmp(char *s1, char *s2);
void	display_base(t_base *base);
int		ft_isspace(char c);
void	rm_node_token(t_token *token);
t_token	*token_parser(t_token *tokens);
int		check_only_redirect(t_token *tokens, t_base *base);
int		ft_isop(char c);
int		ft_isspace(char c);
int		start_pipe(char *s, t_base *base);
int		no_quote(t_token *tokens);
int		get_redir_io(t_token *token);
void	search_dolars(t_token *tokens);
int		check_double_pippe(t_token *tokens);


#endif
