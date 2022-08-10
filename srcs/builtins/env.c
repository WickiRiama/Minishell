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

t_env	*ft_get_ptr_env_var(char *var, t_env *env)
{
	int		j;

	while (env)
	{
		j = 0;
		while (var[j] == env->var[j])
			j++;
		if (var[j] == '\0' && env->var[j] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

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

int	display_env(char **input, t_env *env)
{
	if (input[1])
	{
		ft_fprintf(2, "%s: %s: No such a file or directory\n", input[0],
			input[1]);
		return (g_exitcode);
	}
	while (env)
	{
		ft_printf("%s\n", env->var);
		env = env->next;
	}
	return (0);
}
