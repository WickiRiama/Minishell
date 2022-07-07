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

int	ft_echo(char **input)
{	
	int	nl;
	int	i;

	nl = 0;
	i = 1;

	if (ft_strcmp(input[1], "-n") == 0)
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
