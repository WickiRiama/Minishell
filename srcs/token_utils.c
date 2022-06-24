/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:38:12 by mriant            #+#    #+#             */
/*   Updated: 2022/06/24 08:42:43 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

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
		{	temp = tokens;
			tokens = tokens->next;
			ft_lstdelone_msh(temp, &free);
		}
		else
			tokens = tokens->next;
	}
}