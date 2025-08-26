/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:40:44 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/26 13:37:29 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns head->v_val if str == v_name and is followed by '\0' or ' '

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
	int		expandedlen;

	if (**line != '$')
		return ;
	(*line)++;
	expandedlen = ft_strlen(*expandedline);
	if (**line == '?')
	{
		env_line = ft_getenv(env, "?");
		(*line)++;
	}
	else
		env_line = return_env(env, *line);
	envlen = ft_strlen(env_line);
	*expandedline = \
ft_realloc(*expandedline, expandedlen, expandedlen + envlen + 1);
	if (*expandedline == NULL)
		return ;
	ft_memmove(&(*expandedline)[expandedlen], env_line, envlen);
	while (is_valid_in_name(**line))
		(*line)++;
}

void	expand_line_double_q(t_env *env, char **line, char **expandedline)
{
	int	newlen;
	int	expandedlen;

	newlen = 0;
	expandedlen = 0;
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
	int	newlen;
	int	expandedlen;

	newlen = 0;
	expandedlen = 0;
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

//TODO DONT EXPAND ENV IF IN HEREDOC
char	*parse_word(t_env *env, char **line)
{
	char	*word;

	word = NULL;
	while (**line && !ft_isspace(**line) \
&& **line != '<' && **line != '>' && **line != '|')
	{
		if (**line == '\'')
			expand_line_single_q(line, &word);
		else if (**line == '\"')
			expand_line_double_q(env, line, &word);
		else if (**line == '$')
			expand_line_dollar(env, line, &word);
		else
			expand_line_char(line, &word);
	}
	return (word);
}

int	itoa_heredoc(char *num, int count)
{
	if (count > 9999)
		return (0);
	num[0] = (count / 1000) + '0';
	num[1] = ((count / 100) % 10) + '0';
	num[2] = ((count / 10) % 10) + '0';
	num[3] = (count % 10) + '0';
	num[4] = 0;
	return (1);
}

char	*heredoc_filename(int count)
{
	int		i;
	int		j;
	char	num[5];
	char	*name;

	i = 0;
	if (!itoa_heredoc(num, count))
		return (NULL);
	name = ft_calloc(30, sizeof(char));
	if (!name)
		return (NULL);
	while (HEREDOC_PREFIX[i])
	{
		name[i] = HEREDOC_PREFIX[i];
		i++;
	}
	j = 0;
	while (j < 5)
	{
		name[i + j] = num[j];
		j++;
	}
	return (name);
}

// TODO HANDLE !NAME
void	handle_heredoc(t_cmds *cmds, t_env *env, char **line)
{
	static int	count = 0;
	char		*delim;
	char		*name;
	char		*heredoc_line;
	int			fd;
	extern int	g_signal_received;


	while (ft_isspace(**line))
		(*line)++;
	delim = parse_word(env, line);
	name = heredoc_filename(count);
	if (!name)
		return ;
	if (cmds->infile)
	{
		if (!ft_strncmp(cmds->infile, "/tmp/.heredoc", 14))
			unlink(cmds->infile);
		free(cmds->infile);
	}
	cmds->infile = name;
	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	count++;
	while (1)
	{
		heredoc_line = readline("mini heredoc> ");
		if (g_signal_received)
		{
			g_signal_received = 0;
			break;
		}
		if (!heredoc_line || !ft_strncmp(heredoc_line, delim, ft_strlen(delim))\
&& !heredoc_line[ft_strlen(delim)])
			break ;
		write(fd, heredoc_line, ft_strlen(heredoc_line));
		write(fd, "\n", 1);
		free(heredoc_line);
	}
	free(heredoc_line);
	free(delim);
	close(fd);
}

void	handle_infile(t_cmds *cmds, t_env *env, char **line)
{
	char	*file;

	(*line)++;
	if (**line == '<')
	{
		(*line)++;
		handle_heredoc(cmds, env, line);
		return ;
	}
	while (ft_isspace(**line))
		(*line)++;
	if (!(**line))
		return ;
	file = parse_word(env, line);
	if (!file)
		return ;
	if (cmds->infile)
		free(cmds->infile);
	cmds->infile = file;
}

void	handle_outfile(t_cmds *cmds, t_env *env, char **line)
{
	char	*file;

	(*line)++;
	if (**line == '>')
	{
		(*line)++;
		cmds->append = 1;
	}
	while (ft_isspace(**line))
		(*line)++;
	if (!(**line))
		return ;
	file = parse_word(env, line);
	if (!file)
		return ;
	if (cmds->outfile)
	{
		close(open(cmds->outfile, O_WRONLY | O_CREAT, 0644));
		free(cmds->outfile);
	}
	cmds->outfile = file;
}

void	handle_pipe(t_cmds **cmds, char **line)
{
	t_cmds	*newnode;
	t_cmds	*head;

	(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	newnode = cmd_new_node();
	if (!newnode)
		return ;
	head = cmd_first(*cmds);
	cmd_add_back(&head, newnode);
	(*cmds)->ispiped = 1;
	*cmds = (*cmds)->next;
}

void	make_cmds(t_cmds *cmds, t_env *env, char *line)
{
	char	*cmd;
	char	*expandedline;

	cmd = NULL;
	expandedline = NULL;
	while (*line)
	{
		if (*line == '<')
			handle_infile(cmds, env, &line);
		else if (*line == '>')
			handle_outfile(cmds, env, &line);
		else if (*line == '|')
		{
			expand_line_space(cmds, &line, &expandedline);
			handle_pipe(&cmds, &line);
			continue ;
		}
		else if (*line == '\'')
			expand_line_single_q(&line, &expandedline);
		else if (*line == '\"')
			expand_line_double_q(env, &line, &expandedline);
		else if (*line == '$')
			expand_line_dollar(env, &line, &expandedline);
		else if (!isspace(*line) && *line)
			expand_line_char(&line, &expandedline);
		if (isspace(*line) || !(*line))
			expand_line_space(cmds, &line, &expandedline);
	}
	cmds = cmd_first(cmds);
}
