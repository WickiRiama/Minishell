/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:59:55 by mriant            #+#    #+#             */
/*   Updated: 2022/02/16 12:15:18 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_int(char c, int fd)
{
	int	result;

	result = write(fd, &c, 1);
	return (result);
}

int	ft_putstr_int(char *s, int fd)
{
	int	result;

	if (!s)
		result = write(fd, "(null)", 6);
	else
		result = write(fd, s, ft_strlen(s));
	return (result);
}
