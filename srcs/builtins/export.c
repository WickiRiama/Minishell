/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:17:04 by sle-huec          #+#    #+#             */
/*   Updated: 2022/09/15 15:50:23 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_env	*ft_get_env_var_export(char *var, t_env *env)
{
	int		j;

	while (env)
	{
		j = 0;
		while (var[j] == env->var[j] && (var[j] != '=' && var[j] != '\0'))
			j++;
		if ((var[j] != '=' || var[j] != '\0') && (env->var[j] == '='
				|| env->var[j] == '\0'))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_replace_env_var(char *input, t_env **env)
{
	t_env	*new;
	t_env	*env_var;

	env_var = ft_get_env_var_export(input, *env);
	ft_lstdelone_env(env_var, env, &free);
	new = ft_lstnew_env(input, 1);
	if (!new)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	ft_lstadd_back_env(env, new);
	return (0);
}

int	ft_declared(char *input, t_env **env)
{
	t_env	*new;

	if (!ft_get_env_var_export(input, *env))
	{
		new = ft_lstnew_env(input, 0);
		if (!new)
		{
			ft_fprintf(2, "System error. Malloc failed.\n");
			return (1);
		}
		ft_lstadd_back_env(env, new);
	}
	return (0);
}

int	new_env_var(char *input, t_env **env)
{
	int		i;

	i = 0;
	while (input[i] && (ft_isalpha(input[i]) || input[i] == '_'
			|| (ft_isdigit(input[i]) && i != 0)))
	{
		i++;
	}
	if (i == 0 || (input[i] != '=' && (input[i] != '\0')))
	{
		ft_fprintf(2, "export: '%s': not a valid identifier\n", input);
		return (1);
	}
	else if (input[i] == '\0')
	{
		if (ft_declared(input, env) == 1)
			return (15);
	}
	else if (ft_replace_env_var(input, env) == 1)
		return (15);
	return (0);
}

int	ft_export(char **input, t_env **env)
{
	int		i;
	int		ret;
	int		tmp;

	i = 1;
	ret = 0;
	if (is_invalid_option(input))
		return (2);
	if (!input[i])
	{
		display_env(input, *env, 1);
		return (ret);
	}
	while ((input[i]) && (i <= len_arg_tab(input)))
	{
		tmp = new_env_var(input[i], env);
		if (tmp == 15)
			return (tmp);
		if (tmp)
			ret = tmp;
		i++;
	}
	return (ret);
}
