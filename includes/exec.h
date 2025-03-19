
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
 * 
 * ls -la | grep dr | sort | rev | cat -e > outfile
 * < infile sort > outfile.txt commande de test
 * cat < infile.txt | sort > out.txt
 * cat < input.txt | sort > out.txt | cat Cette commande n'affiche rien dans
 *  bash mais fonction sous zsh
 */

# define HRDOC_FILE ".hrdoc_temp"
# define SIZEOFLINE 1000

/**			free.c */
void	free_doubletab(char ***str);
void	free_null(void	**ptr);
void	free_n_tabint(int **tabint, int n);
void	free_cmd_list(t_cmd *cmd);
void	free_token_list(t_token *tk);
void	free_base(t_base *base);
void	clean_exit(t_base *base, int exit_code);

/**			e_exec.c */
char	**extract_paths(t_base *base);

/**			handler.c */
void	sig_handler(int signal);
void	sig_quit_handler(int signal);

/**			e_check.c */
int		wait_rings(t_base *base);
char	*check_cmd(t_token *actual, t_base *base);
int		count_forks(t_base *base);

/**			e_tolkien */
int		sauron(t_base *base);

/**			e_start_exec.c */
int     prepare_exec(t_token *actual, t_base *base);

/**			e_start_exec_utils.c */
void	close_inpt_outp(t_cmd *actualcmd);
int		handle_redirections(t_token *token, t_base *base, t_cmd *cmd);
void	close_opend_fds_builtins(t_cmd *actualcmd, t_base *base);

/**			e_start_exec_utils2.c */
int		handle_redirec_alone(t_token *token);

/**			e_file_redir.c */
char	*add_in_command(t_base *base);
int		filechk(t_token *token, int type, t_base *base, t_cmd *cmd);



/**			e_utils.c */
int		ft_strslen(char **strs);

/**			e_env_utils.c */
int		search_var_in_env(char **env, char *search);
char	*search_data_in_env(char **env, char *search);
char	**add_var_in_env(char **env, char *data);
int		search_empty(char **env);

/**			e_env_cpy.c */
char	**env_cpy(void);
char	*shlvl_modifier(char **environ, int i);

#endif
