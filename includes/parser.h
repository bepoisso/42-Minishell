#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* 
	Struct for the main things
*/
typedef struct s_base
{
	char	*infile;
	char	*outfile;
	t_cmd *cmd;
	t_token	*token;
}	t_base;

/* 
	Struct for the cmd
*/
typedef struct s_cmd
{
	char	**cmd1;
	char	*path_cmd1;
	bool	bulitin;
	struct s_cmd *next;
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

#endif
