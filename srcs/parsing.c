/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:39:25 by mriant            #+#    #+#             */
/*   Updated: 2022/07/11 16:41:03 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "minishell.h"
#include "libft.h"

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
	free_tab(block->cmd);
	if (block->infile >= 0)
		block->infile = close(block->infile) - 2;
	if (block->outfile >= 0)
		block->outfile = close(block->outfile) - 2;
	free(content);
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

int	ft_copy_tab(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			free_tab(dest);
			free_tab(src);
			ft_fprintf(2, "System error. Malloc failed.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

char **ft_update_cmd(char **cmd, char *new)
{
	char	**result;
	int		size;

	size = 0;
	result = NULL;
	while (cmd && cmd[size])
		size++;
	result = malloc(sizeof(char *) * (size + 2));
	if (!result)
	{
		free_tab(cmd);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (NULL);
	}
	if (ft_copy_tab(result, cmd) == 1)
		return (NULL);
	result[size] = ft_strdup(new);
	if (!result[size])
	{
		free_tab(result);
		free_tab(cmd);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (NULL);
	}
	result[size + 1] = NULL;
	free_tab(cmd);
	return (result);
}

void	ft_open_redir(t_dlist *tokens, t_exec *blocks)
{
	if (((t_token *)tokens->cont)->type == INFILE)
	{
		blocks->infile = open(((t_token *)tokens->cont)->text, O_RDONLY);
		if (blocks->infile == -1)
			ft_fprintf(2, "%s: %s\n", strerror(errno), ((t_token *)tokens->cont)->text);
	}
	else if (((t_token *)tokens->cont)->type == OUTFILE)
	{
		blocks->outfile = open(((t_token *)tokens->cont)->text, O_WRONLY | O_CREAT | O_TRUNC, 00644);
		if (blocks->outfile == -1)
			ft_fprintf(2, "%s: %s\n", strerror(errno), ((t_token *)tokens->cont)->text);
	}
	else if (((t_token *)tokens->cont)->type == APP_FILE)
	{
		blocks->outfile = open(((t_token *)tokens->cont)->text, O_WRONLY | O_CREAT | O_APPEND, 00644);
		if (blocks->outfile == -1)
			ft_fprintf(2, "%s: %s\n", strerror(errno), ((t_token *)tokens->cont)->text);
	}
}

t_dlist	*ft_cmd_orga(t_dlist *tokens, t_dlist **pipes)
{
	t_dlist	*blocks;
	t_dlist	*new;
	t_exec	*new_block;
	t_pipe	*pipe_struct;
	t_dlist	*new_pipe;
	int		fd_pipe[2];

	blocks = NULL;
	while (tokens)
	{
		new_block = ft_init_block();
		if (!new_block)
		{
			ft_lstclear_msh(&blocks, &ft_del_blocks);
			ft_lstclear_msh(pipes, &ft_del_pipes);
			return (NULL);
		}
		while (tokens && ((t_token *)tokens->cont)->type != PIPE)
		{
			if (((t_token *)tokens->cont)->type == WORD)
			{
				new_block->cmd = ft_update_cmd(new_block->cmd, ((t_token *)tokens->cont)->text);
				if (!new_block->cmd)
				{
					ft_lstclear_msh(&blocks, &ft_del_blocks);
					ft_del_blocks((void *)new_block);
					ft_lstclear_msh(pipes, &ft_del_pipes);
					return (NULL);
				}
			}
			else if (((t_token *)tokens->cont)->type == INFILE
				|| ((t_token *)tokens->cont)->type == OUTFILE
				|| ((t_token *)tokens->cont)->type == APP_FILE)
			{
				ft_open_redir(tokens, new_block);
			}
			tokens = tokens->next;
		}
		new = ft_lstnew_msh((void *)new_block);
		if (!new)
		{
			ft_fprintf(2, "System error. Malloc failed.\n");
			ft_lstclear_msh(&blocks, &ft_del_blocks);
			ft_lstclear_msh(pipes, &ft_del_pipes);
			ft_del_blocks((void *)new_block);
			return (NULL);
		}
		ft_lstadd_back_msh(&blocks, new);
		if (tokens)
		{
			if (pipe(fd_pipe) == -1)
			{
				ft_fprintf(2, "%s: %s\n", strerror(errno), "Pipe error\n");
				ft_lstclear_msh(&blocks, &ft_del_blocks);
				ft_lstclear_msh(pipes, &ft_del_pipes);
				return (NULL);
			}
			pipe_struct = malloc(sizeof(t_pipe) * 1);
			if (!pipe_struct)
			{
				ft_fprintf(2, "%s: %s\n", strerror(errno), "Pipe error\n");
				ft_lstclear_msh(&blocks, &ft_del_blocks);
				ft_lstclear_msh(pipes, &ft_del_pipes);
				return (NULL);
			}
			pipe_struct->pipe_in = fd_pipe[1];
			pipe_struct->pipe_out = fd_pipe[0];
			new_pipe = ft_lstnew_msh((void *)pipe_struct);
			if (!new_pipe)
			{
				ft_fprintf(2, "%s: %s\n", strerror(errno), "Pipe error\n");
				ft_lstclear_msh(&blocks, &ft_del_blocks);
				ft_lstclear_msh(pipes, &ft_del_pipes);
				return (NULL);
			}
			ft_lstadd_back_msh(pipes, new_pipe);
			tokens = tokens->next;
		}
	}
	return (blocks);
}
