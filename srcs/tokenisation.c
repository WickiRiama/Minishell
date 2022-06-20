/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:11:49 by mriant            #+#    #+#             */
/*   Updated: 2022/06/20 18:25:31 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

t_token	*ft_tokenisation(char *input)
{
	unsigned int	i;
	int				quoted;
	int				operator;
	unsigned int	start;
	char			*token;
	t_token			*tokens;

	i = 0;
	quoted = 0;
	start = 0;
	operator = 0;
	tokens = NULL;
	if (!input || input[0] == '\0')
		return (NULL);
	while(input[i])
	{
		if (operator == 1 && quoted == 0 && input[i] != '<' && input[i] != '>')
		{
			token = ft_substr(input, start, i - start);
			ft_lstadd_back_msh(&tokens, ft_lstnew_msh("operator", token));
			operator = 0;
			start = i;
		}
		else if (input[i] == '\'' || input[i] == '"')
		{
			if (quoted == 0)
				quoted = 1;
			else
				quoted = 0;
		}
		else if (quoted == 0 && input[i] == '$')
		{	// mark parameter expamsion
			i += 0;
		}
		else if (quoted == 0 && operator == 0 && (input[i] == '<' || input[i] == '>'))
		{
			token = ft_substr(input, start, i - start);
			ft_lstadd_back_msh(&tokens, ft_lstnew_msh("undefined", token));
			start = i;
			operator = 1;
		}
		else if (quoted == 0 && input[i] == ' ')
		{
			token = ft_substr(input, start, i - start);
			ft_lstadd_back_msh(&tokens, ft_lstnew_msh("undefined", token));
			while (input[i + 1] == ' ')
				i++;
			start = i + 1;
		}
		i++;
	}
	token = ft_substr(input, start, i - start);
	ft_lstadd_back_msh(&tokens, ft_lstnew_msh("undefined", token));
	return (tokens);
}