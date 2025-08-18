/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:49:18 by kali              #+#    #+#             */
/*   Updated: 2025/08/18 12:13:57 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO abc | abc ; exit leaks 
int main(int argc, char **argv, char **envp)
{
    char    *line;
	t_env	*env;
	t_cmds *cmds;

    (void)argv;
	(void)argc;
    env = init_env(envp);
    // printf("MINISHELL STARTED\n");
    while (1)
    {
        line = readline("[minishell] $ ");
        cmds = ft_calloc(sizeof(t_cmds), 1);
        make_cmds(cmds, env, line);
		free(line);
		// printf("MAINLOPP\n");
        find_paths(cmds, env);
        execute_cmd(cmds, env);
        free_cmds(cmds);
    }
}