/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:15:16 by mriant            #+#    #+#             */
/*   Updated: 2022/06/14 14:10:22 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long int	result;
	int			ispos;
	int			i;

	i = 0;
	ispos = 1;
	result = 0;
	if (!nptr)
		return (0);
	while (ft_isspace(nptr[i]))
		i ++;
	if (nptr[i] == '+')
		i ++;
	else if (nptr[i] == '-')
	{
		i ++;
		ispos = -1;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10 + (nptr[i] - '0');
		i ++;
	}
	result = ispos * result;
	return ((int)result);
}
