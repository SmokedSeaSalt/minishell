/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:28:16 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/08/11 17:04:05 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"

//no args given. print vars in alphabetical order for v_name

//args given
//export name[=word]... <-- this means multiple name[=word] allowed
//check name is valid identifier


//mvan-rij@f1r2s10:~/Personal_git/minishell/sandbox$ export 4test
//bash: export: `4test': not a valid identifier


static int	n_args(char **args)
{
	int i;

	i = 0;
	while (!args && !args[i])
		i++;
	return (i);
}

int has_equals(char *str)
{
	while (str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

void process_args(char *str, t_env *head)
{
	char **words;

	if (has_equals(str) == 0)
	{
		//find v_name == str and set hidden to 0; make sure invalid name does not segfault.
	}
	else
	{
		words = ft_split(str, '=');
		if (words == NULL)
			return;
		if (words[1] == NULL)
			words[1] = ft_calloc(1, sizeof(char)); //heele vieze fix voor test= (dus dan zou words[1] NULL zijn)
		if (words[1] == NULL)
			return;
		update_env(head, words[0], words[1]);
	}

}


int export_mini(t_cmds *cmds)
{
	int i;

	i = 0;
	if (n_args(cmds->args) == 0)
		;//print sorted v_args
	else
	{
		while (cmds->args[i] != NULL)
		{
			process_args(cmds->args[i], cmds->info->head);
			i++;
		}
	}
}
