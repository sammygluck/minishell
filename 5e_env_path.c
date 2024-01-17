/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5e_env_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:26:24 by jsteenpu          #+#    #+#             */
/*   Updated: 2024/01/17 13:27:09 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_paths_array(char *path)
{
	int		i;
	char	**paths;

	paths = ft_split(path, ':');
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
	path = (char *)ft_malloc(sizeof(char) * ((int)ft_strlen(tmp) + 1));
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
