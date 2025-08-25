/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:27:11 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/20 15:21:28 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

char	*strjoin_path(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	joined = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 2, 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i] = '/';
	i++;
	j = 0;
	while (s2 && s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	return (joined);
}
