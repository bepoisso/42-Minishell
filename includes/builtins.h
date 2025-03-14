#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/**		 */
void	exec_builtins(t_token *actual, t_base *base);
char	**env_cpy(void);
void	builtin_env(t_base *base, t_token *actual_tok);
void	builtin_pwd(t_base *base);
void	builtin_echo(t_base *base, t_token *actual_tok);
void	builtin_exit(t_base *base);
void	builtin_cd(t_base *base, t_token *actual_tok);
void	builtin_export(t_base *base, t_token *actual_tok);


#endif