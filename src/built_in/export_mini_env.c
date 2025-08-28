/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_mini_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:10:09 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/08/28 16:31:36 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"

/// @brief checks if a environment variable exists with name
/// @param head	environment variable linked list
/// @param name	name for the environtment variable
/// @return	return 1 if variable exist. 0 when no variable is found with name
int	env_var_exists(t_env *head, char *name)
{
	if (!head || !name)
		return (-1);
	while (head)
	{
		if (ft_strcmp(head->v_name, name) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

/// @brief sets the is_hidden flag for environment variable name to 0
/// @param head environment variable linked list
/// @param name name for the environtment variable
void	env_set_hidden_0(t_env *head, char *name)
{
	if (!head || !name)
		return ;
	while (head)
	{
		if (ft_strcmp(head->v_name, name) == 0)
			head->is_hidden = 0;
		head = head->next;
	}
	return ;
}
