/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:35:04 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/11 11:39:12 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO error messages
void	exec_builtin(t_cmds *cmds, t_env *env)
{
	if (!ft_strcmp(cmds->cmd, "echo"))
		echo_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "pwd"))
		pwd_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "cd"))
		cd_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "exit"))
		exit_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "env"))
		env_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "export"))
		export_mini(cmds);
}

int	 isbuiltin(t_cmds *cmds)
{
	if (!ft_strcmp(cmds->cmd, "echo") || !ft_strcmp(cmds->cmd, "cd")\
|| !ft_strcmp(cmds->cmd, "exit") || !ft_strcmp(cmds->cmd, "pwd")\
|| !ft_strcmp(cmds->cmd, "export") || !ft_strcmp(cmds->cmd, "env"))
		return (1);
	return (0);
}

void	redirect_infiles(t_cmds *cmds, t_env *env, int *stdin_dup, int *stdout_dup)
{
	int fd;

	if (cmds->infile)
	{
		fd = open(cmds->infile, O_RDONLY);
		if (fd < 0)
			return ;
		*stdin_dup = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmds->outfile)
	{
		if (cmds->append)
			fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return ;
		*stdout_dup = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	restore_stdio(int stdin_dup, int stdout_dup)
{
	if (stdin_dup != -1)
	{
		dup2(stdin_dup, STDIN_FILENO);
		close(stdin_dup);
	}

	if (stdout_dup != -1)
	{
		dup2(stdout_dup, STDOUT_FILENO);
		close(stdout_dup);
	}
}
// TODO FIX EXECVE ERROR CLEANUP
void	exec_single(t_cmds *cmds, t_env *env)
{
	int stdin_dup;
	int stdout_dup;
	pid_t   pid;

	stdin_dup = -1;
	stdout_dup = -1;

	redirect_infiles(cmds, env, &stdin_dup, &stdout_dup);
	if (isbuiltin(cmds))
		exec_builtin(cmds, env);
	else
	{
		pid = fork();
		if (!pid)
		{
			execve(cmds->cmdpath, cmds->args, NULL);
			write(2, "ERROR EXECVE\n", 13);
			exit(1);
		}
		waitpid(pid, NULL, 0);
	}
	restore_stdio(stdin_dup, stdout_dup);
}

int	pipe_setup(int pipefd[2])
{
	if (pipe(pipefd) == -1) 
	{
		write(2, "ERROR PIPE FAIL\n", 16);
		return (1);
	}
	return (0);
}

void	exec_pipes(t_cmds *cmds, t_env *env)
{
	
}
//TODO ERROR HNADLE
void	execute_cmd(t_cmds *cmds, t_env *env)
{
	int pipefd[2];
	int fdin;

	while (cmds)
	{
		if (cmds->ispiped && pipe_setup(pipefd) == 1)
		{
			write(2, "Error msg\n", 10);
			return ;
		}
		if (!cmds->ispiped)
			exec_single(cmds, env);
		else
			exec_pipes();
		cmds = cmds->next;
	}
}