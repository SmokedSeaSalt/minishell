/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:09:01 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/19 12:26:56 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	unset_mini(t_cmds *cmds)
{
	t_env	*env;
	int		i;
	
	i = 0;
	while (cmds->args && cmds->args[i])
	{
		env = cmds->info->head;
		while (env)
		{
			if (!ft_strcmp(cmds->args[i], env->v_name))
			{
				if (env->prev)
					env->prev->next = env->next;
				if (env->next)
					env->next->prev = env->prev;
				free(env->v_name);
				free(env->v_val);
				free(env);
				return (0);
			}
			env = env->next;
		}
		i++;
	}
	return (0);
}
