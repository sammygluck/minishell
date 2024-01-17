/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7b_signals_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:50:33 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/17 09:50:36 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal_handler(int i)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	if (i == HEREDOC_PARENT)
	{
		act.sa_handler = &h_parent_signal;
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == HEREDOC_CHILD)
	{
		act.sa_handler = &h_child_signal;
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	h_parent_signal(int signal)
{
	if (signal == SIGINT)
		g_last_exit_code = 130;
}

void	h_child_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_last_exit_code = 130;
		ft_putstr_fd("\n", 1);
		exit(130);
	}
}
