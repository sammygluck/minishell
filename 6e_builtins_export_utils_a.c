/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6e_builtins_export_utils_a.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:00:06 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/25 10:49:36 by jsteenpu         ###   ########.fr       */
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

void	update(t_export *key_value, char ***env,
		t_env_var **env_list, int append)
{
	t_env_var	*new_node;

	new_node = NULL;
	if (!arg_exists_and_updated(key_value, env_list, append))
	{
		new_node = create_env_var_key_value(key_value);
		add_env_var(env_list, new_node);
	}
	free_old_env(*env);
	*env = mirror_list_to_array(*env_list);
}

void	modified_ft_env(t_env_var *env)
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

int	valid_identifiers(char *string)
{
	int	i;

	i = 0;
	if (!string || string[0] == '\0')
	{
		print_export_error(0);
		return (0);
	}
	if (!is_alpha_under(string[i]))
	{
		print_export_error(1);
		return (0);
	}
	i++;
	while (string[i] && !is_valid_sep(string, i))
	{
		if (!is_alpha_under(string[i]) && !ft_isdigit(string[i]))
		{
			print_export_error(2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	print_export_error(int i)
{
	ft_putstr_fd("minishell: export: Error: ", 2);
	if (i == 0)
		ft_putendl_fd("Empty string or null pointer", 2);
	else if (i == 1)
		ft_putendl_fd("not a valid identifier", 2);
	else if (i == 2)
		ft_putendl_fd("not a valid identifier", 2);
}
