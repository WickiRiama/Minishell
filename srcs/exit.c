/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:25:07 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/07 14:35:38 by sle-huec         ###   ########.fr       */
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
	while(input && input[i])
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
	while(input[1])
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

int	ft_exit(t_token **tokens, char **input, char **env)
{
	int status;
	
	ft_printf("exit\n");
	status = check_arg_and_get_status(input);
	ft_lstclear_msh(tokens, &free);
	free(input);
	free_tab(env);	
	exit(status);
}
