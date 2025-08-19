/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parse_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:06:00 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/18 14:00:16 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_comes_after(char *line, int mode)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '|' || !line[i])
		return (0);
	if (mode == 1 && line[i] == '<' || line[i] == '>')
		return (0);
	return (1);
}

int	char_not_supported(char *line)
{
	write(2, "Parse error: ", 13);
	write(2, line, ft_strlen(line));
	write(2, " not supported by minishell.\n", 30);
	return (1);
}

int	error_parse_line(char *line)
{
	int	i;
	int	wordbefore;
	int	openquote;

	i = -1;
	wordbefore = 0;
	openquote = 0;
	while (line[++i])
	{
		if (!openquote && (line[i] == '\'' || line[i] == '"'))
			openquote = line[i];
		else if (openquote && line[i] == openquote)
			openquote = 0;
		else if (openquote)
		{
			wordbefore = 1;
			continue;
		}
		else if (line[i] == '\\')
			return (char_not_supported("char \\"));
		else if (line[i] == ';')
			return (char_not_supported("char ;"));
		else if (line[i] == '&')
			return (char_not_supported("char &"));
		else if (line[i] == '*')
			return (char_not_supported("char *"));
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				if (!word_comes_after(&line[i + 2], 1))
					return (char_not_supported("missing heredoc delim"));
				i++;
			}
			else if (!word_comes_after(&line[i + 1], 1))
				return (char_not_supported("missing infile"));
			wordbefore = 0;
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
				i++;
			if (!word_comes_after(&line[i + 1], 1))
				return (char_not_supported("missing outfile"));
			wordbefore = 0;
		}
		else if (line[i] == '|')
		{
			if (!wordbefore || !word_comes_after(&line[i + 1], 0))
				return (char_not_supported("empty pipe"));
			wordbefore = 0;
		}
		else if (!ft_isspace(line[i]))
			wordbefore = 1;
	}
	if (openquote)
		return (char_not_supported("unclosed quote"));
	return (0);
}
