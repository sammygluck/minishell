/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6b_builtins_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:30:10 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/24 15:01:21 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env_var **envs)
{
	char	*buffer;

	if (!envs)
		exit(EXIT_FAILURE);
	buffer = get_env_value(*envs, "PWD");
	if (!buffer)
	{
		perror("pwd error");
		return (1);
	}
	printf("%s\n", buffer);
	if (buffer)
		free(buffer);
	return (0);
}

// int	ft_pwd(char **argv)
// {
// 	char	buffer[PATH_MAX];

// 	(void) argv;
// 	if (!getcwd(buffer, PATH_MAX))
// 	{
// 		perror("pwd error");
// 		return (1);
// 	}
// 	printf("%s\n", buffer);
// 	return (0);
// }
