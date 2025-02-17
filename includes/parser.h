#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* 
	Struct for the cmd
*/
typedef struct s_cmd
{
	char	**cmd;
	char	*path_cmd;
	bool	builtin;
	struct s_cmd *next;
	struct s_cmd *prev;
}	t_cmd;

/* 
	Struct for the token
*/
typedef struct s_token
{
	int				token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/* 
	Struct for the main things
*/
typedef struct s_base
{
	char	*infile;
	char	*outfile;
	int		exit_code;
	t_cmd *cmd;
	t_token	*token;
}	t_base;


void	ft_error(char *s, int code, t_base base);
void	parser(char *str, char **env);

#endif
