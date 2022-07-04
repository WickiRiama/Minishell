/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:58:33 by mriant            #+#    #+#             */
/*   Updated: 2022/07/04 13:19:28 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_lstadd_back_msh(t_token **alst, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!(*alst))
		*alst = new;
	else
	{
		last = ft_lstlast_msh(*alst);
		last->next = new;
		new->prev = last;
	}
}

void	ft_lstadd_front_msh(t_token **alst, t_token *new)
{
	new->next = *alst;
	(*alst)->prev = new;
	*alst = new;
}

t_token	*ft_lstnew_msh(t_types type, char *token)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->token = token;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
