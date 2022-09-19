/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <mriant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:52:28 by mriant            #+#    #+#             */
/*   Updated: 2022/09/16 11:56:19 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

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

void	ft_lstinsert_msh(t_dlist *lst, t_dlist *new)
{
	if (!lst || !new)
	{
		ft_fprintf(2, "Error, the list or the new element is empty\n");
		return ;
	}
	new->next = lst->next;
	new->prev = lst;
	new->prev->next = new;
	if (new->next)
		new->next->prev = new;
}
