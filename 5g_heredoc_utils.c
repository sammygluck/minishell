/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5g_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:31:39 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/24 15:04:38 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	remove_prev_file_ref(t_hdoc *hd)
{
	if (!hd)
		return ;
	if (hd->quotes && hd->delimiter)
	{
		hd->quotes = 0;
		free(hd->delimiter);
	}
	if (hd->fd != ERROR)
		close(hd->fd);
	if (hd->file)
		unlink(hd->file);
}

char	*heredoc_delimiter_qoutes(char *delimiter, t_hdoc *hd)
{
	int		len;
	char	*new_delimiter;

	len = ft_strlen(delimiter);
	if (len && ((delimiter[0] == '\'' && delimiter[len - 1] == '\'')
			|| (delimiter[0] == '\"' && delimiter[len - 1] == '\"')))
	{
		hd->quotes = 1;
		new_delimiter = third_clean(delimiter);
		return (new_delimiter);
	}
	return (delimiter);
}
