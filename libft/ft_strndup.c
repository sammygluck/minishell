#include <libft.h>

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