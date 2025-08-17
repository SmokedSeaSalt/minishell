/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:49:18 by kali              #+#    #+#             */
/*   Updated: 2025/08/17 12:23:38 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *line;
	t_env	*env;
	t_cmds *cmds;

    (void)argv;
	(void)argc;
    env = init_env(envp);
    printf("MINISHELL STARTED\n");
    while (1)
    {
        line = readline("[minishell] > ");
        cmds = ft_calloc(sizeof(t_cmds), 1);
        make_cmds(cmds, env, line);
        find_paths(cmds, env);
        execute_cmd(cmds, env);
        free_cmds(cmds);
        free(line);
    }
}