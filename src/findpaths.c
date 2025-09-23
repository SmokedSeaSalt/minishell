/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpaths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:08:41 by fdreijer          #+#    #+#             */
/*   Updated: 2025/09/23 14:15:07 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char ***paths)
{
	int	i;

	i = -1;
	while ((*paths)[++i])
		free((*paths)[i]);
	free(*paths);
	*paths = NULL;
}

void	find_paths_path(t_cmds *cmds, char *env_path)
{
	char	**paths;
	int		i;
	char	*currentpath;

	paths = ft_split(env_path, ':');
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
			free_paths(&paths);
			cmds->cmdpath = currentpath;
			break ;
		}
		free(currentpath);
	}
	if (paths)
		free_paths(&paths);
	if (!cmds->cmdpath)
		cmds->cmdpath = ft_strndup(cmds->cmd, ft_strlen(cmds->cmd));
}

void	find_paths(t_cmds *cmds, t_env *env)
{
	while (cmds)
	{
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
		if (!isbuiltin(cmds))
		{
			while (env && ft_strcmp("PATH", env->v_name))
				env = env->next;
		}
		if (!env)
			cmds->cmdpath = ft_strndup(cmds->cmd, ft_strlen(cmds->cmd));
		else
			find_paths_path(cmds, env->v_val);
		cmds = cmds->next;
	}
}
