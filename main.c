/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:40:04 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/09 10:17:04 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	openfiles(t_pipex *pipex)
{
	pipex->firstcmd = 1;
	pipex->fd_in = open(pipex->argv[1], O_RDONLY);
	if (pipex->fd_in < 0)
		error_exit("Error: open infile failed\n", 0);
	pipex->fd_out = open(pipex->argv[pipex->argc - 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_out < 0)
		error_exit("Error: open outfile failed\n", pipex->fd_in);
}

void	execute_cmd(t_pipex *pipex, int i)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(pipex->argv[i], ' ');
	if (!cmd)
		exit(1);
	path = findpath(pipex, cmd);
	if (!path)
	{
		freesplit(cmd);
		error_exit("Error: command not found\n", 0);
	}
	execve(path, cmd, pipex->envp);
	free(path);
	freesplit(cmd);
	error_exit("Error: execve failed\n", 0);
}

void	pipex_execute(t_pipex *pipex, int i)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		error_exit("Error: pipe failed\n", 0);
	pid = fork();
	if (pid == -1)
		error_exit("Error: fork failed\n", 0);
	if (pid == 0)
	{
		close (fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		execute_cmd(pipex, i);
	}
	else
	{
		close (fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pid;

	pipex.argc = argc;
	pipex.argv = argv;
	pipex.envp = envp;
	if (argc < 5)
		error_exit("Error: Too few arguments\n", 0);
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
		here_doc(&pipex);
	else
		openfiles(&pipex);
	dup2(pipex.fd_in, STDIN_FILENO);
	close(pipex.fd_in);
	while (++pipex.firstcmd < (argc - 2))
		pipex_execute(&pipex, pipex.firstcmd);
	dup2(pipex.fd_out, STDOUT_FILENO);
	close(pipex.fd_out);
	pid = fork();
	if (pid == -1)
		error_exit("Error: fork failed\n", 0);
	if (pid == 0)
		execute_cmd(&pipex, argc - 2);
	else
		waitpid(pid, NULL, 0);
}
