/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_mini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:28:16 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/09 11:47:50 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"
#include "minishell.h"

/// @brief splits the arguments into the environment argument name and value
/// @param str	argument string: name[=value]
/// @param v_name	environment argument name
/// @param v_value	environment argument value
/// @return on error returns EXIT_FAILURE, otherwise returns EXIT_SUCCES
static int	split_first_equals(char *str, char **v_name, char **v_value)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		i++;
	}
	*v_name = ft_strndup(str, i);
	if (*v_name == NULL)
		return (EXIT_FAILURE);
	if (str[i] == '\0')
	{
		*v_value = NULL;
		return (EXIT_SUCCESS);
	}
	str += i + 1;
	*v_value = ft_strndup(str, ft_strlen(str));
	if (*v_value == NULL)
		return (free(v_name), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/// @brief checks if the v_name is a valid identifier for export.
/// @param str the v_name to check
/// @return returns 0 when not valid, 1 when valid
static int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') \
|| str[i] == '_'))
		return (0);
	i++;
	while (is_valid_in_name(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

/// @brief processes every seperate argument of export
/// @param str	the argument string
/// @param head	environment variable linked list
/// @return EXIT_SUCCES on succes, EXIT_FAILURE on failure
static int	process_args(char *str, t_env *head)
{
	char	*v_name;
	char	*v_value;

	if (split_first_equals(str, &v_name, &v_value) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (is_valid_identifier(v_name) != 1)
	{
		write(2, "export: not a valid identifier\n", 31);
		return (free(v_name), free(v_value), -1);
	}
	if (v_value == NULL && env_var_exists(head, v_name) == 1)
		env_set_hidden_0(head, v_name);
	else
		update_env(head, v_name, v_value);
	return (free(v_name), EXIT_SUCCESS);
}

/// @brief prints formatted environment variable
/// @param head environment variable linked list
static void	print_export(t_env *head)
{
	while (head)
	{
		if (head->is_hidden != 1)
		{
			write(1, "declare -x ", 11);
			write(1, head->v_name, ft_strlen(head->v_name));
			if (head->v_val != NULL)
			{
				write(1, "=\"", 2);
				write(1, head->v_val, ft_strlen(head->v_val));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		head = head->next;
	}
}

int	export_mini(t_cmds *cmds)
{
	int	i;
	int	return_val;
	int	exit_val;

	i = 0;
	exit_val = 0;
	if (n_args(cmds->args) == 0)
		print_export(cmds->info->head);
	else
	{
		while (cmds->args[i] != NULL)
		{
			return_val = process_args(cmds->args[i], cmds->info->head);
			if (return_val == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (return_val == -1)
				exit_val = 1;
			i++;
		}
	}
	return (exit_val);
}
