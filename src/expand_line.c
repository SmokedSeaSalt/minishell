/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:37:49 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/05 13:50:39 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_line_char(char **line, char **expandedline)
{
	int	expandedlen;

	expandedlen = ft_strlen(*expandedline);
	*expandedline = ft_realloc(*expandedline, expandedlen, expandedlen + 2);
	if (*expandedline == NULL)
		return ;
	(*expandedline)[expandedlen] = **line;
	(*line)++;
}

void	expand_line_dollar(t_env *env, char **line, char **expandedline)
{
	int		envlen;
	char	*env_line;
	int		len;
	int		isexitval;

	(*line)++;
	if (ft_isspace(**line) || !(**line) || **line == '"')
		return ((*line)--, expand_line_char(line, expandedline));
	isexitval = 0;
	len = ft_strlen(*expandedline);
	if (**line == '?')
	{
		env_line = ft_getenv(env, "?");
		(*line)++;
		isexitval = 1;
	}
	else
		env_line = return_env(env, *line);
	envlen = ft_strlen(env_line);
	*expandedline = ft_realloc(*expandedline, len, len + envlen + 1);
	if (*expandedline == NULL)
		return ;
	ft_memmove(&(*expandedline)[len], env_line, envlen);
	while (is_valid_in_name(**line) && !isexitval)
		(*line)++;
}

void	expand_line_double_q(t_env *env, char **line, char **expandedline)
{
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$')
			expand_line_dollar(env, line, expandedline);
		else
			expand_line_char(line, expandedline);
		if (*expandedline == NULL)
			return ;
	}
	(*line)++;
}

void	expand_line_single_q(char **line, char **expandedline)
{
	(*line)++;
	while (**line && **line != '\'')
	{
		expand_line_char(line, expandedline);
		if (*expandedline == NULL)
			return ;
	}
	(*line)++;
}

void	expand_line_space(t_cmds *cmds, char **line, char **expandedline)
{
	int	i;

	i = 0;
	if (cmds->cmd == NULL)
	{
		cmds->cmd = *expandedline;
		*expandedline = NULL;
	}
	else
	{
		if (cmds->args)
		{
			while (cmds->args[i])
				i++;
		}
		cmds->args = \
ft_realloc(cmds->args, i * sizeof(char *), (i + 2) * sizeof(char *));
		if (!cmds->args)
			return ;
		cmds->args[i] = *expandedline;
		*expandedline = NULL;
	}
	while (ft_isspace(**line))
		(*line)++;
}
