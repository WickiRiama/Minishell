/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:30:22 by mriant            #+#    #+#             */
/*   Updated: 2022/09/12 12:06:34 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

int	ft_fill_block(t_dlist *tokens, t_exec *new_block, t_env **env,
	t_sig *new_sa)
{
	if (((t_token *)tokens->cont)->type == WORD)
	{
		new_block->cmd = ft_update_cmd(new_block->cmd, \
			((t_token *)tokens->cont)->text);
		if (!new_block->cmd)
			return (1);
	}
	else if ((((t_token *)tokens->cont)->type == INFILE
			|| ((t_token *)tokens->cont)->type == OUTFILE
			|| ((t_token *)tokens->cont)->type == APP_FILE
			|| ((t_token *)tokens->cont)->type == DELIM)
		&& new_block->infile != -1)
	{
		ft_close_old_redir(tokens, new_block);
		ft_open_redir(tokens, new_block, env, new_sa);
		if (new_block->infile == -1)
			new_block->outfile = -1;
		else if (new_block->outfile == -1)
			new_block->infile = -1;
		else if (new_block->outfile == -130 || new_block->outfile == -131)
			return (2);
	}
	return (0);
}

void	ft_init_block(t_exec *block)
{
	block->cmd = NULL;
	block->infile = -2;
	block->outfile = -2;
	block->pipe_to_read_from = -2;
	block->pipe_to_write_to = -2;
}

t_exec	*ft_create_block(t_dlist *tokens, t_env **env, t_sig *new_sa)
{
	t_exec	*block;
	int		ret;

	block = malloc(sizeof(t_exec) * 1);
	if (!block)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (NULL);
	}
	ft_init_block(block);
	while (tokens && ((t_token *)tokens->cont)->type != PIPE)
	{
		ret = ft_fill_block(tokens, block, env, new_sa);
		if (ret == 1)
		{
			ft_del_blocks((void *)block);
			ft_fprintf(2, "System error. Malloc failed.\n");
			return (NULL);
		}
		if (ret == 2)
			break ;
		tokens = tokens->next;
	}
	return (block);
}

void	ft_del_blocks(void *content)
{
	t_exec	*block;

	block = (t_exec *)content;
	free_tab(block->cmd);
	if (block->infile >= 0)
		block->infile = close(block->infile) - 2;
	if (block->outfile >= 0)
		block->outfile = close(block->outfile) - 2;
	if (block->pipe_to_read_from >= 0)
		block->pipe_to_read_from = close(block->pipe_to_read_from) - 2;
	if (block->pipe_to_write_to >= 0)
		block->pipe_to_write_to = close(block->pipe_to_write_to) - 2;
	free(content);
}

int	ft_add_block(t_dlist *tokens, t_dlist **blocks, t_env **env, t_sig *new_sa)
{
	t_exec	*block_struct;
	t_dlist	*new_block;

	block_struct = ft_create_block(tokens, env, new_sa);
	if (!block_struct)
		return (1);
	new_block = ft_lstnew_msh((void *)block_struct);
	if (!new_block)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		ft_del_blocks((void *)block_struct);
		return (1);
	}
	ft_lstadd_back_msh(blocks, new_block);
	if (block_struct->outfile == -131 || block_struct->outfile == -130)
		return (2);
	return (0);
}
