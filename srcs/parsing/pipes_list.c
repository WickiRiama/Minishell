/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:46:19 by mriant            #+#    #+#             */
/*   Updated: 2022/08/03 14:14:57 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "minishell.h"
#include "libft.h"

t_pipe	*ft_init_pipe(t_dlist **pipes)
{
	int		fd_pipe[2];
	t_pipe	*pipe_struct;
	t_dlist	*last;

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
	pipe_struct->pipe_to_read_from = fd_pipe[0];
	pipe_struct->pipe_to_write_to = -2;
	last = ft_lstlast_msh(*pipes);
	((t_pipe *)last->cont)->pipe_to_write_to = fd_pipe[1];
	return (pipe_struct);
}

void	ft_del_pipes(void *content)
{
	t_pipe	*pipes;

	pipes = (t_pipe *)content;
	if (pipes->pipe_to_read_from >= 0)
		pipes->pipe_to_read_from = close(pipes->pipe_to_read_from) - 2;
	if (pipes->pipe_to_write_to >= 0)
		pipes->pipe_to_write_to = close(pipes->pipe_to_write_to) - 2;
	free(content);
}

int	ft_add_first_pipe(t_dlist **pipes)
{
	t_pipe	*first_pipe;

	first_pipe = malloc(sizeof(t_pipe) * 1);
	if (!first_pipe)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	first_pipe->pipe_to_read_from = -2;
	first_pipe->pipe_to_write_to = -2;
	*pipes = ft_lstnew_msh((void *)first_pipe);
	if (!(*pipes))
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		ft_del_pipes(first_pipe);
		return (1);
	}
	return (0);
}

int	ft_add_pipe(t_dlist **pipes)
{
	t_pipe	*pipe_struct;
	t_dlist	*new_pipe;

	if (!(*pipes))
	{
		if (ft_add_first_pipe(pipes) == 1)
			return (1);
	}
	pipe_struct = ft_init_pipe(pipes);
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

void	ft_open_redir(t_dlist *tokens, t_exec *blocks, t_env **env)
{
	if (((t_token *)tokens->cont)->type == INFILE)
		blocks->infile = open(((t_token *)tokens->cont)->text, O_RDONLY);
	else if (((t_token *)tokens->cont)->type == OUTFILE)
		blocks->outfile = open(((t_token *)tokens->cont)->text, \
			O_WRONLY | O_CREAT | O_TRUNC, 00644);
	else if (((t_token *)tokens->cont)->type == APP_FILE)
		blocks->outfile = open(((t_token *)tokens->cont)->text, \
			O_WRONLY | O_CREAT | O_APPEND, 00644);
	else if (((t_token *)tokens->cont)->type == DELIM)
		blocks->infile = ft_here_doc(tokens, env);
	if (blocks->infile == -1 || blocks->outfile == -1)
		ft_fprintf(2, "%s: %s\n", \
			strerror(errno), ((t_token *)tokens->cont)->text);
}
