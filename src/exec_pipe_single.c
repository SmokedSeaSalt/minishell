
#include "minishell.h"

void	pipe_single_handle_in(t_cmds *cmds, int fd_in)
{

}

void	pipe_single_handle_out()
{

}

void	single_pipe_execute()
{

}

int	exec_pipe_single(t_cmds *cmds, t_env *env, int fd_in, int fd_out)
{
	pid_t	pid;
	int		fd;
	char	**args;
	char	**envp;

	//TODO CLEANUP
	pid = fork();
	if (!pid)
	{
		set_child_signals();
		//function 1
		if (cmds->permission_denied)
		{
			write(2, "Error: permission denied\n", 25);
			exit_with_val(1, cmds);
		}

		if (cmds->infile)
		{
			fd = open(cmds->infile, O_RDONLY);
			if (fd < 0)
			{
				write(2, "ERROR\n", 6);
				exit(0);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (fd_in != STDIN_FILENO)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		//end function 1
		//function 2
		if (cmds->outfile)
		{
			if (cmds->append)
				fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				write(2, "ERROR\n", 6);
				exit_with_val(1, cmds);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (fd_out != STDOUT_FILENO)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		//end function 2
		if (cmds->ispiped && cmds->info && cmds->info->pipe_read_fd != -1)
			close(cmds->info->pipe_read_fd);
		if (isbuiltin(cmds))
		{
			exec_builtin(cmds);
			exit(0);
		}
		//function 3
		check_access(cmds);
		args = make_args(cmds);
		envp = make_envp(cmds, env);
		execve(cmds->cmdpath, args, envp);
		perror(cmds->cmdpath);
		free(args);
		free_carray(envp);
		exit_with_val(126, cmds);
		// end function 3
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (pid);
}
