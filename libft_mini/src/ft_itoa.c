/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:42:55 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/08/28 13:30:10 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa(int n)
{
	int		nb;
	int		chars;
	char	*out;

	nb = n;
	chars = 1;
	if (n < 0)
		chars++;
	while (nb >= 10 || nb <= -10)
	{
		chars++;
		nb /= 10;
	}
	out = ft_calloc(chars + 1, sizeof(char));
	if (out == NULL)
		return (NULL);
	out[chars] = 0;
	if (n < 0)
		out[0] = '-';
	while ((chars > 0 && nb >= 0) || chars > 1)
	{
		out[chars-- - 1] = (n % 10) * ((((n % 10) < 0) * -2) + 1) + '0';
		n /= 10;
	}
	return (out);
}
