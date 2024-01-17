/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6e_builtins_export_utils_a.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:00:06 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/17 09:22:36 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*create_env_var_key_value(t_export *key_value)
{
	t_env_var	*env_var;

	env_var = ft_malloc(sizeof(t_env_var));
	env_var->name = ft_strdup(key_value->key);
	env_var->value = ft_strdup(key_value->value);
	env_var->next = NULL;
	return (env_var);
}

void	update(t_export *key_value, char ***env, t_env_var **env_list) //return value?
{
	t_env_var	*new_node;

	new_node = NULL;
	if (!arg_exists_and_updated(key_value, env_list))
	{
		new_node = create_env_var_key_value(key_value);
		add_env_var(env_list, new_node);
	}
	free_old_env(*env);
	*env = mirror_list_to_array(*env_list);
}

void	modified_ft_env(t_env_var *env)//parameters + check again if works
{
	t_env_var	*head;

	if (!env)
		return ;
	head = env;
	while (head)
	{
		if (head->value != NULL)
			printf("declare -x %s=\"%s\"\n", head->name, head->value);
		head = head->next;
	}
	return ;
}

int	is_right_format(char *string)
{
	if (!valid_identifiers(string))
		return (0);
	if (!has_equal_sign(string))
		return (0);
	return (1);
}

int	valid_identifiers(char *string)
{
	int	i;

	i = 0;
	if (!string || string[0] == '\0')
	{
		ft_putstr_fd("minishell: export: Error: Empty string or null pointer\n", 2);
		return (0);
	}
	// Check first character
	if (!is_alpha_under(string[i]))
	{
		ft_putstr_fd("minishell: export: Error: First character is not a valid identifier\n", 2);
		return (0);
	}
	i++;
	while (string[i] && string[i] != '=')
	{
		if (!is_alpha_under(string[i]) && !ft_isdigit(string[i]))
		{
			ft_putstr_fd("minishell: export: Error: Invalid character in identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
