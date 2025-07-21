/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:15:37 by fdreijer          #+#    #+#             */
/*   Updated: 2025/07/21 16:29:29 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft_mini/libft_mini.h"

typedef struct s_cmds
{
	char *cmd;
	char *args;
	char *infile;
	char *outfile;
	int	append;
	int	exitstatusprev;
	int	isdependantsuccess;
	int	isdependantfailure;
	int	nextispipe;
	t_cmds *next;
}	t_cmds;


#endif