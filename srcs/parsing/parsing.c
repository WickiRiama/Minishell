/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:39:25 by mriant            #+#    #+#             */
/*   Updated: 2022/09/12 12:02:08 by mriant           ###   ########.fr       */
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

t_dlist	*ft_parsing1(t_dlist *tokens, t_sig *new_sa)
{
	char				*input;

	input = NULL;
	while (1)
	{
		ft_set_sa(new_sa, &ft_handle_sig);
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

t_dlist	*ft_parsing(t_env **env, t_sig *new_sa)
{
	t_dlist	*tokens;
	t_dlist	*blocks;

	tokens = NULL;
	tokens = ft_parsing1(tokens, new_sa);
	if (!tokens)
		return (NULL);
	if (ft_wexpanse(&tokens, env))
		return (NULL);
	blocks = ft_cmd_orga(tokens, env, new_sa);
	ft_lstclear_msh(&tokens, ft_del_token);
	if (!blocks)
		return (NULL);
	return (blocks);
}
