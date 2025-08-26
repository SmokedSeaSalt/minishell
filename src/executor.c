/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:35:04 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/26 11:54:43 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//TODO error messages
//TODO 1 open fd in all pipes;
char	**make_args(t_cmds *cmds)
{
	int		i;
	char	**args;

	i = 1;
	while (cmds->args && (cmds->args)[i - 1])
		i++;
	args = ft_calloc(sizeof(char *), i + 1);
	args[0] = cmds->cmd;
	if (!cmds->args)
		return (args);
	i = 0;
	while ((cmds->args)[i])
	{
		args[i + 1] = (cmds->args)[i];
		i++;
	}
	return (args);
}

//TODO FREE ALL WHEN EXIT;
char	**make_envp(t_cmds *cmds, t_env *env)
{
	int		envlen;
	int		i;
	char	**envp;
	char	*envval;

	i = 0;
	envlen = env_len(env);
	envp = ft_calloc(sizeof(char *), envlen + 1);
	if (!envp)
		exit_with_val(1, cmds);
	while (env->prev)
		env = env->prev;
	while (env)
	{
		envval = strjoin_char(env->v_name, env->v_val, '=');
		if (!envval)
			exit_with_val(1, cmds);
		envp[i] = envval;
		i++;
		env = env->next;
	}
	return (envp);
}

void	exec_builtin(t_cmds *cmds)
{
	int	exitval;

	if (!ft_strcmp(cmds->cmd, "echo"))
		exitval = echo_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "pwd"))
		exitval = pwd_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "cd"))
		exitval = cd_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "exit"))
		exitval = exit_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "env"))
		exitval = env_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "export"))
		exitval = export_mini(cmds);
	if (!ft_strcmp(cmds->cmd, "unset"))
		exitval = unset_mini(cmds);
	if (cmds->ispiped || (cmds->prev && cmds->prev->ispiped))
		exit_with_val(exitval, cmds);
}

int	isbuiltin(t_cmds *cmds)
{
	if (!ft_strcmp(cmds->cmd, "echo") || !ft_strcmp(cmds->cmd, "cd") \
|| !ft_strcmp(cmds->cmd, "exit") || !ft_strcmp(cmds->cmd, "pwd") \
|| !ft_strcmp(cmds->cmd, "export") || !ft_strcmp(cmds->cmd, "env") \
|| !ft_strcmp(cmds->cmd, "unset"))
		return (1);
	return (0);
}

void	redirect_infiles(t_cmds *cmds, int *stdin_dup, int *stdout_dup)
{
	int	fd;

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

void	exec_single(t_cmds *cmds, t_env *env)
{
	int		stdin_dup;
	int		stdout_dup;
	pid_t	pid;
	char	**args;
	char	**envp;

	stdin_dup = -1;
	stdout_dup = -1;
	redirect_infiles(cmds, &stdin_dup, &stdout_dup);
	if (isbuiltin(cmds))
		exec_builtin(cmds);
	else
	{
		pid = fork();
		if (!pid)
		{
			set_child_signals();
			args = make_args(cmds);
			envp = make_envp(cmds, env);
			execve(cmds->cmdpath, args, envp);
			free_carray(envp);
			perror(cmds->cmd);
			free(args);
			exit_with_val(1, cmds);
		}
		set_signals_ignore();
		waitpid(pid, NULL, 0);
		set_signals_default();
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

//TODO CLEANUP
void	exec_pipe_single(t_cmds *cmds, t_env *env, int fd_in, int fd_out)
{
	pid_t	pid;
	int		fd;
	char	**args;
	char	**envp;

	pid = fork();
	if (!pid)
	{
		set_child_signals();
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
		if (isbuiltin(cmds))
		{
			exec_builtin(cmds);
			exit(0);
		}
		args = make_args(cmds);
		envp = make_envp(cmds, env);
		execve(cmds->cmdpath, args, envp);
		perror(cmds->cmdpath);
		free(args);
		free_carray(envp);
		exit_with_val(1, cmds);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
}

void	exec_pipes(t_cmds *cmds, t_env *env)
{
	int	fd[2];
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	while (cmds && cmds->ispiped)
	{
		if (pipe(fd) == -1)
		{
			write(2, "Error: pipe failed\n", 19);
			exit_with_val(1, cmds);
		}
		fd_out = fd[1];
		exec_pipe_single(cmds, env, fd_in, fd_out);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDIN_FILENO)
			close(fd_out);
		fd_in = fd[0];
		cmds = cmds->next;
	}
	if (cmds)
	{
		fd_out = STDOUT_FILENO;
		exec_pipe_single(cmds, env, fd_in, fd_out);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
	}
	set_signals_ignore();
	while (waitpid(-1, NULL, 0) > 0)
		;
	set_signals_default();
}

void	execute_cmd(t_cmds *cmds, t_env *env)
{
	while (cmds)
	{
		if (!cmds->cmd)
			cmds = cmds->next;
		else if (!cmds->ispiped)
		{
			exec_single(cmds, env);
			cmds = cmds->next;
		}
		else
		{
			exec_pipes(cmds, env);
			while (cmds && cmds->ispiped)
				cmds = cmds->next;
			if (cmds)
				cmds = cmds->next;
		}
	}
}

//TODO HANDLE MALLOC FAIL IN SPLIT
void	find_paths(t_cmds *cmds, t_env *env)
{
	char	**paths;
	int		i;
	char	*currentpath;
	t_info	*info;

	info = ft_calloc(sizeof(t_info), 1);
	info->head = env;
	while (cmds)
	{
		cmds->info = info;
		if (!cmds->cmd)
		{
			if (cmds->infile && cmds->next && !cmds->next->infile)
			{
				cmds->next->infile = cmds->infile;
				cmds->infile = NULL;
			}
			cmds = cmds->next;
			continue ;
		}
		if (isbuiltin(cmds))
		{
			cmds = cmds->next;
			continue ;
		}
		while (env && ft_strcmp("PATH", env->v_name))
			env = env->next;
		if (!env)
		{
			cmds->cmdpath = ft_strndup(cmds->cmd, ft_strlen(cmds->cmd));
			return ;
		}
		paths = ft_split(env->v_val, ':');
		if (!paths)
			return ;
		i = -1;
		while (paths[++i])
		{
			currentpath = strjoin_char(paths[i], cmds->cmd, '/');
			if (!currentpath)
				continue ;
			if (access(currentpath, F_OK) == 0)
			{
				i = -1;
				while (paths[++i])
					free(paths[i]);
				free(paths);
				paths = NULL;
				cmds->cmdpath = currentpath;
				break ;
			}
			free(currentpath);
		}
		if (paths)
		{
			i = -1;
			while (paths[++i])
				free(paths[i]);
			free(paths);
			paths = NULL;
		}
		if (!cmds->cmdpath)
			cmds->cmdpath = ft_strndup(cmds->cmd, ft_strlen(cmds->cmd));
		cmds = cmds->next;
	}
}

// int main(int argc, char **argv, char **envp)
// {
// 	// (void)argc;
// 	// (void)argv;
// 	// (void)envp;
// 	if (argc != 2)
// 		return (write(2, "SEGFAULT\n", 9));
// 	t_env	*env = init_env(envp);
// 	t_cmds *cmds = ft_calloc(sizeof(t_cmds), 1);
// 	(void)argv;
// 	(void)argc;
// 	make_cmds(cmds, env, argv[1]);
// 	find_paths(cmds, env);
// 	execute_cmd(cmds, env);
// 	free_cmds(cmds);
// 	free_env(env);
// }