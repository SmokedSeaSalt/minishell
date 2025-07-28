/* ************************************************************************** */
/*                                                                            */
/*                                                       ,--------------      */
/*                                                      /                     */
/*                                                     /                      */
/*                                                    /   ,--,/      ,--      */
/*                                                    |  /  ,'    ,·´         */
/*                                                    |  ;·'   ,·´            */
/*   built_in.h                                       |  ;  ,·´               */
/*                                                    |  :,'                  */
/*   By: mvan-rij <mvan-rij@student.42.fr>             `´.                    */
/*                                                      .¨.                   */
/*   Created: 2025/07/24 11:11:42 by mvan-rij           ¨· .                  */
/*   Updated: 2025/07/25 11:21:35 by mvan-rij          :. ¨.                  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

//built-in commands
int	cd_mini(t_cmds *cmds);
int	echo_mini(t_cmds *cmds);

#endif