/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:50:04 by mriant            #+#    #+#             */
/*   Updated: 2022/07/04 15:50:38 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_isquoted(char c, t_state *state)
{
	if (c == '\'')
	{
		if (state->squoted + state->dquoted == 0)
			state->squoted = 1;
		else if (state->squoted == 1)
			state->squoted = 0;
	}
	else
	{
		if (state->squoted + state->dquoted == 0)
			state->dquoted = 1;
		else if (state->dquoted == 1)
			state->dquoted = 0;
	}
}

int	ft_is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}
