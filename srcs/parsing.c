/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:39:25 by mriant            #+#    #+#             */
/*   Updated: 2022/07/07 16:17:45 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

t_exec	*ft_init_block()
{
	t_exec	*block;

	block = malloc(sizeof(t_exec) * 1);
	if (!block)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (NULL);
	}
	block->cmd = NULL;
	block->infile = -2;
	block->outfile = -2;
	return (block);
}

void	ft_del_blocks(void *content)
{
	t_exec	*block;

	block = (t_exec*)content;
	if (block->infile >= 0)
		block->infile = close(block->infile) - 2;
	if (block->outfile >= 0)
		block->outfile = close(block->outfile) - 2;
}

t_dlist	*ft_cmd_orga(t_dlist *tokens)
{
	t_dlist	*blocks;
	t_exec	*new;

	blocks = NULL;
	while (tokens)
	{
		new = ft_init_block();
		if (!new)
		{
			ft_lstclear_msh(&blocks, &ft_del_blocks);
		}
	}
	return (blocks);
}
