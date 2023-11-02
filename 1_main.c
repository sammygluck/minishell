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
void free_token_list(t_token **head);

int	main(void)
{
	char	*input;
	t_token *token_head;

	int i = 0;
	while (i < 2)
	{
		input = readline("This is a test prompt> ");
		if (!input)
			break ;
		add_history(input);
		printf("You entered: %s\n", input);
		token_head = tokenizer(input);
		print_list(token_head);
		free(input);
		free_token_list(&token_head);
		i++;
	}
	return (0);
}

void free_token_list(t_token **head)
{
	t_token *old_head;
	t_token *new_head;

	old_head = *head;
	while (old_head)
	{
		new_head = old_head->next;
		free(old_head->string);
		free(old_head);
		old_head = new_head;
	}
}
//free tokens
//get head of token
//set new head
//free old head and all in it
//do this as long as there is head

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