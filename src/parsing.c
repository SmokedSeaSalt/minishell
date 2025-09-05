/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:40:44 by fdreijer          #+#    #+#             */
/*   Updated: 2025/09/05 12:58:48 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_empty_cmds(t_cmds *cmds)
{
	int	i;

	while (cmds)
	{
		i = 0;
		if (!cmds->cmd)
		{
			cmds = cmds->next;
			continue ;
		}
		while (ft_isspace(cmds->cmd[i]))
			i++;
		if (!cmds->cmd[i])
		{
			free(cmds->cmd);
			if (!cmds->args)
				cmds->cmd = NULL;
			else
			{
				cmds->cmd = cmds->args[0];
				i = -1;
				while (cmds->args[++i])
					cmds->args[i] = cmds->args[i + 1];
			}
		}
		cmds = cmds->next;
	}
}

char	*parse_word(t_env *env, char **line)
{
	char	*word;

	//TODO DONT EXPAND ENV IF IN HEREDOC
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

void	handle_heredoc(t_cmds *cmds, t_env *env, char **line)
{
	static int	count = 0;
	char		*delim;
	char		*name;
	char		*heredoc_line;
	int			fd;
	extern int	g_signal_received;

	// TODO HANDLE !NAME
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
	set_signals_heredoc();
	rl_event_hook = heredoc_sig_hook;
	while (1)
	{
		heredoc_line = readline("mini heredoc> ");
		if (g_signal_received)
		{
			g_signal_received = 0;
			break ;
		}
		if (!heredoc_line)
			write(2, "Warning: heredoc delimited by end-of-file\n", 42);
		if (!heredoc_line || !ft_strncmp(heredoc_line, delim, \
ft_strlen(delim)) && !heredoc_line[ft_strlen(delim)])
			break ;
		write(fd, heredoc_line, ft_strlen(heredoc_line));
		write(fd, "\n", 1);
		free(heredoc_line);
	}
	set_signals_default();
	rl_event_hook = NULL;
	free(heredoc_line);
	free(delim);
	close(fd);
	if (cmds->permission_denied)
	{
		unlink(cmds->infile);
		free(cmds->infile);
		cmds->infile = NULL;
	}
}

void	check_file(t_cmds *cmds, int mode)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(cmds->infile, O_RDONLY);
		if (fd == -1)
			cmds->permission_denied = 1;
		else
			close(fd);
		return;
	}
	else
	{
		if (mode == 1)
			fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(cmds->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			cmds->permission_denied = 1;
		else
			close(fd);
		return;
	}
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
	check_file(cmds, 0);
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
		free(cmds->outfile);
		cmds->outfile = NULL;
	}
	if (!cmds->permission_denied)
		cmds->outfile = file;
	if (!cmds->permission_denied)
		check_file(cmds, cmds->append + 1);
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
