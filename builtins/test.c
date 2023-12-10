#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int ft_strlen(const char *string)
{
	int i;

	if (!string)
		return (0);
	i = 0;
	while(string[i])
		i++;
	return (i);
}

void *ft_malloc(size_t size)
{
    void *new_pointer;

    new_pointer = malloc(size);
    if (!new_pointer)
    {
        printf("malloc failure\n");
        exit(EXIT_FAILURE);
    }
    return (new_pointer);
}

char *ft_strndup(const char *s, size_t n)
{
    size_t i;
    char *new_string;

    new_string = ft_malloc(n + 1);
    i = 0;
    while (i < n && s[i])
    {
        new_string[i] = s[i];
        i++;
    }
    new_string[i] = '\0';
    return(new_string);
}

char	*ft_env_join(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joined[j++] = s1[i++];
    joined[j++] = '=';
	i = 0;
	while (s2[i])
		joined[j++] = s2[i++];
	joined[j] = '\0';
	return (joined);
}

typedef struct s_export
{
    char *key;
    char *value;
} t_export;

int extract_key_value(char *string, t_export *key_value)
{
    int i;
    int j;

	i = 0;
    while(string[i] && string[i] != '=')
        i++;
    key_value->key = ft_strndup(string, i);
    i++;
    j = i;
    while(string[i])
        i++;
    key_value->value = ft_strndup(&string[j], i);
}

int	main(void)
{
	t_export key_value;

	char *string = strdup("hello=");
	extract_key_value(string, &key_value);
	printf("key->%s\n", key_value.key);
	printf("value->%s\n", key_value.value);
}
