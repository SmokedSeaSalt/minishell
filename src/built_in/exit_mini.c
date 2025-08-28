/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:26:48 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/28 16:23:47 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"

void	exit_with_val(int value, t_cmds *cmds)
{
	free_env(cmds->info->head);
	free_cmds(cmds);
	exit(value);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	exit_mini(t_cmds *cmds)
{
	char	exitval;

	if (!(cmds->ispiped || (cmds->prev && cmds->prev->ispiped)))
		write(2, "exit\n", 5);
	if (n_args(cmds->args) == 0)
		exit_with_val(ft_atoi(ft_getenv(cmds->info->head, "?")), cmds);
	if (is_numeric(cmds->args[0]) == 0)
	{
		write(2, "minishell: exit: ", 17);
		write(2, cmds->args[0], ft_strlen(cmds->args[0]));
		write(2, ": numeric argument required\n", 28);
		exit_with_val(2, cmds);
	}
	if (n_args(cmds->args) == 1)
	{
		exitval = (unsigned char)ft_atoi(cmds->args[0]);
		exit_with_val(exitval, cmds);
	}
	if (n_args(cmds->args) > 1)
		write(2, "minishell: exit: too many arguments\n", 36);
	return (1);
}
