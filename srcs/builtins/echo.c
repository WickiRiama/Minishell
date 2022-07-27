/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:48:14 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/07 16:24:25 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_is_nl(char *str)
{
	int	i;

	if (ft_strcmp(str, "-n") == 0)
		return (1);
	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] == 'n')
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

int	ft_echo(char **input)
{
	int	nl;
	int	i;

	nl = 0;
	i = 1;
	while (ft_is_nl(input[i]))
	{
		nl = 1;
		i++;
	}
	while (input[i])
	{
		ft_printf("%s", input[i]);
		if (input[i + 1])
			ft_printf("%c", ' ');
		i++;
	}
	if (nl == 0)
		ft_printf("\n");
	return (0);
}
