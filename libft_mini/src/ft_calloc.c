/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:42:48 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/19 16:14:44 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*s;
	unsigned char	*s2;
	size_t			n;

	if (size != 0 && ((nmemb * size) / size) != nmemb)
		return (NULL);
	s = malloc(nmemb * size);
	if (s == NULL)
		return (NULL);
	n = nmemb * size;
	s2 = (unsigned char *)s;
	while (n)
	{
		*s2 = 0;
		s2++;
		n--;
	}
	return (s);
}
