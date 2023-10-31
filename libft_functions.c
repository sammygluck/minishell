
#include <minishell.h>

int ft_strlen(char *string)
{
    int i;

    i = 0;
    if (!string)
        return (i);    
    while(string[i])
        i++;
    return (i);
}

// returns string upon succes
// return NULL upon failure
char	*ft_strdup(const char *s)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen((char *)s);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strndup(const char *s, size_t n)
{
    size_t i;
    char *new_string;

    new_string = malloc(n + 1);
    if (!new_string)
        return (NULL);
    i = 0;
    while (i < n && s[i])
    {
        new_string[i] = s[i];
        i++;
    }
    new_string[i] = '\0';
    return(new_string);
}