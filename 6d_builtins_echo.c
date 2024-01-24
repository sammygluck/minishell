/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6d_builtins_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:35:41 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/24 14:47:32 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_flags(char **argv, int *flag_n)
{
	int	i;

	*flag_n = 0;
	i = 1;
	while (argv[i])
	{
		if (only_n(argv[i]))
			*flag_n = 1;
		else
			break ;
		i++;
	}
	return (i);
}

void	print_arguments(char **argv, int start_index, int flag_n)
{
	while (argv[start_index])
	{
		ft_putstr_fd(argv[start_index], 1);
		if (argv[start_index + 1])
			ft_putstr_fd(" ", 1);
		start_index++;
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
}

int	ft_echo(char **argv)
{
	int	flag_n;
	int	start_index;

	if (!argv || !*argv)
		exit(EXIT_FAILURE);
	start_index = process_flags(argv, &flag_n);
	print_arguments(argv, start_index, flag_n);
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
