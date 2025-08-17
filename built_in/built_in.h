/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:40:22 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/17 06:17:23 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../minishell.h"
# include "../libft_mini/mini_structs.h"
//built-in commands
int	cd_mini(t_cmds *cmds);
int	echo_mini(t_cmds *cmds);
int	exit_mini(t_cmds *cmds);
int pwd_mini(t_cmds *cmds);
void free_env(t_env *head);
void free_cmds_node(t_cmds *node);
void free_cmds(t_cmds *node);

#endif