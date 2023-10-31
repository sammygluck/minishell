/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:13:18 by sgluck            #+#    #+#             */
/*   Updated: 2023/10/23 17:54:30 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	is_char(char to_check, char against);

int	main(void)
{
	char	*input;
	t_token *token_head;

	while (1)
	{
		input = readline("This is a test prompt> ");
		if (!input)
			break ;
		add_history(input);
		printf("You entered: %s\n", input);
		token_head = tokenizer(input);
		print_list(token_head);
		free(input);
	}
	return (0);
}


// int	is_char(char to_check, char against)
// {
// 	if (to_check == against)
// 		return (1);
// 	return (0);
// }

// int	tokens(char *string)
// {
// 	//what is considered a token??
// 	//1. a word
// 	//2. a pipe
// 	//3. a double << or a single >>
// 	//4. a single < or a single >
// 	//5. quotes also have to be handled 
// 	//
// }
