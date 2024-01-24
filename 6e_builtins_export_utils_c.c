/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6e_builtins_export_utils_c.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:23:47 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/17 13:23:48 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_right_format(char *string)
{
	if (!valid_identifiers(string))
		return (0);
	if (!has_equal_sign(string) && !has_plus_equal_sign(string))
		return (0);
	return (1);
}

int	is_valid_sep(char *s, int i)
{
	if (s[i] == '=')
		return (1);
	else if (s[i] == '+' && s[i + 1] == '=')
		return (1);
	else
		return (0);
}

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
	return (0);
}

int	has_plus_equal_sign(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '+' && string[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	is_alpha_under(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	else
		return (0);
}
