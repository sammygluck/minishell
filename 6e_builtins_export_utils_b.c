/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6e_builtins_export_utils_b.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:00:26 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 12:00:31 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_equal_sign(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '=')
			return (1);
		i++;
	}
	ft_putstr_fd("minishell: export: Error: '=' not found in the string\n", 2);
	return (0);
}

int	is_alpha_under(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	else
		return (0);
}

int	arg_exists_and_updated(t_export *key_value, t_env_var **env_list)
{
	t_env_var	*head;

	head = *env_list;
	while (head)
	{
		if (ft_strlen(key_value->key) == ft_strlen(head->name))
		{
			if (!strncmp(key_value->key, head->name, ft_strlen(head->name)))
			{
				if (head->value)
					free(head->value);
				head->value = ft_strdup(key_value->value);
				return (1);
			}
		}
		head = head->next;
	}
	return (0); 
}

void	extract_key_value(char *string, t_export *key_value)
{
	int	i;

	i = 0;
	free_key_value(key_value); //issue 1. when it's empty i.e. first time
	while (string[i] && string[i] != '=')
		i++;
	key_value->key = ft_strndup(string, i);
	i++;
	key_value->value = ft_strdup(&string[i]);
}

void	free_key_value(t_export *key_value)
{
	if (key_value->key)
	{
		free(key_value->key);
		key_value->key = NULL;
	}
	if (key_value->value)
	{
		free(key_value->value);
		key_value->value = NULL;
	}
}
