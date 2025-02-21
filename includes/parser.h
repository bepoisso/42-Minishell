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
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

/**
 * Struct for the token
 * j'ai ajoute index_pipe ca va m'aider a gerer naviguer dans le tableau de
 * pipes, comme ca qund je navigue dans la liste et que j'arrive sur un pipe,
 *  je sais comment le gerer avec le tableau de pipes
*/
typedef struct s_token
{
	int				id;
	char			*data;
	int				index_pipe;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/* 
	Struct for the main things
*/
typedef struct s_base
{
	int				exit_code;
	int				count_forks;
	int				count_pipe;
	int				**pipes;
	char			**path_list;
	t_cmd			*cmds;
	t_token			*token;
}	t_base;

void	ft_error(char *s, int code, t_base *base);
t_token	*parser(char *str, char **env);
t_token	*tokenizer(char *s);
void	print_tokens(t_token *tokens);
int		open_quote(char *str);
int		skip_quote(char *s, int i);

#endif
