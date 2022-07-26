/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:03:57 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/07 16:39:26 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"

/*
// int	update_env(char *var, t_env **env, char **envp)
// {
// 	int		i;
// 	t_env	*env_var;
// 	char	*update_pwd;
// 	char	*tmp_var;

// 	i = 0;
// 	env_var = ft_get_ptr_env_var(var, *env);
// 	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
// 		i++;
// 	if (!envp[i])
// 		return (NULL);
// 	path = envp[i] + 5;
// 	tab_paths = ft_split(path, ':');
// 	if (!tab_paths)
// 		return (NULL);
// 	return (tab_paths);

// }
*/

int	update_env(char *var, char *equal, t_env **env)
{
	t_env	*env_var;
	char	*update_pwd;
	char	*tmp_var;

	env_var = ft_get_ptr_env_var(var, *env);
	update_pwd = getcwd(NULL, 0);
	tmp_var = ft_strjoin2(equal, update_pwd);
	free(update_pwd);
	if (!tmp_var)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	free(env_var->var);
	env_var->var = tmp_var;
	return (0);
}

int	ft_cd(char **path, t_env **env)
{
	if (update_env("OLDPWD", "OLDPWD=", env) == 1)
		return (1);
	if (!path || !path[1])
		return (1);
	if (chdir(path[1]) < 0)
	{
		ft_fprintf(2, "cd : %s: %s errno: %d\n", strerror(errno), path[1], errno);
		return (1);
	}
	if (update_env("PWD", "PWD=", env) == 1)
		return (1);
	return (0);
}
