/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6f_builtins_cd_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteenpu <jsteenpu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:09:00 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/25 10:27:26 by jsteenpu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **argv, char ***env, t_env_var **env_head)
{
	if (!argv || !argv[0])
	{
		ft_putstr_fd("minishell: error: ft_cd\n", 2);
		return (1);
	}
	if (!argv[1] || ((!ft_strncmp(argv[1], "--", 2) && ft_strlen(argv[1]) == 2))
		|| (!ft_strncmp(argv[1], "~", 1) && ft_strlen(argv[1]) == 1))
		return (cd_home(env, env_head));
	else if (!ft_strncmp(argv[1], "-", 1) && ft_strlen(argv[1]) == 1)
		return (cd_oldpwd(env, env_head));
	if (argv[2] != NULL)
		return (cd_too_many_args());
	return (ft_chdir(argv[1], env, env_head));
}

int	cd_too_many_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	return (0);
}

int	cd_oldpwd(char ***env, t_env_var **env_head)
{
	char	*old_pwd;
	int		ret_value;

	old_pwd = get_env_value(*env_head, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	ft_putendl_fd(old_pwd, 1);
	ret_value = ft_chdir(old_pwd, env, env_head);
	free(old_pwd);
	return (ret_value);
}

int	cd_home(char ***env, t_env_var **env_head)
{
	char	*home;
	int		ret_value;

	home = get_env_value(*env_head, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	ret_value = ft_chdir(home, env, env_head);
	free(home);
	return (ret_value);
}
