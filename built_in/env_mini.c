/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 10:00:10 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/08/12 16:23:12 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"

void print_var(t_env *var)
{
		write(1, var->v_name, ft_strlen(var->v_name));
		write(1, "=", 1);
		write(1, var->v_val, ft_strlen(var->v_val));
		write(1, "\n", 1);
}

int env_mini(t_cmds *cmds)
{
	t_env *var = cmds->info->head;
	while (var)
	{
		if (var->is_hidden == 0 && var->v_val != NULL)
			print_var(var);
		var = var->next;
	}
	return (0);
}