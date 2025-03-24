#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

struct	s_base;

/* Struct for the cmd */
typedef struct s_cmd
{
	char			**cmd;
	char			*path_cmd;
	bool			builtin;
	int				input;
	int				output;
	int				hrdoc;
	int				bad_fd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

/* Struct Token */
typedef struct s_token
{
	int				id;
	char			*data;
	struct s_cmd	*cmd;
	bool			literal;
	struct s_base	*base;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/* Struct for expansion */
typedef struct s_dollar
{
	char			*name;
	char			*data;
	bool			literal;
	struct s_dollar	*prev;
	struct s_dollar	*next;
}	t_dollar;

/**
 * Struct for the main things
 */
typedef struct s_base
{
	char			**env;
	char			*input;
	char			*tild;
	int				hrdoc_size;
	int				exit_code;
	int				count_forks;
	int				stdin_back;
	int				stdout_back;
	char			**path_list;
	pid_t			lastpid;
	t_cmd			*cmds;
	t_token			*token;
	t_dollar		*dollars;
	int				envir_nb;
}	t_base;

/* LEXER */
int		get_op_token(char *data, int id);
int		skip_quote(char *s, int i);
int		get_redir_io(t_token *token);
t_token	*lexer(char *s, t_base *base);
t_token	*token_parser(t_token *tokens);
void	add_token(t_token **tokens, char *value, bool literal, t_base *base);

/* PARSER */
int		parser(char *str, t_base *base);
void	identify_token(t_token *tokens);
void	identify_builtin(t_cmd *cmd);
t_cmd	*parsing_cmd(t_base *base);

/* UTILS */
int		ft_strcmp(char *s1, char *s2);
int		ft_isspace(char c);
int		ft_isop(char c);
int		ft_isspace(char c);
char	*minitext_rl(char **env, t_base *base);
void	rm_node_token(t_token *token);
void	print_cmd(t_base *base);
void	print_tokens(t_token *tokens);
void	display_base(t_base *base);
void	header(void);
void	print_dollar(t_base *base);
void	free_dollar_list(t_dollar *dollar);

/* ERROR */
int		start_pipe(char *s, t_base *base);
int		open_quote(char *str);
int		check_only_redirect(t_token *tokens, t_base *base);
int		no_quote(t_token *tokens);
int		check_double_pippe(t_token *tokens);
void	ft_error(char *s, int code, t_base *base);

/* EXPANSER */
char	*search_env_var(char *search, char **env, t_base *base);
void	handling_dollar(t_token *tokens, t_base *base);
void	dollar_is_literal(t_dollar *dollars);

#endif
