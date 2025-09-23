/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:40:44 by fdreijer          #+#    #+#             */
/*   Updated: 2025/09/23 14:15:49 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_empty_cmds_h(t_cmds *cmds)
{
	int	i;

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
			fix_empty_cmds_h(cmds);
		cmds = cmds->next;
	}
}

char	*parse_word(t_cmds *cmds, t_env *env, char **line)
{
	char	*word;

	word = NULL;
	while (**line && !ft_isspace(**line) \
&& **line != '<' && **line != '>' && **line != '|')
	{
		if (**line == '\'')
			expand_line_single_q(line, &word);
		else if (**line == '\"')
			expand_line_double_q(cmds, env, line, &word);
		else if (**line == '$')
			expand_line_dollar(cmds, env, line, &word);
		else
			expand_line_char(line, &word);
	}
	return (word);
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
		return ;
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
		return ;
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
	file = parse_word(cmds, env, line);
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
	file = parse_word(cmds, env, line);
	if (!file)
		return ;
	if (cmds->outfile)
	{
		free(cmds->outfile);
		cmds->outfile = NULL;
	}
	cmds->outfile = file;
	if (!cmds->permission_denied)
		check_file(cmds, cmds->append + 1);
}

void	handle_pipe(t_cmds **cmds, t_info *info, char **line)
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
	newnode->info = info;
	(*cmds)->ispiped = 1;
	*cmds = (*cmds)->next;
}
