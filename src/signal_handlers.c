/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:58:46 by fdreijer          #+#    #+#             */
/*   Updated: 2025/08/29 10:09:42 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> //to use signals
#include "minishell.h"

volatile int	g_signal_received = 0;

void	parent_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_sigint_handler(int sig)
{
	g_signal_received = sig;
}

int	heredoc_sig_hook(void)
{
	if (g_signal_received == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_done = 1;
	}
	return 0;
}