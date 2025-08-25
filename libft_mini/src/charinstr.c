/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charinstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:47:01 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/22 12:21:53 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

int	charinstr(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
