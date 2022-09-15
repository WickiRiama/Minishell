/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:22:34 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 16:03:22 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_dlist	*ft_cmd_orga(t_dlist *tokens, t_env **env, t_sig *new_sa)
{
	t_dlist	*blocks;
	int		ret;

	blocks = NULL;
	while (tokens)
	{
		ret = ft_add_block(tokens, &blocks, env, new_sa);
		if (ret == 1)
		{
			ft_lstclear_msh(&blocks, &ft_del_blocks);
			return (NULL);
		}
		if (ret == 2)
			return (blocks);
		while (tokens && ((t_token *)tokens->cont)->type != PIPE)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	if (ft_add_pipe(blocks) == 1)
	{
		ft_lstclear_msh(&blocks, &ft_del_blocks);
		return (NULL);
	}
	return (blocks);
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
