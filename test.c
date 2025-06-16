#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
	char *line;
	int pid = fork();
	int fdhistory = open("history.log" , O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (pid == 0)
		execve("/bin/bash", (char *[]){"sh", "-c", "clear", NULL}, envp);
	else
		waitpid(pid, NULL, 0);
	while (1)
	{
		line = readline("[minishell] > ");
		if (!strcmp(line, "history"))
		{
			int fdreadhistory = open("history.log", O_RDONLY);
			char buffer[10000];
			read(fdreadhistory, buffer, 10000);
			for (int i = 0; buffer[i]; i++)
				write(1, &buffer[i], 1);
			close(fdreadhistory);
			write(fdhistory, line, strlen(line));
			write(fdhistory, &"\n", 1);
			continue;
		}
		if (!strcmp(line, "exit"))
		{
			free (line);
			exit (0);
		}
		write(fdhistory, line, strlen(line));
		write(fdhistory, &"\n", 1);
		int pid = fork();
		if (pid == 0)
			execve("/bin/bash", (char *[]){"sh", "-c", line, NULL}, envp);
		else
			waitpid(pid, NULL, 0);
		free (line);
	}
}