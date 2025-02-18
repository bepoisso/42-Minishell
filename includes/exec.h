#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define INFILE "in"
# define OUTFILE "out"

/**			free.c */
void	free_doubletab(char ***str);
void	free_null(void	**ptr);

/**			e_exec.c */
int		start_exec_cmd(t_cmd *cmd);

/**			handler.c */
void	sig_handler(int signal);

#endif
