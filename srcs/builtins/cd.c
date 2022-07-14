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

	tmp = ft_get_ptr_env_var("OLDPWD", *env);
	tmp->var = ft_strjoin2("OLDPWD=", getcwd(NULL, 0));
	if (!path || !path[1])
		return (1);
	if (chdir(path[1]) < 0)
	{
		ft_fprintf(2, "cd : %s: %s\n", strerror(errno), *path);
		return (1);
	}
	new_pwd = ft_get_ptr_env_var("PWD", *env);
	new_pwd->var = ft_strjoin2("PWD=", getcwd(NULL, 0));
	return (0);
}
