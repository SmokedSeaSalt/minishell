/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:18:17 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/08 17:27:01 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <fcntl.h>

typedef struct s_pipex
{
	char	**envp;
	char	**argv;
	int		argc;
	int		firstcmd;
	int		fd_in;
	int		fd_out;
}			t_pipex;

char	*ft_strjoin_path(char *s1, char *s2);
void	error_exit(char *msg, int fd);
void	freesplit(char **split);
char	*findpath(t_pipex *pipex, char **cmd);
void	here_doc(t_pipex *pipex);

#endif