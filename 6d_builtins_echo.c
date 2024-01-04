/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6d_builtins_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:35:41 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 11:35:44 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1. Start the echo command implementation.

2. Initialize a flag to track if the '-n' option is used.
   - Set the flag to false initially.

3. Check if the first argument after "echo" is '-n'.
   - If yes, set the '-n' flag to true.
   - Skip this argument for the rest of the processing.

4. Loop through each argument provided to the echo command (starting from the first argument or the second if '-n' was found):
   - Print the argument to standard output.
   - If there are more arguments:
       - Print a space after the current argument to separate from the next one.

5. After all arguments are processed:
   - If the '-n' flag is not set:
       - Print a newline character to end the output.

6. End of echo command implementation.

*/

#include "minishell.h"

int	ft_echo(char **argv)//fix parameters
{
	int	flag_n;
	int	i;

	if (!argv)
		exit(EXIT_FAILURE);
	flag_n = 0;
	i = 1;
	if (argv[i] && only_n(argv[i]))
	{
		flag_n = 1;
		i++;
	}
	while (argv[i]) 
	{
		printf("%s", argv[i]);
		if (argv[i + 1]) 
			printf(" "); 
		i++;
	}
	if (!flag_n) 
		printf("\n");
	return (0);
}

int	only_n(char *string)
{
	int	i;

	i = 1;
	if (!string)
		return (0);
	if (string[0] != '-')
		return (0);
	while (string[i])
	{
		if (string[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}
