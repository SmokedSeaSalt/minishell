/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:30:58 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/25 16:11:15 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"
#include <stddef.h> //to use NULL
#include <unistd.h> //to use getcwd

int	pwd_mini(t_cmds *cmds)
{
	char	*curr_pwd;

	curr_pwd = NULL;
	curr_pwd = getcwd(curr_pwd, 0);
	(void)cmds;
	if (curr_pwd == NULL)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	write(1, curr_pwd, ft_strlen(curr_pwd));
	write(1, "\n", 1);
	free(curr_pwd);
	return (EXIT_SUCCESS);
}
