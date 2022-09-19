/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:09:53 by mriant            #+#    #+#             */
/*   Updated: 2022/09/19 14:04:36 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_add_splitted(t_token *content, t_state *state, t_dlist *token)
{
	t_token	*new_token;
	t_dlist	*new_link;

	while (ft_is_blank(content->text[state->i + 1]))
		state->i++;
	if (content->text[state->i + 1])
	{
		new_token = ft_init_token(0, ft_strlen(content->text + state->i + 1),
				content->text + state->i + 1);
		if (!new_token)
			return (1);
		new_link = ft_lstnew_msh(new_token);
		if (!new_link)
		{
			ft_del_token(new_token);
			return (1);
		}
		((t_token *)new_link->cont)->type = WORD;
		ft_lstinsert_msh(token, new_link);
		if (ft_split_token(token->next) == 1)
			return (1);
	}
	return (0);
}

int	ft_split_token(t_dlist *token)
{
	t_state	state;
	t_token	*content;

	if (!token)
		return (0);
	ft_init_state(&state);
	content = (t_token *)token->cont;
	while (content->text[state.i])
	{
		if (content->text[state.i] == '"' || content->text[state.i] == '\'')
			ft_isquoted(content->text[state.i], &state);
		else if (ft_is_blank(content->text[state.i])
			&& state.dquoted + state.squoted == 0)
		{
			content->text[state.i] = '\0';
			if (ft_add_splitted(content, &state, token) == 1)
				return (1);
		}
		state.i++;
	}
	return (0);
}
