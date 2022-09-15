/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:11:49 by mriant            #+#    #+#             */
/*   Updated: 2022/09/15 16:07:40 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_cut_operator(t_dlist **tokens, t_state *state, char *input)
{
	char	c;

	c = input[state->i];
	if (ft_add_token(tokens, state->start, state->i, input) == 1)
	{
		ft_lstclear_msh(tokens, &ft_del_token);
		return (1);
	}
	state->start = state->i;
	if ((c == '<' || c == '>') && c == input[state->i + 1])
		state->i++;
	if (ft_add_token(tokens, state->start, state->i + 1, input) == 1)
	{
		ft_lstclear_msh(tokens, &ft_del_token);
		return (1);
	}
	state->start = state->i + 1;
	return (0);
}

int	ft_cut_blank(t_dlist **tokens, t_state *state, char *input)
{
	if (ft_add_token(tokens, state->start, state->i, input) == 1)
	{
		ft_lstclear_msh(tokens, &ft_del_token);
		return (1);
	}
	while (input[state->i + 1] == ' ')
		state->i++;
	state->start = state->i + 1;
	return (0);
}

int	ft_token_list(t_dlist **tokens, t_state *state, char *input)
{
	while (input[state->i])
	{
		if (state->squoted + state->dquoted == 0
			&& ft_is_operator(input[state->i]))
		{
			if (ft_cut_operator(tokens, state, input) == 1)
				return (1);
		}
		else if (input[state->i] == '\'' || input[state->i] == '"')
			ft_isquoted(input[state->i], state);
		else if (state->squoted + state->dquoted == 0
			&& ft_is_blank(input[state->i]))
		{
			if (ft_cut_blank(tokens, state, input))
				return (1);
		}
		state->i++;
	}
	if (ft_add_token(tokens, state->start, state->i, input) == 1)
	{
		ft_lstclear_msh(tokens, &ft_del_token);
		return (1);
	}
	return (0);
}

void	ft_check_token(t_dlist **tokens, t_state *state)
{
	if (state->squoted == 1)
	{
		ft_fprintf(2, "Syntax error: unclosed quote '''.\n");
		((t_token *)(*tokens)->cont)->type = QUOTE_ERR;
		g_exitcode = 2;
	}
	else if (state->dquoted == 1)
	{
		ft_fprintf(2, "Syntax error: unclosed quote '\"'.\n");
		((t_token *)(*tokens)->cont)->type = QUOTE_ERR;
		g_exitcode = 2;
	}
	else
		*tokens = ft_trim_empty_token(*tokens);
}

t_dlist	*ft_tokenisation(char *input)
{
	t_dlist	*tokens;
	t_state	state;

	ft_init_state(&state);
	tokens = NULL;
	if (!input || input[0] == '\0')
		return (NULL);
	if (ft_token_list(&tokens, &state, input))
		return (NULL);
	ft_check_token(&tokens, &state);
	return (tokens);
}
