#include "minishell.h"

char	*reconstruct_heredoc_line(char **words_array)
{
	int		i;
	char	*new_line;
	char	*temp;

	if (!words_array)
		return (NULL);
	i = 0;
	while (words_array[i])
	{
		words_array[i] = ft_strjoin(words_array[i], " "); // malloc
		i++;
	}
	i = 0;
	new_line = words_array[0];
	while (words_array[i] && words_array[i + 1] != NULL)
	{
		temp = words_array[i + 1];
		new_line = ft_strjoin(new_line, temp); // malloc
		i++;
	}
	return (new_line);
}

char	*replace_heredoc_word(char *old_word, char *var_value, int *index)
{
	char	*new_word;
	int		len_var;
	int		len_new_word;

	len_var = env_var_name_length(old_word);
	if (var_value == NULL)
	{
		len_new_word = ft_strlen(old_word) - len_var;
		new_word = delete_var_name(old_word, var_value, index, len_new_word, len_var); // return malloc new_word
	}
	else
	{
		len_new_word = ft_strlen(old_word) - len_var + ft_strlen(var_value);
		new_word = replace_var_value(old_word, var_value, index, len_new_word, len_var); // return malloc new_word
	}
	return (new_word);
}

char	*init_retrieve_replace_heredoc_var(char *word)
{
	char	*var_value; // string containing the expanded var from env
	int		i; // index to iterate over the str that contains the $ sign

	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] != '\0') // Q: what if the char after $-sign is '?' >> exit code retrieval needed
		{
			var_value = retrieve_env_var_value(word);
			word = replace_heredoc_word(word, var_value, &i);
			free(var_value);
		}
		i++;
	}
	return (word);
}

/*
	init heredoc var expansion will split the input from the heredoc line 
	into the different words separated by a space
	it iterates over the words from the splitted input heredoc line
	and will look for the $-sign in each word
	if $-sign is found, it will initiate the retrieve and replace function
	finally, after iterating over the different words 
	it will reconstruct the line with the variable expansion if needed
*/

char	*init_heredoc_var_expansion(char *line)
{
	int		i;
	char	**words;
	char	*new_line;

	words = ft_split(line, ' '); // malloc
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$')) // returns NULL if not found
			words[i] = init_retrieve_replace_heredoc_var(words[i]);
		i++;
	}
	new_line = reconstruct_heredoc_line(words);
	free_array(words);
	return (new_line);
}

