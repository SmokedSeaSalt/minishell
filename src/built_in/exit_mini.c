/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:26:48 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/25 16:11:05 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"

void	exit_with_val(int value, t_cmds *cmds)
{
	free_env(cmds->info->head);
	free_cmds(cmds);
	exit(value);
}

void	free_env(t_env *head)
{
	t_env	*tmp;

	while (head != NULL)
	{
		tmp = head;
		free(tmp->v_name);
		tmp->v_name = NULL;
		free(tmp->v_val);
		tmp->v_val = NULL;
		head = head->next;
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

//TODO different behaviour if exit is piped or not
//TODO exit a a
//TODO write exit to 1 so doesnt get piped mayb
int	exit_mini(t_cmds *cmds)
{
	char	exitval;

	if (!(cmds->ispiped || (cmds->prev && cmds->prev->ispiped)))
		write(2, "exit\n", 5);
	if (n_args(cmds->args) == 0)
		exit_with_val(cmds->info->last_exit_val, cmds);
	if (n_args(cmds->args) == 1)
	{
		if (is_only_num(cmds->args[0]) == 1)
		{
			exitval = (unsigned char)atoi(cmds->args[0]);
			exit_with_val(exitval, cmds);
		}
		else
		{
			write(2, "minishell: exit: ", 17);
			write(2, cmds->args[0], ft_strlen(cmds->args[0]));
			write(2, ": numeric argument required\n", 28);
			exit_with_val(2, cmds);
		}
	}
	if (n_args(cmds->args) > 1)
		write(2, "minishell: exit: too many arguments\n", 36);
	return (1);
}
