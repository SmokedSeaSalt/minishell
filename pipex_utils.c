/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 12:27:46 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/08 17:17:27 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freesplit(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*findpath(t_pipex *pipex, char **cmd)
{
	int		i;
	char	**paths;
	char	*currentpath;

	i = -1;
	paths = NULL;
	while (pipex->envp[++i])
	{
		if (!ft_strncmp("PATH=", (pipex->envp)[i], 5))
		{
			paths = ft_split((pipex->envp)[i] + 5, ':');
			break ;
		}
	}
	i = -1;
	while (paths[++i])
	{
		currentpath = ft_strjoin_path(paths[i], cmd[0]);
		if (!currentpath)
			continue ;
		if (access(currentpath, F_OK) == 0)
			return (freesplit(paths), currentpath);
		free(currentpath);
	}
	return (freesplit(paths), NULL);
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i] = '/';
	i++;
	j = 0;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	return (joined);
}

void	error_exit(char *msg, int fd)
{
	if (fd)
		close(fd);
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}
