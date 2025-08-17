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
/*   Updated: 2025/07/30 12:48:44 by mvan-rij          :. ¨.                  */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_mini/libft_mini.h"
#include "../minishell.h"
#include <unistd.h> //to use chdir
#include <stdio.h> //to use perror
#include <stddef.h> //to use NULL

//expand args** to single string for file_path
static int	get_filepath(char **args, char **file_path)
{
	char	*tmp;
	int		i;

	if (args[0] == NULL)
	{
		write(2 ,"cd: Not enough arguments\n", 25); //exit code 0
		return (-1);
	}
	*file_path = ft_strndup(args[0], strlen(args[0]));
	if (*file_path == NULL)
		return (-1);
	i = 1;
	while (args[i] != NULL)
	{
		tmp = strjoin_space(*file_path, args[i]);
		free(*file_path);
		*file_path = tmp;
		if (*file_path == NULL)
			return (-1);
		i++;
	}
	return (0);
}
char *get_pwd(void)
{
	char *curr_pwd = NULL;

	curr_pwd = getcwd(curr_pwd, 0);
	if (curr_pwd == NULL)
		return (NULL);
	return (curr_pwd);
}

//get cmds args and do cd
//also updates PWD and OLDPWD environnment variables
int	cd_mini(t_cmds *cmds)
{
	char *old_pwd;
	char *new_pwd;
	char *file_path;

	if (get_filepath(cmds->args, &file_path) != 0)
		return (EXIT_FAILURE);
	old_pwd = get_pwd();
	if (chdir(file_path) != 0 || old_pwd == NULL)
	{
		perror("cd");
		return (free(old_pwd), free(file_path), EXIT_FAILURE);
	}
	free(file_path);
	new_pwd = get_pwd();
	if (new_pwd == NULL)
		return (free(old_pwd), EXIT_FAILURE);
	update_env(cmds->info->head, "PWD", new_pwd);
	update_env(cmds->info->head, "OLDPWD", old_pwd);
	return (EXIT_SUCCESS);
}
