#include "minishell.h"

/*
    valid env variable name check:
		a valid var name must be alfanumeric (ASCII-text format) 
        and may contain the underscore (_) char.
	returns 0 is non valid, 1 if OK
*/

int	valid_env_var_name(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	else
		return (1);
}

/*
	this function obtains the length of the string s after the $-sign
	check for every char in the string if it is a valid char
		a valid char must be alfanumeric (ASCII-text format) and may contain an underscore (_).
*/

int	env_var_name_length(char *line)
{
	int	i; // index to loop through s 
	int	len; // to obtain the length of a valid env var s 

	i = 0;
	while (line[i] != '$') // if there are leading chars before the $-sign
		i++;
	if (line[i] == '$') // skip the $-sign 
		i++;
	if (line[i] == '?') // check if the next char after $-sign is question mark
		return (1);
	len = 0;
	while (line[i])
	{
		if (!valid_env_var_name(line[i]))
			break ;
		len++;
		i++;
	}
	return (len);
}

/*
	retrieves the value of the variable name from the input string line
	first, it calculates the length of the variable name after the $-sign
	to find know when the variable name ends.
	i.e. input str = $USER; valid var name = USER 
	then, it iterate over the input line in case of leading chars before the $-sign
	to find the index where the variable name starts.
	finally, it checks if the variable can be found in env using getenv
	returns the var value from getenv if found,
	if not found, it returns NULL.
*/

char	*retrieve_env_var_value(char *line)
{
	int		len;
	int		start;
	char	*temp;
	char	*var_value;

	len = env_var_name_length(line);
	if (len == 1) //  && str[1] == '?')
		printf("please provide the exit code of the command\n");
	start = 0;
	while (line[start] != '$')
		start++;	
	start++; // skip the $-sign char
	temp = ft_substr(line, start, len); // malloc in ft_substr!!
	if (!temp)
		return (NULL);
	if (getenv(temp)) // check if the env var exists in the env 
		var_value = ft_strdup(getenv(temp)); // ft_malloc in ft_strdup !!!!
	else
		var_value = NULL;
	free(temp);
	return (var_value);
}
