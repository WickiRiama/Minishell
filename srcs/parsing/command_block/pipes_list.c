/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:46:19 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 16:03:59 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>

#include "minishell.h"
#include "libft.h"

int	ft_init_pipe(t_dlist *blocks)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
	{
		ft_fprintf(2, "%s: %s\n", strerror(errno), "Pipe error\n");
		return (1);
	}
	((t_exec *)blocks->next->cont)->pipe_to_read_from = fd_pipe[0];
	((t_exec *)blocks->cont)->pipe_to_write_to = fd_pipe[1];
	return (0);
}

int	ft_add_pipe(t_dlist *blocks)
{
	while (blocks && blocks->next)
	{
		if (ft_init_pipe(blocks) == 1)
			return (1);
		blocks = blocks->next;
	}
	return (0);
}
