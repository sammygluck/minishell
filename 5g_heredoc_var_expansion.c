#include "minishell.h"

char	*replace_or_delete_heredoc_var(char *old_line, char *var_value, int *index)
{
	char	*new_word;
	int		len_var;
	int		len_new_word;

	len_var = env_var_name_length(old_line);
	if (var_value == NULL)
	{
		len_new_word = ft_strlen(old_line) - len_var;
		new_word = delete_var_name(old_line, index, len_new_word, len_var); // return malloc new_word
	}
	else
	{
		len_new_word = ft_strlen(old_line) - len_var + ft_strlen(var_value);
		new_word = replace_var_value(old_line, var_value, index, len_new_word, len_var); // return malloc new_word
	}
	return (new_word);
}

char	*init_retrieve_replace_heredoc_var(char *line)
{
	char	*var_value; // string containing the retrieved/variable value from env
	int		i; // index to iterate over the str that contains the $ sign

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] != '\0' && !ft_isspace(line[i + 1]))
		{
			var_value = retrieve_env_var_value(line);
			line = replace_or_delete_heredoc_var(line, var_value, &i);
			free(var_value);
		}
		i++;
	}
	return (line);
}
