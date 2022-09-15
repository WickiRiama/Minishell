/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 13:44:48 by mriant            #+#    #+#             */
/*   Updated: 2021/12/07 13:12:53 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *) s;
	while (str[i])
	{
		if (str[i] == (unsigned char) c)
			return ((char *)s + i);
		i ++;
	}
	if (str[i] == (unsigned char) c)
		return ((char *)s + i);
	return (NULL);
}
