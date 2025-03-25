#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
/**DEBUG 
 * set follow-fork-mode parent   # Continue de suivre le parent après un fork
 * set follow-fork-mode child    # Passe au processus enfant après un fork
 * set detach-on-fork on
 * set detach-on-fork off permet de suivre les deux
 * info inferiors liste les forks
 * inferior nb bascule sur le fork nb
 * info threads
 * set non-stop on : si multithread, permet de continuer apres un point d'arret
 *  plutot que d'arreter
 * valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all
 *  --trace-children=yes --track-fds=yes --suppressions=./valgrind.sup
 * valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all
 *  --log-file=test_valgrind.log ./minishell
 * <<1 cat -e | <<2 ls -la  |  grep dr  | sort | cat -e | rev | cat -e >
 *  outfile > outfile2
 */

# define HRDOC_FILE ".hrdoc_temp"
# define SIZEOFLINE 1000
# define MAXNAME 1000

typedef struct s_here
{
	int				fd;
	char			*line;
}	t_here;

/**			e_check.c */
int		count_forks(t_base *base);
char	*check_cmd(t_token *actual, t_base *base);

/**			e_env_cpy.c */
char	**env_cpy(void);
char	*shlvl_modifier(char **environ, int i);

/**			e_env_utils.c */
int		search_var_in_env(char **env, char *search);
char	*search_data_in_env(char **env, char *search);
char	**add_var_in_env(char **env, char *data);
int		search_empty(char **env);
char	**extract_paths(t_base *base);

/**			e_exec.c */
void	init_exec(t_base *base);

/**			e_expnse.c */
void	expanse(t_token *tokens, t_dollar *dollars);
int		give_me_dols(char *s, int nbr);

/**			e_file_redir.c */
char	*add_in_command(t_base *base);
int		handle_hrdoc(t_token *tokens, t_base *base);
int		filechk(t_token *token, int type, t_base *base, t_cmd *cmd);

/**			e_free.c */
void	free_n_tabint(int **tabint, int n);
void	free_cmd_list(t_cmd *cmd);
void	free_token_list(t_token *tk);
void	free_dollar_list(t_dollar *dollar);
void	free_base(t_base *base);

/**			e_free2.c */
void	free_null(void	**ptr);
void	free_doubletab(char ***str);
void	clean_exit(t_base *base);

/**			e_start_exec_utils.c */
int		handle_redirections(t_token *token, t_cmd *cmd);
void	close_inpt_outp(t_cmd *actualcmd);
void	close_opend_fds_builtins(t_cmd *actualcmd, t_base *base);

/**			e_start_exec_utils2.c */
int		handle_redirec_alone(t_token *token);
void	messages_heredeoc(int hrdoc_size, char *data);

/**			e_start_exec.c */
int		prepare_exec(t_token *actual, t_base *base);
void	close_fds(t_base *base, t_cmd *actualcmd);

/**			e_tolkien */
void	sauron(t_base *base, int cmd_found, int redir_found);

/**			e_utils.c */
int		ft_strslen(char **strs);
char	*ft_strnjoin(char *str, ...);
char	*ft_strdup_protected(const char *s);

/**			sighand.c */
void	sig_handler(int signal);
void	sig_quit_handler(int signal);

#endif
