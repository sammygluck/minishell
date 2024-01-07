/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6b_builtins_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:30:10 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 11:30:12 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv) // do I need to add other parameters??
{
	char	buffer[PATH_MAX];

	(void) argv;
	if (!getcwd(buffer, PATH_MAX))
	{
		perror("pwd error\n"); //is newline necessary?
		return (1);
	}
	printf("%s\n", buffer);
	return (0);
}
