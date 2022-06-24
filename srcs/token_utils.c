/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:38:12 by mriant            #+#    #+#             */
/*   Updated: 2022/06/24 09:25:19 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

void	ft_init_state(t_state *state)
{
	state->dquoted = 0;
	state->squoted = 0;
	state->i = 0;
	state->start = 0;
}

void	ft_trim_empty_token(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		if (tokens->token[0] == '\0')
		{
			temp = tokens;
			tokens = tokens->next;
			ft_lstdelone_msh(temp, &free);
		}
		else
			tokens = tokens->next;
	}
}

int	ft_add_token(t_token **tokens, t_ui start, t_ui i, char *input)
{
	char	*token;
	t_token	*new;

	token = ft_substr(input, start, i - start);
	if (!token)
	{
		ft_lstclear_msh(tokens, &free);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	if (token[0] == '<' || token[0] == '>' || token[0] == '|')
		new = ft_lstnew_msh("operator", token);
	else
		new = ft_lstnew_msh("word", token);
	if (!new)
		return (1);
	ft_lstadd_back_msh(tokens, new);
	return (0);
}

int	ft_cut_operator(t_token **tokens, t_state *state, char *input)
{
	char	c;

	c = input[state->i];
	if (ft_add_token(tokens, state->start, state->i, input) == 1)
	{
		ft_lstclear_msh(tokens, &free);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	state->start = state->i;
	if ((c == '<' || c == '>') && c == input[state->i + 1])
		state->i++;
	if (ft_add_token(tokens, state->start, state->i + 1, input) == 1)
	{
		ft_lstclear_msh(tokens, &free);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	state->start = state->i + 1;
	return (0);
}

int	ft_cut_blank(t_token **tokens, t_state *state, char *input)
{
	if (ft_add_token(tokens, state->start, state->i, input) == 1)
	{
		ft_lstclear_msh(tokens, &free);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	while (input[state->i + 1] == ' ')
		state->i++;
	state->start = state->i + 1;
	return (0);
}
