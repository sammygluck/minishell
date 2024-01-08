/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3b_first_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:49:32 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/03 12:49:35 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//create a system for the $ sign to be translated to the actual text
//remove quotes and where necessary interpret the $ sign
//handle heredoc quotes
    //remove but flag a quoted heredoc
//also some hardcode stuff for the $ sign

//a lot of string manipulation ahead!!!


//1st manipulation
//extract the strings from $"string"
//if $-sign is followed by a quote
//find second quote and remove dollar sign

char	*initial_clean(char *string);

char	*initial_clean(char *string)
{
	t_quote	q_struct;
	char	*new_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	init_quote(&q_struct);
	new_string = ft_malloc(ft_strlen(string) + 1);
	while (string[i])
	{
		is_in_quote(string[i], &q_struct); // Update quote state
		if (string[i] == '$' && is_quote(string[i + 1]) // Skip the character following '$' if it's a quote and not in a quote
			&& !is_in_any_quote(string, i))
			i++;
		new_string[j++] = string[i];
		i++;
	}
	new_string[j] = '\0';
	return (new_string);
}
