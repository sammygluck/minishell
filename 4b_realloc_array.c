/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4b_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:22:32 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 09:57:05 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_array(char **argv, int argc)
{
	char	**new_argv;
	int		i;

	new_argv = ft_malloc((argc + 2) * sizeof(char *));
	i = 0;
	while (i < argc)
	{
		new_argv[i] = argv[i];
		i++;
	}
	new_argv[argc] = NULL;
	new_argv[argc + 1] = NULL;
	if (argv)
		free(argv);
	return (new_argv);
}
