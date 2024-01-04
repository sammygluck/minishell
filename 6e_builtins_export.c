/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6e_builtins_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:57:47 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/04 11:57:50 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1. Start the export command implementation.

2. Check if any arguments are provided to the export command.
   - If no arguments are provided:
       - Display all environment variables in a sorted manner.
           - Use the 't_env' list or 'char **env' array as per your shell design.
           - If using 't_env', sort the list based on the variable names and then print.
           - If using 'char **env', convert it to a list, sort, and then print.
       - Each variable should be printed in the format "declare -x NAME='value'".
   - If arguments are provided:
       - Loop through each argument:
           - Check if the argument is in the format "KEY=VALUE".
               - If yes, add or update the variable in both 't_env' list and 'char **env' array.
               - If the format is incorrect, display an error message for that argument.

3. For adding or updating environment variables:
   - In 't_env' list:
       - Search for the variable by KEY.
       - If found, update its VALUE.
       - If not found, add a new node with KEY and VALUE.
   - In 'char **env' array:
       - Search for the variable by KEY.
       - If found, update its VALUE.
       - If not found, allocate new memory for the new "KEY=VALUE" string and add it to the array.

4. Optional: Implement functionality to handle variables without '='.
   - If a variable is provided without '=', treat it as a variable with an empty value.
   - Or, only add the variable name to the environment without changing its value if it already exists.

5. End of export command implementation.

*/
#include "minishell.h"

int	ft_export(char **argv, char ***env, t_env_var **list)
{
	t_export	key_value;
	int			i;

	i = 1;
	key_value.key = NULL; //is this necessary? can we boil this down to one function?
	key_value.value = NULL;
	if (!argv)
	{
		ft_putstr_fd("minishell: export: fatal error\n", 2);
		exit(EXIT_FAILURE); //is exit appropriate or return (1)?
	}
	if (!argv[1])
		modified_ft_env(*list);//make sure to set the right parameter; must I return or will I automatically return at the end (0 is the ret value)
	while (argv[i])
	{
		if (is_right_format(argv[i])) //i.e. key=value + check for valid identifier issue
		{
			extract_key_value(argv[i], &key_value);
			update(&key_value, env, list); //i.e. seperate the key from value and update t_env list & char **env
		}
		// if (!right_format) //is this necessary?
		//     error for this argument or skip this 
		i++;
	}
	free_key_value(&key_value);
	return (0); 
}
