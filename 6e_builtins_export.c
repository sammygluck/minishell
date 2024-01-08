/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6e_builtins_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:57:47 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 11:57:50 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **argv, char ***env, t_env_var **list)
{
	t_export	key_value;
	int			i;

	i = 1;
	key_value.key = NULL; //is this necessary? can we boil this down to one function?
	key_value.value = NULL;
	if (!argv)
	{
		ft_putstr_fd("minishell: export: fatal error\n", 2);
		exit(EXIT_FAILURE); //is exit appropriate or return (1)?
	}
	if (!argv[1])
		modified_ft_env(*list);//make sure to set the right parameter; must I return or will I automatically return at the end (0 is the ret value)
	while (argv[i])
	{
		if (is_right_format(argv[i])) //i.e. key=value + check for valid identifier issue
		{
			extract_key_value(argv[i], &key_value);
			update(&key_value, env, list); //i.e. seperate the key from value and update t_env list & char **env
		}
		// if (!right_format) //is this necessary?
		//     error for this argument or skip this 
		i++;
	}
	free_key_value(&key_value);
	return (0); 
}
