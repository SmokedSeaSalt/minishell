/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:15:46 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/05 13:41:04 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>	//to use size_t
#include <aio.h> //to use ssize_t
#include <stdlib.h> //to use malloc()
#include <stdint.h> //to use SIZE_MAX
#include "minishell.h"

void	*gnl_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ret;
	size_t			i;

	i = 0;
	if (nmemb == 0 || size == 0)
	{
		ret = malloc(0);
		if (ret == NULL)
			return (NULL);
		return (ret);
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	ret = malloc(nmemb * size);
	if (ret == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		ret[i] = 0;
		i++;
	}
	return (ret);
}

t_list	*get_fd_node(t_list *head, int fd)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	return (NULL);
}

//returns index for given char
//can function as strlen for char = '\0'
//when the char is not found returns -1;
ssize_t	charpos(char *s, char c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	str_i;
	char			*sptr;
	char			*ret;

	sptr = (char *)s;
	str_i = start;
	if (charpos(sptr, '\0') < start)
	{
		ret = malloc(0);
		return (ret);
	}
	if ((ssize_t)start + (ssize_t)len <= charpos(sptr, '\0'))
		ret = gnl_calloc((len + 1), sizeof(char));
	else
		ret = gnl_calloc(charpos(sptr, '\0') - start + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (sptr[str_i] != '\0' && str_i - start < len)
	{
		ret[str_i - start] = sptr[str_i];
		str_i++;
	}
	ret[str_i - start] = '\0';
	return (ret);
}

int	create_node(t_list **head, char *buffer, int fd)
{
	t_list	*newlist;

	newlist = gnl_calloc(1, sizeof(t_list));
	if (newlist == NULL)
		return (-1);
	newlist->fd = fd;
	newlist->line = buffer;
	if (charpos(newlist->line, '\n') != -1)
		newlist->hasnl = 1;
	if (*head != NULL)
	{
		newlist->next = *head;
		(*head)->prev = newlist;
	}
	*head = newlist;
	return (fd);
}