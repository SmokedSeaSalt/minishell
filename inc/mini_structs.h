/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:45:55 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/28 12:50:44 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STRUCTS_H
# define MINI_STRUCTS_H

typedef struct s_env
{
	char			*v_name;
	char			*v_val;
	struct s_env	*next;
	struct s_env	*prev;
	int				is_hidden;
}					t_env;

typedef struct s_info
{
	int		pipe_read_fd;
	int		last_exit_val;
	t_env	*head;
}			t_info;

typedef struct s_cmds
{
	char			*cmdpath;
	char			*cmd;
	char			**args;
	char			*infile;
	char			*outfile;
	int				addtoenv;
	int				append;
	int				ispiped;
	int				pipefd;
	int				permission_denied;
	struct s_cmds	*prev;
	struct s_cmds	*next;
	t_info			*info;
}					t_cmds;

#endif