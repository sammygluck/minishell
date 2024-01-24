/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:13:18 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/17 09:32:24 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env_var	*envs;

	(void) argv;
	init_env_vars(&env, &envs);
	check_arg_count(argc);
	process_commands(&env, &envs);
	free_env_list(&envs);
	free_char_env(env);
	return (0);
}

void	init_env_vars(char ***env, t_env_var **envs)
{
	*envs = environment_var_handler(*env);
	*env = mirror_list_to_array(*envs);
	shlvl_export(env, envs);
}

void	check_arg_count(int argc)
{
	if (argc > 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	process_commands(char ***env, t_env_var **envs)
{
	t_token	*token_head;
	t_cmd	*parsed;
	char	*input;

	while (1)
	{
		signal_handler(PROMPT);
		input = ft_readline();
		if (!input)
			continue ;
		token_head = tokenizer(input);
		expander(&token_head, *envs);
		process_token_list(&token_head);
		parsed = parser(token_head);
		free_token_list(&token_head);
		executor(&parsed, env, envs);
		free_cmd_list(&parsed);
		free(input);
	}
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
