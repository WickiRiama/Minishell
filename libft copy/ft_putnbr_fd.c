/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:36:32 by mriant            #+#    #+#             */
/*   Updated: 2021/12/04 12:00:48 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnbr_fd(long int n, int fd)
{
	char	c;

	if (n / 10 != 0)
		ft_printnbr_fd(n / 10, fd);
	c = (n % 10) + '0';
	ft_putchar_fd(c, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = (long int)n;
	if (n < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	ft_printnbr_fd(nb, fd);
}
