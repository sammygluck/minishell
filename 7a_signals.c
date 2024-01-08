/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7a_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:41:22 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 10:42:00 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//global variable sigint = 130; sigquit = 131
void	interactive(void)
{
	struct sigaction	act;

	sigquit_ign();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &new_prompt;
	sigaction(SIGINT, &act, NULL);
}

void	sigquit_ign(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	new_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &write_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	write_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}
