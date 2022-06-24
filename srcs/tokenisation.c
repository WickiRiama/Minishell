/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:11:49 by mriant            #+#    #+#             */
/*   Updated: 2022/06/24 08:55:30 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int	ft_add_token(t_token **tokens, unsigned int start, unsigned int i, char *input)
{
	char	*token;
	
	token = ft_substr(input, start, i - start);
	if (!token)
	{
		ft_lstclear_msh(tokens, &free);
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (1);
	}
	if (token[0] == '<' || token[0] == '>' || token[0] == '|')
		ft_lstadd_back_msh(tokens, ft_lstnew_msh("operator", token));
	else
		ft_lstadd_back_msh(tokens, ft_lstnew_msh("word", token));
	return (0);
}

int	ft_is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_cut_operator(t_token **tokens, t_state *state, char *input)
{
	char	c;

	c = input[state->i];
	if (ft_add_token(tokens, state->start, state->i, input) == 1)
		return (1);
	state->start = state->i;
	if ((c == '<' || c == '>') && c == input[state->i + 1])
		state->i++;
	if (ft_add_token(tokens, state->start, state->i + 1, input) == 1)

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
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

t_token	*ft_tokenisation(char *input)
{
	t_token			*tokens;
	t_state			state;

	ft_init_state(&state);
	tokens = NULL;
	if (!input || input[0] == '\0')
		return (NULL);
	while(input[state.i])
	{
		if (state.squoted + state.dquoted == 0 && ft_is_operator(input[state.i]))
		{
			if (ft_cut_operator(&tokens, &state, input) == 1)
				return (NULL);
		}
		else if (input[state.i] == '\'' || input[state.i] == '"')
			ft_isquoted(input[state.i], &state);
		else if (state.squoted + state.dquoted == 0 && input[state.i] == ' ')
		else if (state.squoted + state.dquoted == 0
			&& ft_is_blank(input[state.i]))
		{
			if (ft_cut_blank(&tokens, &state, input))
				return (NULL);
		}
		state.i++;
	}
	if (state.squoted + state.dquoted == 1)
	{
		ft_lstclear_msh(&tokens, &free);
		ft_fprintf(2, "Syntax error. There is an unclosed quote.\n");
		return (NULL);
	}
	if (ft_add_token(&tokens, state.start, state.i, input) == 1)
		return (NULL);
	ft_trim_empty_token(tokens);
	return (tokens);
}