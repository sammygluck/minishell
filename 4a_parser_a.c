/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4a_parser_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:53 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 09:56:37 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *lexer_head)
{
	t_token	*current;
	t_cmd	*commands;
	t_cmd	*new_cmd;
	int		cmd_nr;

	if (!lexer_head)
		return (NULL);
	current = lexer_head;
	commands = NULL;
	cmd_nr = 0;
	while (current)
	{
		cmd_nr++;
		new_cmd = parse_command(&current, cmd_nr);
		append_command(&commands, new_cmd);
	}
	return (commands);
}

t_cmd	*parse_command(t_token **current, int cmd_nr)
{
	t_cmd	*command;

	command = init_cmd(cmd_nr);
	while (*current && (*current)->type != PIPE)
	{
		if (is_redirection_token(*current))
			parse_redirection(current, command);
		else
		{
			if ((*current)->string[0] != '\0')
				add_argument_to_command(command, (*current)->string);
			*current = (*current)->next;
		}
	}
	if (*current && (*current)->type == PIPE)
		*current = (*current)->next;
	return (command);
}

t_cmd	*init_cmd(int cmd_nr)
{
	t_cmd	*command;

	command = ft_malloc(sizeof(t_cmd));
	command->argc = 0;
	command->argv = NULL;
	command->redir = NULL;
	command->next = NULL;
	command->cmd_nr = cmd_nr;
	return (command);
}

void	add_argument_to_command(t_cmd *command, char *arg)
{
	command->argv = realloc_array(command->argv, command->argc);
	command->argv[command->argc] = ft_strdup(arg);
	command->argv[command->argc + 1] = NULL;
	command->argc++;
}

void	append_command(t_cmd **commands, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (!*commands)
		*commands = new_cmd;
	else
	{
		tmp = *commands;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}
