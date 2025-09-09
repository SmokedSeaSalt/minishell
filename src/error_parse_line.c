/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parse_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:06:00 by fdreijer          #+#    #+#             */
/*   Updated: 2025/09/09 11:32:59 by fdreijer         ###   ########.fr       */
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
	if (mode == 1 && (line[i] == '>' || line[i] == '<'))
		return (0);
	return (1);
}

int	char_not_supported(char *line, char c)
{
	write(2, "Parse error: ", 13);
	write(2, line, ft_strlen(line));
	if (c)
	{
		write(2, " ", 1);
		write(2, &c, 1);
	}
	write(2, " not supported by minishell.\n", 30);
	return (1);
}

int	error_check_io(char *line, int *i, int *wordbefore)
{
	if (line[(*i)] == '<')
	{
		if (line[(*i) + 1] == '<')
		{
			if (!word_comes_after(&line[(*i) + 2], 1))
				return (char_not_supported("missing heredoc delim", 0));
			(*i)++;
		}
		else if (!word_comes_after(&line[(*i) + 1], 1))
			return (char_not_supported("missing infile", 0));
		*wordbefore = 0;
	}
	else if (line[(*i)] == '>')
	{
		if (line[(*i) + 1] == '>')
			(*i)++;
		if (!word_comes_after(&line[(*i) + 1], 1))
			return (char_not_supported("missing outfile", 0));
		*wordbefore = 0;
	}
	return (0);
}

int	error_parse_line(char *line, int i, int wordbefore, int openquote)
{
	while (line[++i])
	{
		if (!openquote && (line[i] == '\'' || line[i] == '"'))
			openquote = line[i];
		else if (openquote && line[i] == openquote)
			openquote = 0;
		else if (openquote)
			wordbefore = 1;
		else if ((line[i] == '>' || line[i] == '<') && \
error_check_io(line, &i, &wordbefore))
			return (1);
		else if (line[i] == '|')
		{
			if (!wordbefore || !word_comes_after(&line[i + 1], 0))
				return (char_not_supported("empty pipe", 0));
			wordbefore = 0;
		}
		else if (!ft_isspace(line[i]))
			wordbefore = 1;
	}
	if (openquote)
		return (char_not_supported("unclosed quote", 0));
	return (0);
}
