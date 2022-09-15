/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:29:44 by mriant            #+#    #+#             */
/*   Updated: 2021/12/08 11:12:56 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	need_len;

	if (!(*needle))
		return ((char *)haystack);
	if (!(*haystack))
		return (0);
	i = 0;
	need_len = ft_strlen(needle);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] && haystack[i + j] == needle[j] && i + j < len)
			j ++;
		if (j == need_len)
			return ((char *)haystack + i);
		i ++;
	}
	return (NULL);
}
