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
	this function obtains the length of the string s 
	while looping through the line string from heredoc
	check for every char in the string if it is a valid char
		a valid char must be alfanumeric (ASCII-text format) and may contain an underscore (_).
*/

int	env_var_name_length(char *s)
{
	int	i; // index to loop through s 
	int	len; // to obtain the length of a valid env var s 

	i = 0;
	while (s[i] != '$') // if there are leading chars before the $-sign
		i++;
	if (s[i] == '$') // skip the $-sign 
		i++;
	if (s[i] == '?') // check if the next char after $-sign is question mark
		return (1);
	len = 0;
	while (s[i])
	{
		if (!valid_env_var_name(s[i]))
			break ;
		len++;
		i++;
	}
	return (len);
}

/*
	retrieves the value of the variable name in the input string str
	by checking first the length of the variable name after the $-sign
	i.e. input str = $USER; valid var name = USER 
	i.e. input str = $HOME,$PATH; valid var name = HOME on first iteration
	valid var name = PATH on second interation
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

	// iterate over the input word in case of leading chars before the $-sign
	// to find the index where the variable name starts
	start = 0;
	while (line[start] != '$')
		start++;

	// skip the $-sign char
	start++; 
	
	// create a substring of the chars after the $-sign that contain the valid variable name
	temp = ft_substr(line, start, len); // malloc
	if (!temp)
		return (NULL);

	// check if the env var exists in the env 
	if (getenv(temp)) 
		var_value = ft_strdup(getenv(temp)); // malloc
	else
		var_value = NULL; // '\0' ?
	free(temp);
	return (var_value);
}