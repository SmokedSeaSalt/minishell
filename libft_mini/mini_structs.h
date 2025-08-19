/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:45:55 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/18 14:32:54 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STRUCTS_H
# define MINI_STRUCTS_H

typedef	struct s_env
{
	char	*v_name;
	char	*v_val;
	struct s_env	*next;
	int		is_hidden;
}	t_env;

typedef struct s_info
{
	int last_exit_val;
	char	**mini_env;
	t_env *head;
}	t_info;

typedef struct s_cmds
{
	char *cmdpath;
	char *cmd;
	char **args;
	char *infile;
	char *outfile;
	int addtoenv;
	int append;
	int	ispiped;
	int pipefd;
	struct s_cmds *prev;
	struct s_cmds *next;
	t_info *info;
}	t_cmds;

#endif