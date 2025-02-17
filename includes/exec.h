#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

void	free_doubletab(char ***str);
void	free_null(void	**ptr);
int		start_exec_cmd(t_cmd *cmd);

#endif
