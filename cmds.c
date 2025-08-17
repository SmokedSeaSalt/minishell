/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 06:08:04 by kali              #+#    #+#             */
/*   Updated: 2025/08/17 06:14:38 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds *cmd_first(t_cmds *node)
{
    while (node->prev)
    {
        node = node->prev;
    }
    return (node);
}

t_cmds *cmd_last(t_cmds *node)
{
    while (node->next)
    {
        node = node->next;
    }
    return (node);
}

t_cmds	*cmd_new_node(void)
{
    t_cmds  *newnode;
    newnode = ft_calloc(sizeof(t_cmds), 1);
    return (newnode);
}

void	cmd_add_back(t_cmds **head, t_cmds *newnode)
{
    t_cmds  *last;

    if (!head || !(*head))
    {
        *head = newnode;
        return ;
    }
    last = cmd_last(*head);
    newnode->prev = last;
    last->next = newnode;
}
