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

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	is_char(char to_check, char against);

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("This is a test prompt> ");
		if (!input)
			break ;
		add_history(input);
		printf("You entered: %s\n", input);
		free(input);
	}
	return (0);
}

char	*tokenizer(char *string)
{
	int	i;

	//1. while string
	//2. skip spaces
	//3. check for words/redirects+pipes/quotes
	//4. must I do like ft_split, in the sense of first count words,
	//   malloc, then count each word's length?	
	i = -1;
	while (string[++i])
	{
		while (is_char(string[i], ' ') || is_char(string[i], '	'))
			i++;
		while (string[i])
		{
			if (string[i] == '>')
				if (string[i + 1] == '>')
					add_token(DOUBLE_LEFT);//also i++
				else
					add_token(LEFT);
			if (string[i] == '<')
				if (string[i + 1] == '<')
					add_token(DOUBLE_RIGHT);//also i++
				else
					add_token(RIGHT);
			if (string[i] == '|')
				add_token('|');
			if (string[i] == '\'' || string[i] '"')
				//do some quote stuff
			i++;
		}	
	}
}

int	is_char(char to_check, char against)
{
	if (to_check == against)
		return (1);
	return (0);
}

int	tokens(char *string)
{
	//what is considered a token??
	//1. a word
	//2. a pipe
	//3. a double << or a single >>
	//4. a single < or a single >
	//5. quotes also have to be handled 
	//
}
