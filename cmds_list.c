/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:25:57 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/19 12:34:50 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*cmd_last(t_cmds *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_cmds	*cmd_first(t_cmds *tail)
{
	if (!tail)
		return (NULL);
	while (tail->prev)
		tail = tail->prev;
	return (tail);
}

t_cmds	*cmd_new_node(void)
{
	t_cmds	*node;

	node = ft_calloc(sizeof(t_cmds), 1);
	return (node);
}

void	cmd_add_back(t_cmds **head, t_cmds *newnode)
{
	t_cmds	*last;
	if (!head || !newnode)
		return ;
	if (!*head)
	{
		*head = newnode;
		return;
	}
	last = cmd_last(*head);
	last->next = newnode;
	newnode->prev = last;
}
