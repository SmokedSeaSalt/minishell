/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:49:18 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/26 13:35:53 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//TODO abc | abc ; exit leaks
//TODO exit codes
//TODO catching ctrl c ctrl d
//TODO heredoc expansion
//TODO 1 open fd in pipes >?>?>?./.
//TODO cat /dev/urandom | head -n 5
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_cmds	*cmds;
	extern int	g_signal_received;

	(void)argv;
	(void)argc;
	env = init_env(envp);
	if (set_signals_default() == -1)
		perror("sigaction");
	rl_catch_signals = 0;
	while (1)
	{
		line = readline("[minishell] $ ");
		if (!line)
		{
			write(2, "exit\n", 5);
			free_env(env);
			exit(1);
		}
		add_history(line);
		if (error_parse_line(line))
		{
			free(line);
			continue ;
		}
		cmds = ft_calloc(sizeof(t_cmds), 1);
		make_cmds(cmds, env, line);
		free(line);
		find_paths(cmds, env);
		execute_cmd(cmds, env);
		free_cmds(cmds);
	}
	free_env(env);
}
