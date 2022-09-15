/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:03:57 by sle-huec          #+#    #+#             */
/*   Updated: 2022/09/15 15:44:50 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include "libft.h"
#include "minishell.h"

int	ft_check_arg(char **path)
{
	int	len;

	len = len_arg_tab(path);
	if (len > 2)
	{
		ft_fprintf(2, "%s: too many arguments\n", path[0]);
		return (1);
	}
	if (is_invalid_option(path))
		return (2);
	return (0);
}

int	ft_update_pwd(char *equal, t_env **env)
{
	char	*update_pwd;
	char	*tmp_var;

	update_pwd = getcwd(NULL, 0);
	if (!update_pwd)
	{
		ft_fprintf(2, "getcwd: couldn't update env : %s\n", strerror(errno));
		return (0);
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

void	ft_unset_oldpwd(t_env **env)
{
	char	*cmd_tab[3];
	char	cmd_1[6];
	char	cmd_2[7];

	ft_strlcpy(cmd_1, "unset", 6);
	cmd_tab[0] = cmd_1;
	ft_strlcpy(cmd_2, "OLDPWD", 7);
	cmd_tab[1] = cmd_2;
	cmd_tab[2] = NULL;
	ft_unset(cmd_tab, env);
}

int	ft_update_oldpwd(t_env **env)
{
	t_env	*tmp_pwd;
	char	*update_oldpwd;

	tmp_pwd = ft_get_ptr_env_var("PWD", *env);
	if (!tmp_pwd)
	{
		ft_unset_oldpwd(env);
		return (0);
	}
	update_oldpwd = malloc(sizeof(*update_oldpwd)
			* (ft_strlen(tmp_pwd->var) + 4));
	if (!update_oldpwd)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (15);
	}
	ft_strlcpy(update_oldpwd, "OLDPWD=", 8);
	ft_strlcpy(update_oldpwd + 7, &tmp_pwd->var[4], ft_strlen(tmp_pwd->var));
	if (new_env_var(update_oldpwd, env) == 15)
		return (15);
	free(update_oldpwd);
	return (0);
}

int	ft_cd(char **path, t_env **env)
{
	int	ret;

	ret = ft_check_arg(path);
	if (ret > 0)
		return (ret);
	if (!path || !path[1])
		return (1);
	if (chdir(path[1]) < 0)
	{
		if (errno == 116)
			ft_fprintf(2, "cd: '%s': No such file or directory\n", path[1]);
		else
			ft_fprintf(2, "cd: %s: '%s'\n", path[1], strerror(errno));
		return (1);
	}
	ret = ft_update_oldpwd(env);
	if (ret > 0)
		return (ret);
	ret = ft_update_pwd("PWD=", env);
	if (ret > 0)
		return (ret);
	return (ret);
}
