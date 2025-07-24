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
/*   Updated: 2025/06/23 14:54:14 by mvan-rij          :. ¨.                  */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include <stddef.h> //to use NULL
#include <unistd.h> //to use getcwd

int	pwd_mini(char **input)
{
	char *curr_pwd = NULL;

	curr_pwd = getcwd(curr_pwd, 0);
	if (curr_pwd == NULL)
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", curr_pwd);
	free(curr_pwd);
	return(EXIT_SUCCESS);
}
