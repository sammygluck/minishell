/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6a_builtins_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:23:51 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 09:58:21 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **argv, char ***env, t_env_var **env_l) //double check everything!!
{
	int	i;

	if (!argv || !env || !env_l || !*env_l)
		exit(EXIT_FAILURE);
	i = 1;
	//make sure to do some other error checking perhaps
	if (!argv[i])
		return (0);
	while (argv[i])
	{
		arg_in_env(argv[i], env_l);
		i++;
	}
	free_old_env(*env);
	*env = mirror_list_to_array(*env_l);
	return (0);
}
