/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2e_invalid_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:18:31 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/03 12:46:14 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unexpected_token(t_token *lexer_head)
{
	t_token	*head;
	int		i;

	i = 0;
	head = lexer_head;
	while (head)
	{
		if (head->next && (head->type > STRING && head->type <= SMALLER)
			&& (head->next->type > STRING && head->next->type <= SMALLER))
			return (ft_strdup(head->next->string));
		if (i == 0 && head->type == PIPE)
			return (ft_strdup(head->string));
		if (head->next == NULL
			&& (head->type > STRING && head->type <= SMALLER))
			return (ft_strdup("newline"));
		head = head->next;
		i++;
	}
	return (NULL);
}

int error_unexpected_token(t_token *lexer_head)
{
    char *error_string;

    error_string = unexpected_token(lexer_head);
    if (error_string != NULL)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(error_string, 2);
        ft_putendl_fd("'", 2);
        if (error_string)
            free(error_string);
        return(1);
	}
    else
        return (0);
}
