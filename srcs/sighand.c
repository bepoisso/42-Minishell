#include "../includes/minishell.h"

/**
 * @brief Signal handler function for SIGINT (CTRL-C)
 * 
 * This function is called when a SIGINT signal (CTRL-C) is received.
 * It prints a blue-colored message indicating that CTRL-C was received,
 * followed by resetting the color to default.
 * 
 * @return void
 */
/* void	sig_int_handler(void)
{
	printf(""BLUE"Signal CTRL-C received"RESET"\n");
	exit (0);
} */
void	sig_handler(int signal)
{
	if (waitpid(-1, NULL, WNOHANG) == - 1)
	{
		if (signal == SIGINT)
		{
			ft_printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_exit_status = 130;
		}
	}
}
void	sig_quit_handler(int signal)
{
	printf("Signal %d reçu\n", signal);
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*struct sigaction {
	void     (*sa_handler)(int);
	void     (*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t sa_mask;empty
	int      sa_flags; SA_SIGINFO doit etre defini pour utiliser sa_sigaction
	plutot que sa_handler
};
siginfo_t {
	int      si_signo;    Signal number
	int      si_errno;    An errno value
	int      si_code;     Signal code
	int      si_trapno;   Trap number that caused
							 hardware-generated signal
							 (unused on most architectures)
	pid_t    si_pid;      Sending process ID
	uid_t    si_uid;      Real user ID of sending process
	int      si_status;   Exit value or signal
	clock_t  si_utime;    User time consumed
	clock_t  si_stime;    System time consumed
	sigval_t si_value;    Signal value
	int      si_int;      POSIX.1b signal
	void    *si_ptr;      POSIX.1b signal
	int      si_overrun;  Timer overrun count; POSIX.1b timers
	int      si_timerid;  Timer ID; POSIX.1b timers
	void    *si_addr;     Memory location which caused fault
	int      si_band;     Band event
	int      si_fd;       File descriptor
};
*/
// % cc -g -lreadline sighand.c