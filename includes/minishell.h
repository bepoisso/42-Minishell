#ifndef MINISHELL_H
# define MINISHELL_H

/*used for printf, perror */
# include <stdio.h>
/*used for malloc, free, exit, getenv */
# include <stdlib.h>
/*used for access, fork, read, write, close, getcwd, chdir, execve, dup, dup2,
 pipe, isatty, ttyname, ttyslot */
# include <unistd.h>
/*used for strerror */
# include <string.h>
/*used for errno (used with perror, strerror) */
# include <errno.h>
/*used for wait, waitpid, wait3, wait4*/
# include <sys/wait.h>
/*used for system types (fork, wait, etc.)*/
# include <sys/types.h>
/*used for stat, lstat, fstat */
# include <sys/stat.h>
/*used to retrieve resource usage information(wait3, wait4)*/
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
