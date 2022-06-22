/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:11:49 by mriant            #+#    #+#             */
/*   Updated: 2022/06/22 16:36:13 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

t_token	*ft_tokenisation(char *input)
{
	unsigned int	i;
	unsigned int	start;
	char			*token;
	t_token			*tokens;
	t_state			state;

	i = 0;
	start = 0;
	ft_init_state(&state);
	tokens = NULL;
	if (!input || input[0] == '\0')
		return (NULL);
	while(input[i])
	{
		// Reconnaissance si precedent < et deuxieme >
		if (state.operator == 1 && state.squoted + state.dquoted == 0 && input[i] != '<' && input[i] != '>')
		{
			token = ft_substr(input, start, i - start);
			if (token)
				ft_lstadd_back_msh(&tokens, ft_lstnew_msh("operator", token));
			state.operator = 0;
			start = i + 1;
		}
		else if (input[i] == '\'' || input[i] == '"')
			ft_isquoted(input[i], &state);
		else if (state.squoted + state.dquoted == 0 && state.operator == 0 && (input[i] == '<' || input[i] == '>'))
		{
			token = ft_substr(input, start, i - start);
			if (token)
				ft_lstadd_back_msh(&tokens, ft_lstnew_msh("undefined", token));
			start = i;
			state.operator = 1;
		}
		else if (state.squoted + state.dquoted == 0 && input[i] == ' ')
		{
			token = ft_substr(input, start, i - start);
			if (token)
				ft_lstadd_back_msh(&tokens, ft_lstnew_msh("undefined", token));
			while (input[i + 1] == ' ')
				i++;
			start = i + 1;
		}
		i++;
	}
	if (state.squoted + state.dquoted == 1)
	{
		ft_lstclear_msh(&tokens, &free);
		ft_fprintf(2, "Syntax error. There is an unclosed quote.\n");
		return (NULL);
	}
	token = ft_substr(input, start, i - start);
	ft_lstadd_back_msh(&tokens, ft_lstnew_msh("undefined", token));
	ft_trim_empty_token(tokens);
	return (tokens);
}