/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:39:48 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/20 16:55:27 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"

//check for -n flag and edge cases
void check_n_flag(char **args, int *i, int *print_nl)
{
	int j;

	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] == '\0')
		{
			*print_nl = 0;
			(*i)++;
			continue ;
		}
		else
			break;
	}
}

int	echo_mini(t_cmds *cmds)
{
	int	print_nl;
	int	i;

	print_nl = 1;
	i = 0;
	check_n_flag(cmds->args, &i, &print_nl);
	while (cmds->args[i])
	{
		write(1, cmds->args[i], ft_strlen(cmds->args[i]));
		if (cmds->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (print_nl)
		write(1, "\n", 1);
	return (0);
}
