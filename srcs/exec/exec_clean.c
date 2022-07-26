/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:41:51 by mriant            #+#    #+#             */
/*   Updated: 2022/07/25 15:55:30 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "minishell.h"

void	ft_close_fd_parent(t_dlist *blocks, t_dlist *pipes)
{
	if (blocks)
	{
		if (((t_exec *)blocks->cont)->outfile != -2)
			((t_exec *)blocks->cont)->outfile \
				= close(((t_exec *)blocks->cont)->outfile) -2;
		if (((t_exec *)blocks->cont)->infile != -2)
			((t_exec *)blocks->cont)->infile \
				= close(((t_exec *)blocks->cont)->infile) -2;
	}
	if (pipes)
	{
		if (((t_pipe *)pipes->cont)->pipe_to_read_from != -2)
			((t_pipe *)pipes->cont)->pipe_to_read_from \
				= close(((t_pipe *)pipes->cont)->pipe_to_read_from) -2;
		if (((t_pipe *)pipes->cont)->pipe_to_write_to != -2)
			((t_pipe *)pipes->cont)->pipe_to_write_to \
				= close(((t_pipe *)pipes->cont)->pipe_to_write_to) -2;
	}
}

void	ft_close_fd_all(t_dlist *blocks, t_dlist *pipes)
{
	while (blocks && blocks->prev)
		blocks = blocks->prev;
	while (blocks)
	{
		if (((t_exec *)blocks->cont)->outfile != -2)
			((t_exec *)blocks->cont)->outfile \
				= close(((t_exec *)blocks->cont)->outfile) -2;
		if (((t_exec *)blocks->cont)->infile != -2)
			((t_exec *)blocks->cont)->infile \
				= close(((t_exec *)blocks->cont)->infile) -2;
		blocks = blocks->next;
	}
	while (pipes && pipes->prev)
		pipes = pipes->prev;
	while (pipes)
	{
		if (((t_pipe *)pipes->cont)->pipe_to_read_from != -2)
			((t_pipe *)pipes->cont)->pipe_to_read_from \
				= close(((t_pipe *)pipes->cont)->pipe_to_read_from) -2;
		if (((t_pipe *)pipes->cont)->pipe_to_write_to != -2)
			((t_pipe *)pipes->cont)->pipe_to_write_to \
				= close(((t_pipe *)pipes->cont)->pipe_to_write_to) -2;
		pipes = pipes->next;
	}
}

void	ft_free_lists(t_dlist *blocks, t_dlist *pipes, t_env *env, char **tab)
{
	while (blocks && blocks->prev)
		blocks = blocks->prev;
	ft_lstclear_msh(&blocks, &ft_del_blocks);
	while (pipes && pipes->prev)
		pipes = pipes->prev;
	ft_lstclear_msh(&pipes, &ft_del_pipes);
	while (env && env->prev)
		env = env->prev;
	ft_lstclear_env(&env, &free);
	free_tab(tab);
}
