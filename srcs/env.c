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

char	**copy_envp_in_tab(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(*envp) * (i + 1));
	if (!env)
		ft_fprintf(2, "System error. Malloc failed.\n");
	i = 0;
	while (env && envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			ft_fprintf(2, "System error. Malloc failed.\n");
			free_tab(env);
			return (NULL);
		}
		i++;
	}
	if (env)
		env[i] = NULL;
	return (env);
}

void	display_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}
