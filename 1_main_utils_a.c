/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:13:18 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/08 14:53:40 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// int	is_char(char to_check, char against);
void	free_token_list(t_token **head);
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
	int i;

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


// int	main(int argc, char **argv, char **env)
// {
// 	t_env_var	*envs;
// 	t_token		*token_head;
// 	t_cmd		*parsed;
// 	char		*input;

// 	(void) argv;
// 	envs = environment_var_handler(env);
// 	env = mirror_list_to_array(envs);
// 	shlvl_export(&env, &envs);
// 	if (argc > 1)
// 	{
// 		ft_putstr_fd("minishell: too many arguments\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	while (1)
// 	{
// 		interactive();
// 		input = ft_readline();
// 		if (!input)
// 			continue ;
// 		token_head = tokenizer(input);
// 		expander(&token_head, envs);
// 		parsed = parser(token_head);
// 		noninteractive();
// 		executor(&parsed, &env, &envs);
// 		free(input);
// 		free_token_list(&token_head);
// 	}
// 	//make sure to free env and envs
// 	return (0);
// }
