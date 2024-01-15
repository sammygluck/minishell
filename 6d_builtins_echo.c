/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6d_builtins_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:35:41 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 10:01:24 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
{
	int	flag_n;
	int	i;

	if (!argv || !*argv)
		exit(EXIT_FAILURE);
	flag_n = 0;
	i = 1;
	if (argv[i] && only_n(argv[i]))
	{
		flag_n = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	only_n(char *string)
{
	int	i;

	i = 1;
	if (!string)
		return (0);
	if (string[0] != '-')
		return (0);
	while (string[i])
	{
		if (string[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}
