/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:09:01 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/29 10:25:25 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	unlink_node_and_free(t_cmds *cmds, t_env *env, int i)
{
	if (!ft_strcmp(cmds->args[i], env->v_name))
	{
		if (env->prev)
			env->prev->next = env->next;
		else
			cmds->info->head = env->next;
		if (env->next)
			env->next->prev = env->prev;
		free(env->v_name);
		env->v_name = NULL;
		free(env->v_val);
		env->v_val = NULL;
		free(env);
		env = NULL;
	}
}

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
			unlink_node_and_free(cmds, env, i);
			env = env->next;
		}
		i++;
	}
	return (0);
}
