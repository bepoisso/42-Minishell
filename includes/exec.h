
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
 * ls -la | grep dr | sort | rev | cat -e | rev | cat -e > outfile
 * < infile sort > outfile.txt commande de test
 * cat < infile.txt | sort > out.txt
 * cat < input.txt | sort > out.txt | cat Cette commande n'affiche rien dans
 *  bash mais fonction sous zsh
 * ls -la | grep dr | sort | rev > outfile
 * <<1 ls -la | grep dr | sort | cat -e | rev
 */

# define HRDOC_FILE ".hrdoc_temp"
# define SIZEOFLINE 1000
# define MAXNAME 1000

typedef struct s_here
{
	int				fd;
	char			*line;
}	t_here;


/**			free.c */
void	free_doubletab(char ***str);
void	free_null(void	**ptr);
void	free_n_tabint(int **tabint, int n);
void	free_cmd_list(t_cmd *cmd);
void	free_token_list(t_token *tk);
void	free_base(t_base *base);
void	clean_exit(t_base *base);

/**			e_exec.c */
void	init_exec(t_base *base);

/**			handler.c */
void	sig_handler(int signal);
void	sig_quit_handler(int signal);

/**			e_check.c */
char	*check_cmd(t_token *actual, t_base *base);
int		count_forks(t_base *base);

/**			e_tolkien */
void	sauron(t_base *base, int cmd_found, int redir_found);

/**			e_start_exec.c */
int     prepare_exec(t_token *actual, t_base *base);

/**			e_start_exec_utils.c */
void	close_inpt_outp(t_cmd *actualcmd);
int		handle_redirections(t_token *token, t_cmd *cmd);
void	close_opend_fds_builtins(t_cmd *actualcmd, t_base *base);

/**			e_start_exec_utils2.c */
int		handle_redirec_alone(t_token *token);

/**			e_start_exec_utils3.c */
void	messages_heredeoc(int hrdoc_size, char *data);
int	    open_hrdoc_file(void);
char	*read_heredoc_input(t_token *tokens);
int	    process_heredoc_input(char *line, t_token *tokens, int fd);
int     handle_hrdoc_no_cmd(t_token *tokens, t_base *base);

/**			e_file_redir.c */
char	*add_in_command(t_base *base);
int	    handle_hrdoc(t_token *tokens, t_base *base);

int		filechk(t_token *token, int type, t_base *base, t_cmd *cmd);

/**			e_utils.c */
void	ft_put_arraystr(char **array);
int		ft_strslen(char **strs);
char	*ft_strnjoin(char *str, ...);
char	*ft_strdup_protected(const char *s);

/**			e_env_utils.c */
int		search_var_in_env(char **env, char *search);
char	*search_data_in_env(char **env, char *search);
char	**add_var_in_env(char **env, char *data);
int		search_empty(char **env);
char	**extract_paths(t_base *base);

/**			e_env_cpy.c */
char	**env_cpy(void);
char	*shlvl_modifier(char **environ, int i);

/**			e_expnse.c */
void	expanse(t_token *tokens, t_dollar *dollars);

#endif
