/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:06:24 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/08/26 13:02:09 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

static int	ft_iswhitespace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
	{
		return (c);
	}
	else
	{
		return (0);
	}
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (c);
	}
	else
	{
		return (0);
	}
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		nflag;
	long	result;

	result = 0;
	i = 0;
	nflag = 1;
	while (ft_iswhitespace(nptr[i]))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		nflag = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i] != '\0')
	{
		result *= 10;
		result += (nptr[i] - '0');
		i++;
	}
	return ((int) result * nflag);
}