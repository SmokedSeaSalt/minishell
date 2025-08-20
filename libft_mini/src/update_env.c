/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:58:10 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/20 11:16:32 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

char	*ft_getenv(t_env *head, char *str)
{
	if (!head || !str)
		return (NULL);
	while (head)
	{
		if (!ft_strcmp(head->v_name, str))
			return (head->v_val);
		head = head->next;
	}
	return (NULL);
}

char *return_env(t_env *head, char *str)
{
	while (head)
	{
		if (!ft_strncmp(head->v_name, str, ft_strlen(head->v_name)))
			if (!is_valid_in_name(str[ft_strlen(head->v_name)]))
				return (head->v_val);
		head = head->next;
	}
	return (NULL);
}

int	env_len(t_env *env)
{
	int	n;

	n = 0;
	while (env && env->prev)
		env = env->prev;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

void	update_env(t_env *head, char *name, char *newval)
{
	t_env	*newnode;

	// printf("NAME: %s\n", name);
	// printf("VAL: %s\n", newval);
	while (head)
	{
		if (!ft_strcmp(head->v_name, name))
		{
			free(head->v_val);
			head->v_val = newval;
			return ;
		}
		if (head->next == NULL)
			break;
		head = head->next;
	}
	newnode = ft_calloc(sizeof(t_env), 1);
	if (!newnode)
		return ;
	newnode->v_name = name;
	// printf("NAME: %s\n", newnode->v_name);
	newnode->v_val =newval;
	head->next = newnode;
	newnode->prev = head;
	return ;
}
//TODO FREE IF FAIL
char	*expand_env(t_env *head, char *str)
{
	int		i;
	char	*to_find;
	char	*found;

	i = 1;
	if (!str || str[0] != '$')
		return (NULL);
	while (str[i] && !ft_isspace(str[i]))
		i++;
	to_find = ft_strndup(&str[1], i - 1);
	if (!to_find)
		return (NULL);
	found = ft_getenv(head, to_find);
	free (to_find);
	if (!found)
		return (NULL);
	return (found);
}
