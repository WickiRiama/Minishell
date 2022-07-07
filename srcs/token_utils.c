/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:38:12 by mriant            #+#    #+#             */
/*   Updated: 2022/07/07 12:15:46 by mriant           ###   ########.fr       */
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

t_dlist	*ft_trim_empty_token(t_dlist *tokens)
{
	t_dlist	*temp;
	t_dlist	*last;

	last = NULL;
	while (tokens)
	{
		if (((t_token *)tokens->cont)->text[0] == '\0')
		{
			temp = tokens;
			tokens = tokens->next;
			ft_lstdelone_msh(temp, &ft_del_token);
		}
		else
		{
			last = tokens;
			tokens = tokens->next;
		}
	}
	while (last->prev)
		last = last->prev;
	return (last);
}

t_token	*ft_init_token(t_ui start, t_ui i, char *input)
{
	t_token	*token;

	token = malloc(sizeof(t_token) * 1);
	if (!token)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		return (NULL);
	}
	token->text = ft_substr(input, start, i - start);
	if (!token->text)
	{
		ft_fprintf(2, "System error. Malloc failed.\n");
		free(token);
		return (NULL);
	}
	if (token->text[0] == '<' || token->text[0] == '>' || token->text[0] == '|')
		token->type = OPERATOR;
	else
		token->type = WORD;
	return (token);
}

void	ft_del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->text);
}

int	ft_add_token(t_dlist **tokens, t_ui start, t_ui i, char *input)
{
	t_token	*token;
	t_dlist	*new;

	token = ft_init_token(start, i, input);
	if (!token)
	{
		ft_lstclear_msh(tokens, &ft_del_token);
		return (1);
	}
	new = ft_lstnew_msh(token);
	if (!new)
	{
		ft_lstclear_msh(tokens, &ft_del_token);
		return (1);
	}
	ft_lstadd_back_msh(tokens, new);
	return (0);
}
