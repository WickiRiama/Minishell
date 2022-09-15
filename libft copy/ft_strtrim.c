/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 09:16:29 by mriant            #+#    #+#             */
/*   Updated: 2021/12/06 16:59:08 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_trimleft(int len, const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!ft_strchr(set, s1[i]))
			break ;
		i ++;
	}
	return (i);
}

static int	ft_trimright(int len, const char *s1, const char *set)
{
	int	i;

	i = len - 1;
	while (i >= 0)
	{
		if (!ft_strchr(set, s1[i]))
			break ;
		i --;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		s1_len;
	char	*result;

	i = 0;
	s1_len = (int)ft_strlen(s1);
	i = ft_trimleft(s1_len, s1, set);
	j = ft_trimright(s1_len, s1, set);
	if (j >= i)
		result = (ft_substr(s1, i, j - i + 1));
	else
	{
		result = ft_calloc(1, sizeof(char));
		if (!result)
			return (NULL);
	}
	return (result);
}
