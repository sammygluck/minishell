/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5g_heredoc_var_expansion_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:35:44 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/17 13:40:50 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    valid env variable name check:
		a valid var name must be alfanumeric (ASCII-text format) 
        and may contain the underscore (_) char.
	returns 0 is non valid, 1 if OK
*/

int	valid_env_var_name(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	else
		return (1);
}

int	env_var_name_length(char *line)
{
	int	i;
	int	len;

	i = 0;
	while (line[i] != '$')
		i++;
	if (line[i] == '$')
		i++;
	if (line[i] == '?')
		return (-1);
	len = 0;
	while (line[i])
	{
		if (!valid_env_var_name(line[i]))
			break ;
		len++;
		i++;
	}
	return (len);
}

/*
	retrieves the value of the variable name from the input string line
	first, it calculates the length of the variable name after the $-sign
	to find know when the variable name ends.
	i.e. input str = $USER; valid var name = USER 
	then, it iterate over the input line in case of leading chars before the $-sign
	to find the index where the variable name starts.
	finally, it checks if the variable can be found in env using getenv
	returns the var value from getenv if found,
	if not found, it returns NULL.
*/

char	*retrieve_env_var_value(char *line, t_env_var **envs)
{
	int		len;
	int		start;
	char	*temp;
	char	*var_value;

	len = env_var_name_length(line);
	if (len == -1)
		return (ft_itoa(g_last_exit_code));
	start = 0;
	while (line[start] != '$')
		start++;
	start++;
	temp = ft_substr(line, start, len);
	if (!temp)
		return (NULL);
	var_value = get_env_value(*envs, temp);
	free(temp);
	return (var_value);
}
