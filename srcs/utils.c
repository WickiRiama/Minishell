/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-huec <sle-huec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:18:56 by sle-huec          #+#    #+#             */
/*   Updated: 2022/07/06 15:52:35 by sle-huec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char		*new_str;
	size_t		size;

	size = (ft_strlen(s1) + ft_strlen(s2) + 1);
	new_str = (char *)malloc(sizeof(char) * size);
	if (!new_str)
		return (0);
	ft_strlcpy(new_str, s1, size);
	ft_strlcat((char *)new_str, s2, size);
	return (new_str);
}

int	len_arg_tab(char **input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		i++;
	}
	return (i);
}