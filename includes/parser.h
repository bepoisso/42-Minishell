#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* 
	Struct for the cmd
*/
typedef struct s_cmd
{
	char	**cmd1;
	char	*path_cmd1;
	char	**env;
}	t_cmd;

#endif
