/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6e_builtins_export_utils_b.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:00:26 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/17 13:20:49 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_exists_and_updated(t_export *key_value,
		t_env_var **env_list, int append)
{
	t_env_var	*head;

	head = *env_list;
	while (head)
	{
		if (compare_key_length(key_value, head))
		{
			if (update_env_value(key_value, head, append))
				return (1);
		}
		head = head->next;
	}
	return (0);
}

int	update_env_value(t_export *key_value, t_env_var *env_var, int append)
{
	char	*temp;

	if (!strncmp(key_value->key, env_var->name, ft_strlen(env_var->name)))
	{
		if (append && env_var->value)
		{
			temp = ft_strjoin(env_var->value, key_value->value);
			free(env_var->value);
			env_var->value = temp;
		}
		else
		{
			if (env_var->value)
				free(env_var->value);
			env_var->value = ft_strdup(key_value->value);
		}
		return (1);
	}
	return (0);
}

int	compare_key_length(t_export *key_value, t_env_var *env_var)
{
	int	key_value_length;
	int	env_var_name_length;

	key_value_length = ft_strlen(key_value->key);
	env_var_name_length = ft_strlen(env_var->name);
	if (key_value_length == env_var_name_length)
		return (1);
	else
		return (0);
}

void	extract_key_value(char *string, t_export *key_value, int *append)
{
	int	i;

	i = 0;
	free_key_value(key_value);
	while (string[i])
	{
		if (string[i] == '+' && string[i + 1] == '=')
		{
			*append = 1;
			break ;
		}
		if (string[i] == '=')
			break ;
		i++;
	}
	key_value->key = ft_strndup(string, i);
	if (*append)
		i += 2;
	else
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
