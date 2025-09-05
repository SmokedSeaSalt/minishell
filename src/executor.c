/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:35:04 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/29 16:09:00 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	check_access(t_cmds *cmds)
{
	struct stat	path_stat;

	if (!charinstr('/', cmds->cmdpath))
	{
		write(2, "Error: command not found\n", 25);
		exit_with_val(127, cmds);
	}
	if (access(cmds->cmdpath, F_OK) != 0)
	{
		write(2, "Error: command not found\n", 25);
		exit_with_val(127, cmds);
	}
	if (stat(cmds->cmdpath, &path_stat) != 0)
	{
		write(2, "Error: stat fail\n", 16);
		exit_with_val(126, cmds);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		write(2, "Error: path is a directory\n", 27);
		exit_with_val(126, cmds);
	}
	if (access(cmds->cmdpath, X_OK) != 0)
	{
		write(2, "Error: command not executable\n", 30);
		exit_with_val(126, cmds);
	}
}

char	**make_args(t_cmds *cmds)
{
	int		i;
	char	**args;

	//TODO error messages
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

char	**make_envp(t_cmds *cmds, t_env *env)
{
	int		envlen;
	int		i;
	char	**envp;
	char	*envval;

	//TODO FREE ALL WHEN EXIT;
	i = 0;
	envlen = env_len(env);
	envp = ft_calloc(sizeof(char *), envlen + 1);
	if (!envp)
		exit_with_val(1, cmds);
	while (env->prev)
		env = env->prev;
	while (env)
	{
		if (env->is_hidden)
		{
			env = env->next;
			continue ;
		}
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
	int		exitval;
	char	*exitvar;

	if (cmds->permission_denied)
	{
		write(2, "Error: permission denied\n", 25);
		exit_with_val(1, cmds);
	}
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
	exitvar = ft_itoa(exitval);
	if (exitvar == NULL)
		exit_with_val(1, cmds);
	update_env(cmds->info->head, "?", exitvar);
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

void	restore_stdio(int *stdin_dup, int *stdout_dup)
{
	if (*stdin_dup != -1)
	{
		dup2(*stdin_dup, STDIN_FILENO);
		close(*stdin_dup);
		*stdin_dup = -1;
	}
	if (*stdout_dup != -1)
	{
		dup2(*stdout_dup, STDOUT_FILENO);
		close(*stdout_dup);
		*stdout_dup = -1;
	}
}

void	exec_single(t_cmds *cmds, t_env *env)
{
	int		stdin_dup;
	int		stdout_dup;
	pid_t	pid;
	char	**args;
	char	**envp;
	int		status;

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
			if (stdin_dup != -1)
        		close(stdin_dup);
    		if (stdout_dup != -1)
        		close(stdout_dup);
			if (cmds->permission_denied)
			{
				write(2, "Error: permission denied\n", 25);
				exit_with_val(1, cmds);
			}
			set_child_signals();
			check_access(cmds);
			args = make_args(cmds);
			envp = make_envp(cmds, env);
			execve(cmds->cmdpath, args, envp);
			free_carray(envp);
			perror(cmds->cmd);
			free(args);
			exit_with_val(1, cmds);
		}
		set_signals_ignore();
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			update_env(env, "?", ft_itoa(WEXITSTATUS(status)));
		set_signals_default();
	}
	restore_stdio(&stdin_dup, &stdout_dup);
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
		if (cmds->ispiped && cmds->info && cmds->info->pipe_read_fd != -1)
			close(cmds->info->pipe_read_fd);
		if (isbuiltin(cmds))
		{
			exec_builtin(cmds);
			exit(0);
		}
		check_access(cmds);
		args = make_args(cmds);
		envp = make_envp(cmds, env);
		execve(cmds->cmdpath, args, envp);
		perror(cmds->cmdpath);
		free(args);
		free_carray(envp);
		exit_with_val(126, cmds);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (pid);
}

void	exec_pipes(t_cmds *cmds, t_env *env)
{
	int	fd[2];
	int	fd_in;
	int	fd_out;
	int	status;
	int	lastpid;
	int	checkpid;

	fd_in = dup(STDIN_FILENO);
	while (cmds && cmds->ispiped)
	{
		if (pipe(fd) == -1)
		{
			write(2, "Error: pipe failed\n", 19);
			exit_with_val(1, cmds);
		}
		fd_out = fd[1];
		cmds->info->pipe_read_fd = fd[0];
		exec_pipe_single(cmds, env, fd_in, fd_out);
		close(fd_out);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		fd_in = fd[0];
		cmds = cmds->next;
	}
	if (cmds)
	{
		fd_out = STDOUT_FILENO;
		cmds->info->pipe_read_fd = -1;
		lastpid = exec_pipe_single(cmds, env, fd_in, fd_out);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	set_signals_ignore();
	checkpid = waitpid(-1, &status, 0);
	while (checkpid > 0)
	{
		if (checkpid == lastpid)
			if (WIFEXITED(status))
				update_env(env, "?", ft_itoa(WEXITSTATUS(status)));
		checkpid = waitpid(-1, &status, 0);
	}
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

void	find_paths(t_cmds *cmds, t_env *env)
{
	char	**paths;
	int		i;
	char	*currentpath;
	t_info	*info;

	//TODO HANDLE MALLOC FAIL IN SPLIT
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
