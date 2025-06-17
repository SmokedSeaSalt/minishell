#include <signal.h>
#include <stdio.h>
#include <unistd.h>


// Global variable to store the received signal number
// So it can easily be used in the main
volatile sig_atomic_t signal_received = 0;

void signal_handler(int sig)
{
	printf("received signal %d\n", sig);
	signal_received = sig;
}

// | Key      | Signal/Action | Effect at Prompt             | Effect During Running Command  |
// | -------- | ------------- | ---------------------------- | ------------------------------ |
// | `Ctrl-C` | `SIGINT`      | Cancels current input        | Interrupts the process         |
// | `Ctrl-\` | `SIGQUIT`     | Usually ignored by Bash      | Terminates process + core dump |

// not really a signall but sends ascii code 4 as a return val
// | `Ctrl-D` | `EOF`         | Exits shell if line is empty | Ends input to `stdin`          |
int main() {
    // Register signal handler
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Handle SIGINT and SIGTERM
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);

	printf("PID: %d\n", getpid());
    printf("Program running. Press Ctrl+C to send SIGINT or kill to send SIGQUIT.\n");
	printf("To actually stop this send SIGTERM via kill\n");
    // Main loop
    while (1) {
        if (signal_received != 0) {
            printf("Received signal: %d\n", signal_received);
            // Reset signal_received to allow further signal handling if needed
            signal_received = 0;
        }

        // Simulate work
        sleep(1);
    }

    return 0;
}