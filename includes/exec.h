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
 *  plutot aue d'arreter
 * valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all  --trace-children=yes --track-fds=yes --suppressions=./valgrind.sup ./minishell 
 * 
 * cat < input.txt | sort > out.txt
 * cat < input.txt | sort > out.txt | cat Cette commande n'affiche rien dans
 *  bash mais fonction sous zsh
 */

/**			free.c */
void	free_doubletab(char ***str);
void	free_null(void	**ptr);
void	free_n_tabint(int **tabint, int n);
void	free_cmd_list(t_cmd *cmd);
void	free_token_list(t_token *tk);
void	free_base(t_base *base);
void	clean_exit(t_base *base, int exit_code);

/**			e_exec.c */
char	**extract_paths(void);

/**			handler.c */
void	sig_handler(int signal);

/**			e_check.c */
int		wait_rings(t_base *base);
char	*check_cmd(char **env_list, char *cmd);
int		filechk(char *file, int type, t_base *base);
int		count_forks(t_base *base);

/**			e_tolkien */
int		sauron(t_base *base);

/**			e_start_exec.c */
void	prepare_exec(t_cmd *actual_cmd, t_token *act_tok, t_base *base);
void	cls_pipes(int keep_open, int in, int out, t_base *base);

/**			e_file_redir.c */
int		file_redir(t_token *tok, t_base *base);

#endif
