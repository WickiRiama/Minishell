/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriant <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:21:39 by mriant            #+#    #+#             */
/*   Updated: 2021/12/10 11:22:01 by mriant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*temp;

	newlist = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		temp = ft_lstnew(lst->content);
		if (!temp)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		temp->content = f(temp->content);
		ft_lstadd_back(&newlist, temp);
		lst = lst->next;
	}
	return (newlist);
}
