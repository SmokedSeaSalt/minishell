/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:21:56 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/23 14:16:53 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_cmds_h(t_cmds **cmds, t_env *env, char **line, char **expandedline)
{
	if (**line == '<')
		handle_infile(*cmds, env, line);
	else if (**line == '>')
		handle_outfile(*cmds, env, line);
	else if (**line == '|')
	{
		expand_line_space(*cmds, line, expandedline);
		handle_pipe(cmds, (*cmds)->info, line);
		return ;
	}
	else if (**line == '\'')
		expand_line_single_q(line, expandedline);
	else if (**line == '\"')
		expand_line_double_q(*cmds, env, line, expandedline);
	else if (**line == '$')
		expand_line_dollar(*cmds, env, line, expandedline);
	else if (!isspace(**line) && **line)
		expand_line_char(line, expandedline);
	if (isspace(**line) || !(**line))
		expand_line_space(*cmds, line, expandedline);
}

void	make_cmds(t_cmds *cmds, t_env *env, char *line)
{
	char	*expandedline;
	t_info	*info;

	expandedline = NULL;
	info = ft_calloc(sizeof(t_info), 1);
	info->head = env;
	cmds->info = info;
	while (*line)
		make_cmds_h(&cmds, env, &line, &expandedline);
	cmds = cmd_first(cmds);
}

//pass any cmds node and free all of them
void	free_cmds(t_cmds *node)
{
	t_cmds	*tmp;

	free(node->info);
	while (node->prev != NULL)
		node = node->prev;
	while (node != NULL)
	{
		tmp = node;
		free_cmds_node(tmp);
		node = node->next;
		free(tmp);
		tmp = NULL;
	}
}

//free's all the content of the given node
void	free_cmds_node(t_cmds *node)
{
	int	i;

	if (node->infile && !ft_strncmp(node->infile, "/tmp/.heredoc_", 14))
		unlink(node->infile);
	free(node->cmdpath);
	node->cmdpath = NULL;
	free(node->cmd);
	node->cmd = NULL;
	free(node->infile);
	node->infile = NULL;
	free(node->outfile);
	node->outfile = NULL;
	i = 0;
	if (node->args != NULL)
	{
		while (node->args[i] != NULL)
		{
			free(node->args[i]);
			node->args[i] = NULL;
			i++;
		}
		free(node->args);
		node->args = NULL;
	}
}
