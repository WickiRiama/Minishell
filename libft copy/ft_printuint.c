/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:53:30 by mriant            #+#    #+#             */
/*   Updated: 2022/02/16 13:32:50 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printuint(t_llui n, int *result, char *base, int fd)
{
	char	c;
	int		len;

	len = ft_strlen(base);
	if (n / len != 0)
		ft_printuint(n / len, result, base, fd);
	c = base[(n % len)];
	*result += ft_putchar_int(c, fd);
}

int	ft_putpoint(intptr_t n, int fd)
{
	int	result;

	result = 0;
	result += ft_putstr_int("0x", fd);
	ft_printuint(n, &result, "0123456789abcdef", fd);
	return (result);
}

int	ft_putuint(unsigned int n, int fd)
{
	int	result;

	result = 0;
	ft_printuint(n, &result, "0123456789", fd);
	return (result);
}

int	ft_putx(unsigned int n, int fd)
{
	int	result;

	result = 0;
	ft_printuint(n, &result, "0123456789abcdef", fd);
	return (result);
}

int	ft_putxmaj(unsigned int n, int fd)
{
	int	result;

	result = 0;
	ft_printuint(n, &result, "0123456789ABCDEF", fd);
	return (result);
}
