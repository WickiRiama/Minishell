/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:17:13 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/06 14:17:14 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_invalid_option(char *input)
{
	if ((input[0] == '-') && (input[1]))
		return (1);
	else
		return (0);
}

int	get_return_value(char *input)
{
	int	i;

	i = 0;

	if (is_invalid_option(input))
		return (2);
	else
	{
		while (input[i])
		{
			if (!ft_isalpha(input[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_unset(char **input, t_env **env)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while ((input[i]) && (i <= len_arg_tab(input)))
	{
		if (ft_get_ptr_env_var(input[i], *env) != NULL)
		{
			ft_lstdelone_env(ft_get_ptr_env_var(input[i], *env), &free);
			ret = 0;
		}
		else
			ret = get_return_value(input[i]);
		i++;
	}
	return (ret);
}
