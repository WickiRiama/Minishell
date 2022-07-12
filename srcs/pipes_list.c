/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:46:19 by mriant            #+#    #+#             */
/*   Updated: 2022/07/12 16:39:15 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "minishell.h"
#include "libft.h"

t_pipe	*ft_init_pipe(void)
{
	int		fd_pipe[2];
	t_pipe	*pipe_struct;

	if (pipe(fd_pipe) == -1)
	{
		ft_fprintf(2, "%s: %s\n", strerror(errno), "Pipe error\n");
		return (NULL);
	}
	pipe_struct = malloc(sizeof(t_pipe) * 1);
	if (!pipe_struct)
	{
		ft_fprintf(2, "%s: %s\n", strerror(errno), "Pipe error\n");
		return (NULL);
	}
	pipe_struct->pipe_in = fd_pipe[1];
	pipe_struct->pipe_out = fd_pipe[0];
	return (pipe_struct);
}

void	ft_del_pipes(void *content)
{
	t_pipe	*pipes;

	pipes = (t_pipe *)content;
	if (pipes->pipe_in >= 0)
		pipes->pipe_in = close(pipes->pipe_in) - 2;
	if (pipes->pipe_out >= 0)
		pipes->pipe_out = close(pipes->pipe_out) - 2;
	free(content);
}

int	ft_add_pipe(t_dlist **pipes)
{
	t_pipe	*pipe_struct;
	t_dlist	*new_pipe;

	pipe_struct = ft_init_pipe();
	if (!pipe_struct)
		return (1);
	new_pipe = ft_lstnew_msh((void *)pipe_struct);
	if (!new_pipe)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		ft_del_pipes((void *)pipe_struct);
		return (1);
	}
	ft_lstadd_back_msh(pipes, new_pipe);
	return (0);
}

void	ft_open_redir(t_dlist *tokens, t_exec *blocks)
{
	if (((t_token *)tokens->cont)->type == INFILE)
	{
		blocks->infile = open(((t_token *)tokens->cont)->text, O_RDONLY);
		if (blocks->infile == -1)
			ft_fprintf(2, "%s: %s\n", \
				strerror(errno), ((t_token *)tokens->cont)->text);
	}
	else if (((t_token *)tokens->cont)->type == OUTFILE)
	{
		blocks->outfile = open(((t_token *)tokens->cont)->text, \
			O_WRONLY | O_CREAT | O_TRUNC, 00644);
		if (blocks->outfile == -1)
			ft_fprintf(2, "%s: %s\n", \
				strerror(errno), ((t_token *)tokens->cont)->text);
	}
	else if (((t_token *)tokens->cont)->type == APP_FILE)
	{
		blocks->outfile = open(((t_token *)tokens->cont)->text, \
			O_WRONLY | O_CREAT | O_APPEND, 00644);
		if (blocks->outfile == -1)
			ft_fprintf(2, "%s: %s\n", \
				strerror(errno), ((t_token *)tokens->cont)->text);
	}
}
