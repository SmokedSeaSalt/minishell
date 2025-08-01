/* ************************************************************************** */
/*                                                                            */
/*                                                       ,--------------      */
/*                                                      /                     */
/*                                                     /                      */
/*                                                    /   ,--,/      ,--      */
/*                                                    |  /  ,'    ,·´         */
/*                                                    |  ;·'   ,·´            */
/*   exit_mini.c                                      |  ;  ,·´               */
/*                                                    |  :,'                  */
/*   By: mvan-rij <mvan-rij@student.42.fr>             `´.                    */
/*                                                      .¨.                   */
/*   Created: 2025/07/25 11:17:23 by mvan-rij           ¨· .                  */
/*   Updated: 2025/07/29 15:55:09 by mvan-rij          :. ¨.                  */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"

static int	n_args(char **args)
{
	int i;

	i = 0;
	while (!args && !args[i])
		i++;
	return (i);
}

void exit_with_val(int value, t_cmds *cmds)
{
	free_env(cmds->info->head);
	free_cmds(cmds);
	exit(value);
}

void free_env(t_env *head)
{
	t_env *tmp;

	while (tmp != NULL)
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
void free_cmds_node(t_cmds *node)
{
	int i;

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
void free_cmds(t_cmds *node)
{
	t_cmds *tmp;
	int i;

	while (node->prev != NULL)
		node = node->prev;
	while (node != NULL)
	{
		tmp = node;
		free_cmds_node(tmp);
		free(tmp);
		tmp == NULL;
		node = node->next;
	}
}

//TODO different behaviour if exit is piped or not
int	exit_mini(t_cmds *cmds)
{
	char exitval;

	write(2, "exit\n", 5);
	if (n_args(cmds->args) == 0)
		exit_with_val(cmds->info->last_exit_val, cmds);
	if (n_args(cmds->args) == 1)
	{
		if (is_only_numeric(cmds->args[0]) == 1)
		{
			exitval = (char)atoi(cmds->args[0]);
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
