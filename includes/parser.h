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

/**
 * 
 */
typedef struct s_token
{
	int				id;
	char			*data;
	struct s_cmd	*cmd;
	bool			literal;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_base	*base;
}	t_token;

typedef struct s_dollar
{
	char	*name;
	char	*data;
	bool	literal;
	struct s_dollar *prev;
	struct s_dollar *next;
}	t_dollar;

/**
 * Struct for the main things
 */
typedef struct s_base
{
	char			**env;
	char			*input;
	int				exit_code;
	int				count_forks;
	char			**path_list;
	pid_t			lastpid;
	t_cmd			*cmds;
	t_token			*token;
	t_dollar		*dollars;
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
void	handling_dollar(t_token *tokens, t_base *base);
int		check_double_pippe(t_token *tokens);
void	print_dollar(t_base *base);


#endif
