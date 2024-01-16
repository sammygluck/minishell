#include "minishell.h"

char	**create_paths_array(char *path)
{
	int		i;
	char	**paths; // 2D array with different paths to binaries

	paths = ft_split(path, ':'); //make sure to free this in all cases
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		if (!paths[i])
		{
			free_array(paths);
			return (NULL);
		}
		i++;
	}
	return (paths);
}

int	retrieve_path_var_env(t_process *p)
{
	char	*tmp;
	char	*path;
	int		i;

	tmp = getenv("PATH");
	if (!tmp)
		return (0);
	path = (char *)malloc(sizeof(char) * ((int)ft_strlen(tmp) + 1)); //make sure to free this in all cases + use ft_malloc instead
	if (!path)
		return (0);
	i = 0;
	while (tmp[i])
	{
		path[i] = tmp[i];
		i++;
	}
	path[i] = '\0';
	p->paths = create_paths_array(path);
	if (!p->paths)
		return (0);
	return (1);
}