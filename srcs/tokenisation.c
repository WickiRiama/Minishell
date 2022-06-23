/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:11:49 by mriant            #+#    #+#             */
/*   Updated: 2022/06/23 11:28:44 by mriant           ###   ########.fr       */
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

t_token	*ft_tokenisation(char *input)
{
	unsigned int	i;
	unsigned int	start;
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
			if (ft_add_token(&tokens, start, i, input) == 1)
				return (NULL);
			state.operator = 0;
			start = i + 1;
		}
		else if (input[i] == '\'' || input[i] == '"')
			ft_isquoted(input[i], &state);
		else if (state.squoted + state.dquoted == 0 && state.operator == 0 && (input[i] == '<' || input[i] == '>'))
		{
			if (ft_add_token(&tokens, start, i, input) == 1)
				return (NULL);
			start = i;
			state.operator = 1;
		}
		else if (state.squoted + state.dquoted == 0 && input[i] == ' ')
		{
			if (ft_add_token(&tokens, start, i, input) == 1)
				return (NULL);
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
	if (state.operator == 1)
	{
		ft_lstclear_msh(&tokens, &free);
		ft_fprintf(2, "Syntax error near unexpected token `newline'\n");
		return (NULL);
	}
	if (ft_add_token(&tokens, start, i, input) == 1)
		return (NULL);
	ft_trim_empty_token(tokens);
	return (tokens);
}