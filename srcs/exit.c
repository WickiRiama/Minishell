/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:25:07 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/11 10:30:52 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	len_arg_tab(char **input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		i++;
	}
	return (i);
}

int	check_arg_and_get_status(char **input)
{
	int	i;
	int	len;

	i = 0;
	while (input[1])
	{
		if (!ft_isdigit(input[1][i]))
		{
			ft_fprintf(2, "%s: %s: numeric argument required\n", input[0],
				input[1]);
			return (2);
		}
		else
		{
			len = len_arg_tab(input);
			if (len > 2)
			{
				ft_fprintf(2, "%s: too many arguments\n", input[0]);
				return (1);
			}
			return (ft_atoi(input[1]));
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_token **tokens, char **input, t_env **env)
{
	(void)env;
	int	status;

	ft_printf("exit\n");
	status = check_arg_and_get_status(input);
	ft_lstclear_msh(tokens, &free);
	free_tab(input);
	// ft_lstclear_env(env, &free);
	exit(status);
}
