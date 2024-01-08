/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3c_second_clean_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:00:56 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 09:55:31 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expanded(char *string, t_env_var *env_list)
{
	t_begin_end	values;
	char		*to_replace;
	char		*replace_with;
	char		*tmp;
	int			we_done;

	init_begin_end(&values);
	we_done = stuff_to_replace(string, &values);
	if (!we_done)
		return (NULL);
	while (we_done)
	{
		to_replace = extract(string, values.begin, values.end);
		replace_with = make_replace_string(env_list, to_replace);
		tmp = replace(string, replace_with, &values);
		free(to_replace);
		free(replace_with);
		free(string);
		string = tmp;
		we_done = stuff_to_replace(string, &values);
	}
	return (string);
}

char	*extract(char *string, int begin, int end)
{
	char	*extracted;
	int		n;

	n = end - begin;
	//if n = 0;
	//return (NULL);
	extracted = ft_strndup(&string[begin], n);
	return (extracted);
}

char	*make_replace_string(t_env_var *env_list, char *to_replace)
{
	if (to_replace[0] == '$' && (to_replace[1] == '\0'
			|| is_space(to_replace[1])
			|| to_replace[1] == '"'))
		return (ft_strdup("$"));
	// else if (to_replace[0] == '$' && to_replace[1] == '?' && to_replace[2] == 0)
	//     printf("exit code: \n");//to handle
	else
		return (var_extractor(to_replace, env_list));
}

char	*var_extractor(char *string, t_env_var *env_head)
{
	t_env_var	*head;

	head = env_head;
	while (head)
	{
		if (!ft_strncmp(head->name, &string[1], ft_strlen(&string[1]))
			&& head->value != NULL) //ft_strlen check
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (ft_strdup(""));
}

char	*replace(char *old_string, char *to_replace, t_begin_end *v)
{
	char	*new_string;
	int		i;
	int		j;

	new_string = ft_malloc(ft_strlen(old_string) - (v->end - v->begin)
			+ ft_strlen(to_replace) + 1);
	i = 0;
	j = 0;
	while (i < v->begin)
		new_string[j++] = old_string[i++];
	i = 0;
	while (to_replace[i])
		new_string[j++] = to_replace[i++];
	i = v->end;
	v->end = v->begin + i;
	while (old_string[i])
		new_string[j++] = old_string[i++];
	new_string[j] = '\0';
	return (new_string);
}
