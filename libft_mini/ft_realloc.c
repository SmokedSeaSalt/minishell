/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:55:28 by fdreijer          #+#    #+#             */
/*   Updated: 2025/07/24 11:17:51 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

void	*ft_realloc(void *oldptr, int oldsize, int newsize)
{
	void	*newptr;

	if (oldsize < 0 || newsize < 0)
    	return (NULL);
	if (oldptr == NULL)
		return (malloc(newsize));
	if (newsize == 0)
		return (free(oldptr), NULL);
	newptr = ft_calloc(newsize, sizeof(char));
	if (!newptr)
		return (NULL);
	if (newsize > oldsize)
		ft_memmove(newptr, oldptr, oldsize);
	else
		ft_memmove(newptr, oldptr, newsize);
	free(oldptr);
	return (newptr);
}
