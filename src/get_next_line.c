/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:15:43 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/23 14:17:13 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h> //to use read
#include <stdlib.h> //to use free
#include <stdlib.h> //to use (s)size_t

char	*free_all(t_list **head)
{
	t_list	*current;
	t_list	*next;

	if (*head == NULL)
		return (NULL);
	current = *head;
	next = *head;
	while (next != NULL)
	{
		next = current->next;
		free(current->line);
		free(current);
		current = next;
	}
	*head = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*buffer;
	ssize_t			bytesread;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (free_all (&head));
	if (get_fd_node(head, fd) != NULL && (get_fd_node(head, fd))->hasnl == 1)
		return (return_line(&head, fd));
	buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (free_all(&head));
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread < 0)
		return (free(buffer), free_all(&head));
	if (bytesread == 0 && get_fd_node(head, fd) != NULL)
		return (free(buffer), return_line(&head, fd));
	if (bytesread == 0 && get_fd_node(head, fd) == NULL)
		return (free(buffer), NULL);
	if (get_fd_node(head, fd) == NULL && bytesread > 0)
		return (get_next_line(create_node(&head, buffer, fd)));
	if (bytesread > 0 || (get_fd_node(head, fd))->hasnl == 0)
		return (get_next_line(fill_node(head, fd, buffer)));
	return (free(buffer), free_all(&head));
}

char	*return_line(t_list **head, int fd)
{
	t_list	*fd_node;
	char	*tmp;
	char	*ret;

	fd_node = get_fd_node(*head, fd);
	if (fd_node->hasnl == 0)
	{
		ret = gnl_substr(fd_node->line, 0, charpos(fd_node->line, '\0') + 1);
		delnode(fd_node, head);
		return (ret);
	}
	ret = gnl_substr(fd_node->line, 0, charpos(fd_node->line, '\n') + 1);
	if (ret == NULL)
		return (free_all(head));
	tmp = gnl_substr(fd_node->line, charpos(fd_node->line, '\n') + 1,
			charpos(fd_node->line, '\0'));
	if (tmp == NULL)
		return (free(ret), free_all(head));
	free(fd_node->line);
	fd_node->line = tmp;
	if (charpos(fd_node->line, '\n') == -1)
		fd_node ->hasnl = 0;
	if (fd_node->line[0] == '\0')
		delnode(fd_node, head);
	return (ret);
}

void	delnode(t_list *node, t_list **head)
{
	if (node->prev == NULL)
		*head = node->next;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->line != NULL)
		free(node->line);
	free(node);
}

int	fill_node(t_list *head, int fd, char *buffer)
{
	char	*tmp;
	t_list	*fd_node;
	size_t	linelen;
	ssize_t	i;

	fd_node = get_fd_node(head, fd);
	linelen = charpos(fd_node->line, '\0');
	tmp = gnl_calloc((linelen + charpos(buffer, '\0') + 1), sizeof(char));
	if (tmp == NULL)
		return (-1);
	i = -1;
	while (fd_node->line[++i] != '\0')
		tmp[i] = fd_node->line[i];
	i = -1;
	while (buffer[++i] != '\0')
		tmp[i + linelen] = buffer[i];
	free(buffer);
	free(fd_node->line);
	fd_node->line = tmp;
	if (charpos(fd_node->line, '\n') != -1)
		fd_node ->hasnl = 1;
	return (fd);
}
