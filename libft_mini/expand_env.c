/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:58:10 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/20 16:50:02 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

char	*expand_env(char *str)
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
	found = getenv(to_find);
	free (to_find);
	if (!found)
		return (NULL);
	return (found);
}
