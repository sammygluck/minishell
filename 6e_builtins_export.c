/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6e_builtins_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:57:47 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/25 10:22:55 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **argv, char ***env, t_env_var **list)
{
	t_export	key_value;

	if (!ft_export_init(argv, list, &key_value))
		return (1);
	return (ft_export_process_args(argv, env, list, &key_value));
}

int	ft_export_init(char **argv, t_env_var **list, t_export *key_value)
{
	key_value->key = NULL;
	key_value->value = NULL;
	if (!argv)
	{
		ft_putstr_fd("minishell: export: fatal error\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!argv[1])
		modified_ft_env(*list);
	return (1);
}

int	ft_export_process_args(char **argv, char ***env,
		t_env_var **list, t_export *key_value)
{
	int	i;
	int	ret_value;
	int	append;

	i = 1;
	ret_value = 0;
	while (argv[i])
	{
		append = 0;
		if (is_right_format(argv[i]))
		{
			extract_key_value(argv[i], key_value, &append);
			update(key_value, env, list, append);
		}
		else
			ret_value = 1;
		i++;
	}
	free_key_value(key_value);
	return (ret_value);
}
