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

int	write_env(char *str)
{
	int		i;
	char	*env;

	i = 0;
	env = expand_env(str);
	write(1, env, ft_strlen(env));
	return (strlen(str));
}

int	echo_quote(char *str)
{
	int		i;
	char	c;

	c = *str;
	i = 1;
	while (str[i] != c && str[i])
	{
		if (c == '"' && str[i] == '$')
			i += write_env(&str[i]);
		else
		{
			write(1, &str[i], 1);
			i++;
		}
	}
	if (str[i] == c)
		i++;
	return (i);
}

void	execute_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
			i += echo_quote(&str[i]);
		else if (str[i] == '$')
			i += write_env(&str[i]);
		else
			i += write(1, &str[i], 1);
	}
}

int	echo_mini(char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	if (ft_strncmp(cmd[0], "echo", 5))
	{
		printf("echo: Command not recognized\n");
		return (-1);
	}
	if (!strncmp(cmd[1], "-n", 3))
	{
		flag = 1;
		i++;
	}
	while (cmd[i])
	{
		execute_echo(cmd[i]);
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
