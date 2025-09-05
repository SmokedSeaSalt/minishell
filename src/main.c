/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:49:18 by fdreijer          #+#    #+#             */
/*   Updated: 2025/09/05 14:50:24 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;
	t_cmds		*cmds;
	extern int	g_signal_received;

	//TODO exit codes
	//TODO heredoc expansion
	(void)argv;
	(void)argc;
	env = init_env(envp);
	if (env == NULL)
		exit(EXIT_FAILURE);
	if (set_signals_default() == -1)
		perror("sigaction");
	rl_catch_signals = 0;
	while (1)
	{
		line = readline("[minishell] $ ");
		if (!line)
		{
			int exitval = (unsigned char)ft_atoi(ft_getenv(env, "?"));
			free_env(env);
			exit(exitval);
		}
		add_history(line);
		if (error_parse_line(line, -1, 0, 0))
		{
			free(line);
			update_env(env, "?", ft_itoa(2));
			continue ;
		}
		cmds = ft_calloc(sizeof(t_cmds), 1);
		make_cmds(cmds, env, line);
		free(line);
		fix_empty_cmds(cmds);
		if (!cmds->cmd)
			update_env(env, "?", ft_itoa(0));
		find_paths(cmds, env);
		execute_cmd(cmds, env);
		free_cmds(cmds);
	}
	free_env(env);
}
