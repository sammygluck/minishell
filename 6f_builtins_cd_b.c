/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6f_builtins_cd_b.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 08:32:03 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/24 14:50:58 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//comment recheck !getcwd actions
int	ft_chdir(const char *path, char ***env, t_env_var **env_head)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (!getcwd(old_pwd, PATH_MAX))
		old_pwd[0] = '\0';
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	if (!getcwd(new_pwd, PATH_MAX))
		return (ft_fallback_to_home(env, env_head));
	pwd_export(new_pwd, env, env_head);
	oldpwd_export(old_pwd, env, env_head);
	return (0);
}

// If home is not set, consider error handling or fallback to root ("/")
int	ft_fallback_to_home(char ***env, t_env_var **env_head)
{
	char	*home;
	char	new_pwd[PATH_MAX];

	home = get_env_value(*env_head, "HOME");
	if (home && chdir(home) == 0)
	{
		strncpy(new_pwd, home, PATH_MAX);
		free(home);
	}
	else
	{
		perror("minishell: cd: error finding valid directory");
		return (1);
	}
	pwd_export(new_pwd, env, env_head);
	oldpwd_export("", env, env_head);
	return (0);
}

char	*get_env_value(t_env_var *env, char *string)
{
	t_env_var	*head;
	size_t		string_len;

	if (!env || !string)
		return (NULL);
	string_len = ft_strlen(string);
	head = env;
	while (head)
	{
		if (ft_strlen(head->name) == string_len
			&& !strncmp(head->name, string, string_len)
			&& head->value)
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (NULL);
}

void	pwd_export(char *pwd, char ***env, t_env_var **env_l)
{
	char	*new_pwd;
	char	*argv[3];

	new_pwd = ft_strjoin("PWD=", pwd);
	argv[0] = "export";
	argv[1] = new_pwd;
	argv[2] = NULL;
	ft_export(argv, env, env_l);
	free(new_pwd);
}

void	oldpwd_export(char *oldpwd, char ***env, t_env_var **env_l)
{
	char	*old_pwd;
	char	*argv[3];

	old_pwd = ft_strjoin("OLDPWD=", oldpwd);
	argv[0] = "export";
	argv[1] = old_pwd;
	argv[2] = NULL;
	ft_export(argv, env, env_l);
	free(old_pwd);
}
