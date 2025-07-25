/* ************************************************************************** */
/*                                                                            */
/*                                                       ,--------------      */
/*                                                      /                     */
/*                                                     /                      */
/*                                                    /   ,--,/      ,--      */
/*                                                    |  /  ,'    ,·´         */
/*                                                    |  ;·'   ,·´            */
/*   cd_mini.c                                        |  ;  ,·´               */
/*                                                    |  :,'                  */
/*   By: mvan-rij <mvan-rij@student.42.fr>             `´.                    */
/*                                                      .¨.                   */
/*   Created: 2025/06/20 10:57:58 by mvan-rij           ¨· .                  */
/*   Updated: 2025/07/24 11:42:00 by mvan-rij          :. ¨.                  */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"
#include <unistd.h> //to use chdir
#include <stdio.h> //to use perror
#include <stddef.h> //to use NULL

//expand args** to single string for file_path
static int	get_filepath(char **input, char **file_path)
{
	char	*tmp;
	int		i;

	if (input[0] == NULL)
	{
		printf("cd: Not enough arguments\n"); //exit code 0
		return (-1);
	}
	*file_path = ft_strndup(input[0], strlen(input[0]));
	if (*file_path == NULL)
		return (-1);
	i = 1;
	while (input[i] != NULL)
	{
		tmp = strjoin_space(*file_path, input[i]);
		free(file_path);
		*file_path = tmp;
		if (file_path == NULL)
			return (-1);
	}
	return (0);
}

//get cmds args and do cd
int	cd_mini(t_cmds *cmds)
{
	//TODO: PWD and OLDPWD in envoirenment vars
	char *file_path;

	//old_pwd = pwd();

	if (get_filepath(cmds->args, &file_path) != 0)
		return (EXIT_SUCCESS);
	if (chdir(file_path) != 0)
	{
		perror("cd:");
		free(file_path);
		return (EXIT_FAILURE);
	}
	free(file_path);

	/*
	export OLDPWD=old_pwd
	export PWD=pwd();
	*/

	return (EXIT_SUCCESS);
}
