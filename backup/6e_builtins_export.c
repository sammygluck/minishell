/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6e_builtins_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:57:47 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/14 04:54:09 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **argv, char ***env, t_env_var **list)
{
	t_export	key_value;
	int			i;

	i = 1;
	key_value.key = NULL;
	key_value.value = NULL;
	if (!argv)
	{
		ft_putstr_fd("minishell: export: fatal error\n", 2);
		exit(EXIT_FAILURE);//option return (1)
	}
	if (!argv[1])
		modified_ft_env(*list);
	while (argv[i])
	{
		if (is_right_format(argv[i]))
		{
			extract_key_value(argv[i], &key_value);
			update(&key_value, env, list);
		}
		i++;
	}
	free_key_value(&key_value);
	return (0);
}
