/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:17:04 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/06 14:20:55 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	replace_env_var(char *input, t_env **env)
{
	t_env	*new;

	ft_lstdelone_env(ft_get_ptr_env_var(input, *env), &free);
	new = ft_lstnew_env(input);
	if (!new)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return ;
	}
	ft_lstadd_back_env(env, new);
}

int	identify_var(char *var, t_env *env)
{
	// int		j;

	// while (env)
	// {
	// 	j = 0;
	// 	while (var[j] == env->var[j])
	// 		j++;
	// 	if (var[j] == '\0' && env->var[j] == '=')
	// 		return (env);
	// 	env = env->next;
	// }
	// return (NULL);
}

int	new_env_var(char *input, t_env **env)
{
	t_env	*new;
	int		i;

	i = 0;
	if (ft_get_ptr_env_var(input, *env) != NULL)
	{
		ft_printf("var d env a unset\n");
		replace_env_var(input, env);
		return (1);
	}
	while (input[i])
	{
		if (input[i] == '=')
		{
			new = ft_lstnew_env(input);
			if (!new)
			{
				ft_fprintf(2, "System error. Malloc failed.\n");
				return (0);
			}
			ft_lstadd_back_env(env, new);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(char **input, t_env **env)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while ((input[i]) && (i <= len_arg_tab(input)))
	{
		if (new_env_var(input[i], env))
			ret = 0;
		else
			ret = get_return_value(input, input[i]);
		i++;
	}
	return (ret);
}
