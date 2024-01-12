#include "minishell.h"

char	*replace_or_delete_heredoc_var(char *old_line, char *var_value, int *index)
{
	char	*new_line;
	int		len_var;
	int		len_new_word;

	len_var = env_var_name_length(old_line);
	if (var_value == NULL)
	{
		len_new_word = ft_strlen(old_line) - len_var;
		new_line = delete_var_name(old_line, index, len_new_word, len_var);
	}
	else
	{
		len_new_word = ft_strlen(old_line) - len_var + ft_strlen(var_value);
		new_line = replace_var_value(old_line, var_value, index, len_new_word, len_var);
	}
	return (new_line);
}

char	*heredoc_var_expansion(char *line)
{
	char	*var_value;
	int		i; 

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			t_begin_end	values;

			init_begin_end(&values);
			stuff_to_replace(line, &values);
			var_value = retrieve_env_var_value(line);
			line = replace(line, var_value, &values);
			return (line);
		}
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
