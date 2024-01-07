#include "minishell.h"

int	ft_chdir(const char *path, char ***env, t_env_var **env_head) //change in minishell.h
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (!getcwd(old_pwd, PATH_MAX))
		old_pwd[0] = '\0'; //must I error out instead?
	if (chdir(path) != 0) 
	{
		perror("minishell: cd"); // Improved error handling
		return (1);
	}
	if (!getcwd(new_pwd, PATH_MAX))
		new_pwd[0] = '\0'; //perror("minishell: cd"); //exit here or return 1
	pwd_export(new_pwd, env, env_head);
	oldpwd_export(old_pwd, env, env_head);
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
			&& !strncmp(head->name, string, string_len))
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