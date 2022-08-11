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

int	ft_check_arg(char **path)
{
	int	len;

	len = len_arg_tab(path);
	if (len > 3)
	{
		ft_fprintf(2, "%s: too many arguments\n", path[0]);
		return (1);
	}
	if (is_invalid_option(path))
		return (2);
	return (0);
}

int	update_env(char *equal, t_env **env)
{
	char	*update_pwd;
	char	*tmp_var;

	update_pwd = getcwd(NULL, 0);
	if (!update_pwd)
	{
		ft_fprintf(2, "getcwd error : cd : %s\n", strerror(errno));
		return (1);
	}
	tmp_var = ft_strjoin2(equal, update_pwd);
	if (!tmp_var)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (15);
	}
	if (new_env_var(tmp_var, env) == 15)
		return (15);
	free(update_pwd);
	free(tmp_var);
	return (0);
}

int	ft_cd(char **path, t_env **env)
{
	int	ret;

	ret = ft_check_arg(path);
	if (ret > 0)
		return (ret);
	ret = update_env("OLDPWD=", env);
	if (ret > 0)
		return (ret);
	if (!path || !path[1])
		return (1);
	if (chdir(path[1]) < 0)
	{
		ft_fprintf(2, "cd : %s: %s\n", strerror(errno), path[1]);
		return (1);
	}
	ret = update_env("PWD=", env);
	return (ret);
}
