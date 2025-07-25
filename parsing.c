/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdreijer <fdreijer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:40:44 by fdreijer          #+#    #+#             */
/*   Updated: 2025/07/25 10:25:21 by fdreijer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns head->v_val if str == v_name and is followed by '\0' or ' '
char *return_env(t_env *head, char *str)
{
	if (*str != '$')
		return (NULL);
	str++;
	while (head)
	{
		if (!ft_strncmp(head->v_name, str, ft_strlen(head->v_name)))
			if (!is_valid_in_name(str[ft_strlen(head->v_name)]))
				return (head->v_val);
		head = head->next;
	}
	return (NULL);
}

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

void	expand_line_dollar(t_env *head, char **line, char **expandedline)
{
	int	envlen;
	char *env;
	int	expandedlen;

	if (**line != '$')
		return ;
	expandedlen = ft_strlen(*expandedline);
	env = return_env(head, *line);
	envlen = ft_strlen(env);
	*expandedline = ft_realloc(*expandedline, expandedlen, expandedlen + envlen + 1);
	if (*expandedline == NULL)
		return ;
	ft_memmove(&(*expandedline)[expandedlen], env, envlen);
	(*line)++;
	while (is_valid_in_name(**line))
		(*line)++;
}

void	expand_line_double_q(t_env *head, char **line, char **expandedline)
{
	int newlen;
	int	expandedlen;
	int	envlen;
	char *env;

	newlen = 0;
	expandedlen = 0;
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '$')
			expand_line_dollar(head, line, expandedline);
		else
			expand_line_char(line, expandedline);
		if (*expandedline == NULL)
			return ;
	}
	(*line)++;
}


void	expand_line_single_q(char **line, char **expandedline)
{
	int	i;
	int start;
	int	expandedlen;

	i = 0;
	(*line)++;
	while ((*line)[i] && (*line)[i] != '\'')
		i++;
	expandedlen = ft_strlen(*expandedline);
	*expandedline = ft_realloc(*expandedline, expandedlen, expandedlen + i + 1);
	if (*expandedline == NULL)
		return ;
	start = 0;
	while (start < i)
	{
		(*expandedline)[expandedlen + start] = (*line)[start];
		start++;
	}
	*line += i + 1;
}

t_cmds *make_cmds(t_env *head, char *line)
{
	char *expandedline;

	expandedline = NULL;
	while (*line)
	{
		if (*line == '\'')
			expand_line_single_q(&line, &expandedline);
		if (*line == '\"')
			expand_line_double_q(head, &line, &expandedline);
		if (*line  == '$')
			expand_line_dollar(head, &line, &expandedline);
		else
			expand_line_char(&line, &expandedline);
		if (*expandedline == NULL)
			return (NULL);
	}
	printf("%s\n", expandedline);
	return (NULL);
}



int main(int argc, char **argv, char **envp)
{
	t_env	*env = init_env(envp);
	make_cmds(env, "abcdef\"\'abc$USER-aaaaaa-$HOME--\'\"");
	// while (env)
	// {
	// 	printf("%s=%s\n", env->v_name, env->v_val);
	// 	env = env->next;
	// }
}
