/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6g_builtins_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:42:55 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 12:42:58 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1. Start the exit command implementation.

2. Check if there are any arguments provided to the exit command:
   - If no arguments are provided:
       - Print a message "exit" to standard output.
       - Exit the shell with the status of the last executed command.

   - If one argument is provided:
       - Check if the argument is a valid number (integer).
           - If valid, convert it to an integer and use it as the exit status.
           - If invalid (non-integer or overflow), display an error message indicating an invalid exit argument and do not exit the shell.

   - If more than one argument is provided:
       - Display an error message indicating too many arguments and do not exit the shell.

3. If the shell is to be exited (in cases of no argument or one valid argument):
   - Perform any necessary cleanup operations (like freeing allocated memory, if any).
   - Exit the shell using the exit() function with the appropriate status.

4. End of exit command implementation.

*/

#include "minishell.h"

int	ft_exit(char **argv)
{
	int	exit_code;

	if (!argv)
		exit(EXIT_FAILURE);
	if (!argv[1]) 
		final_exit(0);//implement when global exit status is done
	else if (argv[1] && argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (argv[1]) //not sure if this condition is even necessary
	{
		exit_code = validate_and_process_exit_code(argv[1]);
		if (exit_code != -1) 
			final_exit(exit_code);
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
			final_exit(2);
		}
	}
	return (0);//got compilation error without this 
}

void	final_exit(int exit_number)
{
	// is cleanup necessary?
	printf("exit\n");
	exit(exit_number);
}
