/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 08:49:18 by fdreijer          #+#    #+#             */
/*   Updated: 2025/09/26 13:55:26 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	str_i;
	char			*ret;

	str_i = start;
	if (ft_strlen(s) < start)
	{
		ret = malloc(1);
		if (ret == NULL)
			return (NULL);
		ret[0] = '\0';
		return (ret);
	}
	if (start + len <= ft_strlen(s))
		ret = malloc((len + 1) * sizeof(unsigned char));
	else
		ret = malloc((ft_strlen(s) - start + 1));
	if (ret == NULL)
		return (NULL);
	while (s[str_i] != '\0' && str_i - start < len)
	{
		ret[str_i - start] = s[str_i];
		str_i++;
	}
	ret[str_i - start] = '\0';
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	char	*strp;
	size_t	i;

	strp = (char *)s;
	i = 0;
	while (strp[i] != '\0')
	{
		if (strp[i] == (char) c)
			return (&strp[i]);
		i++;
	}
	if (strp[i] == (char) c)
		return (&strp[i]);
	return ((void *)0);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*strp;
	size_t	i;
	size_t	len;

	strp = (char *)s;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (strp[len - i] == (char) c)
			return (&strp[len - i]);
		i++;
	}
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	int				end;
	char			*ret;

	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) != NULL && s1[start] != '\0')
		start++;
	while (ft_strrchr(set, s1[end - 1]) != NULL && end >= 0)
		end--;
	ret = ft_substr(s1, start, end - start);
	if (ret == NULL)
		return (NULL);
	return (ret);
}

/* DELETE ALL ABOVE HERE*/
/* DELETE get_next_line.c & get_next_line_utils.c*/
/* DELETE constructors from minishell.h*/
/* DELETE everything below marked with //DELETE */
/* Replace main with norm main and delte norm_main.c*/
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*tmpline; //DELETE
	t_env		*env;
	t_cmds		*cmds;

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
		if (isatty(fileno(stdin))) //DELETE
			line = readline("[minishell] $ ");
		else //DELETE
		{ //DELETE
			tmpline = get_next_line(fileno(stdin)); //DELETE
			if (tmpline != NULL) //DELETE
			{ //DELETE
				line = ft_strtrim(tmpline, "\n"); //DELETE
				free(tmpline); //DELETE
			} //DELETE
			else //DELETE
				line = NULL; //DELETE
		} //DELETE
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
		execute_cmd(cmds);
		free_cmds(cmds);
	}
	free_env(env);
}
