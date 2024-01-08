/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6c_builtins_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:32:24 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 11:32:30 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env_var **env_l)//parameters?
{
	t_env_var	*head;

	head = *env_l;
	if (!env_l) //also check if there are arguments and failure on more parameters should they come up
	{
		printf("no env variables\n");//add ft_putstrfd_fd instead
		return (1);
	}
	while (head)
	{
		if (head->value == NULL)
		{
			head = head->next;
			continue ;
		}
		printf("%s=%s\n", head->name, head->value); //check for correctness also I can just print char **array
		head = head->next;
	}
	return (0);
}
