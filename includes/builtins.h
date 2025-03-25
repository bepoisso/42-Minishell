
#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/**				b_builtins.c */
int		exec_builtins(t_token *actual);
void	identify_builtin(t_cmd *cmd);

int		builtin_env(t_token *actual_tok);
int		builtin_pwd(t_base *base);
int		builtin_echo(t_base *base, t_token *actual_tok);

/**				b_exit.c */
int		builtin_exit(t_token *actual);

/**				b_export.c */
int		builtin_export(t_token *actual_tok);

/**				b_export_utils.c */
void	put_xport(char **env);
int		check_xport_arg(char *cmd, char *name, t_base *base);

/**				b_export_utils2.c */
int		is_ok(int c);
int		namelen(char *arg);
char	*xtract_var_name(char *data);
int		search_equal(const char *s);

/**				b_cd.c */
int		builtin_cd(t_token *actual_tok, t_base *base);

/**				b_cd_utils1.c */
int		go_back(t_base *base);
int		update_oldpwd(char *new_data, t_base *base);
int		update_pwd(char *new_data, t_base *base);
int		cd_dot(t_base *base);

/**				b_cd_utils2.c */
int		go_before(t_base *base);

/**				b_unset.c */
int		builtin_unset(t_token *actual_tok);

#endif
