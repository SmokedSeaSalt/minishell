/* ************************************************************************** */
/*                                                                            */
/*                                                       ,--------------      */
/*                                                      /                     */
/*                                                     /                      */
/*                                                    /   ,--,/      ,--      */
/*                                                    |  /  ,'    ,·´         */
/*                                                    |  ;·'   ,·´            */
/*   pwd_mini.c                                       |  ;  ,·´               */
/*                                                    |  :,'                  */
/*   By: mvan-rij <mvan-rij@student.42.fr>             `´.                    */
/*                                                      .¨.                   */
/*   Created: 2025/06/20 10:58:18 by mvan-rij           ¨· .                  */
/*   Updated: 2025/07/29 15:56:45 by mvan-rij          :. ¨.                  */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"
#include <stddef.h> //to use NULL
#include <unistd.h> //to use getcwd

int	pwd_mini(t_cmds *cmds)
{
	char *curr_pwd = NULL;

	curr_pwd = getcwd(curr_pwd, 0);
	if (curr_pwd == NULL)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	write(1, curr_pwd, ft_strlen(curr_pwd));
	write(1, "\n", 1);
	free(curr_pwd);
	return(EXIT_SUCCESS);
}
