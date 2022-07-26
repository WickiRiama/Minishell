/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:52:28 by mriant            #+#    #+#             */
/*   Updated: 2022/07/25 13:52:31 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"

void	ft_lstadd_back_msh(t_dlist **alst, t_dlist *new)
{
	t_dlist	*last;

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

void	ft_lstadd_front_msh(t_dlist **alst, t_dlist *new)
{
	new->next = *alst;
	(*alst)->prev = new;
	*alst = new;
}

t_dlist	*ft_lstnew_msh(void *content)
{
	t_dlist	*new;

	new = malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->cont = content;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
