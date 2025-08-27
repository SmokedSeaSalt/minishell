/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:42:55 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/08/27 16:33:43 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_malloc_a(long n, int *malloc_size)
{
	*malloc_size = 1;
	if (n < 0)
	{
		(*malloc_size)++;
		n *= -1;
	}
	if (n == 0)
		(*malloc_size)++;
	while (n != 0)
	{
		(*malloc_size)++;
		n /= 10;
	}
	return (malloc((*malloc_size) * sizeof(char)));
}

static void	ft_fill_a(char *ret, long nbr, int *malloc_size)
{
	int			offset;
	int			i;

	offset = 2;
	i = 0;
	if (nbr < 0)
	{
		ret[i] = '-';
		i++;
		nbr *= -1;
		offset = 1;
	}
	if (nbr == 0)
		ret[0] = '0';
	while (nbr != 0)
	{
		ret[(*malloc_size) - i - offset] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	ret[(*malloc_size) - 1] = '\0';
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*ret;
	int		malloc_size;

	nbr = (long)n;
	ret = ft_malloc_a(nbr, &malloc_size);
	if (ret == NULL)
		return (NULL);
	ft_fill_a(ret, nbr, &malloc_size);
	return (ret);
}
