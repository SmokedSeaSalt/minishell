/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:53:11 by fdreijer          #+#    #+#             */
/*   Updated: 2025/09/05 14:29:11 by fdreijer         ###   ########.fr       */
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

void	path_check_access(t_cmds *cmds, char **paths)
{
	int		i;
	char	*currentpath;

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
	char	**paths;
	int		i;
	char	*currentpath;
	t_info	*info;

	//TODO HANDLE MALLOC FAIL IN SPLIT
	info = ft_calloc(sizeof(t_info), 1);
	if (!info)
		exit_with_val(1, cmds);
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
			exit_with_val(1, cmds);
		cmds = cmds->next;
	}
}
