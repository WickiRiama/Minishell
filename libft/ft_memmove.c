/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:15:30 by mriant            #+#    #+#             */
/*   Updated: 2021/12/08 11:46:37 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (!s1 && !s2)
		return (NULL);
	str1 = s1;
	str2 = (unsigned char *) s2;
	if (str1 >= str2 && str1 < str2 + n)
	{
		while (n > 0)
		{
			str1[n - 1] = str2[n - 1];
			n --;
		}
	}
	else
		ft_memcpy(str1, str2, n);
	return (s1);
}
