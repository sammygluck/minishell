/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6g_builtins_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:42:55 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 10:07:14 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **argv)
{
	int	exit_code;

	if (!argv)
		exit(EXIT_FAILURE);
	if (!argv[1])
		final_exit(g_last_exit_code);
	else if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (argv[1])
	{
		exit_code = validate_and_process_exit_code(argv[1]);
		if (exit_code != -1)
			final_exit(exit_code);
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
			final_exit(2);
		}
	}
	return (0);
}

void	final_exit(int exit_number)
{
	// cleanup?
	printf("exit\n");
	exit(exit_number);
}
