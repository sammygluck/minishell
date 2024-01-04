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

/*
1. Start the env command implementation.

2. Check if any arguments are provided to the env command.
   - If arguments are provided, display an error message because 'env' typically does not take arguments.
   - Exit the function.

3. Loop through the 't_env' linked list (if you're using this as your primary environment data structure):
   - For each element in the list:
       - Concatenate the variable name and value with an '=' sign in between.
       - Print this concatenated string to standard output followed by a newline.
   - Continue until all elements in the list have been processed.

   (or)

   Loop through the 'char **env' array (if you're using this as your primary environment data structure):
   - For each string in the array:
       - Print the string to standard output followed by a newline.
   - Continue until all strings in the array have been processed.

4. Note: Depending on your shell's design, you might be using either the 't_env' list or the 'char **env' array as your primary source of environment variables. Choose the appropriate looping mechanism based on which one you use.

5. End of env command implementation.

*/
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
