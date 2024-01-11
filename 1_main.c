/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:13:18 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/10 17:24:20 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_char(char to_check, char against);
void	free_token_list(t_token **head);
void	print_command_table(t_cmd *cmd);
void	print_redirections(t_redir *redir);

int	main(int argc, char **argv, char **env)
{
	t_env_var	*envs;
	t_token		*token_head;
	t_cmd		*parsed;
	char		*input;

	(void) argv;
	envs = environment_var_handler(env);
	env = mirror_list_to_array(envs);
	shlvl_export(&env, &envs);
	if (argc > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	// char *test = ft_strdup("\'yes\'");
	// printf("old: %s\n", test);
	// char *new = third_clean(test);
	// printf("new: %s\n", new);
	// exit(EXIT_FAILURE);
	while (1)
	{
		interactive();
		input = ft_readline();
		if (!input)
			continue ;
		token_head = tokenizer(input);
		expander(&token_head, envs);
		parsed = parser(token_head);
		noninteractive();
		executor(&parsed, &env, &envs);
		free(input);
		free_token_list(&token_head);
	}
	//make sure to free env and envs
	return (0);
}

char	*ft_readline(void)
{
	char	*input;

	input = readline("\033[0;34mMiniShell> \033[0m");
	if (!input)
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	if (input[0] == 0)
	{
		free(input);
		return (NULL);
	}
	add_history(input);
	return (input);
}

void	free_token_list(t_token **head)
{
	t_token	*old_head;
	t_token	*new_head;

	old_head = *head;
	while (old_head)
	{
		new_head = old_head->next;
		if (old_head->string)
			free(old_head->string);
		if (old_head)
			free(old_head);
		old_head = new_head;
	}
}
//free tokens
//get head of token
//set new head
//free old head and all in it
//do this as long as there is head

// Assuming the definitions of t_redir and t_cmd are given as you provided.

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
	printf("Command Table:\n");
	printf("-------------------------------------------------\n");
	while (cmd != NULL)
	{
		printf("Command Number: %d\n", cmd->cmd_nr);
		printf("Arguments Count: %d\n", cmd->argc);
		printf("Arguments: ");
		for (int i = 0; i < cmd->argc; ++i)
		{
			printf("[\"%s\"] ", cmd->argv[i]);
		}
		printf("\nRedirections:\n");
		print_redirections(cmd->redir);
		printf("-------------------------------------------------\n");
		cmd = cmd->next;
	}
}
