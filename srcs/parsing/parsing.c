/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:39:25 by mriant            #+#    #+#             */
/*   Updated: 2022/08/12 14:28:48 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "minishell.h"
#include "libft.h"

int	ft_copy_tab(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (1);
		i++;
	}
	return (0);
}

t_dlist	*ft_cmd_orga(t_dlist *tokens, t_env **env)
{
	t_dlist	*blocks;

	blocks = NULL;
	while (tokens)
	{
		if (ft_add_block(tokens, &blocks, env) == 1)
		{
			ft_lstclear_msh(&blocks, &ft_del_blocks);
			return (NULL);
		}
		while (tokens && ((t_token *)tokens->cont)->type != PIPE)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	if (blocks)
	{
		if (ft_add_pipe(blocks) == 1)
		{
			ft_lstclear_msh(&blocks, &ft_del_blocks);
			return (NULL);
		}
	}
	return (blocks);
}

t_dlist	*ft_parsing1(t_dlist *tokens, t_sas *all_sa)
{
	char				*input;

	input = NULL;
	while (1)
	{
		ft_set_sa(&all_sa->new_sa, &all_sa->old_sigint, &all_sa->old_sigquit);
		free(input);
		input = readline("$> ");
		if (input && input[0] == '\0')
			continue ;
		tokens = ft_tokenisation(input);
		if (!tokens)
		{
			free(input);
			return (NULL);
		}
		add_history(input);
		if (ft_token_types(tokens))
		{
			ft_lstclear_msh(&tokens, ft_del_token);
			continue ;
		}
		free(input);
		return (tokens);
	}
}

t_dlist	*ft_parsing(t_env **env, t_sas *all_sa)
{
	t_dlist	*tokens;
	t_dlist	*blocks;

	ft_init_all_sas(all_sa);
	all_sa->new_sa.sa_handler = &ft_handle_sigint;
	tokens = NULL;
	tokens = ft_parsing1(tokens, all_sa);
	if (!tokens)
		return (NULL);
	if (ft_wexpanse(&tokens, env))
		return (NULL);
	blocks = ft_cmd_orga(tokens, env);
	ft_lstclear_msh(&tokens, ft_del_token);
	if (!blocks)
		return (NULL);
	return (blocks);
}
