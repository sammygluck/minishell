/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5g_heredoc_var_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:41:09 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/17 17:58:31 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_or_delete_heredoc_var(char *old_line, \
			char *var_value, int *index)
{
	char	*new_line;
	int		len_var;
	int		len_new_word;

	len_var = env_var_name_length(old_line);
	if (var_value == NULL)
	{
		len_new_word = ft_strlen(old_line) - len_var;
		new_line = delete_var_name(old_line, index, len_new_word, len_var);
	}
	else
		new_line = replace_var_value(old_line, var_value, \
			index, len_var);
	return (new_line);
}

char	*heredoc_var_expansion(char *line, t_env_var **envs)
{
	t_begin_end	values;
	char		*var_value;
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\0' && !ft_isspace(line[i + 1]))
		{
			var_value = retrieve_env_var_value(line, envs);
			if (line[i + 1] == '?')
			{
				values.begin = i;
				values.end = i + 2;
				line = replace(line, var_value, &values);
			}
			else
				line = replace_or_delete_heredoc_var(line, var_value, &i);
			free(var_value);
		}
		i++;
	}
	return (line);
}
