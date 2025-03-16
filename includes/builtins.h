#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/**				b_builtins.c */
void	exec_builtins(t_token *actual);

void	builtin_env(t_token *actual_tok);
void	builtin_pwd(t_base *base);
void	builtin_echo(t_token *actual_tok);
//void	builtin_exit(t_base *base);
void	builtin_export(t_token *actual_tok);

/**				b_cd.c */
char	*search_in_env(char **env, char * search);
int		sizeof_db_tab(char **array);
void	builtin_cd(t_token *actual_tok, t_base *base);
//t_var	*search_in_var(t_var *var, char *search);

/**				b_unset.c */
int	builtin_unset(t_token *actual_tok);

#endif