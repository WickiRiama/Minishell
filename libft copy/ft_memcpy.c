/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:31:58 by mriant            #+#    #+#             */
/*   Updated: 2021/12/08 11:54:25 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	if (!s2 && !s1 && n > 0)
		return (NULL);
	str1 = s1;
	str2 = (char *) s2;
	i = 0;
	while (i < n)
	{
		str1[i] = str2[i];
		i ++;
	}
	return (s1);
}
