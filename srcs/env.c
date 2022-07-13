/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:05:36 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/06 16:02:48 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"




char	*get_env_var(char **envp, t_env **env)
{
	int		i;
	t_env	*env_var;

	i = 0;
	while (envp[i])
	{
		env_var = ft_lstnew_env(envp[i]);
		if (!env_var)
		{
			ft_fprintf(2, "System error. Malloc failed.\n");
			return (NULL);
		}
		ft_lstadd_back_env(env, env_var);
		i++;
	}
	return (0);
}

void	display_env(t_env *env)
{
	while (env)
	{
		ft_printf("%s\n", env->var);
		env = env->next;
	}
}
