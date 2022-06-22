/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:11:49 by mriant            #+#    #+#             */
/*   Updated: 2022/06/22 12:24:22 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

t_token	*ft_tokenisation(char *input)
{
	unsigned int	i;
	int				squoted;
	int				dquoted;
	int				operator;
	unsigned int	start;
	char			*token;
	t_token			*tokens;

	i = 0;
	squoted = 0;
	dquoted = 0;
	start = 0;
	operator = 0;
	tokens = NULL;
	if (!input || input[0] == '\0')
		return (NULL);
	while(input[i])
	{
		if (operator == 1 && ft_isquoted(squoted, dquoted) == 0 && input[i] != '<' && input[i] != '>')
		{
			token = ft_substr(input, start, i - start);
			ft_lstadd_back_msh(&tokens, ft_lstnew_msh("operator", token));
			operator = 0;
			start = i;
		}
		else if (input[i] == '\'')
		{
			if (ft_isquoted(squoted, dquoted) == 0)
				squoted = 1;
			else if (squoted == 1)
				squoted = 0;
		}
		else if (input[i] == '"')
		{
			if (ft_isquoted(squoted, dquoted) == 0)
				dquoted = 1;
			else if (dquoted == 1)
				dquoted = 0;
		}
		else if (squoted == 0 && input[i] == '$')
		{	// mark parameter expamsion
			i += 0;
		}
		else if (ft_isquoted(squoted, dquoted) == 0 && operator == 0 && (input[i] == '<' || input[i] == '>'))
		{
			token = ft_substr(input, start, i - start);
			if (token && token[0])
				ft_lstadd_back_msh(&tokens, ft_lstnew_msh("undefined", token));
			start = i;
			operator = 1;
		}
		else if (ft_isquoted(squoted, dquoted) == 0 && input[i] == ' ')
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
	if (ft_isquoted(squoted, dquoted) == 1)
	{
		ft_fprintf(2, "Error. There is an unclosed quote.\n");
		return (NULL);
	}
	token = ft_substr(input, start, i - start);
	ft_lstadd_back_msh(&tokens, ft_lstnew_msh("undefined", token));
	return (tokens);
}