#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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
}	t_token;

/**
 * Struct for the main things
 */
typedef struct s_base
{
	int				exit_code;
	int				count_forks;
	char			**path_list;
	pid_t			lastpid;
	t_cmd			*cmds;
	t_token			*token;
}	t_base;


void	ft_error(char *s, int code, t_base *base);
int		parser(char *str, t_base *base);
t_token	*tokenizer(char *s, t_base *base);
void	print_tokens(t_token *tokens);
int		open_quote(char *str);
int		skip_quote(char *s, int	i);
void	identify_token(t_base *base);
int		get_op_token(char *data);
t_cmd	*parsing_cmd(t_base *base);
void	print_cmd(t_base *base);
void	pipe_counter(t_base *base);
void	header(void);
void	identify_builtin(t_cmd *cmd);
int		ft_strcmp(char *s1, char *s2);
void	display_base(t_base *base);
int		ft_isspace(char c);
void	rm_node_token(t_token *token);
t_token	*token_parser(t_token *tokens);

#endif
