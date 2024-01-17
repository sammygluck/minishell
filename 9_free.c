/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 09:51:55 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/17 09:52:08 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token **head)
{
	t_token	*old_head;
	t_token	*new_head;

	old_head = *head;
	while (old_head)
	{
		new_head = old_head->next;
		if (old_head->string)
			free(old_head->string);
		if (old_head)
			free(old_head);
		old_head = new_head;
	}
}

//free char **env
void	free_char_env(char **env)
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

//free t_env_var *env
void	free_env_list(t_env_var **head)
{
	t_env_var	*old_head;
	t_env_var	*new_head;

	old_head = *head;
	while (old_head)
	{
		new_head = old_head->next;
		if (old_head->name)
			free(old_head->name);
		if (old_head->value)
			free(old_head->value);
		if (old_head)
			free(old_head);
		old_head = new_head;
	}
}

void	free_redirection_list(t_redir **head)
{
	t_redir	*old_head;
	t_redir	*new_head;

	old_head = *head;
	while (old_head)
	{
		new_head = old_head->next;
		if (old_head->file)
			free(old_head->file);
		if (old_head)
			free(old_head);
		old_head = new_head;
	}
}

void	free_cmd_list(t_cmd **head)
{
	t_cmd	*old_head;
	t_cmd	*new_head;

	old_head = *head;
	while (old_head)
	{
		new_head = old_head->next;
		if (old_head->argv)
			free_char_env(old_head->argv);
		if (old_head->redir)
			free_redirection_list(&old_head->redir);
		if (old_head)
			free(old_head);
		old_head = new_head;
	}
}
