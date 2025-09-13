#include "minishell.h"

void	find_paths(t_cmds *cmds, t_env *env)
{
	// if info is able to be set somewhere else for all nodes saves many lines
	char	**paths;
	int		i;
	char	*currentpath;

	//TODO HANDLE MALLOC FAIL IN SPLIT
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
		if (isbuiltin(cmds))
		{
			cmds = cmds->next;
			continue ;
		}
		// function 2
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
		// function 2 end
		// function 1
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
		// function 1 end
		cmds = cmds->next;
	}
}
