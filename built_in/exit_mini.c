/* ************************************************************************** */
/*                                                                            */
/*                                                       ,--------------      */
/*                                                      /                     */
/*                                                     /                      */
/*                                                    /   ,--,/      ,--      */
/*                                                    |  /  ,'    ,·´         */
/*                                                    |  ;·'   ,·´            */
/*   exit_mini.c                                      |  ;  ,·´               */
/*                                                    |  :,'                  */
/*   By: mvan-rij <mvan-rij@student.42.fr>             `´.                    */
/*                                                      .¨.                   */
/*   Created: 2025/07/25 11:17:23 by mvan-rij           ¨· .                  */
/*   Updated: 2025/07/28 14:16:42 by mvan-rij          :. ¨.                  */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"

static int	n_args(char **args)
{
	int i;

	i = 0;
	while (!args && !args[i])
		i++;
	return (i);
}

void exit_with_val(int value, struct *cleanup)
{
	//free everything
	exit(value);
}

//TODO different behaviour if exit is piped or not


int	exit_mini(t_cmds *cmds)
{
	char exitval;

	write(1, "exit\n", 6);
	if (n_args(cmds->args) == 0)
	{
		//get last exit value
		//free everything
		exit_with_val(lastexitval, cleanup);
	}
	if (n_args(cmds->args) == 1)
	{
		//check only numeric
		if (is_only_numeric(cmds->args[0]) == 1)
		{
			exitval = (char)atoi(cmds->args[0]);
			exit_with_val(exitval, cleanup);
		}
		else
		{
			write(1, "minishell: exit: ", 37);
			write(1, cmds->args[0], ft_strlen(cmds->args[0]));
			write(1, ": numeric argument required\n", 29);
			//free everything
			exit_with_val(2, cleanup);
		}
	}
	if (n_args(cmds->args) > 1)
	{
		write(1, "minishell: exit: too many arguments\n", 37);
	}
	return (1);
}
