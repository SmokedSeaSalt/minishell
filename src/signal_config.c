/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:49:51 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/08/28 16:59:10 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> //to use signals
#include "minishell.h"

int	set_signals_default(void)
{
	struct sigaction	sa;

	sa.sa_handler = parent_sigint_handler;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (-1);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (0);
}

int	set_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (-1);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (0);
}

int	set_signals_ignore(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (-1);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (0);
}

int	set_signals_heredoc(void)
{
	struct sigaction	sa;

	//TODO check all CTRL+D, CTRL+C, CTRL+'\'
	sa.sa_handler = heredoc_sigint_handler;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (-1);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (0);
}
