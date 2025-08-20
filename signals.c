#include <signal.h> //to use signals
#include <stddef.h> //to use NULL

volatile int	g_signal_received = 0;

void	signal_handler(int sig)
{
	g_signal_received = sig;
}

int	init_signals(void)
{
	struct sigaction	sa;
	sa.sa_handler = signal_handler;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (-1);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (0);
}