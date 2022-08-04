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

// int	is_syntax_err(char *input))
// {

// }

// int	is_invalid_option(char *input)
// {
// 	int	i;

// 	i = 0;
// 	if ((input[i] == '-') && (input[i + 1]))
// 		return (1);
// 	else
// 		return (0);
// }

// int	get_ret(char *input, t_env **env)
// {
// 	int	i;

// 	i = 0;
// 	if (ft_get_ptr_env_var(input, env) != NULL)
// 	{

// 	}
// 	else if (is_invalid_option(input))
// 		return (2);
// 	while (input[i])
// 	{
// 		// if (is_syntax_err(input[i]))
// 		// 	return (2);
// 		if (!ft_isalpha(input[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	print_error(int ret)
// {
// 	if (ret == 1)

// 	else if ()
// }

// int	ft_unset(char **input, t_env **env)
// {
// 	int	i;
// 	int	ret;

// 	i = 1;
// 	while (input[i])
// 	{
// 		ret = get_ret(input, env);
// 		if (ret == 0)
// 			return (ret);
// 		else
// 		{
// 			print_error(ret);
// 			return (ret);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	ft_unset(char **input, t_env **env)
{
	int	i;

	i = 1;
	while ((input[i]) && (i <= len_arg_tab(input)))
	{
		if (ft_get_ptr_env_var(input[i], *env) != NULL)
			ft_lstdelone_env(ft_get_ptr_env_var(input[i], *env), &free);
		i++;
	}
	return (0);
}
