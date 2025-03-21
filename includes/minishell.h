#ifndef MINISHELL_H
# define MINISHELL_H

/*			used for bool type*/
# include <stdbool.h>
# include <limits.h>

/*			Our includes */
# include "../libft/includes/libft.h"
# include "parser.h"
# include "exec.h"
# include "builtins.h"

extern int g_exit_status;
/* 
INDEX	TYPE	DESCRIPTION
0		space	ignore
1		infile	infile
2		outfile	outfile
3		<		redir infile replace
4		>		redir outfile replace
5		<<		redir infile append
6		>>		redir outfile append
7		|		pipe
9		cmd		commande
10		args	commande args
11		quote	like "" & ''
*/

/*used forft_printf, perror */
# include <stdio.h>
/*			used for malloc, free, exit, getenv */
# include <stdlib.h>
/*			used for access, fork, read, write, close, getcwd,
 chdir, execve, dup, dup2, pipe, isatty, ttyname, ttyslot */
# include <unistd.h>
/*			used for strerror */
# include <string.h>
/*			used for errno (used with perror, strerror) */
# include <errno.h>
/*			used for wait, waitpid, wait3, wait4*/
# include <sys/wait.h>
/*			used for system types (fork, wait, etc.)*/
# include <sys/types.h>
/*			used for stat, lstat, fstat */
# include <sys/stat.h>
/*			used to retrieve resource usage information(wait3, wait4)*/
# include <sys/resource.h>
/*			used for open et les options de contrôle de fichier */
# include <fcntl.h>
/*			used for signal, sigaction, sigemptyset, sigaddset, kill */
# include <signal.h>
/*			used for readline, rl_on_new_line, rl_replace_line, rl_redisplay */
# include <readline/readline.h>
/*			used for rl_clear_history, add_history */
# include <readline/history.h>
/*			used for PATH_MAX (with getcwd) */
# include <limits.h>
/*			used for ioctl */
# include <sys/ioctl.h>
/*			used for tcsetattr, tcgetattr */
# include <termios.h>
/*			used for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs */
# include <term.h>

# define BLUE "\001\033[0;34m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[0;32m\002"
# define YELLOW "\001\033[0;33m\002"
# define CYAN "\001\033[0;36m\002"
# define VIOLET "\001\033[0;35m\002"
# define RESET "\001\033[0m\002"
# define BLUE_BOLD "\001\033[1;34m"
# define RED_BOLD "\001\033[1;31m"
# define GREEN_BOLD "\001\033[1;32m"
# define YELLOW_BOLD "\001\033[1;33m"
# define CYAN_BOLD "\001\033[1;36m"
# define VIOLET_BOLD "\001\033[1;35m"


# define PATH_MAX 4096
# define DELAY_TIME 200000
# define DELAY_DOT 20000000

#endif
