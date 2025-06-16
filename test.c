#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
	char *line;
	int pid = fork();
	if (pid == 0)
		execve("/bin/bash", (char *[]){"sh", "-c", "clear", NULL}, envp);
	else
		waitpid(pid, NULL, 0);
	while (1)
	{
		line = readline("[minishell] > ");
		int pid = fork();
		if (pid == 0)
			execve("/bin/bash", (char *[]){"sh", "-c", line, NULL}, envp);
		else
			waitpid(pid, NULL, 0);
	}
}