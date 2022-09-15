/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:25:42 by mriant            #+#    #+#             */
/*   Updated: 2021/12/08 10:34:25 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (!s || start > ft_strlen(s))
	{
		result = ft_calloc(1, 1);
		return (result);
	}
	if (ft_strlen(s) - start < len)
		i = ft_strlen(s) - start;
	else
		i = len;
	result = ft_calloc(sizeof(char), (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len)
	{
		result[i] = s[i + start];
		i ++;
	}
	return (result);
}
