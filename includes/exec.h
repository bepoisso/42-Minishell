#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

/**			free.c */
void	free_doubletab(char ***str);
void	free_null(void	**ptr);
void	free_n_tabint(int **tabint, int n);
void	free_exec(t_base *base);

/**			e_exec.c */
int		start_exec_cmd(t_cmd *cmd);
char	**extract_paths(void);

/**			handler.c */
void	sig_handler(int signal);

/**			e_check.c */
char	*check_cmd(char **env_list, t_cmd *cmd);
int		file_check(char *file, int type, t_base *base);

/**			e_tolkien */
int		sauron(t_base *base);

/**			e_start_exec.c */
int		prepare_exec(t_cmd *actual_cmd, t_token *act_tok, t_base *base);
void	close_fds(int keep_open, int in, int out, t_base *base);

#endif
