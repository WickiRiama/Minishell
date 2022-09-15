/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:38:19 by mriant            #+#    #+#             */
/*   Updated: 2022/08/08 10:20:27 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s, char const *s2, char *sep)
{
	char	*result;
	size_t	i;

	i = 0;
	result = ft_calloc(sizeof(char),
			(ft_strlen(s) + ft_strlen(sep) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s && s[i])
	{
		result[i] = s[i];
		i ++;
	}
	while (sep && sep[i - ft_strlen(s)])
	{
		result[i] = sep[i - ft_strlen(s)];
		i ++;
	}
	while (s2 && s2[i - ft_strlen(s) - ft_strlen(sep)])
	{
		result[i] = s2[i - ft_strlen(s) - ft_strlen(sep)];
		i ++;
	}
	result[i] = '\0';
	return (result);
}
