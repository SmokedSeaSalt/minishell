/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:15:26 by fdreijer          #+#    #+#             */
/*   Updated: 2025/06/08 17:27:07 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_help(t_pipex *pipex)
{
	pipex->fd_out = open(pipex->argv[pipex->argc - 1] \
, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->fd_out < 0)
		error_exit("Error: open outfile failed\n", pipex->fd_in);
}

void	here_doc(t_pipex *pipex)
{
	int		fd[2];
	char	*l;

	pipex->firstcmd = 2;
	if (pipex->argc < 6)
		error_exit("Error: Too few arguments for heredoc\n", 0);
	if (pipe(fd) == -1)
		error_exit("Error: pipe failed\n", 0);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		l = get_next_line(0);
		if (!l)
			error_exit("Error: Get next line failed\n", 0);
		if (!ft_strncmp(pipex->argv[2], l, ft_strlen(pipex->argv[2])) && (\
l[ft_strlen(pipex->argv[2])] == 0 || l[ft_strlen(pipex->argv[2])] == '\n'))
			break ;
		write(fd[1], l, ft_strlen(l));
		free(l);
	}
	free(l);
	close(fd[1]);
	pipex->fd_in = fd[0];
	here_doc_help(pipex);
}
