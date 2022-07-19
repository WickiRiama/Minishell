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

int	ft_cd(char **path, t_env **env)
{
	t_env	*tmp;
	t_env	*new_pwd;
	char	*tmp_oldpwd;
	char	*tmp_pwd;

	tmp = ft_get_ptr_env_var("OLDPWD", *env);
	tmp_oldpwd = getcwd(NULL, 0);
	tmp->var = ft_strjoin2("OLDPWD=", tmp_oldpwd);
	if (!tmp->var)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		free(tmp_oldpwd);
		return (1);
	}
	else
	{
		free(tmp->var);
		free(tmp_oldpwd);
	}
	if (!path || !path[1])
		return (1);
	if (chdir(path[1]) < 0)
	{
		ft_fprintf(2, "cd : %s: %s\n", strerror(errno), *path);
		return (1);
	}
	new_pwd = ft_get_ptr_env_var("PWD", *env);
	tmp_pwd = getcwd(NULL, 0);
	new_pwd->var = ft_strjoin2("PWD=", tmp_pwd);
	if (!new_pwd->var)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		free(tmp_pwd);
		return (1);
	}
	else
	{
		free(new_pwd->var);
		free(tmp_pwd);
	}
	return (0);
}
