/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:55:36 by mriant            #+#    #+#             */
/*   Updated: 2021/12/07 13:22:33 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				s_len;
	unsigned char	*str;

	s_len = ft_strlen(s);
	str = (unsigned char *) s;
	while (s_len >= 0)
	{
		if (str[s_len] == (unsigned char) c)
			return ((char *)s + s_len);
		s_len --;
	}
	return (NULL);
}
