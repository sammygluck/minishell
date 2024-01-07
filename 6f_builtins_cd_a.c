/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6f_builtins_cd_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:09:00 by sgluck            #+#    #+#             */
/*   Updated: 2024/01/07 08:31:40 by sgluck           ###   ########.fr       */
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
	if (!argv[1] || (!ft_strncmp(argv[1], "--", 2) && ft_strlen(argv[1]) == 2))
		return (cd_home(env, env_head));//two statements in one
	else if (!ft_strncmp(argv[1], "-", 1) && ft_strlen(argv[1]) == 1)
		return (cd_oldpwd(env, env_head));//same as previous comment
	if (argv[2] != NULL)
		return (cd_too_many_args());
	return (ft_chdir(argv[1], env, env_head));
}

int	cd_too_many_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	return (1);
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

// int	ft_cd(char **argv, char ***env, t_env_var **env_head)
// {
// 	char	*home;
// 	char	*old_pwd;
// 	int		ret_value;

// 	ret_value = 0;
// 	if (!argv || !argv[0]) 
// 	{
// 		ft_putstr_fd("error:ft_cd\n", 2); // Provide more specific error message
// 		return (1);
// 	}
// 	if (!argv[1] || (!ft_strncmp(argv[1], "--", 2) && ft_strlen(argv[1]) == 2))
// 	{
// 		home = get_env_value(*env_head, "HOME");
// 		if (!home) 
// 		{
// 			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
// 			return (1);
// 		}
// 		ret_value = ft_chdir(home, env, env_head);
// 		free(home); // Free memory allocated by get_env_value
// 		return (ret_value);
// 	}
// 	else if (!ft_strncmp(argv[1], "-", 1) && ft_strlen(argv[1]) == 1)
// 	{
// 		old_pwd = get_env_value(*env_head, "OLDPWD");
// 		if (!old_pwd)
// 		{
// 			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
// 			return (1);
// 		}
// 		ft_putendl_fd(old_pwd, 1);
// 		ret_value = ft_chdir(old_pwd, env, env_head);
// 		free(old_pwd);
// 		return (ret_value);
// 	}
// 	if (argv[2] != NULL) // Corrected argument check
// 	{
// 		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
// 		return (1);
// 	}
// 	// Path formatting can be done here if needed
// 	ret_value = ft_chdir(argv[1], env, env_head);
// 	return (ret_value);
// }







