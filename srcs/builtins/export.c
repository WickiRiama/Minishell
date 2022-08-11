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

t_env	*ft_get_env_var_export(char *var, t_env *env)
{
	int		j;

	while (env)
	{
		j = 0;
		while (var[j] == env->var[j] && var[j] != '=')
			j++;
		if (var[j] == '=' && env->var[j] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_replace_env_var(char *input, t_env **env)
{
	t_env	*new;

	ft_lstdelone_env(ft_get_env_var_export(input, *env), &free);
	new = ft_lstnew_env(input);
	if (!new)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	ft_lstadd_back_env(env, new);
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
	if (input[i] != '=' && (input[i] != '\0'))
	{
		ft_fprintf(2, "export: %s: not a valid identifier\n", input);
		return (1);
	}
	else if (input[i] == '\0')
		return (0);
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
