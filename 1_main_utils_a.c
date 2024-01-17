/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main_utils_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:13:18 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/17 14:49:47 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_command_table(t_cmd *cmd);
void	print_redirections(t_redir *redir);

void	print_redirections(t_redir *redir)
{
	while (redir != NULL)
	{
		printf("\tType: %d, File: %s\n", redir->type, redir->file);
		redir = redir->next;
	}
}

void	print_command_table(t_cmd *cmd)
{
	int	i;

	printf("Command Table:\n");
	printf("-------------------------------------------------\n");
	while (cmd != NULL)
	{
		printf("Command Number: %d\n", cmd->cmd_nr);
		printf("Arguments Count: %d\n", cmd->argc);
		printf("Arguments: ");
		i = 0;
		while (i < cmd->argc)
		{
			printf("[\"%s\"] ", cmd->argv[i]);
			i++;
		}
		printf("\nRedirections:\n");
		print_redirections(cmd->redir);
		printf("-------------------------------------------------\n");
		cmd = cmd->next;
	}
}
