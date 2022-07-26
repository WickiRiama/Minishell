/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:30:22 by mriant            #+#    #+#             */
/*   Updated: 2022/07/12 16:28:15 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

int	ft_fill_block(t_dlist *tokens, t_exec *new_block)
{
	if (((t_token *)tokens->cont)->type == WORD)
	{
		new_block->cmd = ft_update_cmd(new_block->cmd, \
			((t_token *)tokens->cont)->text);
		if (!new_block->cmd)
			return (1);
	}
	else if (((t_token *)tokens->cont)->type == INFILE
		|| ((t_token *)tokens->cont)->type == OUTFILE
		|| ((t_token *)tokens->cont)->type == APP_FILE)
	{
		ft_open_redir(tokens, new_block);
	}
	return (0);
}

t_exec	*ft_init_block(t_dlist *tokens)
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
	while (tokens && ((t_token *)tokens->cont)->type != PIPE)
	{
		if (ft_fill_block(tokens, block) == 1)
		{
			ft_del_blocks((void *)block);
			ft_fprintf(2, "System error. Malloc failed.\n");
			return (NULL);
		}
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
	free(content);
}

int	ft_add_block(t_dlist *tokens, t_dlist **blocks)
{
	t_exec	*block_struct;
	t_dlist	*new_block;

	block_struct = ft_init_block(tokens);
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
	return (0);
}

char	**ft_update_cmd(char **cmd, char *new)
{
	char	**result;
	int		size;

	size = 0;
	while (cmd && cmd[size])
		size++;
	result = malloc(sizeof(char *) * (size + 2));
	if (!result || ft_copy_tab(result, cmd) == 1)
	{
		free_tab(cmd);
		free(result);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (NULL);
	}
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
