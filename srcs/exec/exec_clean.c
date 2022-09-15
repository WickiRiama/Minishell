/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:41:51 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 15:53:07 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"

void	ft_close_fd_parent(t_dlist *blocks)
{
	if (blocks)
	{
		if (((t_exec *)blocks->cont)->outfile != -2)
			((t_exec *)blocks->cont)->outfile \
				= close(((t_exec *)blocks->cont)->outfile) -2;
		if (((t_exec *)blocks->cont)->infile != -2)
			((t_exec *)blocks->cont)->infile \
				= close(((t_exec *)blocks->cont)->infile) -2;
		if (((t_exec *)blocks->cont)->pipe_to_read_from != -2)
			((t_exec *)blocks->cont)->pipe_to_read_from \
				= close(((t_exec *)blocks->cont)->pipe_to_read_from) -2;
		if (((t_exec *)blocks->cont)->pipe_to_write_to != -2)
			((t_exec *)blocks->cont)->pipe_to_write_to \
				= close(((t_exec *)blocks->cont)->pipe_to_write_to) -2;
	}
}

void	ft_close_fd_all(t_dlist *blocks)
{
	while (blocks && blocks->prev)
		blocks = blocks->prev;
	while (blocks)
	{
		if (((t_exec *)blocks->cont)->outfile >= 0)
			((t_exec *)blocks->cont)->outfile \
				= close(((t_exec *)blocks->cont)->outfile) -2;
		if (((t_exec *)blocks->cont)->infile >= 0)
			((t_exec *)blocks->cont)->infile \
				= close(((t_exec *)blocks->cont)->infile) -2;
		if (((t_exec *)blocks->cont)->pipe_to_read_from >= 0)
			((t_exec *)blocks->cont)->pipe_to_read_from \
				= close(((t_exec *)blocks->cont)->pipe_to_read_from) -2;
		if (((t_exec *)blocks->cont)->pipe_to_write_to >= 0)
			((t_exec *)blocks->cont)->pipe_to_write_to \
				= close(((t_exec *)blocks->cont)->pipe_to_write_to) -2;
		blocks = blocks->next;
	}
}

void	ft_free_lists(t_dlist *blocks, t_env *env, char **tab)
{
	while (blocks && blocks->prev)
		blocks = blocks->prev;
	ft_lstclear_msh(&blocks, &ft_del_blocks);
	while (env && env->prev)
		env = env->prev;
	ft_lstclear_env(&env, &free);
	free_tab(tab);
}
