/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6c_builtins_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:32:24 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/24 15:05:13 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env_var **env_l)
{
	t_env_var	*head;

	head = *env_l;
	if (!check_path_var(env_l))
		return (1);
	if (!env_l || !head)
	{
		ft_putstr_fd("no env variables\n", 2);
		return (1);
	}
	while (head)
	{
		if (head->value == NULL)
		{
			head = head->next;
			continue ;
		}
		printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
	return (0);
}

int	check_path_var(t_env_var **env_l)
{
	char	*value;

	value = get_env_value(*env_l, "PATH");
	if (!value)
	{
		ft_putendl_fd("minishell: env: No such file or directory", 2);
		return (0);
	}
	else
		return (1);
}
