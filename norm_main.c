/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:48:48 by fdreijer          #+#    #+#             */
/*   Updated: 2025/09/26 13:34:07 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

#include "libft_mini/inc/libft_mini.h"
void	main_help(char *line, t_env *env)
{
	t_cmds		*cmds;

	cmds = ft_calloc(sizeof(t_cmds), 1);
	if (!cmds)
	{
		free(line);
		free_env(env);
		exit(123);
	}
	make_cmds(cmds, env, line);
	free(line);
	fix_empty_cmds(cmds);
	if (!cmds->cmd)
		update_env(env, "?", ft_itoa(0));
	find_paths(cmds, env);
	execute_cmd(cmds);
	free_cmds(cmds);
}

int	rl_fail(t_env *env)
{
	int	exitval;

	exitval = (unsigned char)ft_atoi(ft_getenv(env, "?"));
	free_env(env);
	exit(exitval);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;

	1;
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
			rl_fail(env);
		add_history(line);
		if (error_parse_line(line, -1, 0, 0))
		{
			free(line);
			update_env(env, "?", ft_itoa(2));
			continue ;
		}
		main_help(line, env);
	}
	free_env(env);
}
