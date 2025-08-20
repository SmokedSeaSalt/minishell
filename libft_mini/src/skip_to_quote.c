/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_to_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:33:53 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/19 16:14:56 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

int	skip_to_quote(char **str)
{
	char	c;
	char	*temp;

	if (!str || !(*str) || !ft_isquote(**str))
		return (0);
	temp = *str;
	c = **str;
	(**str)++;
	while (**str != c)
	{
		(**str)++;
		if (**str == 0)
		{
			*str = temp;
			return (0);
		}
	}
	return (1);
}
