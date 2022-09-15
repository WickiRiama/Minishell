/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:56:29 by mriant            #+#    #+#             */
/*   Updated: 2022/02/16 13:31:25 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printint(long long int n, int *result, char *base, int fd)
{
	char	c;
	int		len;

	len = ft_strlen(base);
	if (n / len != 0)
		ft_printint(n / len, result, base, fd);
	c = base[(n % len)];
	*result += ft_putchar_int(c, fd);
}

int	ft_putdec(int n, int fd)
{
	int			result;
	long int	nb;

	result = 0;
	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		result += ft_putchar_int('-', fd);
	}
	ft_printint(nb, &result, "0123456789", fd);
	return (result);
}
