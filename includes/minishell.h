#ifndef MINISHELL_H
# define MINISHELL_H

/* 
INDEX	TYPE	DESCRIPTION
1		infile	infile
2		outfile	outfile
3		<		redir infile replace
4		>		redir outfile replace
5		<<		redir infile append
6		<<		redir outfile append
7		|		pipe
8		$		variable
9		cmd		commande
10		args	commande args
*/

/*used for printf, perror */
# include <stdio.h>
/*used for malloc, free, exit, getenv */
# include <stdlib.h>
/*used for access, fork, read, write, close, getcwd, chdir, execve, dup, dup2,
 pipe, isatty, ttyname, ttyslot */
# include <unistd.h>
/*used for stres (fork, wait, etc.)*/
# include <sys/types.h>
/*used for stat, lstat, fstat */
# include <sys/stat.h>
/*usedd to retrieve resource usage information(wait3, wait4)*/
# include <sys/resource.h>
/*used for open et les options de contrôle de fichier */
# include <fcntl.h>
/*used for signal, sigaction, sigemptyset, sigaddset, kill */
# include <signal.h>
/*used for readline, rl_on_new_line, rl_replace_line, rl_redisplay */
# include <readline/readline.h>
/*used for rl_clear_history, add_history */
# include <readline/history.h>
/*used for PATH_MAX (with getcwd) */
# include <limits.h>
/*used for ioctl */
# include <sys/ioctl.h>
/*used for tcsetattr, tcgetattr */
# include <termios.h>
/*used for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs */
# include <term.h>

/* Our includes */
# include <stdbool.h>
# include "parser.h"
# include "exec.h"
# include "../libft/includes/libft.h"

# define BLUE "\033[0;34m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

#endif
