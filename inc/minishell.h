/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:15:37 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/20 15:48:57 by mvan-rij         ###   ########.fr       */
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
# include "libft_mini.h"
# include "mini_structs.h"
#define HEREDOC_PREFIX "/tmp/.heredoc_"

t_cmds	*cmd_last(t_cmds *head);
t_cmds	*cmd_new_node(void);
void	cmd_add_back(t_cmds **head, t_cmds *newnode);
t_cmds	*cmd_first(t_cmds *tail);
void	make_cmds(t_cmds *cmds, t_env *env, char *line);
void	find_paths(t_cmds *cmds, t_env *env);
void	execute_cmd(t_cmds *cmds, t_env *env);
int		error_parse_line(char *line);
int	init_signals(void);

#endif
