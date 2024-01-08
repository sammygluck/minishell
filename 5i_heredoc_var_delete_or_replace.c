#include "minishell.h"

char	*delete_var_name(char *old_word, char *var_value, int *index, int len_newstr, int len_var)
{
	char	*new_word;
	int		i; // index to iterate over the original string
	int		j; // index to iterate over the new string with the copied variable value

	new_word = (char *)malloc(sizeof(char) * (len_newstr));// Q: extra for null terminator needed?
	if (!new_word)
		return (NULL);
	i = 0;
	j = 0;
	while (old_word[i])
	{
		if (old_word[i] == '$' && i == *index)
		{
			i = i + len_var + 1;
			if (old_word[i] == '\0')
				break ;
		}
		new_word[j] = old_word[i];
		j++;
		i++;
	}
	new_word[j] = '\0';
	return (new_word);
}

static char	*copy_var_value(char *new_word, char *var_value, int *j)
{
	int	i;

	if (!var_value)
		return (NULL);
	i = 0;
	while (var_value[i])
	{
		new_word[*j] = var_value[i];
		(*j)++;
		i++;
	}
	new_word[*j] = '\0';
	return (new_word);
}

char	*replace_var_value(char *old_word, char *var_value, int *index, int len_newstr, int len_var)
{
	char	*new_word;
	int		i; // index to iterate over the original string
	int		j; // index to iterate over the new string with the copied variable value
	
	new_word = (char *)malloc(sizeof(char) * (len_newstr)); // malloc
	if (!new_word)
		return (NULL);
	i = j = 0;
	while (old_word[i])
	{
		if (old_word[i] == '$' && i == *index)// && var_value != NULL)
		{
			new_word = copy_var_value(new_word, var_value, &j);
			i = i + len_var + 1;
		}
		new_word[j] = old_word[i];
		j++;
		i++;
	}
	new_word[j] = '\0';
	return (new_word);
}