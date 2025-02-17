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
	char			*infile;
	char			*outfile;
	t_cmd			*cmd;
	t_token			*token;
}	t_base;

#endif