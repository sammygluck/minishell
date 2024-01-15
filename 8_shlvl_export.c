/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_shlvl_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:35:17 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 10:09:48 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_export(char ***env, t_env_var **env_l)
{
	char	*argv[3];
	char	*shell_level;
	char	*shell_argument;
	int		level_to_int;

	shell_level = get_env_value(*env_l, "SHLVL");
	if (!shell_level)
		shell_level = ft_strdup("0");
	level_to_int = ft_atoi(shell_level);
	level_to_int++;
	free(shell_level);
	shell_level = ft_itoa(level_to_int);
	shell_argument = ft_strjoin("SHLVL=", shell_level);
	argv[0] = "export";
	argv[1] = shell_argument;
	argv[2] = NULL;
	ft_export(argv, env, env_l);
	free(shell_level);
	free(shell_argument);
}

// //cd has duplicate of this function, remove one of the two
// char	*return_env_value(char *string, t_env_var *env_l)
// {
// 	t_env_var	*head;
// 	size_t		string_len;

// 	if (!env_l || !string)
// 		return (NULL);
// 	string_len = ft_strlen(string);
// 	head = env_l;
// 	while (head)
// 	{
// 		if (ft_strlen(head->name) == string_len
// 			&& !ft_strncmp(head->name, string, string_len))
// 			return (ft_strdup(head->value));
// 		head = head->next;
// 	}
// 	return (NULL);
// }
