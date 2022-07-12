/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:39:25 by mriant            #+#    #+#             */
/*   Updated: 2022/07/12 16:37:21 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "minishell.h"
#include "libft.h"

int	ft_copy_tab(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (1);
		i++;
	}
	return (0);
}

t_dlist	*ft_cmd_orga(t_dlist *tokens, t_dlist **pipes)
{
	t_dlist	*blocks;

	blocks = NULL;
	while (tokens)
	{
		if (ft_add_block(tokens, &blocks) == 1)
		{
			ft_lstclear_msh(&blocks, &ft_del_blocks);
			ft_lstclear_msh(pipes, &ft_del_pipes);
			return (NULL);
		}
		while (tokens && ((t_token *)tokens->cont)->type != PIPE)
			tokens = tokens->next;
		if (tokens)
		{
			if (ft_add_pipe(pipes) == 1)
			{
				ft_lstclear_msh(&blocks, &ft_del_blocks);
				ft_lstclear_msh(pipes, &ft_del_pipes);
				return (NULL);
			}
			tokens = tokens->next;
		}
	}
	return (blocks);
}
