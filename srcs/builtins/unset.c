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

int	is_invalid_option(char **input)
{
	if (input && input[1])
	{
		if ((input[1][0] == '-') && (input[1][1]))
		{
			ft_fprintf(2, "%s: %s: invalid option\n", input[0],
				input[1]);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	is_variable_sh(char *input)
{
	int	i;

	i = 1;
	if (input[0] != '_' && (!ft_isalpha(input[0])))
		return (0);
	else
	{
		while (input[i])
		{
			if (ft_isalnum(input[i]) || input[i] == '_')
				i++;
			else
				return (0);
		}
	}
	return (1);
}

int	get_return_value(char **all_input, char *input)
{
	if (is_invalid_option(all_input))
		return (2);
	else if (!is_variable_sh(input))
	{
		ft_fprintf(2, "%s: %s: not a valid identifier\n", all_input[0],
			input);
		return (1);
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
			ret = get_return_value(input, input[i]);
		i++;
	}
	return (ret);
}
