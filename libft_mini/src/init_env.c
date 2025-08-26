/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:10:10 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/26 13:36:42 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

//TODO line 29?
t_env	*new_node_env(char *env)
{
	t_env	*node;
	int		i;

	i = 0;
	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return (NULL);
	while (is_valid_in_name(env[i]))
		i++;
	if (!(env[i] == '=' || env[i] == 0))
	{
		errno = 1;
		perror("");
		return (free(node), NULL);
	}
	node->v_name = ft_strndup(env, i);
	if (!node->v_name)
		return (free(node), NULL);
	if (env[i] == '=')
		i++;
	node->v_val = ft_strndup(&env[i], ft_strlen(&env[i]));
	if (!node->v_val)
		return (free(node->v_name), free(node), NULL);
	return (node);
}

t_env	*env_last(t_env	*head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	env_add_back(t_env *node, t_env **head)
{
	t_env	*lastnode;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	lastnode = env_last(*head);
	lastnode->next = node;
	node->prev = lastnode;
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*current;
	int		i;

	i = 0;
	head = ft_calloc(1, sizeof(t_env));
	if (head == NULL)
		return (NULL);
	head->is_hidden = 0;
	head->v_name = ft_strndup("?", 1);
	if (head->v_name == NULL)
		return (free(head), NULL);
	while (envp[i])
	{
		current = new_node_env(envp[i]);
		if (!current)
			return (NULL);
		env_add_back(current, &head);
		i++;
	}
	return (head);
}
