/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:18:00 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/22 12:18:01 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

char	*strjoin_char(char *s1, char *s2, char c)
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
	joined[i] = c;
	i++;
	j = 0;
	while (s2 && s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	return (joined);
}
