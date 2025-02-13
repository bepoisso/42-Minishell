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
void	sig_int_handler()
{
	printf(""BLUE"Signal CTRL-C received"RESET"\n");
	exit (0);
}


/**
 * sigemptyset(&sa_int.sa_mask)
 * The sigemptyset() function initializes the signal set set to empty, with
 *  all signals excluded from the set.
 * you guarantee that this mask does not contain any signal. The sa_mask field
 *  is used to indicate which signals should be temporarily blocked while the
 *  signal handler is running. By flushing it, you ensure that no signals are
 *  blocked by default while your handler for SIGINT is running. You can then,
 *  if necessary, add specific signals to block using sigaddset.
 */
int	sig_handler(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = sig_int_handler;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("sigaction SIGINT");
        exit(EXIT_FAILURE);
    }
	
	sa_quit.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("sigaction SIGQUIT");
		exit(EXIT_FAILURE);
	}
	while (1)
		sleep(1);
	return (0);
}
/*struct sigaction {
	void     (*sa_handler)(int);
	void     (*sa_sigaction)(int, siginfo_t *, void *);
	sigset_t sa_mask;
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

int	main(void)
{
	//sig_handler(str);
	char * str;
	while (1)
	{
	str = readline("Enter a string: ");
	if (!str)
	{
		printf("Exit\n");
		break;
	}
	if (*str)
		add_history(str);
	printf("You entered: %s\n", str);
	}
	return (0);
}