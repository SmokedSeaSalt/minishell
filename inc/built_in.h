/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:40:22 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/28 16:26:18 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"
# include "mini_structs.h"

//built-in commands
int		cd_mini(t_cmds *cmds);
int		echo_mini(t_cmds *cmds);
int		exit_mini(t_cmds *cmds);
int		env_mini(t_cmds *cmds);
int		pwd_mini(t_cmds *cmds);
int		export_mini(t_cmds *cmds);
int		unset_mini(t_cmds *cmds);
int		env_var_exists(t_env *head, char *name);
void	env_set_hidden_0(t_env *head, char *name);

#endif