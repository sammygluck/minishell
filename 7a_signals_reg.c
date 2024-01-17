/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7a_signals_reg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:49:52 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/17 09:50:12 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_handler(int i)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	if (i == PROMPT)
	{
		act.sa_handler = &prompt_signal;
		sigaction(SIGINT, &act, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == PARENT)
	{
		act.sa_handler = &p_parent_signal;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
	}
	if (i == FORK)
	{
		act.sa_handler = &p_fork_signal;
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
	}
	return (0);
}

void	prompt_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_last_exit_code = 130;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	p_parent_signal(int signal)
{
	if (signal == SIGINT)
	{	
		g_last_exit_code = 130;
		ft_putstr_fd("\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		g_last_exit_code = 131;
		ft_putstr_fd("Quit\n", 1);
	}
}

void	p_fork_signal(int signal)
{
	if (signal == SIGINT)
		g_last_exit_code = 130;
	else if (signal == SIGQUIT)
		g_last_exit_code = 131;
	exit(g_last_exit_code);
}
