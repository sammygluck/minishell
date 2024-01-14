/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3e_expander_utils_env_handler.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:13:26 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/03 13:13:33 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*environment_var_handler(char **env)
{
	t_env_var	*new_env;
	t_env_var	*var_head;
	char		*current_env;
	int			i;

	if (!env || !*env)
	{
		ft_putendl_fd("minishell: error: no valid env", 2);
		exit(EXIT_FAILURE);
	}
	var_head = NULL;
	i = 0;
	while (env[i])
	{
		current_env = env[i];
		new_env = create_env_var(current_env);
		add_env_var(&var_head, new_env);
		i++;
	}
	return (var_head);
}

t_env_var	*create_env_var(char *current_env)
{
	t_env_var	*env_var;

	env_var = ft_malloc(sizeof(t_env_var));
	env_var->name = extract_var_name(current_env);
	env_var->value = extract_var_value(current_env);
	env_var->next = NULL;
	return (env_var);
}

char	*extract_var_name(char *current_env)
{
	int		len;
	char	*extracted;

	len = 0;
	while (current_env[len] && current_env[len] != '=')
		len++;
	extracted = ft_strndup(current_env, len);
	return (extracted);
}

char	*extract_var_value(char *current_env)
{
	int		len;
	char	*extracted;

	len = 0;
	while (current_env[len] && current_env[len] != '=')
		len++;
	if (current_env[len] == '=')
		len++;
	else
		return (NULL);
	extracted = ft_strdup(&current_env[len]);
	return (extracted);
}

void	add_env_var(t_env_var **env_head, t_env_var *env_var)
{
	t_env_var	*head;

	if (!env_head || !env_var)
	{
		ft_putstr_fd("failure in env variable creation", 2);
		exit(EXIT_FAILURE);
	}
	if (!*env_head)
	{
		*env_head = env_var;
		return ;
	}
	head = *env_head;
	while (head->next)
		head = head->next;
	head->next = env_var;
}
