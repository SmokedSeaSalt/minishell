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
/*   Updated: 2025/06/20 16:28:54 by mvan-rij          :. ¨.                  */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include <unistd.h> //to use chdir
#include <stdio.h> //to use perror

//plan changed, will get "cd" "test" "something"
static int	get_filepath(char **input, char **file_path)
{
	char	*tmp;
	int		i;

	if (input[1] == NULL)
	{
		printf("cd: Not enough arguments\n");
		return (-1);
	}
	*file_path = ft_strndup(input[1], strlen(input[1]));
	if (*file_path == NULL)
		return (-1);
	i = 2;
	while (input[i] != NULL)
	{
		tmp = strjoin_space(*file_path, input[i]);
		free(file_path);
		*file_path = tmp;
		if (file_path == NULL)
		{
			return (-1);
		}
	}
	return (0);
}

int	ft_cd(char **input)
{
	char *file_path;

	if (ft_strncmp(input[0], "cd", 3) != 0)
	{
		printf("cd: Command not recognized\n");
		return (-1);
	}
	if (get_filepath(input, &file_path) != 0)
		return (-1);
	if (chdir(file_path) != 0)
	{
		perror("cd:");
		free(file_path);
		return (-1);
	}
	free(file_path);
	return (0);
}
