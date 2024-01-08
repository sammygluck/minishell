/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6a_builtins_unset_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:24:30 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 11:28:32 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_in_env(char *string, t_env_var **env_list)
{
	t_env_var	*head;

	head = *env_list;
	while (head)
	{
		if (!strncmp(string, head->name, ft_strlen(string) + 1))
		{
			free(head->value);
			head->value = NULL;
			return (1);
		}
		head = head->next;
	}
	return (0);
}

void	free_old_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i])
			free(env[i]);
		i++;
	}
	if (env)
		free(env);
}

char	**mirror_list_to_array(t_env_var *list)
{
	char	**env;
	int		arr_size;

	env = NULL;
	arr_size = 0;
	while (list)
	{
		if (list->name && list->value)
		{
			env = realloc_array(env, arr_size);
			env[arr_size] = ft_env_join(list->name, list->value);
			env[arr_size + 1] = NULL;
			arr_size++;
		}
		list = list->next;
	}
	return (env);
}

char	*ft_env_join(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joined[j++] = s1[i++];
	joined[j++] = '=';
	i = 0;
	while (s2[i])
		joined[j++] = s2[i++];
	joined[j] = '\0';
	return (joined);
}
